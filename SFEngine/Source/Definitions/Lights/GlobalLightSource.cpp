#include "../../Headers/Lights/GlobalLightSource.h"

namespace Engine
{

  std::shared_ptr<GlobalLightSource> GlobalLightSource::Create()
  {
    return std::make_shared<GlobalLightSource>();
  }

  GlobalLightSource::GlobalLightSource()
  {
    bDoesCastShadows = false;
    Attenutation = sf::Vector2f(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
  }

  GlobalLightSource::GlobalLightSource(const GlobalLightSource &src)
  {
    Position = src.Position;
    Attenutation = src.Attenutation;
    Intensity = src.Intensity;
    Color = src.Color;
    bDoesCastShadows = src.bDoesCastShadows;
  }

  GlobalLightSource::~GlobalLightSource()
  {
    
  }

}
