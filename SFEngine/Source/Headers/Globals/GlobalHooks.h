#ifndef SFENGINE_GLOBAL_HOOKS_H
#define SFENGINE_GLOBAL_HOOKS_H

#include <SFML\Graphics.hpp>
#include "../Resources/ResourceManager.h"

namespace Engine
{
  extern sf::RenderWindow *currentRenderWindow;
  extern std::shared_ptr<Resource::ResourceManager> ResourceManager;
  extern sf::Vector2f WindowSize;

  class BaseUIElement;

}

#endif
