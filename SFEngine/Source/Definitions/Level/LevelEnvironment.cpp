#include "../../Headers/Level/LevelEnvironment.h"
#include "../../Headers/Actor/Player.h"

Engine::LevelEnvironment *CurrentLevelEnvironment;

namespace Engine
{

  LevelEnvironment::LevelEnvironment()
    : BackgroundTiles(nullptr)
  {

  }

  LevelEnvironment::~LevelEnvironment()
  {
    if (BackgroundTiles)
      delete BackgroundTiles;
  }

  void LevelEnvironment::AddGlobalLight(const std::string &ID, std::shared_ptr<GlobalLightSource> src)
  {
    //std::shared_ptr<GlobalLightSource> light(src);
    src->SetID(ID);
    LevelLights.push_back(src);
  }

  void LevelEnvironment::AddActor(const std::string &ID, std::shared_ptr<GenericActor> src)
  {
    src->SetID(ID);
    LevelActors.push_back(src);
  }

  void LevelEnvironment::AddLight(const std::string &ID, std::shared_ptr<GenericLightSource> src)
  {
    src->SetID(ID);
    LevelLights.push_back(std::shared_ptr<GenericLightSource>(src));
  }

  void LevelEnvironment::SetPlayer(std::shared_ptr<Player> player)
  {
    LevelPlayerActor = player;
  }

  GlobalLightSource* LevelEnvironment::GetGlobalLight(const std::string &ID)
  {
    if (LevelGlobalLight->GetID() == ID)
      return LevelGlobalLight.get();
    else {
      //ugh
      return nullptr;
    }
  }

  GenericActor* LevelEnvironment::GetActor(const std::string &ID)
  {
    for (auto & actor : LevelActors) {
      if (actor->GetID() == ID) {
        return actor.get();
      }
    }

    //Create the actor with that ID and return it
    std::shared_ptr<GenericActor> actor(new GenericActor);
    actor->SetID(ID);
    LevelActors.push_back(actor);

    return actor.get();
  }

  GenericLightSource* LevelEnvironment::GetLight(const std::string &ID)
  {
    for (auto & light : LevelLights) {
      if (light->GetID() == ID) {
        return light.get();
      }
    }

    std::shared_ptr<GenericLightSource> light(new GenericLightSource);
    light->SetID(ID);
    LevelLights.push_back(light);

    return light.get();
  }

  Player* LevelEnvironment::GetPlayer(const std::string &ID)
  {
    if (LevelPlayerActor)
      return LevelPlayerActor.get();
    else {
      return nullptr;
    }

    //Ugh WHYYYYYYY
    std::shared_ptr<Player> player(new Player);
    player->SetID(ID);

    LevelActors.push_back(player);
    return player.get();
  }

  void LevelEnvironment::Render()
  {
    BackgroundTiles->Render();
  }

}
