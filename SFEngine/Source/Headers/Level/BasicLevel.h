#ifndef SFENGINE_BASIC_LEVEL_H
#define SFENGINE_BASIC_LEVEL_H

#include "../Engine/BaseEngineInterface.h"
#include "../../../ThirdParty/PhysicsEngine.h"
#include "../Globals/GlobalHooks.h"
#include "../../../ThirdParty/SelbaWard/TileMap.hpp"
#include "../Weather/WeatherSystem.h"

namespace Engine
{

  class LevelObject;
  class TileSheet;
  class Animation;
  class Collider2D;
  class GenericActor;
  class ProjectileBase;
  class WeatherSystem;
  class WeatherEvent;

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
    virtual void Reset();

    virtual void SpawnActor(std::shared_ptr<GenericActor> Actor, const sf::Vector2f &Position);
    virtual void SpawnObject(std::shared_ptr<LevelObject> Object, const sf::Vector2f &Position);

    virtual bool SpawnAutoGeneratedObject(std::shared_ptr<LevelObject> Object, std::string IDPrePend = "");
  
    //functions for loading from file
    virtual void LoadFromFile(const std::string &file);
    virtual void LoadAssets(const Json::Value &value);
    virtual void LoadAudio(const Json::Value &value);
    virtual void LoadTextures(const Json::Value &value);
    virtual void LoadTileSheets(const Json::Value &value);
    virtual void LoadSheet(const Json::Value &value);
    virtual void LoadAnimations(const Json::Value &value);
    virtual void CleanUp();

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

    ::vec2d *Gravity;
    std::map<std::string, std::shared_ptr<Engine::LevelObject>> LevelObjects;
    WeatherSystem m_WeatherSystem;

    std::vector<SegmentPtr> Segments;
    std::vector<WaveSegmentPtr> Waves;
    std::vector<std::shared_ptr<LevelObject>> Objects;
    sf::RectangleShape LevelRectangle; //to draw the scene to
    std::shared_ptr<sf::RenderTexture> SceneTarget;
    std::map<std::string, std::shared_ptr<sf::Texture>> Textures;
    std::map<std::string, std::shared_ptr<TileSheet>> TileSheets;
    std::map<std::string, std::shared_ptr<Animation>> Animations;
    std::map<std::string, std::shared_ptr<sf::SoundBuffer>> SoundBuffers;

    std::vector<thor::UniversalEmitter> ParticleEmitters;
    std::vector<std::shared_ptr<ProjectileBase>> Projectiles;

#ifdef WITH_EDITOR
    static void UpdateEditorUI(const double &delta);
    static void RenderEditorUI(std::shared_ptr<sf::RenderTexture> Target);
    
    void ShowObjectProperties(std::shared_ptr<Engine::LevelObject> Object);
    void ShowSceneGraph();
    void ShowAssetGraph();
    void ShowGraphicalSettings();
    void ShowAnimationEditor(const std::string &name);
    void ShowSpawner();
    void ShowPhysicsSpawner();
    void ShowScene(std::shared_ptr<sf::RenderTexture> Texture);
    void ShowAssetEditor();
    void ShowNewAssetMaker(); void ShowExistingAssetEditor();
    std::map<std::string, sf::RectangleShape> TextureRectsForAssetGraph;
    std::map<std::string, std::shared_ptr<Animation>> EditorGraphAnimations;

    bool m_HideEditor = false;
#endif

    virtual void SpawnBall
    (
      char BallType,
      const sf::Vector2f & InitialPosition,
      const sf::Vector2f & InitialVelocity,
      unsigned int Radius,
      float Mass,
      float CoeffecientOfRest,
      const sf::Color & Color
    );

    virtual void SpawnSquare
    (
      float radius,
      float init_rotation,
      const sf::Vector2f & InitialPosition,
      const sf::Vector2f & InitialVelocity,
      float mass,
      float CoeffOfRest,
      const sf::Color & Color
    );

    virtual void SpawnRect
    (
      float radius,
      float init_rotation,
      const sf::Vector2f & InitialPosition,
      const sf::Vector2f & InitialVelocity,
      float mass,
      float CoeffOfRest,
      const sf::Color & Color
    );

    virtual void SpawnTriangle
    (
      float radius,
      float init_rotation,
      const sf::Vector2f & InitialPosition,
      const sf::Vector2f & InitialVelocity,
      float mass,
      float CoeffOfRest,
      const sf::Color & Color
    );
    virtual void SpawnNPoly
    (
      unsigned int num_sides,
      float radius,
      float init_rotation,
      const sf::Vector2f & InitialPosition,
      const sf::Vector2f & InitialVelocity,
      float mass,
      float CoeffOfRest,
      const sf::Color & Color
    );

    virtual void SpawnWave
    (
      char type,
      const sf::Vector2i &TopLeftCorner,
      const sf::Vector2i &BottomRightCorner,
      float radius,
      bool IsHard,
      unsigned int NumWavePts,
      float ampRight,
      float waveLenRight,
      float rFreqRight,
      float ampLeft,
      float waveLenLeft,
      float rFreqLeft,
      float elev,
      float airDen,
      float depth,
      float fluidDen
    );
  };

}

#endif
