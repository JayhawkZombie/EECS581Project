#include "../../Headers/Engine/Editor.h"
#include "../../Headers/UI/Theme.h"
#include "../../Headers/UI/UICreationMacros.h"
#include "../../Headers/UI/UIIconSheet.h"
#include "../../Headers/Level/Level.h"

namespace Engine
{

  bool FlagForClose = false;

  Editor::Editor()
    : EditorScriptEngine{ std::make_shared<chaiscript::ChaiScript>(chaiscript::Std_Lib::library()) }
  {
    std::cerr << "Creating editor script engine" << std::endl;
    SetKeyRepeatEnabled(false);
    std::cerr << "Adding editor methods" << std::endl;
    chaiscript::ModulePtr tptr(new chaiscript::Module);
    BindEditorMethods(tptr);
    EditorScriptEngine->add(tptr);
    EditorScriptEngine->eval_file("./SFEngine/Samples/Scripts/TestEditorScript.chai");

    //Load the icon sheet
    UI::LoadIconSheet("./SFEngine/Source/CoreFiles/Textures/Icons/Icons.txt");
    IconSheet = std::make_shared<sf::Texture>();
    IconSheet->loadFromFile("./SFEngine/Source/CoreFiles/Textures/Icons/ui_icons_light.png");

    IconsTexture.load("./SFEngine/Source/CoreFiles/Textures/Icons/ui_icons_light.png");
    ForArrorMediumTexture = IconsTexture;
    BackArrowMediumTexture = IconsTexture;

    EditorFont.loadFromFile("./SFEngine/Source/CoreFiles/Fonts/Raleway-Regular.ttf");
    EditorModeText.setFont(EditorFont);
    EditorModeText.setCharacterSize(8);
    EditorModeText.setFillColor(sf::Color::White);
    EditorModeText.setPosition({ 400, 10 });
    EditorModeText.setString("Editor : Mode <No Selection>");

    MenuFont = std::make_shared<sf::Font>();
    MenuFont->loadFromFile("./SFEngine/Source/CoreFiles/Fonts/exo/Exo-Light.otf");

    TextFont = std::make_shared<sf::Font>();
    TextFont->loadFromFile("./SFEngine/Source/CoreFiles/Fonts/Raleway-Regular.ttf");

    PreviewGridInfoText.setFont(EditorFont);
    PreviewGridInfoText.setCharacterSize(6);
    PreviewGridInfoText.setFillColor(sf::Color::White);
    PreviewGridInfoText.setPosition({ 10, 820 });
    PreviewGridInfoText.setString("Grid Cell: 40 x 40");

    UITexture = std::shared_ptr<sf::RenderTexture>(new sf::RenderTexture);
    UITexture->create(static_cast<unsigned int>(std::ceil(WindowSize.x)), static_cast<unsigned int>(std::ceil(WindowSize.y)));

    EditorRenderState.blendMode = sf::BlendAdd;

    EditLevel = std::make_shared<Level>(sf::Vector2u({ 1920, 1080 }), sf::FloatRect(0, 0, 1920, 1080), true, sf::Vector2f({ 1920 / 16.f,1080 / 16.f }));


    TestActorSpriteSheet = std::make_shared<sf::Texture>();
    if (!TestActorSpriteSheet->loadFromFile("./SFEngine/Samples/Actors/ninjagirlnew/Animations/AnimCombined.png")) {
      std::cerr << "Failed to load actor animation sheet" << std::endl;
      exit(1);
    }

    GenericActor::BuildAnimations("./SFEngine/Samples/Actors/ninjagirlnew/Animations/AnimCombined.txt", "./SFEngine/Samples/Actors/ninjagirlnew/Animations/AnimCombined.png", &TestActor);

    EditorScriptEngine->add_global(chaiscript::var(&TestActor), "MainPlayer");
    LoadProject("C:\\Projects\\TestProject\\testproject.json");
  }

  Editor::~Editor()
  {
    //TestMenu->Close();
    //GUI->remove(SideTabPanel);
  }

  void Editor::TickUpdate(const double &delta)
  {
    static float update_delta = 16.66667f;
    static float update_current = 0.f;

    update_current += delta;

    //TestActor.TickUpdate(delta);
    std::string deltastr = std::to_string(delta);
    EditorScriptEngine->eval("Update(" + deltastr + ");");

    if (EnabledPhysics && (TestObjects.size() > 0 || Segments.size() > 0) && update_current >= update_delta) {
      UpdatePhysics(TestObjects, Segments, 2);
      update_current = 0.f;
    }

    if (IsUpdateLevelEnabled)
      EditLevel->TickUpdate(delta);
  }

  void Editor::Render(std::shared_ptr<sf::RenderTexture> Texture)
  {
    EditLevel->Render(Texture);
    
    sf::VertexArray Varr = sf::VertexArray(sf::Lines, 2);

    for (auto & seg : Segments) {
      seg->draw(*currentRenderWindow);
    }

    sf::CircleShape circle;

    TestActor.Render(Texture);

    for (auto & obj : TestObjects) {
      obj->draw(*currentRenderWindow);
    }
  }

