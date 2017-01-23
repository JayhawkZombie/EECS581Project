#include "../../Headers/Level/LevelTile.h"

namespace Engine
{


  LevelTile::LevelTile()
    :
    AnimationDuration(0),
    CurrentFrame(0),
    FrameTime(0),
    CurrentAnimationDuration(0)
  {
    SetID("UnnamedTile");
  }

  LevelTile::LevelTile(const LevelTile &other)
    :
    TileSheet(other.TileSheet),
    FrameIndices(other.FrameIndices),
    IsAnimated(other.IsAnimated),
    IsTraversible(other.IsTraversible),
    AnimationDuration(other.AnimationDuration),
    FrameTime(other.FrameTime),
    LayoutID(other.LayoutID)
  {

  }

  LevelTile::~LevelTile()
  {

  }

  void LevelTile::Render()
  {
    
  }

  void LevelTile::TickUpdate(const double &delta)
  {
    
  }

  void LevelTile::OnShutDown()
  {
    
  }

  void LevelTile::SerializeOut(std::ofstream &out)
  {
    

  }

  void LevelTile::SerializeIn(std::ifstream &in)
  {

  }
}
