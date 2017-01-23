#include "../../Headers/Engine/Engine.h"

/**
 * Header that contains the methods in the engine exposed to the scripting engine (and thus available inside sripts)
 *
 */

namespace Engine
{


  void SFEngine::SetAALevel(unsigned int level)
  {
    ContextSettings.antialiasingLevel = level;
  }

  void SFEngine::SetFramerateLimit(unsigned int level)
  {
    
  }

  void SFEngine::SetBrightness(unsigned int level)
  {
    RenderSettings.Brightness = level;
  }

  void SFEngine::SetGamma(unsigned int level)
  {
    RenderSettings.Gamma = level;
  }

  void SFEngine::SetTimeScale(float amount)
  {

  }

  void SFEngine::SetContrast(unsigned int level)
  {
    RenderSettings.Contrast = level;
  }


}
