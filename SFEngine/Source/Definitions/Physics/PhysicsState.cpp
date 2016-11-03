#include "../../Headers/Physics/PhysicsState.h"
#include "../../Headers/Actor/Actor.h"


namespace Engine
{

  PhysicsState::PhysicsState()
  {

  }

  PhysicsState::PhysicsState(const PhysicsState &state)
  {
    LevelPosition = state.LevelPosition;
    ScreenPosition = state.ScreenPosition;
    Acceleration = state.Acceleration;
    Velocity = state.Velocity;
    BoundingBox = state.BoundingBox;
  }

  PhysicsState::~PhysicsState()
  {

  }

  void PhysicsState::RetrieveState(GenericActor *actor)
  {
    LevelPosition = actor->CurrentPhysicsState.LevelPosition;
    ScreenPosition = actor->CurrentPhysicsState.ScreenPosition;
    Acceleration = actor->CurrentPhysicsState.Acceleration;
    Velocity = actor->CurrentPhysicsState.Velocity;
    BoundingBox = actor->CurrentPhysicsState.BoundingBox;
  }

  sf::Vector2f PhysicsState::GetLevelPosition() const
  {
    return LevelPosition;
  }

  sf::Vector2f PhysicsState::GetScreenPosition() const
  {
    return ScreenPosition;
  }

  sf::Vector2f PhysicsState::GetVelocity() const
  {
    return Velocity;
  }

  sf::Vector2f PhysicsState::GetAcceleration() const
  {
    return Acceleration;
  }

  sf::FloatRect PhysicsState::GetBoundingBox() const
  {
    return BoundingBox;
  }

  void PhysicsState::SetLevelPosition(const sf::Vector2f &pos)
  {
    LevelPosition = pos;
  }

  void PhysicsState::SetScreenPosition(const sf::Vector2f &pos)
  {
    ScreenPosition = pos;
  }

  void PhysicsState::SetVelocity(const sf::Vector2f &vel)
  {
    Velocity = vel;
  }

  void PhysicsState::SetAcceleration(const sf::Vector2f &acc)
  {
    Acceleration = acc;
  }

  void PhysicsState::SetBoundingBox(const sf::FloatRect &box)
  {
    BoundingBox = box;
  }

}
