#ifndef SFENGINE_EDITOR_PROJECT_H
#define SFENGINE_EDITOR_PROJECT_H

#include "../Level/Level.h"

namespace Engine
{
  enum ProjectFileTag
  {
    Beginning = (1 << 0),
    End = (1 << 1),
    ID = (1 << 2),
    ProjectVersion = (1 << 3),
    EditorVersion = (1 << 4),
    EngineVersion = (1 << 5),
    TileBeginning = (1 << 6),
    LevelBeginning = (1 << 7),
    PlacementDataBeginning = (1 << 8),
    PlacementDataEnd = (1 << 9),
    TextureDataBegin = (1 << 10),
    TextureDataEnd = (1 << 11),
    CollisionDataBegin = (1 << 12),
    CollisionDataEnd = (1 << 13),
    TileSheetBeginning = (1 << 14),
    TileSheetEnd = (1 << 15),
    TileSheetCount = (1 << 16),
  };

  enum SettingsTag
  {
    visible = (1 << 1),
    Animated = (1 << 2),
    CollisionEnabled = (1 << 3),
    NonGenericMeshUsed = (1 << 4),
    LightingEnabled = (1 << 5),
    IsLiquid = (1 << 6),
    AllowShaders = (1 << 7)
  };

  struct ProjectSettings
  {
    std::string ProjectPath = "";
    std::vector<std::string> Scripts;
  };

  class EditorProject
  {
  public:
    EditorProject() = default;
    ~EditorProject() = default;

    void Read(const std::string &in);
    void Write(const std::string &out);

    std::vector<std::shared_ptr<TileSheet>> TileSheets;
    ProjectSettings Settings;
    std::string ProjectName;

  private:
    void WriteTileSheet(std::shared_ptr<TileSheet> sheet);
  };

}

#endif
