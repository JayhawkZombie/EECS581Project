#include "../../Headers/Level/LevelEnvironment.h"
#include "../../Headers/Actor/Player.h"

Engine::LevelEnvironment *CurrentLevelEnvironment;

namespace Engine
{

  LevelEnvironment::LevelEnvironment()
  {

  }

  LevelEnvironment::~LevelEnvironment()
  {

  }

  void LevelEnvironment::AddGlobalLight(const std::string &ID, GlobalLightSource *src)
  {
    std::shared_ptr<GlobalLightSource> light(src);
    light->SetID(ID);
    LevelLights.push_back(light);
  }

  void LevelEnvironment::AddActor(const std::string &ID, GenericActor *src)
  {
    LevelActors.push_back(std::shared_ptr<GenericActor>(src));
  }

  void LevelEnvironment::AddLight(const std::string &ID, GenericLightSource *src)
  {
    LevelLights.push_back(std::shared_ptr<GenericLightSource>(src));
  }

  void LevelEnvironment::SetPlayer(const std::string &ID)
  {
    if (LevelPlayerActor->GetID() == ID)
      return;
    else {
      for (auto & it : LevelActors) {
        if (it->GetID() == ID) {
          
          break;
        }
      }
    }
  }

  GlobalLightSource* LevelEnvironment::GetGlobalLight(const std::string &ID)
  {
    if (LevelGlobalLight->GetID() == ID)
      return LevelGlobalLight.get();
    else {
      //ugh

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

}
