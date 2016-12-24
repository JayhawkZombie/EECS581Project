#include "../../Headers/Level/LevelTile.h"

namespace Engine
{


  LevelTile::LevelTile()
  {
    SetID("UnnamedTile");
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

  void LevelTile::SerializeOut(std::ostream &out)
  {

  }


  void LevelTile::SetISAnimated(bool anim)
  {
    IsAnimated = anim;
  }

  void LevelTile::SetIsTraversible(bool trav)
  {
    IsTraversible = trav;
  }

  void LevelTile::SetTextureFrameIndices(std::vector<std::size_t> frames)
  {
    FrameIndices = frames;
  }

  std::vector<std::size_t> LevelTile::GetFrameIndices() const
  {
    return FrameIndices;
  }

  void LevelTile::SetTileSheet(std::shared_ptr<SpriteSheet> sheet)
  {
    TileSheet = sheet;
  }

  std::shared_ptr<SpriteSheet> LevelTile::GetTileSheet() const
  {
    return TileSheet;
  }

  bool LevelTile::GetIsAnimated() const
  {
    return IsAnimated;
  }

  bool LevelTile::GetIsTraversible() const
  {
    return IsTraversible;
  }
}
