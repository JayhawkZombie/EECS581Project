#include "../../Headers/Engine/Editor.h"

namespace Engine
{

  Editor::Editor()
    //:
    //TileList(std::shared_ptr<UI::List>(new UI::List({ 800, 600 }, { 200, 400 }))),
    //LightList(std::shared_ptr<UI::List>(new UI::List({ 1000, 600 }, { 200, 400 }))),
    //ObjectList(std::shared_ptr<UI::List>(new UI::List({ 10, 500 }, { 200, 200 })))
  {
    EditorFont.loadFromFile("./SFEngine/Source/CoreFiles/Fonts/Raleway-Regular.ttf");
    EditorModeText.setFont(EditorFont);
    EditorModeText.setCharacterSize(8);
    EditorModeText.setFillColor(sf::Color::White);
    EditorModeText.setPosition({ 400, 10 });
    EditorModeText.setString("Editor : Mode <No Selection>");

    PreviewGridInfoText.setFont(EditorFont);
    PreviewGridInfoText.setCharacterSize(6);
    PreviewGridInfoText.setFillColor(sf::Color::White);
    PreviewGridInfoText.setPosition({ 10, 820 });
    PreviewGridInfoText.setString("Grid Cell: 40 x 40");

    //create the grid lines for the preview
    sf::Vector2f GridStart = { 0, 40 };
    sf::Vector2f GridCellSize = { 40.f, 40.f };
    sf::Vector2f Pos1, Pos2, Pos3, Pos4;

    for (std::size_t x = 0; x < 30; ++x) {
      for (std::size_t y = 0; y < 30; ++y) {
        Pos1 = { GridStart.x + GridCellSize.x * x, GridStart.y + GridCellSize.y * y };
        Pos2 = { Pos1.x + GridCellSize.x, Pos1.y };
        Pos3 = { Pos2.x, Pos2.y + GridCellSize.y };
        Pos4 = { Pos1.x, Pos3.y };

        PreviewGridLines.push_back(sf::VertexArray(sf::Lines, 2));
        PreviewGridLines.back()[0].position = Pos1; PreviewGridLines.back()[0].color = sf::Color(0, 246, 255, 100);
        PreviewGridLines.back()[1].position = Pos2; PreviewGridLines.back()[1].color = sf::Color(0, 246, 255, 100);

        PreviewGridLines.push_back(sf::VertexArray(sf::Lines, 2));
        PreviewGridLines.back()[0].position = Pos2; PreviewGridLines.back()[0].color = sf::Color(0, 246, 255, 100);
        PreviewGridLines.back()[1].position = Pos3; PreviewGridLines.back()[1].color = sf::Color(0, 246, 255, 100);

        PreviewGridLines.push_back(sf::VertexArray(sf::Lines, 2));
        PreviewGridLines.back()[0].position = Pos3; PreviewGridLines.back()[0].color = sf::Color(0, 246, 255, 100);
        PreviewGridLines.back()[1].position = Pos4; PreviewGridLines.back()[1].color = sf::Color(0, 246, 255, 100);

        PreviewGridLines.push_back(sf::VertexArray(sf::Lines, 2));
        PreviewGridLines.back()[0].position = Pos4; PreviewGridLines.back()[0].color = sf::Color(0, 246, 255, 100);
        PreviewGridLines.back()[1].position = Pos1; PreviewGridLines.back()[1].color = sf::Color(0, 246, 255, 100);
      }
    }


    PreviewTexture.create(EditorPreviewSize.x, EditorPreviewSize.y);
    PreviewTexture.clear(sf::Color::Transparent);

    PreviewShape.setPosition({ 0, 40 });
    PreviewShape.setTexture(&PreviewTexture.getTexture());
    PreviewShape.setSize({ (float)EditorPreviewSize.x, (float)EditorPreviewSize.y });

    PreviewShape.setFillColor(sf::Color::Transparent);
    PreviewShape.setOutlineColor(sf::Color::White);
    PreviewShape.setOutlineThickness(-2);

    PreviewSprite.setPosition({ 0, 0 });
    PreviewSprite.setTexture(PreviewTexture.getTexture());
    PreviewSprite.setTextureRect({ 0, 0, (int)ceil(EditorPreviewSize.x),(int)ceil(EditorPreviewSize.y) });

    //set info for tile editing
    TileEditInfo.TileText.setFont(EditorFont);
    TileEditInfo.TileSheet.loadFromFile("./SFEngine/Samples/Levels/Graveyard/TileSheetGraveyard.png");

    TileEditInfo.TileSheetSprite.setTexture(TileEditInfo.TileSheet);
    TileEditInfo.TileSheetPreviewSprite.setTexture(TileEditInfo.TileSheet);

    //get factors needed for scaling sprites (so they fit inside their boundaries)
    sf::Vector2f ScaleFactors = sf::Vector2f({
      400.f / TileEditInfo.TileSheet.getSize().x, 400.f / TileEditInfo.TileSheet.getSize().y
    });

    TileEditInfo.TileSheetSprite.setPosition({ TileSheetPreviewPosition });
    TileEditInfo.TileSheetSprite.setScale(ScaleFactors);

    //get the rect for the tile sheet rect currently selected (default = 0)
    sf::IntRect rect = TileFrames[TileEditInfo.SheetIndex];
    TileEditInfo.TileSheetOutline.setPosition({ TileSheetPreviewPosition.x + rect.left * ScaleFactors.x, TileSheetPreviewPosition.y + rect.top * ScaleFactors.y });
    TileEditInfo.TileSheetOutline.setSize({ (float)rect.width * ScaleFactors.x, (float)rect.height * ScaleFactors.y });
    TileEditInfo.TileSheetOutline.setFillColor(sf::Color::Transparent);
    TileEditInfo.TileSheetOutline.setOutlineColor(sf::Color::Blue);
    TileEditInfo.TileSheetOutline.setOutlineThickness(2);
    
    TileEditInfo.TileSheetPreviewSprite.setPosition({ TileSheetPreviewPosition.x, TileSheetPreviewPosition.y + TileSheetPreviewSize.y + 10 });
    TileEditInfo.TileSheetPreviewSprite.setTexture(TileEditInfo.TileSheet);
    TileEditInfo.TileSheetPreviewSprite.setTextureRect(TileFrames[TileEditInfo.SheetIndex]);

    //set up the outlines for the frames in the tile sheet
    /**
     *  (1)____(2)
     *  |        |
     *  |        |
     *  |(4)__(3)|
     */
    sf::IntRect Frame;
    for (std::size_t i = 0; i < TileFrames.size(); ++i) {
      TileEditInfo.TileFrameOutlines.push_back(sf::VertexArray(sf::Lines, 2));
      Frame = TileFrames[i];
      Pos1 = { TileSheetPreviewPosition.x + Frame.left * ScaleFactors.x, TileSheetPreviewPosition.y + Frame.top * ScaleFactors.y };
      Pos2 = { Pos1.x + Frame.width * ScaleFactors.x, Pos1.y };
      Pos3 = { Pos2.x, Pos2.y + Frame.height * ScaleFactors.y };
      Pos4 = { Pos1.x, Pos3.y };

      TileEditInfo.TileFrameOutlines.back()[0].position = Pos1; //(1)
      TileEditInfo.TileFrameOutlines.back()[1].position = Pos2; //(2)
      TileEditInfo.TileFrameOutlines.back()[0].color = sf::Color::Red;
      TileEditInfo.TileFrameOutlines.back()[1].color = sf::Color::Red;

      TileEditInfo.TileFrameOutlines.push_back(sf::VertexArray(sf::Lines, 2));
      TileEditInfo.TileFrameOutlines.back()[0].position = Pos2;
      TileEditInfo.TileFrameOutlines.back()[1].position = Pos3;
      TileEditInfo.TileFrameOutlines.back()[0].color = sf::Color::Red;
      TileEditInfo.TileFrameOutlines.back()[1].color = sf::Color::Red;

      TileEditInfo.TileFrameOutlines.push_back(sf::VertexArray(sf::Lines, 2));
      TileEditInfo.TileFrameOutlines.back()[0].position = Pos3;
      TileEditInfo.TileFrameOutlines.back()[1].position = Pos4;
      TileEditInfo.TileFrameOutlines.back()[0].color = sf::Color::Red;
      TileEditInfo.TileFrameOutlines.back()[1].color = sf::Color::Red;

      TileEditInfo.TileFrameOutlines.push_back(sf::VertexArray(sf::Lines, 2));
      TileEditInfo.TileFrameOutlines.back()[0].position = Pos4;
      TileEditInfo.TileFrameOutlines.back()[1].position = Pos1;
      TileEditInfo.TileFrameOutlines.back()[0].color = sf::Color::Red;
      TileEditInfo.TileFrameOutlines.back()[1].color = sf::Color::Red;
    }

    UITexture = std::shared_ptr<sf::RenderTexture>(new sf::RenderTexture);
    UITexture->create(1200, 900);
    UISprite.setTexture(UITexture->getTexture());

    TilesTexture = std::make_shared<sf::Texture>();
    TilesTexture->loadFromFile("./SFEngine/Samples/Levels/Graveyard/TileSheetGraveyard.png");

    try
    {
      UIHelper = UI::WidgetHelper::Create();

      TestButton = UI::ClickButtonBase::Create(UIHelper, { 800, 600 }, { 150, 45 });
      TestButton2 = UI::ClickButtonBase::Create(UIHelper, { 400, 800 }, { 150, 45 });

      TestButton->ButtonText.setFont(EditorFont);
      TestButton->ButtonText.setCharacterSize(16);
      TestButton->ButtonText.setString("TestButton");
      TestButton->ButtonText.setFillColor(sf::Color::White);
      TestButton->ButtonText.setPosition({ 820, 820 });

      float ScaleX = 400.f / TilesTexture->getSize().x;
      float ScaleY = 400.f / TilesTexture->getSize().y;

      sf::Vector2f TileStart{ 810, 40 };
      sf::IntRect LastTileDim{ 0,0,0,0 };
      sf::FloatRect ThisTileDim;
      for (auto & tile : TileFrames) {
        ThisTileDim.left = TileStart.x + ScaleX * tile.left;
        ThisTileDim.top = TileStart.y + ScaleY * tile.top;
        ThisTileDim.width = tile.width;
        ThisTileDim.height = tile.height;

        try {
          auto _tile = UI::DraggableTile::Create(UIHelper, TilesTexture, tile, { ThisTileDim.left, ThisTileDim.top }, { ThisTileDim.width * ScaleX, ThisTileDim.height * ScaleY });
          DragTiles.push_back(_tile);
        }
        catch (ConstructionException &cerr) {
          std::cerr << "Draggable exception error:\n" << cerr.what() << std::endl;
        }
      } //for tile : TileFrames

      ObjectList = UI::ListWidget::Create(UIHelper, { 400, 400 }, { 100, 400 });

    }
    catch (std::exception &err)
    {
      std::cerr << "Fuck: " << err.what() << std::endl;
    }


  }

  Editor::~Editor()
  {

  }

  void Editor::TickUpdate(const double &delta)
  {

    UIHelper->TickUpdate(delta);
  }

  void Editor::Render()
  {
    currentRenderWindow->clear(sf::Color::Black);
    PreviewTexture.clear(sf::Color::Transparent);
    UITexture->clear(sf::Color::Transparent);


    UIHelper->Render(UITexture);


    PreviewTexture.display();

    //draw UI elements
    TestButton->Render(UITexture);

    UITexture->display();

    UISprite.setTexture(UITexture->getTexture());

    currentRenderWindow->draw(EditorModeText);

    currentRenderWindow->draw(UISprite);

    currentRenderWindow->display();
  }


}
