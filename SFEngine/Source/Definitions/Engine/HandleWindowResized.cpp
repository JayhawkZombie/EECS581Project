#include "../../Headers/Engine/Engine.h"

namespace Engine
{
  void SFEngine::HandleWindowResized()
  {
    sf::Vector2u wsize = currentRenderWindow->getSize();

    WindowSize = sf::Vector2f(wsize.x, wsize.y);

    for (auto & lvl : Levels) {
      lvl->HandleWindowResized();
    }
  }
}
