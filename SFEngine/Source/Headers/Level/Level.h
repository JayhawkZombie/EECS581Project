#ifndef SFENGINE_OPT_LEVEL_G
#define SFENGINE_OPT_LEVEL_G

#include "../Actor/Player.h"
#include "../Physics/Physics.h"
#include "../Lights/LightingSystem.h"
#include "../Tiles/TileSheet.h"
#include "../../../ThirdParty/SelbaWard.hpp"

#include "BasicLevel.h"

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

  class Level : public BasicLevel
  {

  public:
    friend class GameMain;
    TYPEDEF_PARENT_CLASS(Engine::BasicLevel);

    Level() = delete;
    Level(const sf::Vector2u &LevelSize, const sf::FloatRect &DefaultView, bool showlines = false, const sf::Vector2f &GridSpacing = { 0,0 });
    Level(const Level &) = delete;
    ~Level();
    
    static void BindMethods(chaiscript::ModulePtr mptr);

    void TickUpdate(const double &delta) override;
    void Render(std::shared_ptr<sf::RenderTarget> Target) override;
    void RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture) override;
    void OnShutDown() override;
    void SerializeOut(std::ofstream &out) override;
    void SerializeIn(std::ifstream &in) override;

    void SpawnActor(std::shared_ptr<GenericActor> Actor, const sf::Vector2f &Position);
    void SpawnObject(std::shared_ptr<LevelObject> Object, const sf::Vector2f &Position);
    //void SpawnLight(std::shared_ptr<LightObject> Light, const sf::Vector2f &Position);

    void HandleInputEvent(const UserEvent &evnt);
    void HandleKeyPress(const sf::Keyboard::Key &key) override;
    void HandleKeyRelease(const sf::Keyboard::Key &key) override;
    void HandleWindowResized() override;

    static std::shared_ptr<LevelObject> GetObjectByName(const std::string &ID);
    void LoadLevel(const std::string &lvlfile) override;
    void OnBegin() override;
    void OnEnd() override;

    std::size_t GetNumLayers() const {
      return Layers.size();
    }

  private:
    void RenderRegular();
    void RenderLoadingScreen();
    void GenerateGrid();
    sf::View Camera;
    std::shared_ptr<sf::RenderTexture> SceneTexture;

#ifdef WITH_EDITOR
    void ShowObjectProperties(std::shared_ptr<Engine::LevelObject> Object);
    //void ShowActorProperties(std::shared_ptr<Engine::GenericActor> Actor);
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
#endif
    //Methods for spawning in new object
    void SpawnBall
    (
      char BallType, 
      const sf::Vector2f & InitialPosition, 
      const sf::Vector2f & InitialVelocity,
      unsigned int Radius, 
      float Mass, 
      float CoeffecientOfRest, 
      const sf::Color & Color
    );

    void SpawnSquare
    (
      float radius, 
      float init_rotation, 
      const sf::Vector2f & InitialPosition, 
      const sf::Vector2f & InitialVelocity, 
      float mass, 
      float CoeffOfRest, 
      const sf::Color & Color
    );

    void SpawnRect
    (
      float radius, 
      float init_rotation, 
      const sf::Vector2f & InitialPosition, 
      const sf::Vector2f & InitialVelocity, 
      float mass, 
      float CoeffOfRest, 
      const sf::Color & Color
    );

    void SpawnTriangle
    (
      float radius, 
      float init_rotation, 
      const sf::Vector2f & InitialPosition, 
      const sf::Vector2f & InitialVelocity, 
      float mass, 
      float CoeffOfRest, 
      const sf::Color & Color
    );
    void SpawnNPoly
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

    void SpawnWave
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

    bool SpawnAutoGeneratedObject(std::shared_ptr<LevelObject> Object, std::string IDPrePend = "");
    
    void UpdateObjectPhysics() override;
    std::vector<unsigned char> lvlData;
    std::vector<Layer> Layers;

    //functions for loading from file
    void LoadFromFile(const std::string &file) override;
    void LoadAssets(const Json::Value &value) override;
    void LoadAudio(const Json::Value &value) override;
    void LoadTextures(const Json::Value &value) override;
    void LoadTileSheets(const Json::Value &value) override;
    void LoadSheet(const Json::Value &value) override;
    void LoadAnimations(const Json::Value &value) override;
  };
}

#endif