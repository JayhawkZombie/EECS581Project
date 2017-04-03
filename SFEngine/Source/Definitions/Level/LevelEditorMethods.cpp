#include "../../Headers/Level/Level.h"
#include "../../../ThirdParty/chaiscript/chaiscript.hpp"

#ifdef WITH_EDITOR

namespace Engine
{
  void Level::SpawnActor(std::shared_ptr<GenericActor> Actor, const sf::Vector2f &Position)
  {
	  Actor->SetActorPosition(Position);

    if (!SpawnAutoGeneratedObject(Actor, "Actor")) {
      ERR_STREAM << "Failed to spawn ACTOR" << std::endl;
    }
    else
      Actor->ScriptInit();
  }

  void Level::SpawnObject(std::shared_ptr<LevelObject> Object, const sf::Vector2f &Position)
  {
	  
  }

}

#endif
