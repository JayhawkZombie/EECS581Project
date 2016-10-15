#ifndef SFENGINE_COLLISION_H
#define SFENGINE_COLLISION_H

#include "../BasicIncludes.h"

namespace Engine
{
  class CollisionBox
  {
  public:
    CollisionBox();
    CollisionBox(const CollisionBox &box);
    ~CollisionBox();

    sf::Vector2f Position;
    sf::Vector2f Size;
  };
}

#endif
