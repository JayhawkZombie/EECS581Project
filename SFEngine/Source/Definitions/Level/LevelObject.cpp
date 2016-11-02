#include "../../Headers/Level/LevelObject.h"

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

  void LevelObject::CollisionUpdate(const sf::Vector2f &movement)
  {
    for (auto & box : CollisionBoxes) {
      PreviousPhysicsState[box.first] = box.second;
      box.second.Position += movement;
    }
  }

}
