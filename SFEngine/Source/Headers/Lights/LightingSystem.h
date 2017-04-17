#ifndef SFENGINE_LIGHTING_SYSTEM_H
#define SFENGINE_LIGHTING_SYSTEM_H

#include "Lights\LightObject.h"
#include "Utils\RayCast.h"

#define COSPIBY4 0.25

namespace Engine
{


  void _normalize(sf::Vector2f &v);

  float Dot(const sf::Vector2f &v1, const sf::Vector2f &v2);

  float DistanceBetween(const sf::Vector2f &a, const sf::Vector2f &b);
  
}
#endif
