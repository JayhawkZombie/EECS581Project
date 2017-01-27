#include "../../Headers/Engine/Editor.h"

namespace Engine
{

  Editor::Editor()
  {
    EditorFont.loadFromFile("./SFEngine/Source/CoreFiles/Fonts/Raleway-Regular.ttf");
    EditorModeText.setFont(EditorFont);
    EditorModeText.setCharacterSize(8);
    EditorModeText.setFillColor(sf::Color::White);
    EditorModeText.setPosition({ 400, 10 });
    EditorModeText.setString("Editor : Mode <No Selection>");

    MenuFont = std::make_shared<sf::Font>();
    MenuFont->loadFromFile("./SFEngine/Source/CoreFiles/Fonts/Raleway-Regular.ttf");

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

    UITexture = std::shared_ptr<sf::RenderTexture>(new sf::RenderTexture);
    UITexture->create(1200, 900);
    UISprite.setTexture(UITexture->getTexture());

    TilesTexture = std::make_shared<sf::Texture>();
    TilesTexture->loadFromFile("./SFEngine/Samples/Levels/Graveyard/TileSheetGraveyard.png");

    try
    {
      UIHelper = UI::WidgetHelper::Create();
      UILayer = UI::UILayer::Create(UIHelper);
      UIHelper->AddUILayer(UILayer);

      TestButton = UI::ClickButtonBase::Create(UILayer, UIHelper, { 800, 600 }, { 150, 45 });
      TestButton2 = UI::ClickButtonBase::Create(UILayer, UIHelper, { 400, 800 }, { 150, 45 });

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
          auto _tile = UI::DraggableTile::Create(UILayer, UIHelper, TilesTexture, tile, { ThisTileDim.left, ThisTileDim.top }, { ThisTileDim.width * ScaleX, ThisTileDim.height * ScaleY });
          DragTiles.push_back(_tile);
        }
        catch (ConstructionException &cerr) {
          std::cerr << "Draggable exception error:\n" << cerr.what() << std::endl;
        }
      } //for tile : TileFrames


      EditOptionsList = UI::ListWidget::Create(UILayer, UIHelper, TextFont, { 0, 0 }, { 1200.f, 80.f },
                                               UI::ButtonPlacement::BottomCenter, { 0.f, 15.f }, { 100.f, 15.f });

      TestPopup = UI::PopupObject::Create(UILayer, UIHelper, { 100, 100 }, { 900, 700 }, TextFont);

      TestScreen = UI::MenuScreen::Create();
      TestScreen->TestRect.setFillColor(sf::Color(1, 168, 148));
      TestScreen->TestRect.setPosition({ 200, 200 });
      TestScreen->TestRect.setSize({ 500, 500 });
      TestScreen2 = UI::MenuScreen::Create();
      TestScreen2->TestRect.setFillColor(sf::Color(1, 76, 168));
      TestScreen2->TestRect.setPosition({ 200, 200 });
      TestScreen2->TestRect.setSize({ 500, 500 });

      TestMenu = UI::MenuWidget::Create(UILayer, UIHelper, { 200, 200 }, { 500, 500 });

      assert(TestMenu && TestMenu->Helper.lock() && TestMenu->MyLayer.lock());
      UI::MenuWidget::SetDefaultScreen(TestScreen, TestMenu);
      UI::MenuWidget::AddScreen(TestScreen2, TestMenu);
      UI::MenuWidget::SetFont(TestMenu, MenuFont);

      TestScreenButton1 = UI::ClickButtonBase::Create(TestScreen->ScreenLayer, TestScreen->ScreenHelper, { 300, 300 }, { 150, 45 });
      TestScreenButton1->MouseReleaseCB = [this]() { this->TestScreen->CloseScreen(); };
      auto txtlabel1 = UI::TextLabel::Create(TestScreenButton1, TestScreenButton1->Helper, UI::TextAlignment::CenterJustified, "Close Menu", sf::Color(1, 56, 49), MenuFont, 16, { 0,0,1000,1000 }, { 0,0 });

      TestScreenButton2 = UI::ClickButtonBase::Create(TestScreen->ScreenLayer, TestScreen->ScreenHelper, { 300, 400 }, { 150, 45 });
      TestScreenButton2->MouseReleaseCB = [this]() { this->TestMenu->ShowScreen(this->TestScreen2); };
      auto txtlabel2 = UI::TextLabel::Create(TestScreenButton2, TestScreenButton1->Helper, UI::TextAlignment::CenterJustified, "Test Screen 2", sf::Color(1, 56, 49), MenuFont, 16, { 0,0,1000,1000 }, { 0,0 });

      TestScreenButton3 = UI::ClickButtonBase::Create(TestScreen2->ScreenLayer, TestScreen2->ScreenHelper, { 300, 300 }, { 150, 45 });
      TestScreenButton3->MouseReleaseCB = [this]() { this->TestScreen2->CloseScreen(); };
      auto txtlabel3 = UI::TextLabel::Create(TestScreenButton3, TestScreenButton1->Helper, UI::TextAlignment::CenterJustified, "Back", sf::Color(1, 56, 49), MenuFont, 16, { 0,0,1000,1000 }, { 0,0 });

      assert(TestMenu && TestScreen);
    }
    catch (std::exception &err)
    {
      std::cerr << "Fuck: " << err.what() << std::endl;
    }


  }

  Editor::~Editor()
  {
    TestMenu->Close();
  }

  void Editor::TickUpdate(const double &delta)
  {

    UIHelper->TickUpdate(delta);
  }

  void Editor::Render()
  {
    //currentRenderWindow->clear(sf::Color::Black);
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
