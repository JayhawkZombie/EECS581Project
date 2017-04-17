#include "Level\ExposedLevelApi.h"

#include "chaiscript\chaiscript.hpp"
#include "chaiscript\chaiscript_defines.hpp"
#include "chaiscript\chaiscript_stdlib.hpp"

namespace Engine
{

  void SetCurrentLevel(Level *lvl)
  {
    Api_CurrentLevel = lvl;
  }

  void BindLevelMethods(chaiscript::ChaiScript *Engine)
  {
    if (Engine) {
      Engine->add(chaiscript::fun(&AddActor), "AddActor");
      Engine->add(chaiscript::fun(&KillActor), "KillActor");
      Engine->add(chaiscript::fun(&GetTileName), "GetTileName");
      Engine->add(chaiscript::fun(&LoadLevelInformation), "LoadLevelInformation");
    }
  }

  void AddActor(std::string Name, float x, float y)
  {

  }

  void KillActor(std::string Name)
  {

  }

  std::string GetTileName(float x, float y)
  {
    return{};
  }

  void LoadLevelInformation(std::string Filename)
  {

  }

}
