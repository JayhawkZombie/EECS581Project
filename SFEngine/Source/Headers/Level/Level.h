#ifndef SFENGINE_OPT_LEVEL_G
#define SFENGINE_OPT_LEVEL_G


#include "../Engine/BaseEngineInterface.h"
#include "LevelObject.h"
#include "LevelEventSequences.h"
#include "../Events/EventSequence.h"
#include "../Actor/Player.h"
#include "../Actor/Actor.h"
#include "../Lights/GlobalLightSource.h"
#include "../Physics/Physics.h"
#include "LevelLoader.h"
#include "../Lights/LightingSystem.h"
#include "../Lights/LightObject.h"

#include "../../../ThirdParty/rapidxml-1.13/rapidxml.hpp"
#include "../../../ThirdParty/rapidxml-1.13/rapidxml_iterators.hpp"
#include "../../../ThirdParty/rapidxml-1.13/rapidxml_utils.hpp"

class GameMain;

namespace Engine
{

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
    TYPEDEF_PARENT_CLASS(Engine::BaseEngineInterface);

    Level();
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

    void LoadLevel(const std::string &lvlfile);

  private:
    void RenderRegular();
    void RenderLoadingScreen();

    std::map<std::string, LevelTile> Tiles;
    bool ShowGridLines = false;
  };

}

#endif