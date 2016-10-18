#ifndef SFENGINE_OPT_LEVEL_G
#define SFENGINE_OPT_LEVEL_G


#include "../Engine/BaseEngineInterface.h"
#include "Layer.h"
#include "LevelObject.h"
#include "../Events/EventSequence.h"
#include "../Actor/Player.h"

#include "../Lights/GlobalLightSource.h"

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

  private:
    void HandleKeyEvent(const sf::Keyboard::Key &key);
    void CheckCollisions();
    void CorrectActorMovement(const std::size_t &boxIndex);
    std::size_t CanActorMove(const sf::FloatRect &ActorBox);

    GlobalLightSource GlobalLight;

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




    void __LoadLevel();
    void __ReadLoadTextures(const std::size_t &layer, std::ifstream &IN);
    void __LoadLayout(std::ifstream &IN);
    void __DrawTiles();
    void ReceiveTexture(const std::string &ID, std::shared_ptr<sf::Texture> texture);

    std::thread LOADER;
    std::string LevelFile;

    bool Playable;
    LevelLayer BackgroundLayer;

  };

}

#endif
