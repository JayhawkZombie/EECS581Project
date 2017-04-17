#include "Engine\Engine.h"

namespace Engine
{
  void SFEngine::HandleWindowResized()
  {
    sf::Vector2u wsize = currentRenderWindow->getSize();

    WindowSize = sf::Vector2f(static_cast<float>(wsize.x), static_cast<float>(wsize.y));

    if (CurrentLevel)
      CurrentLevel->HandleWindowResized();
  }
}
