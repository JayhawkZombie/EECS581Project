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

    sf::RectangleShape LevelRectangle; //to draw the scene to
    std::shared_ptr<sf::RenderTexture> SceneTarget;

    sf::Vector2u Size;
    sf::Vector2f GridBlockSize;
    
    std::vector<sf::VertexArray> GridLines;
    std::vector<Layer> Layers;
    vec2d Gravity;
    sf::FloatRect CurrentView;

    bool ShowGridLines = false;
  };

}

#endif