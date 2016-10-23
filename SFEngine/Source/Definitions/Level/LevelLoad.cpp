#include "../../Headers/Level/Level.h"

namespace Engine
{
  void Level::LoadLevel()
  {
    LOADER = std::thread(
     [this]() { this->LoadFromFile(LevelFile); }
    );
    Playable = true;
  }

  void Level::LoadFromFile(const std::string &file)
  {
    LevelFile = file;

    std::ifstream IN(file);
    if (IN.fail()) {
      std::cerr << "Error: Failed to open level file \"" << file << "\"" << std::endl;
      return;
    }
    else {
      __LoadWithGrid(IN);
    }
  }

  void  Level::__LoadWithGrid(std::ifstream &IN)
  {

    TileGridWidth     = Util::GetUnsignedIntConfig("Layer0/Layout", "Width",        0, LevelFile, IN);
    TileGridHeight    = Util::GetUnsignedIntConfig("Layer0/Layout", "Height",       0, LevelFile, IN);
    TileTextureWidth  = Util::GetUnsignedIntConfig("Layer0/Layout", "TextureWidth", 1, LevelFile, IN);

    //Get the braced level layout
    /**
     * { T T T T 
     *    ...
     *   O W X C }
     */
    //And then chop off the 
    GridTileLayout      = Util::GetBracedConfig("Layer0/Layout",        "TileLayout", "{}", LevelFile, IN);
    GridTextures        = Util::GetBracedConfig("Layer0/Textures",      "Textures",   "{}", LevelFile, IN);
    NumGridTextures     = Util::GetUnsignedIntConfig("Layer0/Textures", "NumTextures", 0,   LevelFile, IN);

    GridTileLayout.erase(0, 1);
    GridTileLayout.erase(GridTileLayout.size() - 1);

    Environment.BackgroundTiles = new TileGrid;
    Environment.BackgroundTiles->SetGridSize(TileGridHeight, TileGridWidth, { 1,1 });
    //Get the textures and request them from the resource manager
    auto texvector = Util::ParsePairedText(GridTextures, NumGridTextures);
    
    for (auto & pair : texvector) {
      ResourceManager->RequestTexture(pair.second, pair.first,
                                      [this](const std::shared_ptr<sf::Texture> t, const std::string &str) -> void
                                      { this->__GetGridTexture(str, t); } );
    }
  }

  void Level::__GetGridTexture(const std::string &ID, std::shared_ptr<sf::Texture> texture)
  {
    static std::size_t Count = 0;
    Environment.BackgroundTiles->GetTexture(ID, texture);

    ++Count;
    if (Count >= NumGridTextures) {
      //We've already gotten all of the texutres now
      Environment.BackgroundTiles->CreateTexturizedGrid(GridTileLayout);
    }
  }

}