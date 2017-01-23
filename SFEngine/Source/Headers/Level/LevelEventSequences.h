#ifndef SFENGINE_LEVEL_EVENT_SEQUENCES_H
#define SFENGINE_LEVEL_EVENT_SEQUENCES_H

#include "../Events/EventSequence.h"
#include "../Events/EventHandler.h"

namespace Engine
{

  //Simulate user pressing a key
  struct UserKeyPressEvent : public GenericEvent {
    UserKeyPressEvent(sf::Keyboard::Key k, std::function<void(sf::Keyboard::Key k)> &cb, const double &duration)
      : _key(k), __CALLBACK(cb), GenericEvent(Events::KeyPressed, duration)
    {
      Trigger = [this]()->void {__CALLBACK(_key); };
    }
    UserKeyPressEvent(const UserKeyPressEvent &e) : GenericEvent(e.EventTrigger, e.TotalDuration)
    {
      Trigger = e.Trigger;
      TotalDuration = e.TotalDuration;
      EventTrigger = e.EventTrigger;
      Repeat = e.Repeat;
      _key = e._key;
    }

    std::function<void(sf::Keyboard::Key k)> __CALLBACK;
    sf::Keyboard::Key _key;
  };

  //Simulate a user releasing a key
  struct UserKeyReleaseEvent : public GenericEvent {
    UserKeyReleaseEvent(sf::Keyboard::Key k, std::function<void(sf::Keyboard::Key k)> cb, const double &duration)
      : _key(k), GenericEvent(Events::KeyReleased, duration)
    {
      Trigger = [=]()->void {cb(_key); };
    }
    UserKeyReleaseEvent(const UserKeyReleaseEvent &e)
      : GenericEvent(e.EventTrigger, e.TotalDuration)
    {
      Trigger = e.Trigger;
      TotalDuration = e.TotalDuration;
      EventTrigger = e.EventTrigger;
      Repeat = e.Repeat;
      _key = e._key;
    }


    sf::Keyboard::Key _key;
  };

  //Simulate user pressing a mouse button
  struct UserMousePressEvent : public GenericEvent
  {
    UserMousePressEvent(const sf::Mouse::Button &b, const sf::Vector2i &p,
                        std::function<void(const sf::Vector2i &, const sf::Mouse::Button &)> cb, const double &duration)
      : _button(b), _pos(p), GenericEvent(Events::MouseDown, duration)
    {
      Trigger = [=]()->void {cb(_pos, _button); };
    }
    UserMousePressEvent(const UserMousePressEvent &e)
      : GenericEvent(e.EventTrigger, e.TotalDuration)
    {
      Trigger = e.Trigger;
      TotalDuration = e.TotalDuration;
      EventTrigger = e.EventTrigger;
      Repeat = e.Repeat;
      _pos = e._pos;
      _button = e._button;
    }

    sf::Vector2i _pos;
    sf::Mouse::Button _button;
  };

  //Simulate user releasing a mouse button
  struct UserMouseReleaseEvent : public GenericEvent
  {
    UserMouseReleaseEvent(const sf::Mouse::Button &b, const sf::Vector2i &p,
                          std::function<void(const sf::Vector2i &, const sf::Mouse::Button &)> cb, const double &duration)
      : _pos(p), _button(b), GenericEvent(Events::MouseReleased, duration)
    {
      Trigger = [=]()->void {cb(_pos, _button); };
    }
    UserMouseReleaseEvent(const UserMouseReleaseEvent &e)
      : GenericEvent(e.EventTrigger, e.TotalDuration)
    {
      Trigger = e.Trigger;
      TotalDuration = e.TotalDuration;
      EventTrigger = e.EventTrigger;
      Repeat = e.Repeat;
      _pos = e._pos;
      _button = e._button;
    }

    sf::Vector2i _pos;
    sf::Mouse::Button _button;
  };

}

#endif