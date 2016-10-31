#include "../../Headers/Level/Level.h"

namespace Engine
{

  void Level::LoadLevel()
  {
    LOADER = std::thread(
      [this]() {this->LoadFromFile(); }
    );
  }

  void Level::LoadFromFile()
  {
    std::ifstream IN(LevelFile);
    if (IN.fail()) {
      std::cerr << "Unable to open level file: \"" << LevelFile << std::endl;
      return;
    }

    ResourceLock->lock();

    CurrentLoadingMessage = "Loading Level Config";

    ResourceLock->unlock();

    TileSize = Util::GetUnsignedIntConfig("Config", "TileSize", 0, LevelFile, IN);
    std::cerr << "TileSize = " << TileSize << std::endl;
    LevelSizeX = Util::GetUnsignedIntConfig("Config", "LevelSizeX", 0, LevelFile, IN);
    LevelSizeY = Util::GetUnsignedIntConfig("Config", "LevelSizeY", 0, LevelFile, IN);
    sf::FloatRect StartingView = Util::GetFloatRectConfig("Config", "StartingView", sf::FloatRect(0, 0, 0, 0), LevelFile, IN);


    TilesAcross = Util::GetUnsignedIntConfig("Config", "TilesAcross", 1, LevelFile, IN);
    std::cerr << "TilesAcross = " << TilesAcross << std::endl;
    if (LevelSizeX == 0 || LevelSizeY == 0) {
      std::cerr << "Level size is 0. Aborting loading" << std::endl;
      return;
    }

    Environment.CurrentView = StartingView;
    Environment.TileSize = TileSize;
    Environment.TilesAcross = TilesAcross;
    Environment.LevelSizeX = LevelSizeX;
    Environment.LevelSizeY = LevelSizeY;
    BGTiles.Create(LevelSizeY, LevelSizeX);

    NumTiles = Util::GetUnsignedIntConfig("Tiles", "NumTiles", 0, LevelFile, IN);
    NumTextures = Util::GetUnsignedIntConfig("Tiles", "NumTextures", 0, LevelFile, IN);
    std::string TilesBraced = Util::GetBracedConfig("Tiles", "Tiles", "{}", LevelFile, IN);
    if (TilesBraced == "{}") {
      std::cerr << "No tiles are present in the level file. Aborting loading" << std::endl;
      return;
    }

    auto v = Util::ParsePairedText(TilesBraced, NumTiles);
    for (std::size_t i = 0; i < v.size(); ++i) {
      LayoutIDTOTextureID.emplace(
        std::piecewise_construct,
        std::make_tuple(v[i].first),
        std::make_tuple(v[i].second)
      );
    }

    for (auto & tile : LayoutIDTOTextureID) {
      LoadTileData(tile.first, tile.second, IN);
    }

    while (TexturesReceived < NumTextures)
    {
    }

    LoadTileLayout(IN);
    AssignTileTextures();
  }

  void Level::LoadTileData(const std::string &layoutTag, const std::string &TileTag, std::ifstream &IN)
  {
    //Go to the tag in the file and retrieve the relevant information
    ResourceLock->lock();

    Tiles.push_back({});
    std::size_t Index = Tiles.size() - 1;

    std::string TileFile = Util::GetStringConfig(TileTag, "FilePath", "", LevelFile, IN);
    bool IsAnimated = Util::GetBooleanConfig(TileTag, "Animated", false, LevelFile, IN);

    Tiles[Index].FilePath = TileFile;
    Tiles[Index].TileID = TileTag;
    Tiles[Index].animated = IsAnimated;
    Tiles[Index].TileSprite.setTextureRect({ 0, 0, static_cast<int>(TileSize), static_cast<int>(TileSize) });

    float scalex = WindowSize.x / (TileSize * TilesAcross);
    float scaley = WindowSize.y / (TileSize * TilesAcross);
    Tiles[Index].TileSprite.setScale({ scalex , scaley});
    Environment.Scale = sf::Vector2f(scalex, scaley);
    
    ResourceLock->unlock();

    ResourceManager->RequestTexture(TileFile, TileTag, 
                                    [this](std::shared_ptr<sf::Texture> t, const std::string &s) -> void
                                    {
                                    this->StoreTexture(t, s);
                                    }
    );
  }

  void Level::LoadTileLayout(std::ifstream &IN)
  {
    std::string layout = Util::GetBracedConfig("Layer0", "TileLayout", "{}", LevelFile, IN);
    if (layout == "{}") {
      std::cerr << "Error reading tile layout from file. Aborting loading." << std::endl;
      return;
    }

    layout.erase(layout.end() - 1);
    layout.erase(layout.begin());

    std::stringstream ss(layout);
    std::string temp{ "" };
    
    while (ss >> temp)
      TileLayout.push_back(temp);

    //Now that we have the tile layout loaded, we can populate the grid with the background tiles
    Environment.EnvironmentGrid.Create(LevelSizeY, LevelSizeX);

    //Loop through the grid and assign the LEVEL position, IDs, etc for the grid cells
    for (std::size_t Y = 0; Y < LevelSizeY; ++Y) {
      for (std::size_t X = 0; X < LevelSizeX; ++X) {
        ResourceLock->lock();

        Environment.EnvironmentGrid.Mat[Y][X].LevelPosition = sf::Vector2f(X * TileSize, Y * TileSize);
        Environment.EnvironmentGrid.Mat[Y][X].BGTile.TileID = LayoutIDTOTextureID[TileLayout[LevelSizeX * Y + X]];
        ++Environment.TilesAssigned;

        ResourceLock->unlock();
      }
    }
  }

  void Level::AssignTileTextures()
  {
    for (auto & Tile : Tiles) {
      Tile.TileSprite.setTexture(*TileIDToTexture[Tile.TileID]);
    }

    //Loop through the grid and assign the textures to each background tile
    //IF, for some strange reason, there's an ID in there we can't recognize, we'll catch it
    for (std::size_t Y = 0; Y < LevelSizeY; ++Y) {
      for (std::size_t X = 0; X < LevelSizeX; ++X) {
        ResourceLock->lock();
        
        std::string ID = Environment.EnvironmentGrid.Mat[Y][X].BGTile.TileID;
        auto it = TileIDToTexture.find(ID);

        if (it != TileIDToTexture.end()) {
          Environment.EnvironmentGrid.Mat[Y][X].BGTile.TileSprite.setTexture(
            *it->second);
        }

        ResourceLock->unlock();
      }
    }

    ResourceLock->lock();
    ReadyToPlay = true;
    Environment.UpdateView();
    ResourceLock->unlock();
  }

  void Level::StoreTexture(std::shared_ptr<sf::Texture> texture, const std::string &ID)
  {
    TexturesReceived++;

    ResourceLock->lock();
    TileIDToTexture.emplace(
      std::piecewise_construct,
      std::make_tuple(ID),
      std::make_tuple(texture)
    );

    ResourceLock->unlock();
  }
}