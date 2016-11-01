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
    //BGTiles.Create(LevelSizeY, LevelSizeX);

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

  void Level::LoadLights(std::ifstream &IN)
  {
    auto color = Util::GetFloatRectConfig("GlobalLight", "Color", sf::FloatRect(255,255,255,0), LevelFile, IN);
    auto intensity = Util::GetFloatConfig("GlobalLight", "Intensity", 0, LevelFile, IN);

    std::shared_ptr<GlobalLightSource> Light(new GlobalLightSource);
    Light->SetColor(sf::Color(color.left, color.top, color.width, color.height));
    Light->SetIntensity(intensity);

    Environment.AddGlobalLight("GlobalLight", Light);
  }

  void Level::LoadVolumes(std::ifstream &IN)
  {

  }

  void Level::LoadTileData(const std::string &layoutTag, const std::string &TileTag, std::ifstream &IN)
  {
    //Go to the tag in the file and retrieve the relevant information
    ResourceLock->lock();

    std::string TileFile = Util::GetStringConfig(TileTag, "FilePath", "", LevelFile, IN);
    bool IsAnimated = Util::GetBooleanConfig(TileTag, "Animated", false, LevelFile, IN);
    std::string Frames = Util::GetBracedConfig(TileTag, "Frames", "{}", LevelFile, IN);
    std::size_t NumFrames = Util::GetUnsignedIntConfig(TileTag, "NumFrames", 1, LevelFile, IN);
    if (NumFrames <= 0)
      NumFrames = 1;

    double AnimationDuration = (double)Util::GetUnsignedIntConfig(TileTag, "AnimationDuration", 0, LevelFile, IN);;
    double FrameDelta = AnimationDuration / NumFrames;

    Frames.erase(Frames.begin());
    Frames.erase(Frames.end() - 1);
    auto V = Util::ParseSFRectConfig<int>(Frames, NumFrames);

    MapTileIDToTile[TileTag] = Tile{};
    Tile *tile = &MapTileIDToTile[TileTag];
    tile->FilePath = TileFile;
    tile->Frames = V;
    tile->CurrentFrame = 0;
    tile->IsAnimated = IsAnimated;
    tile->NumFrames = NumFrames;
    tile->FrameDelta = AnimationDuration / NumFrames;
    tile->TotalAnimationDuration = AnimationDuration;

    float scalex = WindowSize.x / (TileSize * TilesAcross);
    float scaley = WindowSize.y / (TileSize * TilesAcross);
    
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

        std::string _ID = LayoutIDTOTextureID[TileLayout[LevelSizeX * Y + X]];
        //auto it = MapTileIDToTile.find(_ID);
        //if (it != MapTileIDToTile.end()) {
        //  Environment.EnvironmentGrid.Mat[Y][X].BGTile.FrameDelta = it->second.FrameDelta;
        //  Environment.EnvironmentGrid.Mat[Y][X].BGTile.Frames = it->second.Frames;
        //  Environment.EnvironmentGrid.Mat[Y][X].BGTile.NumFrames = it->second.NumFrames;
        //  Environment.EnvironmentGrid.Mat[Y][X].BGTile.IsAnimated = it->second.IsAnimated;
        //  Environment.EnvironmentGrid.Mat[Y][X].BGTile.TotalAnimationDuration = it->second.TotalAnimationDuration;
        //}

        Environment.EnvironmentGrid.Mat[Y][X].LevelPosition = sf::Vector2f(X * TileSize, Y * TileSize);
        Environment.EnvironmentGrid.Mat[Y][X].BGTile.TileID = _ID;
        ++Environment.TilesAssigned;

        ResourceLock->unlock();
      }
    }
  }

  void Level::AssignTileTextures()
  {
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

        std::string _ID = LayoutIDTOTextureID[TileLayout[LevelSizeX * Y + X]];
        auto _it = MapTileIDToTile.find(_ID);
        if (_it != MapTileIDToTile.end()) {
          Environment.EnvironmentGrid.Mat[Y][X].BGTile.FrameDelta = _it->second.FrameDelta;
          Environment.EnvironmentGrid.Mat[Y][X].BGTile.Frames = _it->second.Frames;
          Environment.EnvironmentGrid.Mat[Y][X].BGTile.NumFrames = _it->second.NumFrames;
          Environment.EnvironmentGrid.Mat[Y][X].BGTile.IsAnimated = _it->second.IsAnimated;
          Environment.EnvironmentGrid.Mat[Y][X].BGTile.TotalAnimationDuration = _it->second.TotalAnimationDuration;
        }

        ResourceLock->unlock();
      }
    }

    ResourceLock->lock();
    ReadyToPlay = true;
    Environment.UpdateView(0.f);
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