  void Editor::PreLoopSetup()
  {
    //set up the physics environment
    auto boundaries = WindowSize;
    std::cerr << "Editor::PreLoopSetup() : Boundaries {" << boundaries.x << ", " << boundaries.y << "}" << std::endl;
    AssignBoundaries(boundaries.y, boundaries.x);
    Gravity.x = 0.f;
    Gravity.y = 0.09f;
    SetGravity(&Gravity);

    UIThemePtr = std::make_shared<tgui::Theme>("./SFEngine/Source/CoreFiles/UIThemes/Black.txt");

    tgui::Label::Ptr btntooltip = UIThemePtr->load("ToolTip");
    btntooltip->setFont(GUI->getFont());
    btntooltip->setText("tooltip");
    btntooltip->setTextSize(12);
  }

  void Editor::BindEditorMethods(chaiscript::ModulePtr mptr)
  {
    GenericActor::BindScriptMethods(mptr);

    //bind the method that allows a message to pop up on screen
    
    mptr->add(chaiscript::fun(&MessageAlert), "ShowAlertMessage");
  }

  void Editor::MenuBarItemSelected(std::vector<sf::String> vec)
  {
    MenuBar->moveToFront();
    if (vec[0].toAnsiString() == "file") {
      //do "file" stuff
      if (vec[1].toAnsiString() == "exit")
        ShutDownEditor();
      else if (vec[1].toAnsiString() == "new project")
        OpenProjectCreator();
    }
    else if (vec[0].toAnsiString() == "edit") {
      //do edit stuff
      if (vec[1].toAnsiString() == "tiles")
        EditTilesWindow->Open();
    }
  }

  void Editor::ShutDownEditor()
  {
    FlagForClose = true;
  }

  void Editor::OpenTilesheetViewer()
  {
  }

  void Editor::OpenProjectCreator()
  {
    ProjectCreator = std::make_shared<NewProjectCreator>();
    ProjectCreator->Open(UIThemePtr);
  }

