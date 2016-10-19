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

    virtual void SetPosition(const sf::Vector2f &pos);
    virtual const sf::Vector2f& GetPosition() const;

    virtual void SetAttenuation(const sf::Vector2f &atten);
    virtual const sf::Vector2f& GetAttenuation() const;

    virtual void SetIntensity(const float in);
    virtual const float& GetIntensity() const;

    virtual void SetColor(const sf::Color &color);
    virtual const sf::Color& GetColor() const;

    virtual void SetDoesCastShadows(const bool &b);
    virtual const bool& GetDoesCastShadows() const;

    void SetID(const std::string &ID);
    const std::string& GetID() const;

  protected:
    sf::Vector2f Position;
    sf::Vector2f Attenutation;
    float Intensity;
    sf::Color Color;
    std::string LightID;
    bool bDoesCastShadows;

  };

}

#endif
