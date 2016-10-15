#include "../../Headers/Globals/GlobalHooks.h"

namespace Engine
{
  sf::RenderWindow *currentRenderWindow = nullptr;
  std::shared_ptr<Resource::ResourceManager> ResourceManager;
  sf::Vector2f WindowSize;
}
