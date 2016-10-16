#include "../../Headers/Engine/Engine.h"

namespace Engine
{
  UINT32 SFEngine::Shutdown()
  {
    delete Window;

    currentRenderWindow = nullptr;
    ResourceManager->Shutdown();

    delete FragmentShader;
    delete VertexShader;

    return Success::GAMELOOP_SUCCESS;
  }
}
