#ifndef SFENGINE_LEVEL_ENV_H
#define SFENGINE_LEVEL_ENV_H

#include "LevelObject.h"
#include "../Lights/GlobalLightSource.h"
#include "LevelGrid.h"

#include "../Physics/PhysicsState.h"
#include "../Physics/Collision.h"
#include "../Physics/Physics.h"

namespace Engine
{
  class GenericActor;
  class Player;
  class LevelObject;

  class Tile {
  public:
    Tile();

    void TickUpdate(const double &delta);
    void Render();

    sf::Sprite TileSprite;
    std::string TileID;
    std::vector<sf::IntRect> Frames;
    sf::Vector2f LevelPosition;
    sf::Vector2f ScreenPosition;
    std::string FilePath;
    bool IsAnimated;
    double TotalAnimationDuration;
    double FrameDelta;
    std::size_t NumFrames, CurrentFrame;
    double CurrentAnimationDuration;
  };

  struct GridCell {
    GridCell();

    void TickUpdate(const double &delta);
    void EndOfFrame();
    void PhysicsUpdate();
    void Render(std::function<void(sf::Vector2f &LC, sf::Vector2f &WC)> conversion);

    std::vector<std::shared_ptr<GenericActor>> Actors;
    std::vector<std::shared_ptr<LevelObject>> Objects;
    Tile BGTile;
    std::vector<Tile> Tiles;
    sf::Vector2f LevelPosition;
    sf::Vector2f ScreenPosition;
  };

  class LevelEnvironment
  {
  public:
    friend class Level;

    LevelEnvironment();
    ~LevelEnvironment();

    /**
     * Add a global light to the level
     * Param: String, a unique ID for the light
     * Param: std::shared_ptr<GlobalLightSource>, a shared_ptr to the allocated light source
     */
    void AddGlobalLight(const std::string &ID, std::shared_ptr<GlobalLightSource> src);

    /**
    * Add an actor to the level
    * Param: String, a unique ID for the light
    * Param: std::shared_ptr<Actor>, a shared_ptr to the allocated Actor
    */
    void AddActor(const std::string &ID, std::shared_ptr<GenericActor> src);

    /**
    * Add a light to the level
    * Param: String, a unique ID for the light
    * Param: std::shared_ptr<GenericLightSource>, a shared_ptr to the allocated light source
    */
    void AddLight(const std::string &ID, std::shared_ptr<GenericLightSource> src);

    /**
    * Add an object to the level
    * Param: String, a unique ID for the light
    * Param: std::shared_ptr<LevelObject>, a shared_ptr to the allocated LevelObject
    */
    void AddObject(const std::string &D, std::shared_ptr<LevelObject> obj);

    /**
    * Add a Player
    * Param: String, a unique ID for the light
    * Param: std::shared_ptr<Player>, a shared_ptr to the allocated Player
    */
    void SetPlayer(std::shared_ptr<Player> player);

    GlobalLightSource* GetGlobalLight(const std::string &ID);
    GenericActor* GetActor(const std::string &ID);
    GenericLightSource* GetLight(const std::string &ID);
    LevelObject* GetObject(const std::string &ID);
    Player* GetPlayer(const std::string &ID);

    void Render();
    void TickUpdate(const double &delta);
    void EndOfFrame();

    void PhysicsUpdate();
    void UpdateView(const double &delta);
    void UpdateGemoetry(const double &delta);
    void MoveView(const sf::Vector2f &Movement);
    void ComputeLevelToWindowTransformation(sf::Vector2f &LC, sf::Vector2f &WC);
    void ComputeLevelScale();

    void HandleKeyPress(const sf::Keyboard::Key &key);
    void HandleKeyRelease(const sf::Keyboard::Key &key);

  protected:
    void ProcessCollisions();
    void UpdateDayCycle(const double &delta);

    std::size_t CELL_LEFT, CELL_TOP, CELL_RIGHT, CELL_BOTTOM;

    std::size_t TilesAssigned, TileSize, TilesAcross;
    std::size_t LevelSizeX, LevelSizeY;
    std::vector<std::shared_ptr<GenericLightSource>> LevelLights;
    std::shared_ptr<GlobalLightSource> LevelGlobalLight;
    std::vector<std::shared_ptr<GenericActor>> LevelActors;
    std::vector<std::shared_ptr<LevelObject>> LevelObjects;
    std::shared_ptr<Player> LevelPlayerActor;

    Matrix<GridCell> EnvironmentGrid;
    sf::Vector2f Scale;
    sf::Vector2f LevelScale;
    sf::FloatRect CurrentView;

    sf::Vector2f LevelMovement;

    sf::Font DiagnosticFont;
    sf::Text DiagnosticText;
  };
}

#endif
