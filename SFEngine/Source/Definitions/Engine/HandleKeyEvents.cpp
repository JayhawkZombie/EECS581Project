#include "../../Headers/Engine/Engine.h"

namespace Engine
{

  void SFEngine::HandleTextEntered(const sf::Uint32 &unicode)
  {
    UIInputEvent.Key = sf::Keyboard::Unknown;
    UIInputEvent.TextUnicode = unicode;
    UIInputEvent.TextWasEntered = true;
    UIInputEvent.PreviousMousePosition = UIInputEvent.CurrentMousePosition;
    UIInputEvent.CurrentMousePosition = sf::Mouse::getPosition(*currentRenderWindow);
    UIInputEvent.MouseButtonWasPressed = false;
    UIInputEvent.MouseButtonWasReleased = false;
    UIInputEvent.EventType = InputEventType::TextEntered;
    UIInputEvent.KeyRepeat = false;
    UIInputEvent.KeyWasPressed = false;
    UIInputEvent.KeyWasReleased = false;

#ifdef WITH_EDITOR
    GameEditor.HandleTextEntered(UIInputEvent);
#endif
  }

  void SFEngine::HandleKeyPress(const sf::Keyboard::Key &k)
  {
    UIInputEvent.Key = k;
    UIInputEvent.TextUnicode = k;
    UIInputEvent.TextWasEntered = false;
    UIInputEvent.PreviousMousePosition = UIInputEvent.CurrentMousePosition;
    UIInputEvent.CurrentMousePosition = sf::Mouse::getPosition(*currentRenderWindow);
    UIInputEvent.MouseButtonWasPressed = false;
    UIInputEvent.MouseButtonWasReleased = false;
    UIInputEvent.EventType = InputEventType::KeyboardPress;
    UIInputEvent.KeyRepeat = false;
    UIInputEvent.KeyWasPressed = true;
    UIInputEvent.KeyWasReleased = false;
    
#ifdef WITH_EDITOR
    GameEditor.HandleKeyPressed(UIInputEvent);
#else

    if (k == sf::Keyboard::Escape)
      EngineUIController.ToggleShown();
    else
      EngineUIController.Handler.HandleKeyPress(k);

    for (auto & level : Levels) {
      level->Handler.HandleKeyPress(k);
    }

#endif
  }

  void SFEngine::HandleKeyRelease(const sf::Keyboard::Key &k)
  {
    UIInputEvent.Key = k;
    UIInputEvent.TextUnicode = 0;
    UIInputEvent.TextWasEntered = false;
    UIInputEvent.PreviousMousePosition = UIInputEvent.CurrentMousePosition;
    UIInputEvent.CurrentMousePosition = sf::Mouse::getPosition(*currentRenderWindow);
    UIInputEvent.MouseButtonWasPressed = false;
    UIInputEvent.MouseButtonWasReleased = false;
    UIInputEvent.EventType = InputEventType::KeyboardRelease;
    UIInputEvent.KeyRepeat = false;
    UIInputEvent.KeyWasPressed = false;
    UIInputEvent.KeyWasReleased = true;

#ifdef WITH_EDITOR
    GameEditor.HandleKeyReleased(UIInputEvent);
#endif

    switch (k)
    {
      case sf::Keyboard::Num0:
        RenderSettings.PostProcess = 0;
        break;
      case sf::Keyboard::Num1:
        RenderSettings.PostProcess = 1;
        break;
      case sf::Keyboard::Num2:
        RenderSettings.PostProcess = 2;
        break;
      case sf::Keyboard::Num3:
        RenderSettings.PostProcess = 3;
        break;
    }

    Render::__Set__Render__Settings(RenderSettings);

    for (auto & level : Levels) {
      level->HandleKeyRelease(k);
    }
  }

}