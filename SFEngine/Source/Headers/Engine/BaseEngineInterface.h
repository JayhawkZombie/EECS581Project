#ifndef SFENGINE_BASE_ENGINE_INTERFACE_H
#define SFENGINE_BASE_ENGINE_INTERFACE_H

#include "../BasicIncludes.h"
#include "../Events/EventHandler.h"

namespace Engine
{
  class BaseEngineInterface
  {
  public:
    BaseEngineInterface();
    BaseEngineInterface(const BaseEngineInterface &b);
    ~BaseEngineInterface();

    virtual void TickUpdate(const double &delta) = 0;

    virtual void Render() = 0;

    virtual void OnShutDown() = 0;

    EventHandler Handler;

  protected:
    std::function<void(void)> Callback_HandleWindowClosed;
    std::function<void(void)> Callback_HandleWindowResized;
    std::function<void(void)> Callback_HandleWindowLostFocus;
    std::function<void(void)> Callback_HandleWindowGainedFocus;
    std::function<void(const sf::Vector2i &v)> Callback_HandleMouseMovement;
    std::function<void(const sf::Vector2i &v, const sf::Mouse::Button &b)> Callback_HandleMousePress;
    std::function<void(const sf::Vector2i &v, const sf::Mouse::Button &b)> Callback_HandleMouseRelease;
    std::function<void(const sf::Keyboard::Key &k)> Callback_HandleKeyPress;
    std::function<void(const sf::Keyboard::Key &k)> Callback_HandleKeyRelease;

  private:
    static void NO_ACTION(BaseEngineInterface *item, const sf::Vector2i &i);
    static void NO_ACTION(BaseEngineInterface *item, const sf::Mouse::Button &);
    static void NO_ACTION(BaseEngineInterface *item, const sf::Keyboard::Key &);
    static void NO_ACTION(BaseEngineInterface *item);

  };
}

#endif