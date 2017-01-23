#ifndef SFENGINE_UI_EVENTS_H
#define SFENGINE_UI_EVENTS_H

#include <cinttypes>

#include <SFML/Graphics.hpp>

namespace Engine
{

    //enum FocusChangeEvent : std::uint32_t
    //{
    //  ItemForced, //Another UI item forced the change
    //  UserForced, //The user did this manually
    //  Opening, //Opening the UI gave focus
    //  ItemClosed, //Focus given because another item was closed
    //};

    enum class FocusChangeType : std::uint32_t
    {
      ItemForced,
      UserForced,
      Opening,
      ItemClosed,
      Unknown
    };

    enum class InputEventType : std::uint32_t
    {
        MousePress, //Pressing on a mouse button
        MouseRelease, //Releasing a mouse button
        MouseMovement, //Moving the mouse inside the bounds of an element
        MouseScrollUp, //Scrolling a mouse wheel up
        MouseScrollDown, //Scrolling a mouse wheel down
        KeyboardPress, //Pressing a key on the keyboard
        KeyboardRelease, //Releasing a key on the keyboard
        Unknown
    };

    class FocusChangeEvent
    {
    public:
      FocusChangeEvent() = default;
      ~FocusChangeEvent() = default;
      FocusChangeEvent(const FocusChangeEvent &event) 
      
      {}

      bool IsButtonPressed(const sf::Keyboard::Key key) const {
        return sf::Keyboard::isKeyPressed(key);
      }
      bool IsMouseButtonDown(const sf::Mouse::Button &button) const {
        return sf::Mouse::isButtonPressed(button);
      }

      sf::Vector2i CurrentMousePosition = { 0, 0 };
      sf::Vector2i PreviousMousePosition = { 0, 0 };

      FocusChangeType ChangeType;
    };

    class InputEvent
    {
    public:
      InputEvent() = default;
      ~InputEvent() = default;
      InputEvent(const InputEvent &event)
        :
        MouseButtonWasPressed(event.MouseButtonWasPressed),
        MouseButtonWasReleased(event.MouseButtonWasReleased),
        KeyWasPressed(event.KeyWasPressed),
        KeyWasReleased(event.KeyWasReleased),
        KeyRepeat(event.KeyRepeat),
        Key(event.Key),
        Button(event.Button)
      {}

      bool IsButtonPressed(const sf::Keyboard::Key key) const {
        return sf::Keyboard::isKeyPressed(key);
      }
      bool IsMouseButtonDown(const sf::Mouse::Button &button) const {
        return sf::Mouse::isButtonPressed(button);
      }

      bool MouseButtonWasPressed = false;
      bool MouseButtonWasReleased = false;

      bool KeyWasPressed = false;
      bool KeyWasReleased = false;
      bool KeyRepeat = false;

      sf::Keyboard::Key Key;
      sf::Mouse::Button Button;

      sf::Vector2i CurrentMousePosition = { 0, 0 };
      sf::Vector2i PreviousMousePosition = { 0, 0 };

      InputEventType EventType;
    };

    //enum InputEvent : std::uint32_t
    //{
    //  MousePress, //Pressing on a mouse button
    //  MouseRelease, //Releasing a mouse button
    //  MouseMovement, //Moving the mouse inside the bounds of an element
    //  MouseScrollUp, //Scrolling a mouse wheel up
    //  MouseScrollDown, //Scrolling a mouse wheel down
    //  KeyboardPress, //Pressing a key on the keyboard
    //  KeyboardRelease, //Releasing a key on the keyboard
    //};

}


#endif
