#include "Engine\Engine.h"


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
    UEvent.Key = sf::Keyboard::Unknown;
    UEvent.TextUnicode = unicode;
    UEvent.TextWasEntered = true;
    UEvent.PreviousMousePosition = UEvent.CurrentMousePosition;
    UEvent.CurrentMousePosition = sf::Mouse::getPosition(*currentRenderWindow);
    UEvent.MouseButtonWasPressed = false;
    UEvent.MouseButtonWasReleased = false;
    UEvent.EventType = UserEventType::TextEntered;
    UEvent.KeyRepeat = false;
    UEvent.KeyWasPressed = false;
    UEvent.KeyWasReleased = false;
    UEvent.MouseScrollDelta = 0.f;
    UEvent.MouseScrolled = false;

    if (CurrentLevel)
      CurrentLevel->HandleInputEvent(UEvent);

  }

  void SFEngine::HandleKeyPress(const sf::Keyboard::Key &k)
  {
    UEvent.Key = k;
    UEvent.TextUnicode = k;
    UEvent.TextWasEntered = false;
    UEvent.PreviousMousePosition = UEvent.CurrentMousePosition;
    UEvent.CurrentMousePosition = sf::Mouse::getPosition(*currentRenderWindow);
    UEvent.MouseButtonWasPressed = false;
    UEvent.MouseButtonWasReleased = false;
    UEvent.EventType = UserEventType::KeyboardPress;
    UEvent.KeyRepeat = false;
    UEvent.KeyWasPressed = true;
    UEvent.KeyWasReleased = false;
    UEvent.MouseScrollDelta = 0.f;
    UEvent.MouseScrolled = false;

    if (CurrentLevel)
      CurrentLevel->HandleInputEvent(UEvent);

    CheckKeyboardShortcuts();
  }

  void SFEngine::HandleKeyRelease(const sf::Keyboard::Key &k)
  {
    UEvent.Key = k;
    UEvent.TextUnicode = 0;
    UEvent.TextWasEntered = false;
    UEvent.PreviousMousePosition = UEvent.CurrentMousePosition;
    UEvent.CurrentMousePosition = sf::Mouse::getPosition(*currentRenderWindow);
    UEvent.MouseButtonWasPressed = false;
    UEvent.MouseButtonWasReleased = false;
    UEvent.EventType = UserEventType::KeyboardRelease;
    UEvent.KeyRepeat = false;
    UEvent.KeyWasPressed = false;
    UEvent.KeyWasReleased = true;
    UEvent.MouseScrollDelta = 0.f;
    UEvent.MouseScrolled = false;

    if (CurrentLevel)
      CurrentLevel->HandleInputEvent(UEvent);
  }

}