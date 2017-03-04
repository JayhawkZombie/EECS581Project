#ifndef SFENGINE_LIGHT_OBJECT_H
#define SFENGINE_LIGHT_OBJECT_H


#include "../Level/LevelObject.h"

#include "../Utils/Vec.hpp"
#include "GlobalLightSource.h"

namespace Engine
{
  struct Edge {
    sf::Vector2f Start;
    sf::Vector2f End;

    sf::Vector2f FakeStart;
    sf::Vector2f FakeEnd;
  };

  class LightSystem;

  class LightObject
  {
  public:
    friend class LightSystem;

    LightObject() = default;
    LightObject(const LightObject &obj)
    {
      
    }
    ~LightObject() = default;

    //Add light-related variables
    std::vector<Edge> Edges;
    std::uint32_t ID;

  };
}
#endif
