#ifndef SFENGINE_ENGINE_H
#define SFENGINE_ENGINE_H

#include "Engine\BaseEngineInterface.h"
#include "Engine\EngineConfiguration.h"
#include "Engine\ReturnValues.h"
#include "Events\EventHandler.h"
#include "Level\BasicLevel.h"
#include "Logging\Logger.h"
#include "Globals\GlobalHooks.h"
#include "Events\UserEvent.h"

#include <TGUI/TGUI.hpp>

namespace Engine
{

  class SFEngine
  {
  public:
    SFEngine();
    SFEngine(const SFEngine &) = delete; //No copy constructor allowed
    SFEngine(const SFEngine &&) = delete;
    ~SFEngine();

    UINT32 Go(int argc, char **argv);
    UINT32 Init(int argc, char **argv);
    UINT32 Startup();
    void HandleEngineCrash();

    unsigned int GetCurrentFrameRate() {
      return FrameRate;
    }

    bool GetIsFramerateLimited() {
      return IsFramerateLimited;
    }

    sf::Vector2u GetCurrentWindowsize() const {
      if (Window)
        return Window->getSize();
      else
        return{ 0, 0 };
    }

  private:

    //event objects
    UserEvent UEvent;

    bool IsFramerateLimited = false;
    unsigned int FrameRate;

    void BindScripts();

    Logger EngineLogger;

    UINT32 Shutdown();
    UINT32 GameLoop();

    static bool IsKeyLeftDown();

    //chaiscript::ChaiScript *ScriptEngine;
    chaiscript::ModulePtr EngineModule;
    chaiscript::ModulePtr LevelModule;
    //Methods that we will expose to the scripting engine to change engine settings
    void SetAALevel(unsigned int level);
    void SetFramerateLimit(unsigned int level);
    void SetBrightness(unsigned int level);
    void SetGamma(unsigned int level);
    void SetTimeScale(float amount);
    void SetContrast(unsigned int level);

    void LoadLevel(std::string lvl);
    void SwitchToLevel(std::string lvl);

    sf::Sprite EngineLogoSprite;
    sf::Texture EngineLogoTexture;
    sf::Text EngineLoadingText;
    sf::Font EngineLoadingFont;

    void Render();
    void InitRenderWindow();

    sf::Shader *VertexShader;
    sf::Shader *FragmentShader;

    sf::RenderStates RenderStates;
    Render::RenderSettings RenderSettings;
    sf::ContextSettings ContextSettings;

    Config EngineConfig;

    sf::View MaximumWindowView;
    sf::RenderWindow *Window;

    EventHandler Handler;

    /**
     * Engine configuration settings
     *
     */
    std::string InitialLevel;
    //std::vector<std::shared_ptr<Level>> Levels;

    //Every method used for event handling must contain its own personal method AND
    //a function pointer bound to that method
    //so that the event handler only has to store the bound function pointer
    void HandleWindowClosed();
    std::function<void(void)> Callback_HandleWindowClosed;

    void HandleTextEntered(const sf::Uint32 &unicode);
    std::function<void(const sf::Uint32 &unicode)> Callback_HandleTextEntered;

    void HandleWindowResized();
    std::function<void(void)> Callback_HandleWindowResized;

    void HandleWindowLostFocus();
    std::function<void(void)> Callback_HandleWindowLostFocus;

    void HandleWindowGainedFocus();
    std::function<void(void)> Callback_HandleWindowGainedFocus;

    void HandleMouseMovement(const sf::Vector2i &v);
    std::function<void(const sf::Vector2i &v)> Callback_HandleMouseMovement;

    void HandleMousePress(const sf::Vector2i &v, const sf::Mouse::Button &b);
    std::function<void(const sf::Vector2i &v, const sf::Mouse::Button &b)> Callback_HandleMousePress;

    void HandleMouseRelease(const sf::Vector2i &v, const sf::Mouse::Button &b);
    std::function<void(const sf::Vector2i &v, const sf::Mouse::Button &b)> Callback_HandleMouseRelease;

    void HandleKeyPress(const sf::Keyboard::Key &k);
    std::function<void(const sf::Keyboard::Key &k)> Callback_HandleKeyPress;

    void HandleKeyRelease(const sf::Keyboard::Key &k);
    std::function<void(const sf::Keyboard::Key &k)> Callback_HandleKeyRelease;

    void HandleMouseScroll(const sf::Vector2i &v, sf::Mouse::Wheel wheel, float delta);
    std::function<void(const sf::Vector2i &v, sf::Mouse::Wheel, float delta)> Callback_MouseScrolled;
  };

}

#endif
