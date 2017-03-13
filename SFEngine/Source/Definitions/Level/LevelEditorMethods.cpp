#include "../../Headers/Level/Level.h"
#include "../../../ThirdParty/chaiscript/chaiscript.hpp"

#ifdef WITH_EDITOR

namespace Engine
{


  void Level::SpawnActor(std::shared_ptr<GenericActor> Actor, const sf::Vector2f &Position)
  {
	  Actor->SetActorPosition(Position);
	  Objects.push_back(Actor);
	  TestObjects.push_back(Actor->GetMesh());
  }

  void Level::SpawnObject(std::shared_ptr<LevelObject> Object, const sf::Vector2f &Position)
  {
	  
  }

  void Level::SpawnLight(std::shared_ptr<LightObject> Light, const sf::Vector2f &Position)
  {

  }

}

#endif
