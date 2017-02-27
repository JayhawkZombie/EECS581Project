#ifndef SFENGINE_FACTORY_CLASS_CREATE_BIND_H
#define SFENGINE_FACTORY_CLASS_CREATE_BIND_H

#include "../BasicIncludes.h"

#include "../../../ThirdParty/json/json.h"

namespace Engine
{

  class GenericActor;
  class Player;
  class Level;
  class TileSheet;
  class LevelTile;
  class Animation;


  namespace Factory
  {

    std::shared_ptr<Engine::GenericActor> GenericActor(const Json::Value &jsonobj);
    std::shared_ptr<Engine::Player> Player(const Json::Value &jsonobj);
    std::shared_ptr<Engine::Level> Level(const Json::Value &jsonobj);
    std::shared_ptr<Engine::TileSheet> TileSheet(const Json::Value &jsonobj);
    std::shared_ptr<Engine::LevelTile> Tile(const Json::Value &jsonobj);
    std::shared_ptr<Engine::Animation> Animation(const Json::Value &jsonobj);

  }


}


#endif
