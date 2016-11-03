#include "../../Headers/Physics/Collision.h"
#include "../../Headers/Level/LevelObject.h"

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

  namespace Physics
  {
    bool DoObjectsOverlap(LevelObject *Obj1, LevelObject *Obj2)
    {
      if (Obj1 && Obj2) {
        sf::FloatRect Rect1 = Obj1->CurrentPhysicsState.GetBoundingBox();
        sf::FloatRect Rect2 = Obj2->CurrentPhysicsState.GetBoundingBox();

        return (Rect1.intersects(Rect2));
      }
      return false;
    }
  }
}