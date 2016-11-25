#ifndef SFENGINE_EXPOSED_LEVEL_API_H
#define SFENGINE_EXPOSED_LEVEL_API_H

#include "../BasicIncludes.h"
#include "Level.h"
#include "LevelEnvironment.h"

namespace Engine
{

  Level *Api_CurrentLevel = nullptr;
  LevelEnvironment *Api_CurrentEnvironment = nullptr;

  void SetCurrentLevel(Level *lvl);
  void BindLevelMethods(chaiscript::ChaiScript *Engine);

  void AddActor(std::string Name, float x, float y);
  void KillActor(std::string Name);
  std::string GetTileName(float x, float y);

  void LoadLevelInformation(std::string filename);
}

#endif
