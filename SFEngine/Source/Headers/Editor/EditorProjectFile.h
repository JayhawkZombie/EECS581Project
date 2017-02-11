#ifndef SFENGINE_EDITOR_PROJECT_FILE_H
#define SFENGINE_EDITOR_PROJECT_FILE_H

#include "../Level/Level.h"

namespace Engine
{

  const std::uint64_t FileBeginningTag = static_cast<std::uint64_t>(1 << 1);
  const std::uint64_t ProjectIDTag = static_cast<std::uint64_t>(1 << 2);
  const std::uint64_t TileBeginningTag = static_cast<std::uint64_t>(1 << 5);

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
    CollisionDataEnd = (1 << 13)
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

  struct ProjectFileTextureStruct {
    std::string TextureName;
    std::vector<sf::IntRect> TextureFrames;
  };

  struct ProjectFileTileStruct {
    std::string Name;
    float posX, posY;
    float sizeX, sizeY;
    std::uint32_t LayerIndex;
   
    ProjectFileTextureStruct TileSheetData;
  };

  class ProjectFile
  {
  public:
    ProjectFile() = default;
    ~ProjectFile() = default;

    void Read(const std::string &path);
    void Write(const std::string &path);

    std::bitset<32> Settings;
    std::string ProjectName;
    std::uint64_t ProjectVersion;
    std::vector<ProjectFileTileStruct> Tiles;
    
  };

}

#endif
