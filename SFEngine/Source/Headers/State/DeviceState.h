#ifndef SFENGINE_DEVICE_STATE_H
#define SFENGINE_DEVICE_STATE_H

#include "Events\UserEvent.h"
#include <unordered_map>
#include <SFML\System.hpp>

namespace Engine
{
  using sf::Keyboard;
  using sf::Mouse;

  class KeyboardInputState
  {
  public:
    KeyboardInputState();
    ~KeyboardInputState() = default;

    void Update(const sf::Event &event);

    bool IsKeyDown(const Keyboard::Key &key) const;
    bool WasKeyDown(const Keyboard::Key &key) const;

  private:
    std::unordered_map<Keyboard::Key, bool> m_KeysDown;
    std::unordered_map<Keyboard::Key, bool> m_KeysDownLast;

    std::vector<Keyboard::Key> m_KeysReleasedVec;
    std::vector<Keyboard::Key> m_KeysPressedVec;
  };

  class MouseInputState
  {
  public:
    MouseInputState();
    ~MouseInputState() = default;

    void Update(const sf::Event &event);
    sf::Vector2i GetPosition() const;
    sf::Vector2i GetLastPosition() const;

    bool IsMouseButtonDown(const Mouse::Button &mouse) const;
    bool WasMouseButtonDown(const Mouse::Button &mouse) const;

  private:
    std::unordered_map<sf::Mouse::Button, bool> m_ButtonsDown;
    std::unordered_map<sf::Mouse::Button, bool> m_ButtonsDownLast;
    sf::Vector2i m_Position;
    sf::Vector2i m_LastPosition;
    std::vector<Mouse::Button> m_ButtonPressedVec;
    std::vector<Mouse::Button> m_ButtonsReleasedVec;
  };

  class TouchInputState
  {

  };

  class JoystickInputState
  {

  };

  class InputDeviceState
  {
  public:
    InputDeviceState() = default;
    InputDeviceState(const InputDeviceState &);
    ~InputDeviceState() = default;

    void Update(const sf::Event &event);

    bool IsKeyDown(const Keyboard::Key &key) const;
    bool IsKeyUp(const Keyboard::Key &key) const;
    bool WasKeyDown(const Keyboard::Key &key) const;
    bool WasKeyReleased(const Keyboard::Key &key) const;
    bool IsMouseButtonDown(const Mouse::Button &mouse) const;
    bool IsMouseButtonUp(const Mouse::Button &mouse) const;
    bool WasMouseButtonReleased(const Mouse::Button &mouse) const;

  protected:
    KeyboardInputState m_KeyState;
    MouseInputState    m_MouseState;
  };

}

#endif
