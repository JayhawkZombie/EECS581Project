#include "../../Headers/Engine/Engine.h"

namespace Engine
{

  void SFEngine::InitRenderWindow()
  {
    Window = new sf::RenderWindow(sf::VideoMode(EngineConfig.Window_v2fWindowSize.x, EngineConfig.Window_v2fWindowSize.y), "SFEngine V0.1.1", sf::Style::Default, ContextSettings);
    MaximumWindowView = Window->getDefaultView();
    Window->setKeyRepeatEnabled(false);
    currentRenderWindow = Window;

    RenderSettings.texture = new sf::RenderTexture;
    RenderSettings.texture->create(EngineConfig.Window_v2fWindowSize.x, EngineConfig.Window_v2fWindowSize.y);
    RenderSettings.texture->setActive(true);

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

    std::ifstream _IN("SFEngine/Config/Engine.ini");
    if (_IN.fail()) {
      std::cerr << "Failed to open configuration file: \"Engine.ini\"" << std::endl;

    }
    else {
      EngineConfig.Window_v2fWindowSize = Util::GetVec2fConfig("Window", "WindowSize", sf::Vector2f(800, 800), "Engine.ini", _IN);
      WindowSize = EngineConfig.Window_v2fWindowSize;
      std::string bracetxt = Util::GetBracedConfig("Tests", "SampleBrace", "{}", "Engine.ini", _IN);
      std::cerr << "\n\nBracedText\"" << bracetxt << "\"" << std::endl;
      auto pair = Util::GetStringPair("Tests", "SamplePair", { "", "" }, "Engine.ini", _IN);
      std::cerr << "Pair.first = \"" << pair.first << "\", .second = \"" << pair.second << "\"" << std::endl;
      InitialLevel = Util::GetStringConfig("Game", "InitialLevel", "test.map", "Engine.ini", _IN);
      std::cout << "Initial Level: " << InitialLevel << std::endl;
      RenderSettings.Brightness = Util::GetFloatConfig("Render", "Brightness", 1, "Engine.ini", _IN);
      RenderSettings.Contrast = Util::GetFloatConfig("Render", "Contrast", 0.5, "Engine.ini", _IN);
      RenderSettings.Gamma = Util::GetFloatConfig("Render", "Gamma", 0.5, "Engine.ini", _IN);
      RenderSettings.PostProcess = Util::GetUnsignedIntConfig("Render", "PostProcess", 0, "Engine.ini", _IN);

      ContextSettings.antialiasingLevel = Util::GetUnsignedIntConfig("Render", "uiAALevel", 1, "Engine.ini", _IN);
      ContextSettings.depthBits = Util::GetUnsignedIntConfig("Render", "uiDepthBits", 0, "Engine.ini", _IN);
      ContextSettings.sRgbCapable = Util::GetBooleanConfig("Render", "bSRGBCapable", true, "Engine.ini", _IN);
      ContextSettings.stencilBits = Util::GetUnsignedIntConfig("Render", "uiStencilBits", 0, "Engine.ini", _IN);

      sf::FloatRect testRect = Util::GetFloatRectConfig("Tests", "SampleRect", sf::FloatRect(), "Engine.ini", _IN);
      std::cerr << "TestRect: (" << testRect.left << ", " << testRect.top << ", " << testRect.width << ", " << testRect.height << ")" << std::endl;

      _IN.clear();
      _IN.close();
    }

    InitRenderWindow();
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
    chaiscript::utility::add_class<Engine::SFEngine>(*__mptr, "Engine",
    { chaiscript::constructor<Engine::SFEngine()>() },
    { {chaiscript::fun(static_cast<void(SFEngine::*)(unsigned int)>(&SFEngine::SetAALevel)), "SetAALevel"},
    {chaiscript::fun(static_cast<void(SFEngine::*)(unsigned int)>(&SFEngine::SetBrightness)), "SetBrightness"},
    {chaiscript::fun(static_cast<void(SFEngine::*)(unsigned int)>(&SFEngine::SetContrast)), "SetContrast"},
    {chaiscript::fun(static_cast<void(SFEngine::*)(unsigned int)>(&SFEngine::SetFramerateLimit)), "SetFramerateLimit"},
    {chaiscript::fun(static_cast<void(SFEngine::*)(unsigned int)>(&SFEngine::SetGamma)), "SetGamma"},
    {chaiscript::fun(static_cast<void(SFEngine::*)(std::string)> (&SFEngine::LoadLevel)), "LoadLevel"},
    {chaiscript::fun(static_cast<void(SFEngine::*)(std::string)>(&SFEngine::SwitchToLevel)), "SwitchToLevel"} }
    );

    //Bind the exposed engine apis to chaiscript
    EngineLoadingText.setString("Binding APIs to Chaiscript...");
    Window->draw(EngineLogoSprite);
    Window->draw(EngineLoadingText);
    Window->display();

    EngineModule = chaiscript::ModulePtr(new chaiscript::Module);
    EngineModule->add(chaiscript::fun(&SFEngine::SetBrightness, this), "SetBrightness");
    EngineModule->add(chaiscript::fun(&SFEngine::SetAALevel, this), "SetAALevel");
    EngineModule->add(chaiscript::fun(&SFEngine::SetContrast, this), "SetContrast");
    EngineModule->add(chaiscript::fun(&SFEngine::SetGamma, this), "SetGamma");

    ScriptEngine->add(EngineModule);

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

    return GameLoop();
  }
}
