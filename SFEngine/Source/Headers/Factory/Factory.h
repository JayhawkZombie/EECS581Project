#ifndef SFENGINE_FACTORY_CLASS_CREATE_BIND_H
#define SFENGINE_FACTORY_CLASS_CREATE_BIND_H


#include "../BasicIncludes.h"

#include "../Actor/Actor.h"
#include "../Actor/Player.h"
#include "../Level/LevelTile.h"

namespace Engine
{

  namespace Factory
  {
    std::shared_ptr<Engine::GenericActor> GenericActor(ActorInfo *info, std::ifstream &infile, chaiscript::ChaiScript *engine);
    std::shared_ptr<Engine::GenericActor> GenericActor(const Engine::GenericActor &actor);
    std::shared_ptr<Engine::GenericActor> Actor(std::string ID = "");
    std::shared_ptr<Engine::Animation> Animation(AnimationInfo *info, chaiscript::ChaiScript *engine);
    std::shared_ptr<Engine::Animation> Animation(std::string ID = "");
    std::shared_ptr<Engine::LevelTile> Tile(std::string ID = "");
    std::shared_ptr<Engine::LevelTile> Tile(const Engine::LevelTile &tile);
  }

}


#endif
