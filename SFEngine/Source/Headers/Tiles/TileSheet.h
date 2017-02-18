#ifndef SFENGINE_TILE_SHEET_H
#define SFENGINE_TILE_SHEET_H

#include "LevelTile.h"

namespace Engine
{

  const std::uint32_t MaxTilesPerSheet = 1000;

  class TileSheet : public BaseEngineInterface
  {
  public:
    TileSheet();
    virtual ~TileSheet();

    void SerializeIn(std::ifstream &in) override final;
    void SerializeOut(std::ofstream &out) override final;

    void TickUpdate(const double &delta) override final;
    void Render(std::shared_ptr<sf::RenderTarget> Target) override final;
    virtual void OnShutDown() override final;

    void RenderTiles(const sf::VertexArray &Vertices);
    void ReadFromMap(const std::string &filename);

    sf::VertexArray GetTileVertices(const std::string &Name) const;
    void SetTileVertices(const std::string &Name);

    std::map<std::string, sf::VertexArray> GetTiles();
    std::shared_ptr<LevelTile> GenerateTile(const std::string &Name);

    std::map<std::string, std::shared_ptr<LevelTile>> GetLevelTiles();

    std::shared_ptr<sf::Texture> GetTexture() const;
    void SetTexture(std::shared_ptr<sf::Texture> Tex);

    void AddTile(const std::string &str, const sf::IntRect &Rect);
    void RemoveTile(const std::string &str);

  protected:
    std::shared_ptr<sf::Texture> Texture;
    std::map<std::string, sf::VertexArray> GenericTiles;
    std::map<std::string, std::shared_ptr<LevelTile>> Tiles;
    sf::RenderStates SheetState;
  };

}

#endif
