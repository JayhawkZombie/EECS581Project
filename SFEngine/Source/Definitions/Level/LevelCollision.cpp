#include "../../Headers/Level/Level.h"

namespace Engine
{

  std::size_t Level::CanActorMove(const sf::FloatRect &ActorBox)
  {
    for (std::size_t i = 0; i < CollisionBoxes.size(); ++i) {
      sf::FloatRect collision(CollisionBoxes[i].Position, CollisionBoxes[i].Size);

      if (ActorBox.intersects(collision)) {
        return i;
      }
    }

    return INT_MAX;
  }

  void Level::CheckCollisions()
  {

    for (auto & box : CollisionBoxes) {

    }

  }

}
