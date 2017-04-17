#include "Utils\Various.h"

namespace Engine
{

  namespace Util
  {

    void Normalize(sf::Vector2f &v)
    {
      float mag = std::sqrt((v.x * v.x) + (v.y * v.y));
      v.x /= mag;
      v.y /= mag;
    }

    float DistanceBetween(const sf::Vector2f &v1, const sf::Vector2f &v2) {
      float x_dist = v2.x - v1.x;
      float y_dist = v2.y - v1.y;

      return (std::sqrt(x_dist * x_dist) + (y_dist * y_dist));
    }

    float Cross2D(const sf::Vector2f &v1, const sf::Vector2f &v2) {
      return ((v1.x * v2.y) - (v1.y * v2.x));
    }

  }

}
