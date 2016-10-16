#include "../../Headers/Engine/Engine.h"

namespace Engine
{
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

    std::ifstream IN("SFEngine/Config/Engine.ini");
    if (IN.fail()) {
      std::cerr << "Failed to open configuration file: \"Engine.ini\"" << std::endl;

    }
    else {
      EngineConfig.Window_v2fWindowSize = Util::GetVec2fConfig("Window", "WindowSize", sf::Vector2f(800, 800), "Engine.ini", IN);
      WindowSize = EngineConfig.Window_v2fWindowSize;
      std::string bracetxt = Util::GetBracedConfig("Tests", "SampleBrace", "{}", "Engine.ini", IN);
      std::cerr << "\n\nBracedText\"" << bracetxt << "\"" << std::endl;
      auto pair = Util::GetStringPair("Tests", "SamplePair", { "", "" }, "Engine.ini", IN);
      std::cerr << "Pair.first = \"" << pair.first << "\", .second = \"" << pair.second << "\"" << std::endl;
      InitialLevel = Util::GetStringConfig("Game", "InitialLevel", "test.map", "Engine.ini", IN);
      std::cout << "Initial Level: " << InitialLevel << std::endl;
      RenderSettings.Brightness = Util::GetFloatConfig("Render", "Brightness", 0, "Engine.ini", IN);
      RenderSettings.Contrast = Util::GetFloatConfig("Render", "Contrast", 0, "Engine.ini", IN);
      RenderSettings.Gamma = Util::GetFloatConfig("Render", "Gamma", 0.5, "Engine.ini", IN);
      RenderSettings.PostProcess = Util::GetUnsignedIntConfig("Render", "PostProcess", 0, "Engine.ini", IN);
      IN.clear();
      IN.close();
    }


    std::cerr << "Starting resource manager" << std::endl;
    ResourceManager = std::shared_ptr<Resource::ResourceManager>(new Resource::ResourceManager);
    ResourceManager->Start();

    //Now begin loading the level
    Levels.push_back(std::make_shared<Level>(*new Level));
    Levels[0]->LoadLevel(InitialLevel);

    return GameLoop();
  }
}
