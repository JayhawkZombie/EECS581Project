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

    //If the PlayerActor moved on top of a collision box, place the actor back at their old position
    //TODO: CORRECT movement instead of disallowing all movement
    //  ie PLACE ACTOR AT EDGE OF BOX
    sf::Vector2f oldActorPos = PlayerActor.Position;

    std::size_t intersects = 0;
    sf::FloatRect Rect(PlayerActor.Collsion.GetBox());
    intersects = CanActorMove(Rect);

    LevelWaitingText.setString("Actor colliding? " + std::to_string(intersects));

    if (intersects != INT_MAX) {
      PlayerActor.Velocity = sf::Vector2f(0, 0);
      PlayerActor.MoveTo(oldActorPos);

    }

  }
}
