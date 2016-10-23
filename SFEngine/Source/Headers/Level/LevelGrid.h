#ifndef SFENGINE_LEVEL_GRID_H
#define SFENGINE_LEVEL_GRID_H

#include "../Utils/ListTemplates.h"
#include "../Utils/Mat2D.h"
#include "../Render/Render.h"
#include "../BasicIncludes.h"

#include <memory>
#include <unordered_map>
#include <SFML\Graphics.hpp>

namespace Engine
{

  class LevelObject;

  struct GridCell {
    float PositionX, PositionY;

    Util::LinkedList<LevelObject *> ContainedItems;
  };

  /**
   * A grid for the background tiles
   *  crafted specifically for quickly running through the tile set
   *  and pulling out the tiles to render very quickly
   */
  class TileGrid
  {
  public:
    TileGrid();
    ~TileGrid();

    void SetGridSize(std::size_t GridHeight, std::size_t GridWidth, const sf::Vector2f &scale);
    void GetTexture(const std::string &ID, std::shared_ptr<sf::Texture> texture);
    void CreateTexturizedGrid(std::string &str);
    void ClearGrid();
    void ScaleTiles(const sf::Vector2f &scale);
    void Render();

  private:
    std::size_t GridSizeX, GridSizeY, TileWidth, TileHeight, TextureWidth, TextureHeight;
    sf::Vector2f TileScale;
    Matrix<sf::RectangleShape> Grid;
    Matrix<std::string> StringGrid;

    sf::RenderTexture RenderTexture;
    sf::Sprite RenderSprite;
    std::unordered_map<std::string, std::shared_ptr<sf::Texture>> Textures;
  };

  class LevelGrid
  {
  public:
    LevelGrid(std::size_t GridHeight, std::size_t GridWidth, size_t GridCellScale /*How big each cell is relative to each game unit*/);
    ~LevelGrid();

    bool AddItem(LevelObject *object, const sf::Vector2f &position);
    

  private:
    std::size_t GridSizeX, GridSizeY, CellScale;
    Matrix<GridCell> Grid;
    //GridCell **Grid;
  };


}

#endif
