#ifndef SFENGINE_EXPOSED_LEVEL_API_H
#define SFENGINE_EXPOSED_LEVEL_API_H

#include "../BasicIncludes.h"
#include "Level.h"

namespace Engine
{

  Level *Api_CurrentLevel = nullptr;

  void SetCurrentLevel(Level *lvl);
  void BindLevelMethods(chaiscript::ChaiScript *Engine);

  void AddActor(std::string Name, float x, float y);
  void KillActor(std::string Name);
  std::string GetTileName(float x, float y);

  void LoadLevelInformation(std::string filename);
}

#endif
