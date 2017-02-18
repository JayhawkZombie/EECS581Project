#include "../../Headers/Tiles/LevelTile.h"
#include "../../Headers/Tiles/TileGrid.h"
#include "../../Headers/Tiles/TileSheet.h"

namespace Engine
{

  LevelTile::LevelTile()
    : LevelObject()
  {
  }

  LevelTile::LevelTile(const LevelTile & copy)
    : LevelTile()
  {
    Grid = copy.Grid;
    Sheet = copy.Sheet;
    Frames = copy.Frames;
    MyCellX = copy.MyCellX;
    MyCellY = copy.MyCellY;
    Name = copy.Name;
  }

  LevelTile::~LevelTile()
  {
  }

  void LevelTile::TickUpdate(const double & delta)
  {
  }

  void LevelTile::Render(std::shared_ptr<sf::RenderTarget> Target)
  {
  }

  void LevelTile::OnShutDown()
  {
  }

  void LevelTile::SerializeOut(std::ofstream & out)
  {
  }

  void LevelTile::SerializeIn(std::ifstream & in)
  {
  }

  void LevelTile::SetPosition(const sf::Vector2f & pos)
  {
  }

  void LevelTile::SetFrames(const sf::VertexArray & vArr, std::uint32_t NumFrames)
  {
  }

  void LevelTile::UpdateMesh()
  {
  }

  void LevelTile::UpdateSegments()
  {
  }

  TileSheet* LevelTile::GetSheet() const
  {
    return Sheet;
  }

  std::weak_ptr<TileGrid> LevelTile::GetGrid() const
  {
    return Grid;
  }

}
