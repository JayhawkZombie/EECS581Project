#include "../../Headers/Engine/Engine.h"

namespace Engine
{

  void SFEngine::HandleMouseMovement(const sf::Vector2i &mousePos)
  {
    EngineUIController.Handler.HandleMouseMovement(mousePos);

    UIInputEvent.Key = sf::Keyboard::Unknown;
    UIInputEvent.PreviousMousePosition = UIInputEvent.CurrentMousePosition;
    UIInputEvent.CurrentMousePosition = sf::Mouse::getPosition(*currentRenderWindow);
    UIInputEvent.MouseButtonWasPressed = false;
    UIInputEvent.MouseButtonWasReleased = false;
    UIInputEvent.KeyRepeat = false;
    UIInputEvent.KeyWasPressed = false;
    UIInputEvent.KeyWasReleased = false;
    UIInputEvent.EventType = InputEventType::MouseMovement;
    
#ifdef WITH_EDITOR
    GameEditor.HandleMouseMoved(UIInputEvent);
#endif

  }

  void SFEngine::HandleMousePress(const sf::Vector2i &v, const sf::Mouse::Button &b)
  {
    std::cerr << "[ENGINE]: Mouse pressed!" << std::endl;

    UIInputEvent.Key = sf::Keyboard::Unknown;
    UIInputEvent.Button = b;
    UIInputEvent.PreviousMousePosition = UIInputEvent.CurrentMousePosition;
    UIInputEvent.CurrentMousePosition = sf::Mouse::getPosition(*currentRenderWindow);
    UIInputEvent.MouseButtonWasPressed = true;
    UIInputEvent.MouseButtonWasReleased = false;
    UIInputEvent.KeyRepeat = false;
    UIInputEvent.KeyWasPressed = false;
    UIInputEvent.KeyWasReleased = false;
    UIInputEvent.EventType = InputEventType::MousePress;

#ifdef WITH_EDITOR
    GameEditor.HandleMousePressed(UIInputEvent);
#endif

    EngineUIController.Handler.HandleMousePress(v, b);
  }

  void SFEngine::HandleMouseRelease(const sf::Vector2i &v, const sf::Mouse::Button &b)
  {
    std::cerr << "[ENGINE]: Mouse released!" << std::endl;

    UIInputEvent.Key = sf::Keyboard::Unknown;
    UIInputEvent.Button = b;
    UIInputEvent.PreviousMousePosition = UIInputEvent.CurrentMousePosition;
    UIInputEvent.CurrentMousePosition = sf::Mouse::getPosition(*currentRenderWindow);
    UIInputEvent.MouseButtonWasPressed = false;
    UIInputEvent.MouseButtonWasReleased = true;
    UIInputEvent.KeyRepeat = false;
    UIInputEvent.KeyWasPressed = false;
    UIInputEvent.KeyWasReleased = false;
    UIInputEvent.EventType = InputEventType::MouseRelease;

#ifdef WITH_EDITOR
    GameEditor.HandleMouseReleased(UIInputEvent);
#endif

    EngineUIController.Handler.HandleMouseRelease(v, b);
  }
}
