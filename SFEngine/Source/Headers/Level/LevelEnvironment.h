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

  class Tile {
  public:
    Tile();

    void TickUpdate(const double &delta);
    void Render();

    sf::Sprite TileSprite;
    std::string TileID;
    std::vector<sf::IntRect> Frames; //Used if tile is animated
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
    void UpdateView(const double &delta);
    void UpdateGemoetry(const double &delta);
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
