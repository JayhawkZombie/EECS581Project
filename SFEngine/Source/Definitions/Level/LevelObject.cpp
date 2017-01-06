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
    /*
    if (RenderOutlined) {
      sf::RectangleShape shape;
      shape.setFillColor(sf::Color::Transparent);
      shape.setOutlineThickness(2);
      shape.setOutlineColor(sf::Color::Black);
      shape.setPosition(this->CurrentPhysicsState.GetScreenPosition());
    }*/
  }

  void LevelObject::OnShutDown()
  {

  }

  void LevelObject::SerializeOut(std::ofstream &out)
  {

  }

  void LevelObject::SerializeIn(std::ifstream &in)
  {

  }

  void LevelObject::SetPosition(const sf::Vector2f &pos)
  {
    CurrentPhysicsState.SetLevelPosition(pos);
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
