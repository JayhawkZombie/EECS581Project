#ifndef SFENGINE_EVENT_HANDLER_H
#define SFENGINE_EVENT_HANDLER_H

#include "../BasicIncludes.h"

namespace Engine
{
  
  /**
   * A class to which event handling can be delegated
   * All event handlers are bound to no_action methods at compile time
   * So it will always be safe to call event handlers
   */

  enum class Events
  {
      MouseDown
    , MouseReleased
    , MouseOver
    , MouseExit
    , MouseMoved
    , KeyPressed
    , KeyReleased
    , TextEntered
    , WindowResized
    , LostFocus
    , GainedFocus
    , WindowClosed
    , MouseScrolled
  };

  class EventHandler
  {
  public:
    friend class BaseEngineInterface;

    EventHandler();
    EventHandler(const EventHandler &);
    ~EventHandler();

    void BindCallback(const Events &type, std::function<void(const sf::Vector2i &)> ftn);
    void BindCallback(const Events &type, std::function<void(const sf::Vector2i &, const sf::Mouse::Button &)> ftn);
    void BindCallback(const Events &type, std::function<void(const sf::Keyboard::Key &)> ftn);
    void BindCallback(const Events &type, std::function<void(void)> ftn);
    void BindTextEnterHandler(std::function<void(const sf::Uint32 &)> ftn);

    bool PollEvents(sf::RenderWindow *win, sf::Event &evnt, const bool &makeCallbacks);

    void HandleMouseMovement(const sf::Vector2i &v);
    void HandleMouseOver(const sf::Vector2i &v);
    void HandleMouseExit(const sf::Vector2i &v);
    void HandleMousePress(const sf::Vector2i &v, const sf::Mouse::Button &b);
    void HandleMouseRelease(const sf::Vector2i &v, const sf::Mouse::Button &b);
    void HandleMouseScroll(const sf::Vector2i &v);
    void HandleKeyPress(const sf::Keyboard::Key &k);
    void HandleKeyRelease(const sf::Keyboard::Key &k);
    void HandleTextEntered(const sf::Keyboard::Key &k);

  protected:
    sf::Vector2i v2iMousePosArg;
    sf::Mouse::Button enMouseButtonArg;
    sf::Keyboard::Key enKeyboardArg;

    std::function<void(const sf::Vector2i &)> ftnCallback_MouseMovement;

    std::function<void(const sf::Vector2i &)> ftnCallback_MouseOver;

    std::function<void(const sf::Vector2i &)> ftnCallback_MouseExit;
    std::function<void(const sf::Vector2i &, const sf::Mouse::Button &)> ftnCallback_MousePress;
    std::function<void(const sf::Vector2i &, const sf::Mouse::Button &)> ftnCallback_MouseRelease;
    std::function<void(const sf::Vector2i &)> ftnCallback_MouseScroll;
    std::function<void(const sf::Keyboard::Key &)> ftnCallback_KeyPress;
    std::function<void(const sf::Keyboard::Key &)> ftnCallback_KeyRelease;
    std::function<void(const sf::Uint32 &)> ftnCallback_TextEntered;

    std::function<void(void)> ftnCallback_WindowClosed;
    std::function<void(void)> ftnCallback_WindowResized;
  };
}

#endif
