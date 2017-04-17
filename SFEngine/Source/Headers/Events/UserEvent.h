#ifndef SFENGINE_USER_EVENT_H
#define SFENGINE_USER_EVENT_H

#include <SFML\Graphics.hpp>

namespace Engine
{
  enum class UserEventType : std::uint32_t
  {
    MousePress, //Pressing on a mouse button
    MouseRelease, //Releasing a mouse button
    MouseMovement, //Moving the mouse inside the bounds of an element
    MouseScrollVertical, //Scrolling a mouse wheel up/down
    MouseScrollHorizontal, //Scrolling a mouse wheel left/right
    KeyboardPress, //Pressing a key on the keyboard
    KeyboardRelease, //Releasing a key on the keyboard
    TextEntered,
    Unknown
  };

  class UserEvent
  {
  public:
    UserEvent() = default;
    ~UserEvent() = default;
    UserEvent(const UserEvent &event)
      :
      MouseButtonWasPressed(event.MouseButtonWasPressed),
      MouseButtonWasReleased(event.MouseButtonWasReleased),
      KeyWasPressed(event.KeyWasPressed),
      KeyWasReleased(event.KeyWasReleased),
      KeyRepeat(event.KeyRepeat),
      Key(event.Key),
      Button(event.Button),
      EventType(event.EventType)
    {}

    bool IsButtonPressed(const sf::Keyboard::Key key) const {
      return sf::Keyboard::isKeyPressed(key);
    }
    bool IsMouseButtonDown(const sf::Mouse::Button &button) const {
      return sf::Mouse::isButtonPressed(button);
    }
    bool WasMouseWheelScrolled() const {
      return MouseScrolled;
    }

    bool MouseButtonWasPressed = false;
    bool MouseButtonWasReleased = false;

    bool KeyWasPressed = false;
    bool KeyWasReleased = false;
    bool KeyRepeat = false;

    bool TextWasEntered = false;
    bool MouseScrolled = false;

    float MouseScrollDelta = 0.f;
    sf::Uint32 TextUnicode;

    sf::Keyboard::Key Key;
    sf::Mouse::Button Button;

    sf::Vector2i CurrentMousePosition = { 0, 0 };
    sf::Vector2i PreviousMousePosition = { 0, 0 };

    sf::Mouse::Wheel MouseWheenScrolled;

    UserEventType EventType;
  };

}

#endif
