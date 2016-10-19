#include "../../Headers/Lights/GenericLightSource.h"

namespace Engine
{

  GenericLightSource::GenericLightSource()
  {
    LightID = "";
  }

  GenericLightSource::GenericLightSource(const GenericLightSource &src)
  {
    LightID = "";
    Position = src.Position;
    Attenutation = src.Attenutation;
    Intensity = src.Intensity;
    Color = src.Color;
    bDoesCastShadows = src.bDoesCastShadows;
  }

  GenericLightSource::~GenericLightSource()
  {

  }

  void GenericLightSource::SetPosition(const sf::Vector2f &pos)
  {
    Position = pos;
  }

  const sf::Vector2f& GenericLightSource::GetPosition() const
  {
    return Position;
  }

  void GenericLightSource::SetAttenuation(const sf::Vector2f &atten)
  {
    Attenutation = atten;
  }

  const sf::Vector2f& GenericLightSource::GetAttenuation() const
  {
    return Attenutation;
  }

  void GenericLightSource::SetIntensity(const float in)
  {
    Intensity = in;
  }

  const float& GenericLightSource::GetIntensity() const
  {
    return Intensity;
  }

  void GenericLightSource::SetColor(const sf::Color &color)
  {
    Color = color;
  }

  const sf::Color& GenericLightSource::GetColor() const
  {
    return Color;
  }

  void GenericLightSource::SetDoesCastShadows(const bool &b)
  {
    bDoesCastShadows = b;
  }

  const bool& GenericLightSource::GetDoesCastShadows() const
  {
    return bDoesCastShadows;
  }

  void GenericLightSource::SetID(const std::string &ID)
  {
    LightID = ID;
  }

  const std::string& GenericLightSource::GetID() const
  {
    return LightID;
  }

}