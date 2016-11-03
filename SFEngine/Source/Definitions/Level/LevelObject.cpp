#include "../../Headers/Level/LevelObject.h"

#include "../../Headers/Actor/Actor.h"

namespace Engine
{

  LevelObject::LevelObject()
  {

  }

  LevelObject::LevelObject(const LevelObject &copy)
  {

  }

  LevelObject::~LevelObject()
  {

  }

  void LevelObject::TickUpdate(const double &delta)
  {

  }

  void LevelObject::Render()
  {

  }

  void LevelObject::OnShutDown()
  {

  }

  OverlapAction LevelObject::OnActorOverlap(GenericActor *actor)
  {
    return OverlapAction::DISALLOW_ACTOR_OVERLAP;
  }

  void LevelObject::CollisionUpdate(const sf::Vector2f &movement)
  {
    
  }

  bool LevelObject::DoTestCollisions() const
  {
    return TestingCollisions;
  }

  bool LevelObject::DoesAllowActorOverlap() const
  {
    return AllowsActorOverlap;
  }

}
