#include "../../Headers/Engine/Engine.h"

namespace Engine
{
  UINT32 SFEngine::Shutdown()
  {
    delete[] Window;

    currentRenderWindow = nullptr;

    return Success::GAMELOOP_SUCCESS;
  }
}
