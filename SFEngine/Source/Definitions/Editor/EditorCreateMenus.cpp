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

      TestButton = UI::ClickButtonBase::Create(UILayer, UIHelper, { 800, 600 }, { 150, 45 }, ButtonOverlayTexture);
      TestButton2 = UI::ClickButtonBase::Create(UILayer, UIHelper, { 400, 800 }, { 150, 45 }, ButtonOverlayTexture);

      TestButton->ButtonText.setFont(EditorFont);
      TestButton->ButtonText.setCharacterSize(16);
      TestButton->ButtonText.setString("TestButton");
      TestButton->ButtonText.setFillColor(sf::Color::White);
      TestButton->ButtonText.setPosition({ 820, 820 });

      float ScaleX = 400.f / TilesTexture->getSize().x;
      float ScaleY = 400.f / TilesTexture->getSize().y;

      //sf::Vector2f TileStart{ 810, 40 };
      //sf::IntRect LastTileDim{ 0,0,0,0 };
      //sf::FloatRect ThisTileDim;
      //for (auto & tile : TileFrames) {
      //  ThisTileDim.left = TileStart.x + ScaleX * tile.left;
      //  ThisTileDim.top = TileStart.y + ScaleY * tile.top;
      //  ThisTileDim.width = tile.width;
      //  ThisTileDim.height = tile.height;

      //  try {
      //    auto _tile = UI::DraggableTile::Create(UILayer, UIHelper, TilesTexture, tile, { ThisTileDim.left, ThisTileDim.top }, { ThisTileDim.width * ScaleX, ThisTileDim.height * ScaleY });
      //    DragTiles.push_back(_tile);
      //  }
      //  catch (ConstructionException &cerr) {
      //    std::cerr << "Draggable exception error:\n" << cerr.what() << std::endl;
      //  }
      //} //for tile : TileFrames


      //EditOptionsList = UI::ListWidget::Create(UILayer, UIHelper, TextFont, { 0, 0 }, { 1200.f, 80.f },
      //                                         UI::ButtonPlacement::BottomCenter, { 0.f, 15.f }, { 100.f, 15.f });

      //EditOptionsList = UI::ListWidget::Create(UILayer, UIHelper, MenuFont, { 10, 400 }, { 200, 400 }, { 200, 40 });

      //TestPopup = UI::PopupObject::Create(UILayer, UIHelper, { 100, 100 }, { 900, 700 }, TextFont);

      EnablePhysicsToggle = UI::SimpleToggle::Create(UILayer, UIHelper, { 300, 80 }, { 20, 20 }, { 15, 15 }, IconSheet, "boxchecked_medium", "boxunchecked_medium", true);
      auto Label = UI::TextLabel::Create(EnablePhysicsToggle, UIHelper, UI::TextAlignment::CenterJustified, "physics", UI::DefaultDarkTheme.TextColorNormal, MenuFont, UI::DefaultDarkTheme.TextSizeMedium, { 0, 0, WindowSize.x, WindowSize.y }, { 0,0 });

      //TestList = UI::ListWidget::Create(UILayer, UIHelper, { 400, 200 }, { 200, 400 }, UI::DefaultDarkTheme);
      //MakeButtonWithText(TestListUpButton, UILayer, UIHelper, sf::Vector2f(610, 210), sf::Vector2f(150, 35), "scroll up", MenuFont, UI::DefaultDarkTheme);
      //MakeButtonWithText(TestListDownButton, UILayer, UIHelper, sf::Vector2f(610, 460), sf::Vector2f(150, 35), "scroll up", MenuFont, UI::DefaultDarkTheme);

      //TestListUpButton->MouseReleaseCB = 
      //  [this]()
      //{
      //  this->TestList->ScrollUpOne();
      //};
      //TestListDownButton->MouseReleaseCB =
      //  [this]()
      //{
      //  this->TestList->ScrollDownOne();
      //};

      //for (std::size_t i = 0; i < 20; ++i) {
      //  auto btn = UI::ClickButtonBase::Create(TestList->ChildLayer, TestList->ChildHelper, { 400,200 + 25 * __TO_FLOAT__(i) }, { 200,25 }, nullptr);
      //  auto __btnlabel = UI::TextLabel::Create(btn, UIHelper, UI::TextAlignment::CenterJustified, "TestListElement " + std::to_string(i), UI::DefaultDarkTheme.TextColorNormal, MenuFont, UI::DefaultDarkTheme.TextSizeSmall, btn->GlobalWidgetBounds.GlobalBounds, { 0,0 });
      //}

      //auto btn = UI::ClickButtonBase::Create(TestList->ChildLayer, TestList->ChildHelper, { 400,400 }, { 200,25 }, nullptr);
      //auto __btnlabel = UI::TextLabel::Create(btn, UIHelper, UI::TextAlignment::CenterJustified, "TestListElement", UI::DefaultDarkTheme.TextColorNormal, MenuFont, UI::DefaultDarkTheme.TextSizeSmall, btn->GlobalWidgetBounds.GlobalBounds, { 0,0 });
      ////TestList->AddItem(btn);
      //auto tstbtn = UI::ClickButtonBase::Create(TestList->ChildLayer, TestList->ChildHelper, { 500, 500 }, UI::DefaultDarkTheme.ButtonSizeNormal, nullptr);

      //assert(TestList && TestList->ChildLayer && TestList->ChildHelper);

      //EnablePhysicsToggle->AlignTextLabel();

      //PhysicsTicksBox = UI::NumericComboBox::Create(UILayer, UIHelper, { 500, 40 }, { 100, 40 }, { 40,20 }, 5, 60, MenuFont, IconSheet);

      TestInput = UI::TextInput::Create(UILayer, UIHelper, { 500, 40 }, { 200, 30 }, MenuFont, "default text");

      TestSpinner = UI::IntSpinner::Create(UILayer, UIHelper, { 500, 80 }, { 200, 30 }, MenuFont, IconSheet);

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
      sf::Vector2f TestMenusPosition = { 200, 200 };
      sf::Vector2f TestMenusSize = { 400, 400 };
      sf::Vector2f TestMenusScreenPosition = { 200, 200 };
      sf::Vector2f TestMenusScreenSize = { 400, 400 };
      MakeMenu(TestMenus, UILayer, UIHelper);
      MakeMenuDefaultScreen(TestSelectScreen, UI::DefaultDarkTheme, TestMenus);
      MakeButtonNormal(OpenTestMenusButton, UILayer, UIHelper, sf::Vector2f(180, 10), sf::Vector2f(150, 40), UI::DefaultDarkTheme, ButtonOverlayTexture);
      auto test_menus_label = UI::TextLabel::Create(OpenTestMenusButton, UIHelper, UI::TextAlignment::CenterJustified, "<test menus>", sf::Color(0, 129, 155), MenuFont, UI::DefaultDarkTheme.TextSizeNormal, { 0, 0, WindowSize.x, WindowSize.y }, { 0,0 });
      OpenTestMenusButton->MouseReleaseCB =
        [this]()
      {
        UI::MenuWidget::OpenMenu(this->TestMenus);
      };

      //create the editing stuff inside the edit animation menu
      MakeMenuScreen(EditAnimationScreen, UI::DefaultDarkTheme, TestMenus);
      AddMenuScreen(TestMenus, EditAnimationScreen);

      MakeMenuScreenButtonNormal(TestSelectCancelButton, TestSelectScreen, TestMenus, sf::Vector2f(210, 260), UI::DefaultDarkTheme, "cancel", MenuFont, nullptr);
      MakeMenuButtonClose(TestSelectCancelButton, TestMenus);

      MakeMenuScreenButtonNormal(TestSelectEditAnimationButton, TestSelectScreen, TestMenus, sf::Vector2f(210, 210), UI::DefaultDarkTheme, "edit animation", MenuFont, nullptr);
      MakeMenuScreenTransition(TestSelectEditAnimationButton, TestMenus, EditAnimationScreen);

      ////create the actual editing menu
      MakeMenuScreenButtonNormal(EditAnimationSaveButton, EditAnimationScreen, TestMenus, sf::Vector2f(210, 560), UI::DefaultDarkTheme, "save(and back)", MenuFont, nullptr);
      MakeMenuScreenButtonBack(EditAnimationSaveButton, TestSelectScreen);

      EditAnimationFileInput = UI::TextInput::Create(EditAnimationScreen->ScreenLayer, EditAnimationScreen->ScreenHelper, { 210, 210 }, { 200, 30 }, MenuFont, "texture path");
      MakeMenuScreenButtonNormal(EditAnimationFileLoadButton, EditAnimationScreen, TestMenus, sf::Vector2f(460, 210), UI::DefaultDarkTheme, "load", MenuFont, nullptr);
      ////load texture

      MakeMenuScreenButtonNormal(EditAnimationTexturePreviewFillinButton, EditAnimationScreen, TestMenus, sf::Vector2f(210, 250), UI::DefaultDarkTheme, "Preview", MenuFont, nullptr);
      MakeMenuScreenButtonNormal(EditAnimationAnimationPreviewFillinButton, EditAnimationScreen, TestMenus, sf::Vector2f(210, 510), UI::DefaultDarkTheme, "Anim Preview", MenuFont, nullptr);

      EditAnimationFrameCountSpinner = UI::IntSpinner::Create(EditAnimationScreen->ScreenLayer, EditAnimationScreen->ScreenHelper, { 410, 450 }, { 60, 30 }, MenuFont, IconSheet);
      auto _frame_cnt_label = UI::TextLabel::Create(EditAnimationFrameCountSpinner, EditAnimationFrameCountSpinner->Helper, UI::TextAlignment::CenterJustified, "# frames", UI::DefaultDarkTheme.TextColorNormal,
                                                    MenuFont, UI::DefaultDarkTheme.TextSizeNormal, EditAnimationFrameCountSpinner->GlobalWidgetBounds.GlobalBounds, { 0,0 });

      EditAnimationFrameSizeXSpinner = UI::IntSpinner::Create(EditAnimationScreen->ScreenLayer, EditAnimationScreen->ScreenHelper, { 410, 490 }, { 60, 30 }, MenuFont, IconSheet);
      auto _frame_size_x_label = UI::TextLabel::Create(EditAnimationFrameSizeXSpinner, EditAnimationFrameSizeXSpinner->Helper, UI::TextAlignment::CenterJustified, "FrameSizeX", UI::DefaultDarkTheme.TextColorNormal,
                                                       MenuFont, UI::DefaultDarkTheme.TextSizeNormal, EditAnimationFrameSizeXSpinner->GlobalWidgetBounds.GlobalBounds, { 0,0 });
      EditAnimationFrameSizeYSpinner = UI::IntSpinner::Create(EditAnimationScreen->ScreenLayer, EditAnimationScreen->ScreenHelper, { 410, 530 }, { 60, 30 }, MenuFont, IconSheet);
      EditAnimationFrameSpeedSpinner = UI::IntSpinner::Create(EditAnimationScreen->ScreenLayer, EditAnimationScreen->ScreenHelper, { 410, 570 }, { 60, 30 }, MenuFont, IconSheet);


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