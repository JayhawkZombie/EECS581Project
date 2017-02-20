#include "../../Headers/Engine/Engine.h"


namespace
{
  struct KeyboardSC
  {
    KeyboardSC() = default;
    KeyboardSC(const KeyboardSC &other)
      : Keys(other.Keys), CB(other.CB), WasUsed(other.WasUsed) {}

    std::vector<sf::Keyboard::Key> Keys;
    std::function<void(void)> CB;
    bool WasUsed = false;
  };
  std::vector<KeyboardSC> KeyboardShortcuts;
}



namespace Engine
{

  void AddKeyboardShortcut(const std::vector<sf::Keyboard::Key> &keys, std::function<void(void)> callback)
  {
    KeyboardSC SC;
    SC.Keys = keys;
    SC.CB = callback;
    SC.WasUsed = false;
    KeyboardShortcuts.push_back(SC);
  }

  void CheckKeyboardShortcuts()
  {
    bool use = true;
    for (auto SC : KeyboardShortcuts) {
      for (auto & key : SC.Keys) {
        if (!sf::Keyboard::isKeyPressed(key)) {
          SC.WasUsed = false;
          use = false;
          break;
        }
      }
      if (use)
        SC.CB();
    }
  }

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

    CheckKeyboardShortcuts();
    
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

    //CheckKeyboardShortcuts();

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