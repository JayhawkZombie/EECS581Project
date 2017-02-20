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

    void GetTile(const sf::Vector2f &Position) const;

    void SetBGTileTexture(std::shared_ptr<sf::Texture> Tex);

    void DrawGridLines(bool draw);

  protected:
    bool DrawGrid = false;
    sf::Vector2f GridSize;
    sf::Vector2f TileSize;
    sf::VertexArray GridLines;
    sf::VertexArray TilesVertices;
    sf::RenderStates TileRenderState;
    std::shared_ptr<sf::Texture> BGTileTexture;
    sf::VertexArray TileVerts;

    std::vector<std::shared_ptr<LevelTile>> Tiles;
  };

}

#endif
