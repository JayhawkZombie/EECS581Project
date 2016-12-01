#ifndef SFENGINE_LEVEL_LOADER_H
#define SFENGINE_LEVEL_LOADER_H


#include "../BasicIncludes.h"
#include "LevelObject.h"
#include "../Actor/Player.h"
#include "LevelTile.h"
#include "../Lights/GenericLightSource.h"
#include "../Lights/GlobalLightSource.h"



namespace Engine
{

  typedef std::shared_ptr<LevelTile> LevelTileResource;
  typedef std::shared_ptr<GenericActor> LevelActorResource;
  typedef std::shared_ptr<GenericLightSource> LevelLightResource;
  typedef std::shared_ptr<LevelObject> LevelObjectResource;

  struct LoaderLayer
  {
    std::shared_ptr<std::vector<std::vector<LevelTileResource>>> Tiles;
    std::shared_ptr<std::vector<LevelActorResource>> Actors;
    std::shared_ptr<std::vector<LevelLightResource>> Lights;
    std::shared_ptr<std::vector<LevelObjectResource>> Objects;
  };

  struct LoaderTileInfo
  {
    LoaderTileInfo()
      : TileID(""), LayoutID(""), FilePath(""), Frames({}), TextureRect({}), Texture({}), Tranversible(false), IsAnimated(false), AnimationDuration(0.f)
    {}
    LoaderTileInfo(const LoaderTileInfo &info)
      : TileID(info.TileID), LayoutID(info.LayoutID), FilePath(info.FilePath), Frames(info.Frames), TextureRect(info.TextureRect),
      Texture(info.Texture), Tranversible(info.Tranversible), IsAnimated(info.IsAnimated), AnimationDuration(info.AnimationDuration)
    {}
    std::string TileID;
    std::string FilePath;
    std::vector<sf::IntRect> Frames;
    sf::IntRect TextureRect;
    std::shared_ptr<sf::Texture> Texture;
    std::string LayoutID;
    bool Tranversible;
    bool IsAnimated;
    double AnimationDuration;
  };

  struct LayerInfo
  {
    std::size_t Height, Width;
    std::string RawLayout;
    std::vector<std::vector<std::string>> FormalLayout;
  };

  class LevelLoader
  {
  public:
    LevelLoader();
    ~LevelLoader();

    void Load(const std::string &lvlfile);
    void JoinThread();
    void TestRender();
    bool DoneLoading() const;

  private:
    std::thread LOADER_THREAD;
    std::mutex *Lock;
    std::map<std::string, std::string> *LayoutIDToTileID;
    std::vector<std::string> *TileIDs;
    std::map<std::string, std::shared_ptr<sf::Texture>> *TileIDToTexture;
    bool FailedToLoad;
    bool IsDoneSettingData = false;

    //ConfigInfo
    bool ShadersEnabled;
    std::size_t NumLayers, LevelSizeX, LevelSizeY, TileSize, TilesAcross;
    std::size_t NumTiles, NumTexturesReceived;
    sf::Vector2f Scale;
    sf::FloatRect StartingView;
    std::string LevelFile;
    std::map<std::string, LoaderTileInfo> TileInformation;
    std::vector<LoaderTileInfo> TileInfos;
    std::vector<LayerInfo> LayersInfo;
    std::vector<std::shared_ptr<LoaderLayer>> Layers;

    void DebugPrintData();

    void LoadLevelInformation(const std::string &filename);
    void LoadFailure(std::ifstream &IN);
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

    void LoadLights(std::ifstream &IN);
    void LoadVolumes(std::ifstream &IN);
    void LoadActors(std::ifstream &IN);
  };


}


#endif
