#include "../../Headers/Engine/Engine.h"

namespace Engine
{
  UINT32 SFEngine::Shutdown()
  {
    ImGui::SFML::Shutdown();

    for (auto & lvl : Levels)
      lvl->OnShutDown();
    GUI.reset();
    delete Window;

    currentRenderWindow = nullptr;
    ResourceManager->Shutdown();

    delete FragmentShader;
    delete VertexShader;

    //Destroy the scripting engine
    if (ScriptEngine) {
      delete ScriptEngine;
    }
    return Success::GAMELOOP_SUCCESS;
  }
}
