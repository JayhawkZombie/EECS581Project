#ifndef SFENGINE_UI_UTILS_H
#define SFENGINE_UI_UTILS_H

#include <SFML\Graphics.hpp>

namespace Engine
{
  namespace UI
  {
    bool IsMouseOverRect(const sf::Vector2i &mouse, const sf::FloatRect &rect);
  }
}


#endif
