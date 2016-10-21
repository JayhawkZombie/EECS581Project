#ifndef SFENGINE_LEVEL_EVENT_SEQUENCES_H
#define SFENGINE_LEVEL_EVENT_SEQUENCES_H

#include "../Events/EventSequence.h"
#include "../Events/EventHandler.h"

namespace Engine
{
  //Simulate user input
  struct UserInputEvent : public GenericEvent {
    UserInputEvent(const Events &e, const double &duration) : TriggerEvent(e), GenericEvent(duration) {}
    UserInputEvent(const UserInputEvent &e)
    {
      Trigger = e.Trigger;
      TotalDuration = e.TotalDuration;
      Repeat = e.Repeat;
      TriggerEvent = e.TriggerEvent;
    }
    Events TriggerEvent;
  };

  //Simulate user pressing a key
  struct UserKeyPressEvent : public UserInputEvent {
    UserKeyPressEvent(sf::Keyboard::Key k, std::function<void(sf::Keyboard::Key k)> &cb, const double &duration)
      : _key(k), UserInputEvent(Events::KeyPressed, duration) 
    {
      Trigger = [&]()->void {cb(_key); };
    }
    UserKeyPressEvent(const UserKeyPressEvent &e) : UserInputEvent(e.TriggerEvent, e.TotalDuration)
    {
      Trigger = e.Trigger;
      TotalDuration = e.TotalDuration;
      TriggerEvent = e.TriggerEvent;
      Repeat = e.Repeat;
      _key = e._key;
    }


    sf::Keyboard::Key _key;
  };

  //Simulate a user releasing a key
  struct UserKeyReleaseEvent : public UserInputEvent {
    UserKeyReleaseEvent(sf::Keyboard::Key k, std::function<void(sf::Keyboard::Key k)> cb, const double &duration)
      : _key(k), UserInputEvent(Events::KeyReleased, duration)
    {
      Trigger = [=]()->void {cb(_key); };
    }
    UserKeyReleaseEvent(const UserKeyReleaseEvent &e)
      : UserInputEvent(e.TriggerEvent, e.TotalDuration)
    {
      Trigger = e.Trigger;
      TotalDuration = e.TotalDuration;
      TriggerEvent = e.TriggerEvent;
      Repeat = e.Repeat;
      _key = e._key;
    }


    sf::Keyboard::Key _key;
  };

  //Simulate user pressing a mouse button
  struct UserMousePressEvent : public UserInputEvent
  {
    UserMousePressEvent(const sf::Mouse::Button &b, const sf::Vector2i &p,
                        std::function<void(const sf::Vector2i &, const sf::Mouse::Button &)> cb, const double &duration)
      : _button(b), _pos(p), UserInputEvent(Events::MouseDown, duration)
    {
      Trigger = [=]()->void {cb(_pos, _button); };
    }
    UserMousePressEvent(const UserMousePressEvent &e)
      : UserInputEvent(e.TriggerEvent, e.TotalDuration)
    {
      Trigger = e.Trigger;
      TotalDuration = e.TotalDuration;
      TriggerEvent = e.TriggerEvent;
      Repeat = e.Repeat;
      _pos = e._pos;
      _button = e._button;
    }

    sf::Vector2i _pos;
    sf::Mouse::Button _button;
  };

  //Simulate user releasing a mouse button
  struct UserMouseReleaseEvent : public UserInputEvent
  {
    UserMouseReleaseEvent(const sf::Mouse::Button &b, const sf::Vector2i &p,
                          std::function<void(const sf::Vector2i &, const sf::Mouse::Button &)> cb, const double &duration)
      : _pos(p), _button(b), UserInputEvent(Events::MouseReleased, duration)
    {
      Trigger = [=]()->void {cb(_pos, _button); };
    }
    UserMouseReleaseEvent(const UserMouseReleaseEvent &e)
      : UserInputEvent(e.TriggerEvent, e.TotalDuration)
    {
      Trigger = e.Trigger; 
      TotalDuration = e.TotalDuration;
      TriggerEvent = e.TriggerEvent;
      Repeat = e.Repeat;
      _pos = e._pos;
      _button = e._button;
    }

    sf::Vector2i _pos;
    sf::Mouse::Button _button;
  };

}

#endif
