#include "../../Headers/Tiles/TileGrid.h"

namespace Engine
{

  TileGrid::TileGrid()
    : BaseEngineInterface()
  {
  }

  TileGrid::~TileGrid()
  {
  }

  void TileGrid::AddTile(std::shared_ptr<LevelTile> Tile)
  {
    Tiles.push_back(Tile);
  }

  void TileGrid::RemoveTile(std::shared_ptr<LevelTile> Tile)
  {
  }

  void TileGrid::SerializeIn(std::ifstream & in)
  {
  }

  void TileGrid::SerializeOut(std::ofstream & out)
  {
  }

  void TileGrid::TickUpdate(const double & delta)
  {
  }

  void TileGrid::Render(std::shared_ptr<sf::RenderTarget> Target)
  {
    for (auto & tile : Tiles)
      tile->Render(Target);
  }

  void TileGrid::GetTile(const sf::Vector2f & Position) const
  {
  }

  void TileGrid::SetBGTileTexture(std::shared_ptr<sf::Texture> Tex)
  {
    BGTileTexture = Tex;
    TileRenderState.texture = BGTileTexture.get();
  }

  void TileGrid::DrawGridLines(bool draw)
  {
    DrawGrid = draw;
  }

}
