#ifndef SFENGINE_LEVEL_TILE_H
#define SFENGINE_LEVEL_TILE_H


#include "../Actor/Player.h"
#include "../Lights/GlobalLightSource.h"
#include "../Utils/SpriteSheet.h"


namespace Engine
{

  class TileGrid;
  class TileSheet;

  class LevelTile : public LevelObject
  {
  public:
    LevelTile();
    LevelTile(const LevelTile &copy);
    virtual ~LevelTile();

    virtual void TickUpdate(const double &delta) override;
    virtual void Render(std::shared_ptr<sf::RenderTarget> Target) override;
    virtual void OnShutDown() override;
    virtual void SerializeOut(std::ofstream &out) override;
    virtual void SerializeIn(std::ifstream &in) override;
    virtual void SetPosition(const sf::Vector2f &pos);
    virtual void SetFrames(const sf::VertexArray &vArr, std::uint32_t NumFrames);
    virtual void UpdateMesh();
    virtual void UpdateSegments();
    virtual TileSheet* GetSheet() const;
    virtual std::weak_ptr<TileGrid> GetGrid() const;
    virtual void SetSize(const sf::Vector2f &Size);
  
    std::vector<sf::VertexArray> Frames = { sf::VertexArray(sf::Quads, 4) };
    sf::IntRect TextureRect;
    sf::RectangleShape TileRect;

    std::weak_ptr<TileGrid> Grid;
    TileSheet *Sheet = nullptr;
    std::uint32_t MyCellX = 0, MyCellY = 0;
    std::string Name;
  };
  
}


#endif
