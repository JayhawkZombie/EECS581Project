#include "../../Headers/Engine/Engine.h"

namespace Engine
{

  void SFEngine::HandleKeyPress(const sf::Keyboard::Key &k)
  {
    if (k == sf::Keyboard::Escape)
      EngineUIController.ToggleShown();
    else
      EngineUIController.Handler.HandleKeyPress(k);

    for (auto & level : Levels) {
      level->Handler.HandleKeyPress(k);
    }
  }

  void SFEngine::HandleKeyRelease(const sf::Keyboard::Key &k)
  {
    EngineUIController.Handler.HandleKeyRelease(k);
  }

}
