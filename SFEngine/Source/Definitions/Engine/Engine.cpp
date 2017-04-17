#include "Engine\Engine.h"

namespace Engine
{

  SFEngine::SFEngine()
  {
    
  }

  SFEngine::~SFEngine()
  {

  }

  void SFEngine::LoadLevel(std::string lvl)
  {

  }

  void SFEngine::SwitchToLevel(std::string lvl)
  {

  }

  bool SFEngine::IsKeyLeftDown()
  {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
  }

}
