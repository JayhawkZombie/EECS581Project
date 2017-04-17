#include "Lights\LightingSystem.h"
#include "Physics\QuadTree.h"

namespace Engine
{
#ifndef ____PI
#define ____PI 3.141592653
#endif

  void _normalize(sf::Vector2f &v)
  {
    if (v.x == 0 && v.y == 0)
      return;

    float mag = (v.x * v.x) + (v.y * v.y);
    mag = std::sqrt(mag);
    v /= mag;
  }

  float Dot(const sf::Vector2f &v1, const sf::Vector2f &v2)
  {
    return ((v1.x * v2.x) + (v1.y * v2.y));
  }

  float DistanceBetween(const sf::Vector2f &a, const sf::Vector2f &b)
  {
    float x_dist = b.x - a.x;
    float y_dist = b.y - a.y;
    return (sqrt(
      (x_dist * x_dist) + (y_dist * y_dist)
    ));
  }

}
