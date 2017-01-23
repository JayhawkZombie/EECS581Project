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

    TextFont = std::make_shared<sf::Font>();
    TextFont->loadFromFile("./SFEngine/Source/CoreFiles/Fonts/Raleway-Regular.ttf");

    PreviewGridInfoText.setFont(EditorFont);
    PreviewGridInfoText.setCharacterSize(6);
    PreviewGridInfoText.setFillColor(sf::Color::White);
    PreviewGridInfoText.setPosition({ 10, 820 });
    PreviewGridInfoText.setString("Grid Cell: 40 x 40");

    //create the grid lines for the preview
    sf::Vector2f GridStart = { 0, 40 };
    sf::Vector2f GridCellSize = { 40.f, 40.f };
    sf::Vector2f Pos1, Pos2, Pos3, Pos4;

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
    //sf::IntRect rect = TileFrames[TileEditInfo.SheetIndex];
    //TileEditInfo.TileSheetOutline.setPosition({ TileSheetPreviewPosition.x + rect.left * ScaleFactors.x, TileSheetPreviewPosition.y + rect.top * ScaleFactors.y });
    //TileEditInfo.TileSheetOutline.setSize({ (float)rect.width * ScaleFactors.x, (float)rect.height * ScaleFactors.y });
    //TileEditInfo.TileSheetOutline.setFillColor(sf::Color::Transparent);
    //TileEditInfo.TileSheetOutline.setOutlineColor(sf::Color::Blue);
    //TileEditInfo.TileSheetOutline.setOutlineThickness(2);
    //
    //TileEditInfo.TileSheetPreviewSprite.setPosition({ TileSheetPreviewPosition.x, TileSheetPreviewPosition.y + TileSheetPreviewSize.y + 10 });
    //TileEditInfo.TileSheetPreviewSprite.setTexture(TileEditInfo.TileSheet);
    //TileEditInfo.TileSheetPreviewSprite.setTextureRect(TileFrames[TileEditInfo.SheetIndex]);

    UITexture = std::shared_ptr<sf::RenderTexture>(new sf::RenderTexture);
    UITexture->create(1200, 900);
    UISprite.setTexture(UITexture->getTexture());

    TilesTexture = std::make_shared<sf::Texture>();
    TilesTexture->loadFromFile("./SFEngine/Samples/Levels/Graveyard/TileSheetGraveyard.png");

    try
    {
      UIHelper = UI::WidgetHelper::Create();
      UILayer = UI::UILayer::Create();
      UIHelper->AddUILayer(UILayer);

      TestButton = UI::ClickButtonBase::Create(UILayer, { 800, 600 }, { 150, 45 });
      TestButton2 = UI::ClickButtonBase::Create(UILayer, { 400, 800 }, { 150, 45 });

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
          auto _tile = UI::DraggableTile::Create(UILayer, TilesTexture, tile, { ThisTileDim.left, ThisTileDim.top }, { ThisTileDim.width * ScaleX, ThisTileDim.height * ScaleY });
          DragTiles.push_back(_tile);
        }
        catch (ConstructionException &cerr) {
          std::cerr << "Draggable exception error:\n" << cerr.what() << std::endl;
        }
      } //for tile : TileFrames

      ObjectList = UI::ListWidget::Create(UILayer, TextFont, { 0, 100.f }, { 100, 700.f },
                                          UI::ButtonPlacement::TopCenter, { 0, 0 }, { 100.f, 15.f });
      
      EditOptionsList = UI::ListWidget::Create(UILayer, TextFont, { 0, 0 }, { 1200.f, 80.f },
                                               UI::ButtonPlacement::BottomCenter, { 0.f, 15.f }, { 100.f, 15.f });

      //auto Label = UI::TextLabel::Create(EditOptionsOpenCloseButton, UI::TextAlignment::CenterJustified, "Close", sf::Color::White, TextFont, 12, { 0, 0, 15, 75 }, { 0, 0 });

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
