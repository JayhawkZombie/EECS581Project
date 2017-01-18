#include "../../Headers/Events/EventHandler.h"

namespace Engine
{
  EventHandler::EventHandler()
  {
    ftnCallback_KeyPress = [this](const sf::Keyboard::Key &k) {};
    ftnCallback_KeyRelease = [this](const sf::Keyboard::Key &k) {};
    ftnCallback_TextEntered = [this](const sf::Keyboard::Key &k) {};
    ftnCallback_MouseExit = [this](const sf::Vector2i &v) {};
    ftnCallback_MouseOver = [this](const sf::Vector2i &v) {};
    ftnCallback_MouseMovement = [this](const sf::Vector2i &v) {};
    ftnCallback_MousePress = [this](const sf::Vector2i &v, const sf::Mouse::Button &b) {};
    ftnCallback_MouseRelease = [this](const sf::Vector2i &v, const sf::Mouse::Button &b) {};
    ftnCallback_MouseScroll = [this](const sf::Vector2i &v) {};
    ftnCallback_WindowClosed = [this]() {};
    ftnCallback_WindowResized = [this]() {}; 
  }

  EventHandler::~EventHandler()
  {

  }

  void EventHandler::HandleMouseMovement(const sf::Vector2i &v)
  {
    ftnCallback_MouseMovement(v);
  }

  void EventHandler::HandleMouseOver(const sf::Vector2i &v)
  {
    ftnCallback_MouseOver(v);
  }

  void EventHandler::HandleMouseExit(const sf::Vector2i &v)
  {
    ftnCallback_MouseExit(v);
  }

  void EventHandler::HandleMousePress(const sf::Vector2i &v, const sf::Mouse::Button &b)
  {
    ftnCallback_MousePress(v, b);
  }

  void EventHandler::HandleMouseRelease(const sf::Vector2i &v, const sf::Mouse::Button &b)
  {
    ftnCallback_MouseRelease(v, b);
  }

  void EventHandler::HandleMouseScroll(const sf::Vector2i &v)
  {
    ftnCallback_MouseScroll(v);
  }

  void EventHandler::HandleKeyPress(const sf::Keyboard::Key &k)
  {
    ftnCallback_KeyPress(k);
  }

  void EventHandler::HandleKeyRelease(const sf::Keyboard::Key &k)
  {
    ftnCallback_KeyRelease(k);
  }

  void EventHandler::HandleTextEntered(const sf::Keyboard::Key &k)
  {
    ftnCallback_TextEntered(k);
  }

  void EventHandler::BindCallback(const Events &type, std::function<void(const sf::Vector2i &)> ftn)
  {
    switch (type)
    {
      case Events::MouseOver:
        ftnCallback_MouseOver = std::bind(ftn, std::placeholders::_1); break;
      case Events::MouseExit:
        ftnCallback_MouseExit = std::bind(ftn, std::placeholders::_1); break;
      case Events::MouseMoved:
        ftnCallback_MouseMovement = std::bind(ftn, std::placeholders::_1); break;
    }
  }

  void EventHandler::BindCallback(const Events &type, std::function<void(const sf::Vector2i &, const sf::Mouse::Button &)> ftn)
  {
    switch (type)
    {
      case Events::MouseDown:
        ftnCallback_MousePress = std::bind(ftn, std::placeholders::_1, std::placeholders::_2); break;
      case Events::MouseReleased:
        ftnCallback_MouseRelease = std::bind(ftn, std::placeholders::_1, std::placeholders::_2); break;
    }
  }

  void EventHandler::BindCallback(const Events &type, std::function<void(const sf::Keyboard::Key &)> ftn)
  {
    switch (type)
    {
      case Events::KeyPressed:
        ftnCallback_KeyPress = std::bind(ftn, std::placeholders::_1); break;
      case Events::KeyReleased:
        ftnCallback_KeyRelease = std::bind(ftn, std::placeholders::_1); break;
    }
  }

  void EventHandler::BindCallback(const Events &type, std::function<void(void)> ftn)
  {
    switch (type)
    {
      case Events::WindowClosed:
        ftnCallback_WindowClosed = std::bind(ftn); break;
      case Events::WindowResized:
        ftnCallback_WindowResized = std::bind(ftn); break;
    }
  }

  bool EventHandler::PollEvents(sf::RenderWindow *win, sf::Event &evnt, const bool &makeCallbacks)
  {
    v2iMousePosArg = sf::Mouse::getPosition(*currentRenderWindow);
    while (win->pollEvent(evnt)) {
      if (makeCallbacks) {
        switch (evnt.type)
        {
          case sf::Event::EventType::Closed:
            ftnCallback_WindowClosed(); return true;
          case sf::Event::MouseButtonPressed:
            ftnCallback_MousePress(v2iMousePosArg, evnt.mouseButton.button); break;
          case sf::Event::MouseButtonReleased:
            ftnCallback_MouseRelease(v2iMousePosArg, evnt.mouseButton.button); break;
          case sf::Event::MouseMoved:
            ftnCallback_MouseMovement(v2iMousePosArg); break;
          case sf::Event::KeyPressed:
            ftnCallback_KeyPress(evnt.key.code); break;
          case sf::Event::KeyReleased:
            ftnCallback_KeyRelease(evnt.key.code); break;
        }
      }
    }

    return false;
  }

  EventHandler::EventHandler(const EventHandler &handler)
  {

  }
}
