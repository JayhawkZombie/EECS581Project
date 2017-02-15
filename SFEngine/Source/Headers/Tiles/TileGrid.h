#ifndef SFENGINE_TILE_GRID_H
#define SFENGINE_TILE_GRID_H

#include "LevelTile.h"

namespace Engine
{

  class TileGrid : public BaseEngineInterface
  {
  public:
    TileGrid();
    virtual ~TileGrid();

    void AddTile(std::shared_ptr<LevelTile> Tile);
    void RemoveTile(std::shared_ptr<LevelTile> Tile);

    void SerializeIn(std::ifstream &in) override final;
    void SerializeOut(std::ofstream &out) override final;

    void TickUpdate(const double &delta) override final;
    void Render(std::shared_ptr<sf::RenderTarget> Target) override final;

    void SetBGTileTexture(std::shared_ptr<sf::Texture> Tex);

  protected:
    sf::VertexArray TilesVertices;
    sf::RenderStates TileRenderState;
    std::shared_ptr<sf::Texture> BGTileTexture;
  };

}

#endif
