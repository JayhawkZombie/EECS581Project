#ifndef SFENGINE_UTILS_VARIOUS_H
#define SFENGINE_UTILS_VARIOUS_H

#include <SFML/Graphics.hpp>

namespace Engine
{


  namespace Util
  {
    void Normalize(sf::Vector2f &v);

    float DistanceBetween(const sf::Vector2f &v1, const sf::Vector2f &v2);

    float Cross2D(const sf::Vector2f &v1, const sf::Vector2f &v2);
  }


}

#endif
