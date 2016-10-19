#ifndef SFENGINE_LEVEL_ENV_H
#define SFENGINE_LEVEL_ENV_H

#include "LevelObject.h"
#include "../Lights/GlobalLightSource.h"

namespace Engine
{
  class GenericActor;
  class Player;

  class LevelEnvironment
  {
  public:
    LevelEnvironment();
    ~LevelEnvironment();

    void AddGlobalLight(const std::string &ID, GlobalLightSource *src);
    void AddActor(const std::string &ID, GenericActor *src);
    void AddLight(const std::string &ID, GenericLightSource *src);
    void SetPlayer(const std::string &ID);

    GlobalLightSource* GetGlobalLight(const std::string &ID);
    GenericActor* GetActor(const std::string &ID);
    GenericLightSource* GetLight(const std::string &ID);
    Player* GetPlayer(const std::string &ID);

  protected:
    std::vector<std::shared_ptr<GenericLightSource>> LevelLights;
    std::shared_ptr<GlobalLightSource> LevelGlobalLight;
    std::vector<std::shared_ptr<GenericActor>> LevelActors;
    std::shared_ptr<Player> LevelPlayerActor;
  };

  extern LevelEnvironment *CurrentLevelEnvironment;


}

#endif
