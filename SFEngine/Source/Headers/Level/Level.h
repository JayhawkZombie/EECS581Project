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
    void IsReady() const;

    void LoadFromFile(const std::string &file);

  private:
    void __LoadWithGrid(std::ifstream &IN);
    void __GetGridTexture(const std::string &ID, std::shared_ptr<sf::Texture> texture);
    std::size_t NumGridTextures, TileTextureWidth, TileGridHeight, TileGridWidth;
    std::string GridTileLayout, GridTextures;



    void HandleKeyEvent(const sf::Keyboard::Key &key);
    void CheckCollisions();
    void CorrectActorMovement(const std::size_t &boxIndex);
    std::size_t CanActorMove(const sf::FloatRect &ActorBox);

    sf::Vector2f OldActorPos;

    std::map<std::string, EventSequence> EventSequences;
    EventSequence *CurrentEventSequence;


    std::vector<std::shared_ptr<LevelLayer>> Layers;
    std::vector<GenericActor> Actors;
    Player PlayerActor;
    std::vector<CollisionBox> CollisionBoxes;

    std::vector<LevelObject> LevelObjects;
    sf::Text LevelWaitingText;

    void ReceiveFont(std::shared_ptr<sf::Font> font, const std::string &ID);
    std::shared_ptr<sf::Font> LevelWaitingFont;


    LevelEnvironment Environment;
    void AddActor(const std::string &ID, std::shared_ptr<GenericActor> src);
    void AddLight(const std::string &ID, std::shared_ptr<GenericLightSource> src);
    void AddGlobalLight(const std::string &ID, std::shared_ptr<GlobalLightSource> src);

    EventSequence Seq;

    std::thread LOADER;
    std::string LevelFile;

    bool Playable;
    LevelLayer BackgroundLayer;

  };

}

#endif
