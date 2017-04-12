#include "../../Headers/Engine/Engine.h"
#include "../../../ThirdParty/chaiscript/chaiscript_defines.hpp"
#include "../../../ThirdParty/chaiscript/chaiscript.hpp"
#include "../../../ThirdParty/chaiscript/chaiscript_stdlib.hpp"
#include "../../../ThirdParty/chaiscript/chaiscript_stdlib.hpp"
#include "../../../../Projects/TestProject/Classes/Levels/OakTree.h"
#include "../../../../Projects/PuzzleDemo/Classes/Level1.h"
#include "../../../../Projects/PuzzleDemo/Classes/StartupLevel.h"

namespace Engine
{

  void SFEngine::InitRenderWindow()
  {
    sf::ContextSettings csettings;
   
    csettings.antialiasingLevel = 8;
    if (currentRenderWindow)
      delete currentRenderWindow;

#ifdef WITH_EDITOR
    Window = new sf::RenderWindow(sf::VideoMode(1700, 900), "SFEngine Editor", sf::Style::None | sf::Style::Titlebar, csettings);
    WindowSize = static_cast<sf::Vector2f>(Window->getSize());
#else
    Window = new sf::RenderWindow(sf::VideoMode(EngineConfig.Window_v2fWindowSize.x, EngineConfig.Window_v2fWindowSize.y), "SFEngine V0.1.1", sf::Style::Default, ContextSettings);
    WindowSize = { EngineConfig.Window_v2fWindowSize.x, EngineConfig.Window_v2fWindowSize.y };
#endif
    MaximumWindowView = Window->getDefaultView();
    Window->setKeyRepeatEnabled(false);
    Window->setVerticalSyncEnabled(false);
    currentRenderWindow = Window;
    CurrentEngine = this;

    //RenderSettings.texture = new sf::RenderTexture;
    //RenderSettings.texture->create(EngineConfig.Window_v2fWindowSize.x, EngineConfig.Window_v2fWindowSize.y);
    //RenderSettings.texture->setActive(true);

    FragmentShader = new sf::Shader;
    VertexShader = new sf::Shader;
    if (!FragmentShader->loadFromFile("./SFEngine/Source/CoreFragmentShader.fsh", sf::Shader::Fragment)) {
      std::cerr << "Failed to load fragment shader from file" << std::endl;
    }
    if (!VertexShader->loadFromFile("./SFEngine/Source/CoreVertexShader.vsh", sf::Shader::Vertex)) {
      std::cerr << "Failed to load vertex shader from file" << std::endl;
    }

    RenderStates.blendMode = sf::BlendAdd;
    Render::__Set__Core__Shaders(FragmentShader, VertexShader);
    Render::__Set__Render__States(RenderStates);
    Render::__Set__Render__Settings(RenderSettings);

    Render::__Set__Window(Window);
    Window->clear(sf::Color::Black);
    Window->display();
  }

