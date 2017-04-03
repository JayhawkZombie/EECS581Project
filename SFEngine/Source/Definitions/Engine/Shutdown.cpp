#include "../../Headers/Engine/Engine.h"
#include "../../../ThirdParty/chaiscript/chaiscript_defines.hpp"
#include "../../../ThirdParty/chaiscript/chaiscript.hpp"
#include "../../../ThirdParty/chaiscript/chaiscript_stdlib.hpp"

namespace Engine
{
  UINT32 SFEngine::Shutdown()
  {
    ImGui::SFML::Shutdown();

    for (auto & lvl : Levels)
      lvl.second->OnEnd();

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
