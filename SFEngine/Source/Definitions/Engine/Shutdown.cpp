#include "Engine\Engine.h"
#include "Resources\ResourceManager.h"

#include "chaiscript\chaiscript.hpp"

namespace Engine
{
  UINT32 SFEngine::Shutdown()
  {
    ImGui::SFML::Shutdown();

    for (auto & lvl : Levels)
      lvl.second->OnShutDown();
    Levels.clear();

    ClearTextures();
    ClearShaders();
    ClearFonts();
    ClearSoundBuffers();

    GUI.reset();
    delete Window;

    currentRenderWindow = nullptr;

    delete FragmentShader;
    delete VertexShader;

    //Destroy the scripting engine
    if (ScriptEngine) {
      delete ScriptEngine;
    }
    return Success::GAMELOOP_SUCCESS;
  }
}
