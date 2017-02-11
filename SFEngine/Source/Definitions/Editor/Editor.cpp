#include "../../Headers/Engine/Editor.h"
#include "../../Headers/UI/Theme.h"
#include "../../Headers/UI/UICreationMacros.h"
#include "../../Headers/UI/UIIconSheet.h"
#include "../../Headers/Level/Level.h"

namespace Engine
{

  bool FlagForClose = false;

  Editor::Editor()
  {
    std::cerr << "Creating editor script engine" << std::endl;
    EditorScriptEngine = new chaiscript::ChaiScript(chaiscript::Std_Lib::library());
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

  }

  Editor::~Editor()
  {
    //TestMenu->Close();
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
  }

  void Editor::MenuBarItemSelected(std::vector<sf::String> vec)
  {
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


}
