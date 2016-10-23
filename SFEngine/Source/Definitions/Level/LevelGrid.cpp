#include "../../Headers/Level/LevelGrid.h"

#include <sstream>
#include "../../Headers/Utils/Mat2D.h"

namespace Engine
{
  TileGrid::TileGrid()
    : GridSizeX(0), GridSizeY(0), TileScale({ 1,1 }), TileHeight(0), TileWidth(0)
  {

  }

  TileGrid::~TileGrid()
  {
    
  }

  void TileGrid::GetTexture(const std::string &ID, std::shared_ptr<sf::Texture> texture)
  {
    Textures.emplace(
      std::piecewise_construct,
      std::make_tuple(ID),
      std::make_tuple(texture)
    );

    TextureWidth = TileWidth = texture.get()->getSize().x;
    TextureHeight = TileHeight = texture.get()->getSize().y;
  }

  void TileGrid::ClearGrid()
  {

  }

  void TileGrid::Render()
  {
    Render::RenderSprite(&RenderSprite);
  }

  void TileGrid::ScaleTiles(const sf::Vector2f &scale)
  {
    TileScale = scale;
  }

  void TileGrid::CreateTexturizedGrid(std::string &str)
  {
    RenderTexture.create(TextureWidth * GridSizeX, TextureHeight * GridSizeY);

    StringGrid.Create(GridSizeY, GridSizeX);
    
    sf::Sprite spr;
    std::vector<std::vector<std::string>> Map;
    
    std::stringstream stream(str);

    std::size_t x{ 0 }, y{ 0 };
    std::string temp{ "" };

    std::vector<std::string> v;

    while (stream >> temp) {
      v.push_back(temp);
      StringGrid.Assign(y, x, temp);
      
      std::cerr << temp << " ";
      ++x;
      if (x >= GridSizeX) {
        ++y;
        x = 0;
        std::cerr << std::endl;
      }
    }

    for (std::size_t ROW = 0; ROW < GridSizeY; ++ROW) {
      for (std::size_t COL = 0; COL < GridSizeX; ++COL) {
        spr.setPosition(COL * TextureWidth, ROW * TextureHeight);
        spr.setTexture(*Textures[*StringGrid(ROW, COL)]);

        RenderTexture.draw(spr);
      }
    }
    RenderTexture.display();
    RenderSprite.setTexture(RenderTexture.getTexture());
    RenderSprite.setTextureRect({ 0, 0, int(GridSizeX) * int(TileWidth), int(GridSizeY) * int(TileHeight) });

    sf::Vector2f scale;
    scale.x = (WindowSize.x) / (TextureWidth * GridSizeX);
    scale.y = (WindowSize.y) / (TextureHeight * GridSizeY);
    TileScale = scale;

    RenderSprite.setScale(TileScale);
  }

  void TileGrid::SetGridSize(std::size_t GridHeight, std::size_t GridWidth, const sf::Vector2f &scale)
  {


    GridSizeX = GridWidth;
    GridSizeY = GridHeight;
    TileScale = scale;

    Grid.Create(GridSizeX, GridSizeY);
  }

  LevelGrid::LevelGrid(std::size_t GridHeight, std::size_t GridWidth, std::size_t GridCellScale)
    : GridSizeX(GridWidth), GridSizeY(GridHeight), CellScale(GridCellScale)
  {
    Grid.Create(GridSizeY, GridSizeX);
  }

  LevelGrid::~LevelGrid()
  {
    
  }

  bool LevelGrid::AddItem(LevelObject *object, const sf::Vector2f &pos)
  {
    std::size_t CELL_X = std::floor(pos.x / CellScale);
    std::size_t CELL_Y = std::floor(pos.y / CellScale);

    if (CELL_X >= GridSizeX || CELL_Y >= GridSizeY)
      return false;

    GridCell* cell = Grid(CELL_X, CELL_Y);
    cell->ContainedItems.AddItem(object);
    return true;
  }


}
