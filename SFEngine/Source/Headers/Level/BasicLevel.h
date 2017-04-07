#ifndef SFENGINE_BASIC_LEVEL_H
#define SFENGINE_BASIC_LEVEL_H

#include "../Engine/BaseEngineInterface.h"
#include "../../../ThirdParty/PhysicsEngine.h"
#include "../Globals/GlobalHooks.h"
#include "../../../ThirdParty/SelbaWard/TileMap.hpp"

namespace Engine
{

  class LevelObject;
  class TileSheet;
  class Animation;
  class Collider2D;

  class BasicLevel : public BaseEngineInterface
  {
  public:
    BasicLevel() = delete;
    BasicLevel(const BasicLevel &) = delete;
    BasicLevel(const sf::Vector2u &LevelSize, const sf::FloatRect &DefaultView, bool showlines = false, const sf::Vector2f &GridSpacing = { 0,0 });
    virtual ~BasicLevel();

    virtual void TickUpdate(const double &delta) override;

    virtual void Render(std::shared_ptr<sf::RenderTarget> Target) override;
    virtual void RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture);

    virtual void OnShutDown() override;

    virtual std::uint32_t GetInternalID() const override { return InternalID; }
    virtual void SetInternalD(const std::uint32_t &ID) override { InternalID = ID; }
    virtual void SerializeOut(std::ofstream &out);
    virtual void SerializeIn(std::ifstream &in);
    virtual void HandleInputEvent(const UserEvent &evnt) override;
    virtual void HandleKeyPress(const sf::Keyboard::Key &key);
    virtual void HandleKeyRelease(const sf::Keyboard::Key &key);
    virtual void HandleWindowResized();
    virtual void LoadLevel(const std::string &lvlfile);
    virtual void OnBegin();
    virtual void OnEnd();
  
    //functions for loading from file
    virtual void LoadFromFile(const std::string &file);
    virtual void LoadAssets(const Json::Value &value);
    virtual void LoadAudio(const Json::Value &value);
    virtual void LoadTextures(const Json::Value &value);
    virtual void LoadTileSheets(const Json::Value &value);
    virtual void LoadSheet(const Json::Value &value);
    virtual void LoadAnimations(const Json::Value &value);

    bool DoUpdatePhysics = true;
    float updateInterval = 16.667f;
    virtual void UpdateObjectPhysics();

    sf::FloatRect CurrentView;
    bool ShowGridLines = false;
    std::vector<sf::VertexArray> GridLines;
    sf::Vector2u Size;
    sf::Vector2f GridBlockSize;
    sw::TileMap TileMap;
    sf::Texture TileMapTexture;

    std::map<std::string, std::shared_ptr<LevelObject>> AssetObjects;

    ::vec2d *Gravity;
    std::map<std::string, std::shared_ptr<Engine::LevelObject>> LevelObjects;
    std::map<std::shared_ptr<Engine::LevelObject>,
      std::vector<std::shared_ptr<Collider2D>>
    > LevelObjectMeshes;

    std::vector<SegmentPtr> Segments;
    std::vector<WaveSegmentPtr> Waves;
    std::vector<std::shared_ptr<LevelObject>> Objects;
    sf::RectangleShape LevelRectangle; //to draw the scene to
    std::shared_ptr<sf::RenderTexture> SceneTarget;
    std::map<std::string, std::shared_ptr<sf::Texture>> Textures;
    std::map<std::string, std::shared_ptr<TileSheet>> TileSheets;
    std::map<std::string, std::shared_ptr<Animation>> Animations;
    std::map<std::string, std::shared_ptr<sf::SoundBuffer>> SoundBuffers;
    std::shared_ptr<sf::RenderTexture> LightTexture;
    std::shared_ptr<sf::RenderTexture> SceneBlendTexture;

    std::vector<thor::UniversalEmitter> ParticleEmitters;
  };

}

#endif
