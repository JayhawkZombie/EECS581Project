#include "Engine\Engine.h"


namespace Engine
{

  void SFEngine::HandleEngineCrash()
  {
    std::cerr << "Handling engine crash" << std::endl;

    for (auto & level : Levels) {
      level.second->OnShutDown();
    }
  }

}
