#include "../../Headers/Engine/Engine.h"

namespace Engine
{
  void SFEngine::HandleWindowResized()
  {
    sf::Vector2u wsize = currentRenderWindow->getSize();

    WindowSize = sf::Vector2f(static_cast<float>(wsize.x), static_cast<float>(wsize.y));

#ifdef WITH_EDITOR
    GameEditor.HandleWindowResized(wsize);
#endif

    for (auto & lvl : Levels) {
      lvl->HandleWindowResized();
    }
  }
}
