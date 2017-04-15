#include "../../Headers/Engine/Engine.h"

namespace Engine
{

  void SFEngine::HandleMouseMovement(const sf::Vector2i &mousePos)
  {
    UEvent.Key = sf::Keyboard::Unknown;
    UEvent.PreviousMousePosition = UEvent.CurrentMousePosition;
    UEvent.CurrentMousePosition = sf::Mouse::getPosition(*currentRenderWindow);
    UEvent.MouseButtonWasPressed = false;
    UEvent.MouseButtonWasReleased = false;
    UEvent.KeyRepeat = false;
    UEvent.KeyWasPressed = false;
    UEvent.KeyWasReleased = false;
    UEvent.EventType = UserEventType::MouseMovement;

    if (CurrentLevel)
      CurrentLevel->HandleInputEvent(UEvent);
  }

  void SFEngine::HandleMousePress(const sf::Vector2i &v, const sf::Mouse::Button &b)
  {
    UEvent.Key = sf::Keyboard::Unknown;
    UEvent.Button = b;
    UEvent.PreviousMousePosition = UEvent.CurrentMousePosition;
    UEvent.CurrentMousePosition = sf::Mouse::getPosition(*currentRenderWindow);
    UEvent.MouseButtonWasPressed = true;
    UEvent.MouseButtonWasReleased = false;
    UEvent.KeyRepeat = false;
    UEvent.KeyWasPressed = false;
    UEvent.KeyWasReleased = false;
    UEvent.EventType = UserEventType::MousePress;

    std::cerr << "MousePressed" << std::endl;

    if (CurrentLevel)
      CurrentLevel->HandleInputEvent(UEvent);
  }

  void SFEngine::HandleMouseRelease(const sf::Vector2i &v, const sf::Mouse::Button &b)
  {
    UEvent.Key = sf::Keyboard::Unknown;
    UEvent.Button = b;
    UEvent.PreviousMousePosition = UEvent.CurrentMousePosition;
    UEvent.CurrentMousePosition = sf::Mouse::getPosition(*currentRenderWindow);
    UEvent.MouseButtonWasPressed = false;
    UEvent.MouseButtonWasReleased = true;
    UEvent.KeyRepeat = false;
    UEvent.KeyWasPressed = false;
    UEvent.KeyWasReleased = false;
    UEvent.EventType = UserEventType::MouseRelease;

    if (CurrentLevel)
      CurrentLevel->HandleInputEvent(UEvent);
  }
}
