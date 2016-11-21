#ifndef SFENGINE_OPT_LEVEL_G
#define SFENGINE_OPT_LEVEL_G


#include "../Engine/BaseEngineInterface.h"
#include "Layer.h"
#include "LevelObject.h"
#include "LevelEventSequences.h"
#include "../Events/EventSequence.h"
#include "../Actor/Player.h"

#include "../Lights/GlobalLightSource.h"
#include "LevelEnvironment.h"

#include "../Physics/Physics.h"

class GameMain;

namespace Engine
{

  struct LayerInformation {
    std::vector<std::string> LayerLayout;
    std::string RawLayout;
    unsigned int Height, Width;
  };

  struct TileInfo {
    std::string TileID;
    std::string LayoutID;
    std::string FilePath;
    bool Animated, Traversible;
    sf::IntRect TextureRect;
    std::vector<sf::IntRect> AnimationFrames;
    std::shared_ptr<sf::Texture> Texture;
  };

  struct LevelLoadInformation {
    bool ShadersEnabled;
    unsigned int NumLayers;
    unsigned int LevelSizeX, LevelSizeY;
    unsigned int TileSize, TilesAcross;
    sf::FloatRect StartingView;

    std::vector<LayerInformation> LayersInfo;
    std::map<std::string, std::string> LayoutIDToTileID;
    unsigned int NumTiles;
    std::vector<TileInfo> TileInfos;
  };

  class Level : public BaseEngineInterface
  {

  public:
    friend class GameMain;
    TYPEDEF_PARENT_CLASS(Engine::BaseEngineInterface);

    Level(const std::string &levelFile);
    Level(const Level &) = delete;
    ~Level();

    void TickUpdate(const double &delta) override;
    void Render() override;
    void OnShutDown() override;
    virtual void SerializeOut(std::ostream &out) override;

    void LoadLevel();
    void JoinLoaderThread();
    bool IsReady() const {
      return ReadyToPlay;
    }

    void HandleKeyPress(const sf::Keyboard::Key &key);
    void HandleKeyRelease(const sf::Keyboard::Key &key);
    void HandleWindowResized();

  private:
    void RenderRegular();
    void RenderLoadingScreen();
    Render::RenderSettings LevelRenderSettings;

    //Mutex for synchronization
    std::mutex *ResourceLock;

    std::thread LOADER;
    std::thread INFO_LOADER;
    std::string LevelFile;

    //Internal method, load the information from the file
    void LoadFromFile();
    
    //Load all of the information about the level before actually loading it off disk
    LevelLoadInformation LoadingInformation;
    void LoadLevelInformation(const std::string &filename);

    void LoadConfigInfo(std::ifstream &IN);
    void LoadLayerInfo(std::ifstream &IN);
    void LoadTileInfo(std::ifstream &IN);
    void LoadLayoutInfo(std::ifstream &IN);
    void RequestLevelData();
    void FormalizeLayerLayouts();
    void ReceiveLevelTexture(std::shared_ptr<sf::Texture> texture, const std::string &ID);
    void SetLevelData();
    void LoadLayerData(std::ifstream &IN);
    void LoadTilesData(std::ifstream &IN);
    void LoadObjectData(std::ifstream &IN);

    void LoadTileData(const std::string &layoutTag, const std::string &TileTag, std::ifstream &IN);
    void LoadTileLayout(std::ifstream &IN);
    void LoadLights(std::ifstream &IN);
    void LoadVolumes(std::ifstream &IN);
    void LoadActors(std::ifstream &IN);
    void AssignTileTextures();
    void StoreTexture(std::shared_ptr<sf::Texture> texture, const std::string &ID);
    std::size_t TexturesReceived;

    LevelEnvironment Environment;
    std::shared_ptr<sf::Font> LevelFont;

    //Map the short sequence of characters used in the layout
    //to the ID used to ID the tile
    std::map <
      std::string, std::string
    > LayoutIDTOTextureID;

    //Map the unique Tile ID to the "Tile"'s texture
    std::map <
      std::string, std::shared_ptr<sf::Texture>
    > TileIDToTexture;

    //Information about how many textures and tiles there are
    std::size_t NumTextures, NumTiles;
    bool ReadyToPlay;

    //Informaton about level size and scaling tiles to fit the screen
    std::size_t LevelSizeX, LevelSizeY, TileSize, TilesAcross;

    //We store information about each tile (unique info, but nothing about position)
    std::map<std::string, Tile> MapTileIDToTile;
    std::vector<std::string> TileLayout;

  };

}

#endif
