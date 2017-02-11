#ifndef SFENGINE_EDITOR_PROJECT_H
#define SFENGINE_EDITOR_PROJECT_H

#include "../Level/Level.h"

namespace Engine
{

  enum ProjectFileTag : std::uint64_t
  {
    Beginning = 0,
    TimeStamp = 1 << 0,
    PathCheck = 1 << 1,
    EngineVersion = 1 << 2,
    Settings = 1 << 3,
    TileSheets = 1 << 4,

    EOFMarker = 1 << 20
  };


  struct ProjectSettings
  {
    std::string ProjectPath = "";
    std::vector<std::string> Scripts;
  };

  struct EditorProject
  {
    std::vector<std::shared_ptr<TileSheet>> TileSheets;
    ProjectSettings Settings;
  };

}

#endif
