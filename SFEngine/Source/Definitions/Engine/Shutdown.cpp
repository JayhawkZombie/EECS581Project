#include "../../Headers/Engine/Engine.h"

namespace Engine
{
  UINT32 SFEngine::Shutdown()
  {
    delete[] Window;

    currentRenderWindow = nullptr;
    ResourceManager->Shutdown();

    return Success::GAMELOOP_SUCCESS;
  }
}
