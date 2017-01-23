#ifndef SFENGINE_COLLISION_HELPERS_H
#define SFENGINE_COLLISION_HELPERS_H

#include <SFML\Graphics.hpp>

namespace Engine
{

  template<typename T, typename U>
  inline bool IsPointInsideRect(const sf::Rect<T> &Rect, const sf::Vector2<U> &Point) {
    return (
      Point.x >= Rect.left && Point.x <= Rect.left + Rect.width &&
      Point.y >= Rect.top && Point.y <= Rect.top + Rect.height
      );
  }




}


#endif
