#include "../../Headers/Level/Level.h"

namespace
{

}

namespace Engine
{

  Level::Level()
  {

  }

  Level::Level(const std::string &lvl)
  {
    Handler.BindCallback(Events::KeyPressed,

                         [this](const sf::Keyboard::Key &k) -> void
    {
      this->HandleKeyPress(k);
    }

    );
    Handler.BindCallback(Events::KeyReleased,

                         [this](const sf::Keyboard::Key &k) ->void
    {
      this->HandleKeyRelease(k);
    }
    );
  }

  Level::~Level()
  {

  }

  void Level::LoadLevel(const std::string &lvlfile)
  {
    std::ifstream in(lvlfile);
    if (!in) {
      std::cerr << "Unable to open level file: " << lvlfile << std::endl;
      return;
    }

    in.seekg(0, std::ios::end);
    auto size = in.tellg();

    in.seekg(std::ios::beg);

    std::vector<char> buffer(size);
    in.read(&buffer[0], size);

    rapidxml::xml_document<> doc;
    doc.parse<0>(&buffer[0]);

    //std::cerr << "Text: " << &buffer[0] << std::endl;
    //need to get the tile sheet path so we can load the texture
    auto LevelNode = doc.first_node();
    auto TileSheetNode = LevelNode->first_node("TileSheet");
    auto TilesNode = TileSheetNode->first_node("Tiles");

    std::string TileSheetPath = TileSheetNode->first_attribute("path")->value();
    unsigned long TileCount = std::stoul(TilesNode->first_attribute("count")->value());
    unsigned long TileHeight = std::stoul(TilesNode->first_attribute("tile_height")->value());
    unsigned long TileWidth = std::stoul(TilesNode->first_attribute("tile_width")->value());

    auto FramesNode = TilesNode->first_node("framedata");

    std::stringstream frames(FramesNode->value());
    std::vector<sf::FloatRect> FrameVec;
    sf::FloatRect rect;

    while (frames >> rect.left >> rect.top >> rect.width >> rect.height) {
      FrameVec.push_back(rect);
    }

    auto tile_node = TilesNode->first_node("tile");

    //parse the tiles
    for (auto i = 0ul; i < TileCount; i++) {
      LevelTile t;
      t.LayoutID = tile_node->first_attribute("id")->value();
      t.SetID(tile_node->first_attribute("title")->value());
      t.IsAnimated = (tile_node->first_attribute("animated")->value() == "true");
      t.IsTraversible = (tile_node->first_attribute("traversible")->value() == "true");

      Tiles[t.LayoutID] = t;
      tile_node = tile_node->next_sibling("tile");
    }

    auto LayoutNode = LevelNode->first_node("Layout");
    auto LayerNode = LayoutNode->first_node("Layer");

    unsigned long layer_height = std::stoul(LayerNode->first_attribute("height")->value());
    unsigned long layer_width = std::stoul(LayerNode->first_attribute("width")->value());

    auto layer_tile_node = LayerNode->first_node("tile");
    while (layer_tile_node) {
      std::string tile_id = layer_tile_node->first_attribute("id")->value();
      std::string positions = layer_tile_node->first_attribute("positions")->value();

      std::cerr << "--------------------------------\n";
      std::cerr << "id: " << tile_id << std::endl;
      std::cerr << "positions: " << positions << "\n--------------------------------" << std::endl;
      layer_tile_node = layer_tile_node->next_sibling("tile");

    }
  }

  void Level::OnShutDown()
  {

  }

  void Level::HandleWindowResized()
  {

  }
}