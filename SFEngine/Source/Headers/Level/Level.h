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

namespace Engine
{



  class Level : public BaseEngineInterface
  {

  public:
    Level(const std::string &levelFile);
    Level(const Level &) = delete;
    ~Level();

    void TickUpdate(const double &delta) override;
    void Render() override;
    void OnShutDown() override;

    void LoadLevel();
    void JoinLoaderThread();
    void IsReady() const;

    void HandleKeyPress(const sf::Keyboard::Key &key);
    void HandleKeyRelease(const sf::Keyboard::Key &key);

  private:
    void RenderRegular();
    void RenderLoadingScreen();
    Render::RenderSettings LevelRenderSettings;

    //Mutex for synchronization
    std::mutex *ResourceLock;

    std::thread LOADER;
    std::string LevelFile;

    void LoadFromFile();
    void LoadTileData(const std::string &layoutTag, const std::string &TileTag, std::ifstream &IN);
    void LoadTileLayout(std::ifstream &IN);
    void LoadLights(std::ifstream &IN);
    void LoadVolumes(std::ifstream &IN);
    void AssignTileTextures();
    void StoreTexture(std::shared_ptr<sf::Texture> texture, const std::string &ID);
    std::size_t TexturesReceived;

    LevelEnvironment Environment;
    std::shared_ptr<sf::Font> LevelFont;

    //A couple things for a crappy makeshift loading screen
    std::string CurrentLoadingMessage;
    unsigned int LoadingProgress;
    sf::RectangleShape LoadingTexturesBar;
    sf::Font LoadingFont;
    sf::Text LoadingMessageText;

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
