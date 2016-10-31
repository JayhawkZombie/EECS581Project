#ifndef SFENGINE_LEVEL_ENV_H
#define SFENGINE_LEVEL_ENV_H

#include "LevelObject.h"
#include "../Lights/GlobalLightSource.h"
#include "LevelGrid.h"

namespace Engine
{
  class GenericActor;
  class Player;
  class LevelObject;

  struct Tile {
    Tile() : animated(false), TileAnimationDuration(0) {}

    sf::Sprite TileSprite;
    std::string TileID;
    std::vector<sf::FloatRect> Frames; //Used if tile is animated
    sf::Vector2f LevelPosition;
    sf::Vector2f ScreenPosition;
    std::string FilePath;
    bool animated;
    double TileAnimationDuration;
  };

  struct GridCell {
    GridCell() :
      LevelPosition({ 0,0 }), ScreenPosition({ -10000, -10000 })
    {
    }

    std::vector<std::shared_ptr<GenericActor>> Actors;
    std::vector<std::shared_ptr<LevelObject>> Objects;
    Tile BGTile;
    sf::Vector2f LevelPosition;
    sf::Vector2f ScreenPosition;
  };

  class LevelEnvironment
  {
  public:
    friend class Level;

    LevelEnvironment();
    ~LevelEnvironment();

    void AddGlobalLight(const std::string &ID, std::shared_ptr<GlobalLightSource> src);
    void AddActor(const std::string &ID, std::shared_ptr<GenericActor> src);
    void AddLight(const std::string &ID, std::shared_ptr<GenericLightSource> src);
    void SetPlayer(std::shared_ptr<Player> player);

    GlobalLightSource* GetGlobalLight(const std::string &ID);
    GenericActor* GetActor(const std::string &ID);
    GenericLightSource* GetLight(const std::string &ID);
    Player* GetPlayer(const std::string &ID);

    void Render();
    void TickUpdate(const double &delta);
    void UpdateView();
    void UpdateGemoetry();
    void MoveView(const sf::Vector2f &Movement);
    void ComputeLevelToWindowTransformation(sf::Vector2f &LC, sf::Vector2f &WC);
    void ComputeLevelScale();

    void HandleKeyPress(const sf::Keyboard::Key &key);
    void HandleKeyRelease(const sf::Keyboard::Key &key);

  protected:
    std::size_t TilesAssigned, TileSize, TilesAcross;
    std::size_t LevelSizeX, LevelSizeY;
    std::vector<std::shared_ptr<GenericLightSource>> LevelLights;
    std::shared_ptr<GlobalLightSource> LevelGlobalLight;
    std::vector<std::shared_ptr<GenericActor>> LevelActors;
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