  void Editor::SelectLevelTab()
  {
    LevelPanel->setPosition({ WindowSize.x - 300.f, MenuBar->getSize().y });
    LevelPanel->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(100));
    if (TilesPanel->isVisible())
      TilesPanel->hide();
    else if (AnimationPanel->isVisible())
      AnimationPanel->hide();
    else if (GUIPanel->isVisible())
      GUIPanel->hide();
    else if (ActorsPanel->isVisible())
      ActorsPanel->hide();
    else if (MusicPanel->isVisible())
      MusicPanel->hide();
  }

  void Editor::ExpandLevelPanel()
  {
    LevelPanel->setPosition({ 300.f, MenuBar->getSize().y });
    LevelPanel->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(200));
    LevelPanelExpandButton->disconnectAll();
    LevelPanelExpandButton->connect("clicked", [this]() {this->ShrinkLevelPanel(); });
  }

  void Editor::ShrinkLevelPanel()
  {
    LevelPanel->setPosition({ WindowSize.x - 300.f, MenuBar->getSize().y });
    LevelPanel->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(200));
    LevelPanelExpandButton->disconnectAll();
    LevelPanelExpandButton->connect("clicked", [this]() {this->ExpandLevelPanel(); });
  }

  void Editor::SelectTilesTab()
  {
    TilesPanel->setPosition({ WindowSize.x - 300.f, MenuBar->getSize().y });
    TilesPanel->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(200));
    if (LevelPanel->isVisible())
      LevelPanel->hide();
    else if (AnimationPanel->isVisible())
      AnimationPanel->hide();
    else if (GUIPanel->isVisible())
      GUIPanel->hide();
    else if (ActorsPanel->isVisible())
      ActorsPanel->hide();
    else if (MusicPanel->isVisible())
      MusicPanel->hide();
  }

  void Editor::ExpandTilesPanel()
  {
    TilesPanel->setPosition({ 300.f, MenuBar->getSize().y });
    TilesPanel->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(200));
    TilesPanelExpandButton->disconnectAll();
    TilesPanelExpandButton->connect("clicked", [this]() {this->ShrinkTilesPanel(); });
  }

  void Editor::ShrinkTilesPanel()
  {
    TilesPanel->setPosition({ WindowSize.x - 300.f, MenuBar->getSize().y });
    TilesPanel->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(200));
    TilesPanelExpandButton->disconnectAll();
    TilesPanelExpandButton->connect("clicked", [this]() {this->ExpandTilesPanel(); });
  }

  void Editor::SelectAnimationTab()
  {
    AnimationPanel->setPosition({ WindowSize.x - 300.f, MenuBar->getSize().y });
    AnimationPanel->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(200));
    if (LevelPanel->isVisible())
      LevelPanel->hide();
    else if (TilesPanel->isVisible())
      TilesPanel->hide();
    else if (GUIPanel->isVisible())
      GUIPanel->hide();
    else if (ActorsPanel->isVisible())
      ActorsPanel->hide();
    else if (MusicPanel->isVisible())
      MusicPanel->hide();
  }

  void Editor::ExpandAnimationPanel()
  {
    AnimationPanel->setPosition({ 300.f, MenuBar->getSize().y });
    AnimationPanel->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(200));
    AnimationPanelExpandButton->disconnectAll();
    AnimationPanelExpandButton->connect("clicked", [this]() {this->ShrinkAnimationPanel(); });
  }

  void Editor::ShrinkAnimationPanel()
  {
    AnimationPanel->setPosition({ WindowSize.x - 300.f, MenuBar->getSize().y });
    AnimationPanel->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(200));
    AnimationPanelExpandButton->disconnectAll();
    AnimationPanelExpandButton->connect("clicked", [this]() {this->ExpandAnimationPanel(); });
  }

  void Editor::SelectGUITab()
  {
    GUIPanel->setPosition({ WindowSize.x - 300.f, MenuBar->getSize().y });
    GUIPanel->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(200));
    if (AnimationPanel->isVisible())
      AnimationPanel->hide();
    else if (TilesPanel->isVisible())
      TilesPanel->hide();
    else if (LevelPanel->isVisible())
      LevelPanel->hide();
    else if (ActorsPanel->isVisible())
      ActorsPanel->hide();
    else if (MusicPanel->isVisible())
      MusicPanel->hide();
  }

  void Editor::ExpandGUIPanel()
  {
    GUIPanel->setPosition({ 300.f, MenuBar->getSize().y });
    GUIPanel->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(200));
    GUIPanelExpandButton->disconnectAll();
    GUIPanelExpandButton->connect("clicked", [this]() {this->ShrinkGUIPanel(); });
  }

  void Editor::ShrinkGUIPanel()
  {
    GUIPanel->setPosition({ WindowSize.x - 300.f, MenuBar->getSize().y });
    GUIPanel->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(200));
    GUIPanelExpandButton->disconnectAll();
    GUIPanelExpandButton->connect("clicked", [this]() {this->ExpandGUIPanel(); });
  }

  void Editor::SelectActorsTab()
  {
    ActorsPanel->setPosition({ WindowSize.x - 300.f, MenuBar->getSize().y });
    ActorsPanel->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(200));
    if (AnimationPanel->isVisible())
      AnimationPanel->hide();
    else if (TilesPanel->isVisible())
      TilesPanel->hide();
    else if (GUIPanel->isVisible())
      GUIPanel->hide();
    else if (LevelPanel->isVisible())
      LevelPanel->hide();
    else if (MusicPanel->isVisible())
      MusicPanel->hide();
  }

  void Editor::ExpandActorsPanel()
  {
    ActorsPanel->setPosition({ 300.f, MenuBar->getSize().y });
    ActorsPanel->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(200));
    ActorsPanelExpandButton->disconnectAll();
    ActorsPanelExpandButton->connect("clicked", [this]() {this->ShrinkActorsPanel(); });
  }

  void Editor::ShrinkActorsPanel()
  {
    ActorsPanel->setPosition({ WindowSize.x - 300.f, MenuBar->getSize().y });
    ActorsPanel->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(200));
    ActorsPanelExpandButton->disconnectAll();
    ActorsPanelExpandButton->connect("clicked", [this]() {this->ExpandActorsPanel(); });
  }

  void Editor::SelectMusicTab()
  {
    MusicPanel->setPosition({ WindowSize.x - 300.f, MenuBar->getSize().y });
    MusicPanel->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(200));
    if (AnimationPanel->isVisible())
      AnimationPanel->hide();
    else if (TilesPanel->isVisible())
      TilesPanel->hide();
    else if (GUIPanel->isVisible())
      GUIPanel->hide();
    else if (ActorsPanel->isVisible())
      ActorsPanel->hide();
    else if (LevelPanel->isVisible())
      LevelPanel->hide();
  }

  void Editor::ExpandMusicPanel()
  {
    MusicPanel->setPosition({ 300.f, MenuBar->getSize().y });
    MusicPanel->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(200));
    MusicPanelExpandButton->disconnectAll();
    MusicPanelExpandButton->connect("clicked", [this]() {this->ShrinkMusicPanel(); });
  }

  void Editor::ShrinkMusicPanel()
  {
    MusicPanel->setPosition({ WindowSize.x - 300.f, MenuBar->getSize().y });
    MusicPanel->showWithEffect(tgui::ShowAnimationType::Fade, sf::milliseconds(200));
    MusicPanelExpandButton->disconnectAll();
    MusicPanelExpandButton->connect("clicked", [this]() {this->ExpandMusicPanel(); });
  }

  void Editor::HideSideTabPanel()
  {
    
  }


}
