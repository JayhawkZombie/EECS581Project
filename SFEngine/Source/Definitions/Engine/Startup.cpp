#include "../../Headers/Engine/Engine.h"

namespace Engine
{

  void SFEngine::InitRenderWindow()
  {
    sf::ContextSettings csettings;
   
    csettings.antialiasingLevel = 8;
    
#ifdef WITH_EDITOR
    Window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "SFEngine Editor", sf::Style::Fullscreen | sf::Style::Titlebar, csettings);
    WindowSize = static_cast<sf::Vector2f>(Window->getSize());
#else
    Window = new sf::RenderWindow(sf::VideoMode(EngineConfig.Window_v2fWindowSize.x, EngineConfig.Window_v2fWindowSize.y), "SFEngine V0.1.1", sf::Style::Default, ContextSettings);
    WindowSize = { EngineConfig.Window_v2fWindowSize.x, EngineConfig.Window_v2fWindowSize.y };
#endif
    MaximumWindowView = Window->getDefaultView();
    Window->setKeyRepeatEnabled(true);
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

    std::cerr << "Core profile settings: " << Window->getSettings().majorVersion << "." << Window->getSettings().minorVersion << std::endl;
    std::cerr << "Created Window Size  : " << Window->getSize().x << ", " << Window->getSize().y << std::endl;
  }

  UINT32 SFEngine::Startup()
  {
    if (!sf::Shader::isAvailable()) {
      return(GL_NO_SHADERS);
    }

    std::cerr << "Binding callbacks" << std::endl;
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
    if (_IN.fail()) {
      std::cerr << "Failed to open configuration file: \"Engine.ini\"" << std::endl;

    }
    else {
      EngineConfig.Window_v2fWindowSize = Util::GetVec2fConfig("Window", "WindowSize", sf::Vector2f(800, 800), "Engine.ini", _IN);
      //WindowSize = EngineConfig.Window_v2fWindowSize;
      InitialLevel = Util::GetStringConfig("Game", "InitialLevel", "test.map", "Engine.ini", _IN);
      RenderSettings.Brightness = Util::GetFloatConfig("Render", "Brightness", 1, "Engine.ini", _IN);
      RenderSettings.Contrast = Util::GetFloatConfig("Render", "Contrast", 0.5, "Engine.ini", _IN);
      RenderSettings.Gamma = Util::GetFloatConfig("Render", "Gamma", 0.5, "Engine.ini", _IN);
      RenderSettings.PostProcess = Util::GetUnsignedIntConfig("Render", "PostProcess", 0, "Engine.ini", _IN);

      ContextSettings.antialiasingLevel = Util::GetUnsignedIntConfig("Render", "uiAALevel", 1, "Engine.ini", _IN);
      ContextSettings.depthBits = Util::GetUnsignedIntConfig("Render", "uiDepthBits", 0, "Engine.ini", _IN);
      ContextSettings.sRgbCapable = Util::GetBooleanConfig("Render", "bSRGBCapable", true, "Engine.ini", _IN);
      ContextSettings.stencilBits = Util::GetUnsignedIntConfig("Render", "uiStencilBits", 0, "Engine.ini", _IN);

      //see if there are any assets that need to be cooked (will not be done like this forever, only for now)
      bool needconvert = Util::GetBooleanConfig("Etc", "AssetsToCovert", false, "Engine.ini", _IN);
      std::cerr << "Need to convert assets? " << (needconvert ? "Yes" : "No") << std::endl;
      std::string assets;
      if (needconvert) {
        assets = Util::GetBracedConfig("Etc", "Assets", "{}", "Engine.ini", _IN);
        assets.erase(assets.begin() + 0); assets.erase(assets.end() - 1);

        std::vector<std::string> ToCovert;
        std::stringstream stream(assets);
        std::string holder;
        while (stream >> holder)
          ToCovert.push_back(holder);

        for (auto & file : ToCovert)
          Convert::Level(file);
      }

      _IN.clear();
      _IN.close();
    }

    InitRenderWindow();
    std::cerr << "Initialized RenderWindow" << std::endl;

    if (!EngineLogoTexture.loadFromFile("./SFEngine/Samples/Textures/Logos/SFEngineLogoLarge_ExtraFlame_Analogized.png")) {
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

    ScriptEngine = new chaiscript::ChaiScript(chaiscript::Std_Lib::library());

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
    return GameLoop();
  }
}