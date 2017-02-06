#include "../../Headers/Engine/Editor.h"

namespace Engine
{

  void Editor::CreateMenus()
  {
    try
    {
      UIHelper = UI::WidgetHelper::Create();
      UILayer = UI::UILayer::Create(UIHelper);
      UIHelper->AddUILayer(UILayer);

      EnablePhysicsToggle = UI::SimpleToggle::Create(UILayer, UIHelper, { 300, 80 }, { 20, 20 }, { 15, 15 }, IconSheet, "boxchecked_medium", "boxunchecked_medium", true);
      auto Label = UI::TextLabel::Create(EnablePhysicsToggle, UIHelper, UI::TextAlignment::CenterJustified, "physics", UI::DefaultDarkTheme.TextColorNormal, MenuFont, UI::DefaultDarkTheme.TextSizeMedium, { 0, 0, WindowSize.x, WindowSize.y }, { 0,0 });
      EnablePhysicsToggle->CheckedCB = [this]() {this->EnabledPhysics = true; };
      EnablePhysicsToggle->UnCheckedCB = [this]() {this->EnabledPhysics = false; };

      MakeButtonWithText(CloseButton, UILayer, UIHelper, sf::Vector2f(1700, 10), UI::DefaultDarkTheme.ToolBarButtonSize, "close", MenuFont, UI::DefaultDarkTheme);
      CloseButton->MouseReleaseCB =
        []()
      {
        FlagForClose = true;
      };

      sf::Vector2f ObjectSelectMenuPosition = { 0, 0 };
      sf::Vector2f ObjectSelectMenuSize = { 140, 900 };
      sf::Vector2f ObjectSelectMenuScreenPosition = { 0, 0 };
      sf::Vector2f ObjectSelectMenuScreenSize = { 140, 900 };

      //ObjectSelectMenu = UI::MenuWidget::Create(UILayer, UIHelper, { 100, 100 }, { 200, 400 });
      MakeMenu(ObjectSelectMenu, UILayer, UIHelper);
      MakeMenuDefaultScreen(ObjectSelectTypeScreen, UI::DefaultDarkTheme, ObjectSelectMenu);
      MakeMenuScreen(ObjectSelectPhysicsObjectScreen, UI::DefaultDarkTheme, ObjectSelectMenu);
      MakeMenuScreen(ObjectSelectLightObjectScreen, UI::DefaultDarkTheme, ObjectSelectMenu);
      MakeMenuScreen(ObjectSelectEffectObjectScreen, UI::DefaultDarkTheme, ObjectSelectMenu);

      AddMenuScreen(ObjectSelectMenu, ObjectSelectPhysicsObjectScreen);
      AddMenuScreen(ObjectSelectMenu, ObjectSelectLightObjectScreen);
      AddMenuScreen(ObjectSelectMenu, ObjectSelectEffectObjectScreen);

      //Make buttons and transitions on first menu screen
      MakeMenuScreenButtonNormal(ObjectSelectType_PhysicsObjectButton, ObjectSelectTypeScreen, ObjectSelectMenu, sf::Vector2f(25, 70), UI::DefaultDarkTheme, "physics object", MenuFont, ButtonOverlayTexture);
      MakeMenuScreenTransition(ObjectSelectType_PhysicsObjectButton, ObjectSelectMenu, ObjectSelectPhysicsObjectScreen);

      MakeMenuScreenButtonNormal(ObjectSelectType_LightObjectButton, ObjectSelectTypeScreen, ObjectSelectMenu, sf::Vector2f(25, 120), UI::DefaultDarkTheme, "light object", MenuFont, ButtonOverlayTexture);
      MakeMenuScreenTransition(ObjectSelectType_LightObjectButton, ObjectSelectMenu, ObjectSelectLightObjectScreen);

      MakeMenuScreenButtonNormal(ObjectSelectType_EffectObjectButton, ObjectSelectTypeScreen, ObjectSelectMenu, sf::Vector2f(25, 170), UI::DefaultDarkTheme, "offect object", MenuFont, ButtonOverlayTexture);
      MakeMenuScreenTransition(ObjectSelectType_EffectObjectButton, ObjectSelectMenu, ObjectSelectEffectObjectScreen);

      MakeMenuScreenButtonNormal(ObjectSelectType_CancelButton, ObjectSelectTypeScreen, ObjectSelectMenu, sf::Vector2f(25, 220), UI::DefaultDarkTheme, "cancel", MenuFont, ButtonOverlayTexture);
      MakeMenuButtonClose(ObjectSelectType_CancelButton, ObjectSelectMenu);

      //Make buttons and transitions on the second screen
      MakeMenuScreenButtonNormal(ObjectSelect_BallButton, ObjectSelectPhysicsObjectScreen, ObjectSelectMenu, sf::Vector2f(25, 70), UI::DefaultDarkTheme, "ball", MenuFont, ButtonOverlayTexture);
      MakeMenuButtonClose(ObjectSelect_BallButton, ObjectSelectMenu);

      MakeMenuScreenButtonNormal(ObjectSelect_SquareButton, ObjectSelectPhysicsObjectScreen, ObjectSelectMenu, sf::Vector2f(25, 120), UI::DefaultDarkTheme, "square", MenuFont, ButtonOverlayTexture);
      MakeMenuButtonClose(ObjectSelect_SquareButton, ObjectSelectMenu);

      MakeMenuScreenButtonNormal(ObjectSelect_RectButton, ObjectSelectPhysicsObjectScreen, ObjectSelectMenu, sf::Vector2f(25, 170), UI::DefaultDarkTheme, "rectangle", MenuFont, ButtonOverlayTexture);
      MakeMenuButtonClose(ObjectSelect_RectButton, ObjectSelectMenu);

      MakeMenuScreenButtonNormal(ObjectSelect_TriangleButton, ObjectSelectPhysicsObjectScreen, ObjectSelectMenu, sf::Vector2f(25, 220), UI::DefaultDarkTheme, "triangle", MenuFont, ButtonOverlayTexture);
      MakeMenuButtonClose(ObjectSelect_TriangleButton, ObjectSelectMenu);

      MakeMenuScreenButtonNormal(ObjectSelect_5PolyButton, ObjectSelectPhysicsObjectScreen, ObjectSelectMenu, sf::Vector2f(25, 270), UI::DefaultDarkTheme, "5poly", MenuFont, ButtonOverlayTexture);
      MakeMenuButtonClose(ObjectSelect_5PolyButton, ObjectSelectMenu);

      MakeMenuScreenButtonNormal(ObjectSelect_BackToSelectTypeButton, ObjectSelectPhysicsObjectScreen, ObjectSelectMenu, sf::Vector2f(25, 320), UI::DefaultDarkTheme, "back", MenuFont, ButtonOverlayTexture);
      MakeMenuScreenButtonBack(ObjectSelect_BackToSelectTypeButton, ObjectSelectPhysicsObjectScreen);

      //Light object menu screen
      MakeMenuScreenButtonNormal(LightSelect_CancelButton, ObjectSelectLightObjectScreen, ObjectSelectMenu, sf::Vector2f(25, 110), UI::DefaultDarkTheme, "back", MenuFont, ButtonOverlayTexture);
      MakeMenuScreenButtonBack(LightSelect_CancelButton, ObjectSelectLightObjectScreen);

      //Effect object menu screen
      MakeMenuScreenButtonNormal(EffectSelect_CancelButton, ObjectSelectEffectObjectScreen, ObjectSelectMenu, sf::Vector2f(25, 110), UI::DefaultDarkTheme, "back", MenuFont, ButtonOverlayTexture);
      MakeMenuScreenButtonBack(EffectSelect_CancelButton, ObjectSelectEffectObjectScreen);

      /*
      Make the menu seen whenyou want to select a tile
      */

      sf::Vector2f AddTileMenuPosition = { 200, 200 };
      sf::Vector2f AddTileMenuSize = { 600, 600 };
      sf::Vector2f AddTileMenuScreenPosition = { 200, 200 };
      sf::Vector2f AddTileMenuScreenSize = { 600, 600 };

      MakeMenu(AddTileMenu, UILayer, UIHelper);
      MakeMenuDefaultScreen(AddTileScreen, UI::DefaultDarkTheme, AddTileMenu);

      MakeMenuScreenButtonNormal(AddTileSaveButton, AddTileScreen, AddTileMenu, sf::Vector2f(210, 700), UI::DefaultDarkTheme, "save", MenuFont, ButtonOverlayTexture);
      MakeMenuButtonClose(AddTileSaveButton, AddTileMenu);
      MakeMenuScreenButtonNormal(AddTileCancelButton, AddTileScreen, AddTileMenu, sf::Vector2f(310, 700), UI::DefaultDarkTheme, "cancel", MenuFont, ButtonOverlayTexture);
      MakeMenuButtonClose(AddTileCancelButton, AddTileMenu);

      AddTileTextureInput = UI::TextInput::Create(AddTileScreen->ScreenLayer, AddTileScreen->ScreenHelper, { 500, 200 }, { 200, 45 }, MenuFont, "texture");
      AddTileFrameLeftInput = UI::TextInput::Create(AddTileScreen->ScreenLayer, AddTileScreen->ScreenHelper, { 250, 250 }, { 100, 45 }, MenuFont, "frameLeft");
      AddTileFrameTopInput = UI::TextInput::Create(AddTileScreen->ScreenLayer, AddTileScreen->ScreenHelper, { 375, 250 }, { 100, 45 }, MenuFont, "frameTop");
      AddTileFrameWidthInput = UI::TextInput::Create(AddTileScreen->ScreenLayer, AddTileScreen->ScreenHelper, { 500, 250 }, { 100, 45 }, MenuFont, "frameWidth");
      AddTileFrameHeightInput = UI::TextInput::Create(AddTileScreen->ScreenLayer, AddTileScreen->ScreenHelper, { 675, 250 }, { 100, 45 }, MenuFont, "frameHeight");
      AddTileIsAnimatedToggle = UI::SimpleToggle::Create(AddTileScreen->ScreenLayer, AddTileScreen->ScreenHelper, { 400, 400 }, { 20, 20 }, { 10, 10 }, IconSheet, "boxchecked_small", "boxunchecked_small", false);
      auto is_animated_toggle = UI::TextLabel::Create(AddTileIsAnimatedToggle, AddTileScreen->ScreenHelper, UI::TextAlignment::CenterJustified, "Is Animated",
                                                      UI::DefaultDarkTheme.TextColorNormal, MenuFont, UI::DefaultDarkTheme.TextSizeMedium, { 0,0,1000,1000 }, { 0,0 });

      MakeButtonNormal(AddTileButton, UILayer, UIHelper, sf::Vector2f(10, 130), sf::Vector2f(150, 40), UI::DefaultDarkTheme, ButtonOverlayTexture);
      auto add_tile_label = UI::TextLabel::Create(AddTileButton, UIHelper, UI::TextAlignment::CenterJustified, "add tile", UI::DefaultDarkTheme.TextColorNormal, MenuFont, UI::DefaultDarkTheme.TextSizeNormal, { 0, 0, WindowSize.x, WindowSize.y }, { 0,0 });
      AddTileButton->MouseReleaseCB =
        [this]()
      {
        UI::MenuWidget::OpenMenu(AddTileMenu);
      };

      /*
      Make the menu to add classes
      */
      sf::Vector2f AddClassMenuPosition = { 0, 0 };
      sf::Vector2f AddClassMenuSize = { 140, 600 };
      sf::Vector2f AddClassMenuScreenPosition = { 0, 0 };
      sf::Vector2f AddClassMenuScreenSize = { 140, 600 };

      MakeMenu(AddClassMenu, UILayer, UIHelper);
      MakeMenuDefaultScreen(AddClassSelectScreen, UI::DefaultDarkTheme, AddClassMenu);
      MakeMenuScreenButtonNormal(AddClassAddCancelButton, AddClassSelectScreen, AddClassMenu, sf::Vector2f(10, 560), UI::DefaultDarkTheme, "cancel", MenuFont, ButtonOverlayTexture);
      MakeMenuButtonClose(AddClassAddCancelButton, AddClassMenu);
      MakeMenuScreen(AddActorClassScreen, UI::DefaultDarkTheme, AddClassMenu);
      MakeMenuScreen(AddObjectClassScreen, UI::DefaultDarkTheme, AddClassMenu);
      MakeMenuScreen(AddLightClassScreen, UI::DefaultDarkTheme, AddClassMenu);
      MakeMenuScreen(AddEffectClassScreen, UI::DefaultDarkTheme, AddClassMenu);

      AddMenuScreen(AddClassMenu, AddActorClassScreen);
      AddMenuScreen(AddClassMenu, AddObjectClassScreen);
      AddMenuScreen(AddClassMenu, AddLightClassScreen);
      AddMenuScreen(AddClassMenu, AddEffectClassScreen);

      MakeMenuScreenButtonNormal(AddClassAddActorButton, AddClassSelectScreen, AddClassMenu, sf::Vector2f(10, 80), UI::DefaultDarkTheme, "actor class", MenuFont, ButtonOverlayTexture);
      MakeMenuScreenTransition(AddClassAddActorButton, AddClassMenu, AddActorClassScreen);
      MakeMenuScreenButtonNormal(AddClassAddObjectButton, AddClassSelectScreen, AddClassMenu, sf::Vector2f(10, 120), UI::DefaultDarkTheme, "object class", MenuFont, ButtonOverlayTexture);
      MakeMenuScreenTransition(AddClassAddObjectButton, AddClassMenu, AddObjectClassScreen);
      MakeMenuScreenButtonNormal(AddClassAddLightButton, AddClassSelectScreen, AddClassMenu, sf::Vector2f(10, 160), UI::DefaultDarkTheme, "light class", MenuFont, ButtonOverlayTexture);
      MakeMenuScreenTransition(AddClassAddLightButton, AddClassMenu, AddLightClassScreen);
      MakeMenuScreenButtonNormal(AddClassAddEffectButton, AddClassSelectScreen, AddClassMenu, sf::Vector2f(10, 200), UI::DefaultDarkTheme, "effect class", MenuFont, ButtonOverlayTexture);
      MakeMenuScreenTransition(AddClassAddEffectButton, AddClassMenu, AddEffectClassScreen);

      //button on main screen to open the menu
      MakeButtonNormal(AddClassButton, UILayer, UIHelper, sf::Vector2f(10, 180), sf::Vector2f(150, 40), UI::DefaultDarkTheme, ButtonOverlayTexture);
      auto __cancel_text = UI::TextLabel::Create(AddClassButton, UIHelper, UI::TextAlignment::CenterJustified, "add class", UI::DefaultDarkTheme.TextColorNormal, MenuFont, UI::DefaultDarkTheme.TextSizeNormal, { 0, 0, WindowSize.x, WindowSize.y }, { 0,0 });
      AddClassButton->MouseReleaseCB =
        [this]()
      {
        UI::MenuWidget::OpenMenu(this->AddClassMenu);
      };

      MakeMenuScreenButtonNormal(AddActorClassCancelButton, AddActorClassScreen, AddClassMenu, sf::Vector2f(10, 10), UI::DefaultDarkTheme, "back", MenuFont, nullptr);
      MakeMenuScreenButtonBack(AddActorClassCancelButton, AddActorClassScreen);
       
      MakeMenuScreenButtonNormal(AddObjectClassCancelButton, AddObjectClassScreen, AddClassMenu, sf::Vector2f(10, 10), UI::DefaultDarkTheme, "back", MenuFont, nullptr);
      MakeMenuScreenButtonBack(AddObjectClassCancelButton, AddObjectClassScreen);

      MakeMenuScreenButtonNormal(AddLightClassCancelButton, AddLightClassScreen, AddClassMenu, sf::Vector2f(10, 10), UI::DefaultDarkTheme, "back", MenuFont, nullptr);
      MakeMenuScreenButtonBack(AddLightClassCancelButton, AddLightClassScreen);

      MakeMenuScreenButtonNormal(AddEffectClassCancelButton, AddEffectClassScreen, AddClassMenu, sf::Vector2f(10, 10), UI::DefaultDarkTheme, "back", MenuFont, nullptr);
      MakeMenuScreenButtonBack(AddEffectClassCancelButton, AddEffectClassScreen);

      //Create the TestingMenus
      sf::Vector2f TestMenusPosition = { 400, 100 };
      sf::Vector2f TestMenusSize = { 500, 500 };
      sf::Vector2f TestMenusScreenPosition = { 400, 100 };
      sf::Vector2f TestMenusScreenSize = { 500, 500 };
      MakeMenu(TestMenus, UILayer, UIHelper);
      MakeMenuDefaultScreen(TestSelectScreen, UI::DefaultDarkTheme, TestMenus);
      MakeButtonNormal(OpenTestMenusButton, UILayer, UIHelper, sf::Vector2f(180, 10), sf::Vector2f(150, 40), UI::DefaultDarkTheme, ButtonOverlayTexture);
      auto test_menus_label = UI::TextLabel::Create(OpenTestMenusButton, UIHelper, UI::TextAlignment::CenterJustified, "<test menus>", sf::Color(0, 129, 155), MenuFont, UI::DefaultDarkTheme.TextSizeNormal, { 0, 0, WindowSize.x, WindowSize.y }, { 0,0 });
      OpenTestMenusButton->MouseReleaseCB =
        [this]()
      {
        UI::MenuWidget::OpenMenu(this->TestMenus);
      };

      MakeMenuScreenButtonNormal(TestSelectCancelButton, TestSelectScreen, TestMenus, sf::Vector2f(210, 260), UI::DefaultDarkTheme, "cancel", MenuFont, nullptr);
      MakeMenuButtonClose(TestSelectCancelButton, TestMenus);



      AnimMenu.ConstructMenu(TestMenus, TestSelectScreen, sf::Vector2f(400, 400), UI::DefaultDarkTheme, MenuFont, TestMenusPosition, TestMenusScreenSize, TestSelectEditAnimationButton, IconSheet);

      TestListWidget = UI::ListWidget::Create(UILayer, UIHelper, { 500,500 }, { 200, 25 }, { 200, 500 }, { 200, 15 }, MenuFont, IconSheet, UI::DefaultDarkTheme);

      MakeButtonNormal(EraseObjectsButton, UILayer, UIHelper, sf::Vector2f(10, 70), sf::Vector2f(150, 40), UI::DefaultDarkTheme, ButtonOverlayTexture);
      auto erase_label = UI::TextLabel::Create(EraseObjectsButton, UIHelper, UI::TextAlignment::CenterJustified, "erase all", sf::Color(0, 129, 155), MenuFont, UI::DefaultDarkTheme.TextSizeNormal, { 0, 0, WindowSize.x, WindowSize.y }, { 0,0 });
      EraseObjectsButton->MouseReleaseCB =
        [this]()
      {
        this->TestObjects.clear();
      };

      MakeButtonNormal(AllObjectButton, UILayer, UIHelper, sf::Vector2f(10, 10), sf::Vector2f(150, 40), UI::DefaultDarkTheme, ButtonOverlayTexture);
      auto label = UI::TextLabel::Create(AllObjectButton, UIHelper, UI::TextAlignment::CenterJustified, "add object", sf::Color(0, 129, 155), MenuFont, UI::DefaultDarkTheme.TextSizeNormal, { 0, 0, WindowSize.x, WindowSize.y }, { 0,0 });
      MakeMenuButtonOpen(AllObjectButton, ObjectSelectMenu);

      ////Bind spawning behavior
      ObjectSelect_BallButton->MouseReleaseCB =
        [this]()
      {
        //this->ObjectSelectMenu->CloseMenu();
        this->SpawnBall(sf::Vector2f(400, 50));
      };

      ObjectSelect_5PolyButton->MouseReleaseCB =
        [this]()
      {
        this->Spawn5Poly(sf::Vector2f(400, 50));
      };

      ObjectSelect_SquareButton->MouseReleaseCB =
        [this]()
      {
        //this->ObjectSelectMenu->CloseMenu();
        this->SpawnSquare(sf::Vector2f(300, 50));
      };

      ObjectSelect_TriangleButton->MouseReleaseCB =
        [this]()
      {
        //this->ObjectSelectMenu->CloseMenu();
        this->SpawnTriangle(sf::Vector2f(150, 50));
      };
    }
    catch (std::exception &err)
    {
      std::cerr << "Fuck: " << err.what() << std::endl;
    }
  }

}