  UINT32 SFEngine::Startup()
  {
    if (!sf::Shader::isAvailable()) {
      return(GL_NO_SHADERS);
    }
    Handler.BindCallback(Events::GainedFocus,
                         [this]() {this->HandleWindowGainedFocus(); });

    Handler.BindCallback(Events::LostFocus,
                         [this]() {this->HandleWindowLostFocus(); });

    Handler.BindCallback(Events::WindowClosed,
                         [this]() {this->HandleWindowClosed(); });

    Handler.BindCallback(Events::WindowResized,
                         [this]() {this->HandleWindowResized(); });

    Handler.BindCallback(Events::MouseDown,
                         [this](const sf::Vector2i &i, const sf::Mouse::Button &b) {this->HandleMousePress(i, b); });

    Handler.BindCallback(Events::MouseReleased,
                         [this](const sf::Vector2i &i, const sf::Mouse::Button &b) {this->HandleMouseRelease(i, b); });

    Handler.BindCallback(Events::MouseMoved,
                         [this](const sf::Vector2i &i) {this->HandleMouseMovement(i); });

    Handler.BindCallback(Events::KeyPressed,
                         [this](const sf::Keyboard::Key &k) {this->HandleKeyPress(k); });

    Handler.BindCallback(Events::KeyReleased,
                         [this](const sf::Keyboard::Key &k) {this->HandleKeyRelease(k); });

    Handler.BindTextEnterHandler([this](const sf::Uint32 &unicode) {this->HandleTextEntered(unicode); });

    std::ifstream _IN("SFEngine/Config/Engine.ini");
    sf::Vector2u lSize;
    sf::Vector2f gridSpac;
    sf::FloatRect initView;
    bool showgrid;
    if (_IN.fail()) {
      std::cerr << "Failed to open configuration file: \"Engine.ini\"" << std::endl;

    }
    else {
      EngineConfig.Window_v2fWindowSize = Util::GetVec2fConfig("Window", "WindowSize", sf::Vector2f(800, 800), "Engine.ini", _IN);
      //WindowSize = EngineConfig.Window_v2fWindowSize;
      InitialLevel = Util::GetStringConfig("Game", "InitialLevel", "test.map", "Engine.ini", _IN);
      EngineRenderSettings.Brightness = Util::GetFloatConfig("Render", "Brightness", 1, "Engine.ini", _IN);
      EngineRenderSettings.Contrast = Util::GetFloatConfig("Render", "Contrast", 0.5, "Engine.ini", _IN);
      EngineRenderSettings.Gamma = Util::GetFloatConfig("Render", "Gamma", 0.5, "Engine.ini", _IN);
      EngineRenderSettings.PostProcess = Util::GetUnsignedIntConfig("Render", "PostProcess", 0, "Engine.ini", _IN);
      EngineRenderSettings.BGClearColor.r = Util::GetUnsignedIntConfig("Render", "ClearColor.r", 0, "Engine.ini", _IN);
      EngineRenderSettings.BGClearColor.g = Util::GetUnsignedIntConfig("Render", "ClearColor.g", 0, "Engine.ini", _IN);
      EngineRenderSettings.BGClearColor.b = Util::GetUnsignedIntConfig("Render", "ClearColor.b", 0, "Engine.ini", _IN);

      ContextSettings.antialiasingLevel = Util::GetUnsignedIntConfig("Render", "uiAALevel", 1, "Engine.ini", _IN);
      ContextSettings.depthBits = Util::GetUnsignedIntConfig("Render", "uiDepthBits", 0, "Engine.ini", _IN);
      ContextSettings.sRgbCapable = Util::GetBooleanConfig("Render", "bSRGBCapable", true, "Engine.ini", _IN);
      ContextSettings.stencilBits = Util::GetUnsignedIntConfig("Render", "uiStencilBits", 0, "Engine.ini", _IN);

      //Misleading variable name, this is actually the file path to the config file for the main entry level
      //EntryLevelName = Util::GetStringConfig("Game", "EntryLevel", "", "Engine.ini", _IN);
      //if (EntryLevelName == "") {
      //  //No entry level found!!
      //  ERR_STREAM << "No entry level defined!" << std::endl;
      //  CurrentLevel = nullptr;
      //}
      //else {
      //  lSize.x = Util::GetFloatConfig("Game", "SizeX", 0.f, "Engine.ini", _IN);
      //  lSize.y = Util::GetFloatConfig("Game", "SizeY", 0.f, "Engine.ini", _IN);
      //  showgrid = Util::GetBooleanConfig("Game", "ShowGrid", false, "Engine.ini", _IN);
      //  gridSpac = Util::GetVec2fConfig("Game", "GridSpacing", sf::Vector2f(0, 0), "Engine.ini", _IN);
      //  initView = Util::GetFloatRectConfig("Game", "InitialView", sf::FloatRect(0, 0, 0, 0), "Engine.ini", _IN);

      //  Levels["Main"] = std::make_shared<BasicLevel>(lSize, initView, showgrid, gridSpac);
      //  Levels["Main"]->LoadLevel(EntryLevelName);
      //  CurrentLevel = Levels["Main"].get();
      //}
      _IN.clear();
      _IN.close();
    }

    InitRenderWindow();
    std::cerr << "Initialized RenderWindow" << std::endl;
    //Create the GUI window immediately
    GUI = std::make_shared<tgui::Gui>(*currentRenderWindow);

    tgui::ToolTip::setTimeToDisplay(sf::milliseconds(300));


    if (!EngineLogoTexture.loadFromFile("./SFEngine/Samples/Logos/SFEngineLogoLarge.png")) {
      std::cerr << "Unable to load EngineLogo texture" << std::endl;
    }
    else {
      EngineLogoSprite.setTexture(EngineLogoTexture);
      Window->draw(EngineLogoSprite);
    }

    if (!EngineLoadingFont.loadFromFile("./SFEngine/Samples/Fonts/PressStart2P.ttf")) {
      std::cerr << "Unable to load EngineLoadingFont" << std::endl;
    }
    else {
      EngineLoadingText.setFont(EngineLoadingFont);
      EngineLoadingText.setPosition(sf::Vector2f(100, 650));
      EngineLoadingText.setFillColor(sf::Color::White);
      EngineLoadingText.setCharacterSize(20);
      Window->draw(EngineLoadingText);
    }
    Window->display();

    //Instantiate the scripting engine
    EngineLoadingText.setString("Initializing Chaiscipt Engine...");
    Window->draw(EngineLogoSprite);
    Window->draw(EngineLoadingText);
    Window->display();

    ScriptEngine = new chaiscript::ChaiScript({}, { "./Projects/TestProject/Scripts/" }, { chaiscript::Options::External_Scripts, chaiscript::Options::Load_Modules });

    //Add the engine class to the script engine
    chaiscript::ModulePtr __mptr(new chaiscript::Module);
    GenericActor::BindScriptMethods(__mptr);

    //Bind the exposed engine apis to chaiscript
    EngineLoadingText.setString("Binding APIs to Chaiscript...");
    Window->draw(EngineLogoSprite);
    Window->draw(EngineLoadingText);
    Window->display();

    BindScripts();

    Window->clear();
    EngineLoadingText.setString("Loading...");
    Window->draw(EngineLogoSprite);
    Window->draw(EngineLoadingText);
    Window->display();

    std::string str{ "" }, str2{ "" };
    ScriptEngine->eval_file("./Game/GameSetup.chai");
    ScriptEngine->eval_file("./SFEngine/Samples/Scripts/EngineEventTests.chai");
    try
    {
      str = (*ScriptEngine).eval<std::string>("InitialGameLevel()");
      str2 = (*ScriptEngine).eval<std::string>("SetupFile()");

      std::cerr << "\n\n------------------InitialGameLevel: " << str << std::endl;
      std::cerr << "\n\n------------------Setup File: " << str2 << std::endl;
    }
    catch (chaiscript::exception::eval_error &e)
    {
      std::cerr << "Script execution error: " << e.what() << std::endl;
    }
    Window->clear();

    std::shared_ptr<::StartupLevel> EngineStartupLevel = std::make_shared<::StartupLevel>();
    Levels["Main"] = EngineStartupLevel;

    EngineStartupLevel->SetNextLevel(std::make_shared<::Level1>());    
    
    ScriptEngine->add(chaiscript::fun(&MessageAlert), "Alert");
    ScriptEngine->add(chaiscript::fun(&Confirm), "Confirm");    
    return GameLoop();
  }
}