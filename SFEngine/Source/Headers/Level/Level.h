#ifndef SFENGINE_OPT_LEVEL_G
#define SFENGINE_OPT_LEVEL_G

#include "../Actor/Player.h"
#include "../Actor/Actor.h"
#include "../Physics/Physics.h"
#include "../Lights/LightingSystem.h"
#include "../Tiles/TileSheet.h"

class GameMain;

namespace Engine
{

#ifdef WITH_EDITOR
  class Editor;
#endif

  class Layer : public BaseEngineInterface
  {
  public:
#ifdef WITH_EDITOR
    friend class Editor;
#endif
    Layer();
    Layer(const Layer &) = delete;
    ~Layer();

    void TickUpdate(const double &delta) override;
    void Render(std::shared_ptr<sf::RenderTarget> Target) override;
    void OnShutDown() override;
    void SerializeOut(std::ofstream &out) override;
    void SerializeIn(std::ifstream &in) override;

  protected:
    std::shared_ptr<sf::Texture> TileTexture;
    std::vector<sf::VertexArray> TileVertices;

    std::vector<std::shared_ptr<LevelObject>> Objects;
    std::vector<std::shared_ptr<GenericLightSource>> Lights;
    std::vector<std::shared_ptr<GenericActor>> Actors;
  };

  class Level : public BaseEngineInterface
  {

  public:
    friend class GameMain;
#ifdef WITH_EDITOR
    friend class Editor;
#endif
    float updateInterval = 16.667f;
    TYPEDEF_PARENT_CLASS(Engine::BaseEngineInterface);

    Level() = default;
    Level(const sf::Vector2u &LevelSize, const sf::FloatRect &DefaultView, bool showlines = false, const sf::Vector2f &GridSpacing = { 0,0 });
    Level(const std::string &levelFile);
    Level(const Level &) = delete;
    ~Level();

    void TickUpdate(const double &delta) override;
    void Render(std::shared_ptr<sf::RenderTarget> Target) override;
    void OnShutDown() override;
    void SerializeOut(std::ofstream &out) override;
    void SerializeIn(std::ifstream &in) override;

    void SpawnActor(std::shared_ptr<GenericActor> Actor, const sf::Vector2f &Position);
    void SpawnObject(std::shared_ptr<LevelObject> Object, const sf::Vector2f &Position);
    void SpawnLight(std::shared_ptr<LightObject> Light, const sf::Vector2f &Position);

    void HandleKeyPress(const sf::Keyboard::Key &key);
    void HandleKeyRelease(const sf::Keyboard::Key &key);
    void HandleWindowResized();

    std::vector<std::shared_ptr<PhysicsEngineBaseMeshType>> TestLevelMeshes;
    std::vector<std::shared_ptr<PhysicsEngineSegmentType>> TestSegments;

    sf::RectangleShape testrect;

    void LoadLevel(const std::string &lvlfile);

    std::size_t GetNumLayers() const {
      return Layers.size();
    }

  private:
    void RenderRegular();
    void RenderLoadingScreen();
    void GenerateGrid();

    std::shared_ptr<sf::RenderTexture> SceneTexture;

#ifdef WITH_EDITOR
    void ShowSceneGraph();
    void ShowAssetGraph();
    void ShowGraphicalSettings();
    void ShowAnimationEditor(const std::string &name);
    void ShowSpawner();
    void ShowPhysicsSpawner();
    void ShowScene(std::shared_ptr<sf::RenderTexture> Texture);

    std::map<std::string, sf::RectangleShape> TextureRectsForAssetGraph;
    std::map<std::string, std::shared_ptr<Animation>> EditorGraphAnimations;
#endif
    void LoadFromFile(const std::string &file);
    //Methods for spawning in new object
    void SpawnBall(char BallType, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, unsigned int Radius, float Mass, float CoeffecientOfRest, const sf::Color & Color);
    void SpawnSquare(float radius, float init_rotation, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, float mass, float CoeffOfRest, const sf::Color & Color);
    void SpawnRect(float radius, float init_rotation, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, float mass, float CoeffOfRest, const sf::Color & Color);
    void SpawnTriangle(float radius, float init_rotation, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, float mass, float CoeffOfRest, const sf::Color & Color);
    void SpawnNPoly(unsigned int num_sides, float radius, float init_rotation, const sf::Vector2f & InitialPosition, const sf::Vector2f & InitialVelocity, float mass, float CoeffOfRest, const sf::Color & Color);
    void SpawnWave(char type, const sf::Vector2i &TopLeftCorner, const sf::Vector2i &BottomRightCorner, float radius, bool IsHard,
                   unsigned int NumWavePts, float ampRight, float waveLenRight, float rFreqRight,
                   unsigned int ampLeft, float waveLenLeft, float rFreqLeft,
                   float elev, float airDen, float depth, float fluidDen);
    bool DoUpdatePhysics = true;

    vec2d Gravity;
    std::vector<BaseMeshPtr> TestObjects;
    std::vector<SegmentPtr> Segments;
    std::vector<WaveSegmentPtr> Waves;
	std::vector<std::shared_ptr<LevelObject>> Objects;
    sf::RectangleShape LevelRectangle; //to draw the scene to
    std::shared_ptr<sf::RenderTexture> SceneTarget;
    std::map<std::string, std::shared_ptr<sf::Texture>> Textures;
    std::map<std::string, std::shared_ptr<TileSheet>> TileSheets;
    std::map<std::string, std::shared_ptr<Animation>> Animations;
    std::map<std::string, std::shared_ptr<sf::SoundBuffer>> SoundBuffers;
    std::map<std::uint32_t, std::shared_ptr<LightSystem>> LightSystems;
    std::map<std::uint32_t, std::shared_ptr<Light>> Lights;
    std::shared_ptr<sf::RenderTexture> LightTexture;
    std::shared_ptr<sf::RenderTexture> SceneBlendTexture;

    std::vector<thor::UniversalEmitter> ParticleEmitters;

    sf::Vector2u Size;
    sf::Vector2f GridBlockSize;
    
    std::vector<sf::VertexArray> GridLines;
    std::vector<Layer> Layers;
    sf::FloatRect CurrentView;

    bool ShowGridLines = false;

    //functions for loading from file
    void LoadAssets(const Json::Value &value);
    void LoadAudio(const Json::Value &value);
    void LoadTextures(const Json::Value &value);
    void LoadTileSheets(const Json::Value &value);
    void LoadSheet(const Json::Value &value);
    void LoadAnimations(const Json::Value &value);
  };

}

#endif