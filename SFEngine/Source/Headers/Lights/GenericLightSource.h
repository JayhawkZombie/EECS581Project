#ifndef SFENGINE_GENERIC_LIGHT_SOURCE_H
#define SFENGINE_GENERIC_LIGHT_SOURCE_H

#include <SFML\Graphics.hpp>

namespace Engine
{

  class GenericLightSource
  {
  public:
    GenericLightSource();
    GenericLightSource(const GenericLightSource &src);
    ~GenericLightSource();


  private:
    sf::Vector2f Position;
    sf::Vector2f Attenutation;
    float Intensity;
    sf::Color Color;

    bool bDoesCastShadows;

  };

}

#endif
