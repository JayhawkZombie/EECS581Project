#include "../../Headers/Physics/Collision.h"

namespace Engine
{
  CollisionBox::CollisionBox()
  {

  }

  CollisionBox::CollisionBox(const CollisionBox &box)
  {
    Position = box.Position;
    Size = box.Size;
  }

  sf::FloatRect CollisionBox::GetBox() const
  {
    return sf::FloatRect(Position, Size);
  }

  CollisionBox::~CollisionBox()
  {

  }
}