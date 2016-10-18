#include "../../Headers/Level/Level.h"

namespace Engine
{
  void Level::HandleKeyEvent(const sf::Keyboard::Key &key)
  {
    //std::cerr << "Level got key event!" << std::endl;

    //If the PlayerActor moved on top of a collision box, place the actor back at their old position
    //TODO: CORRECT movement instead of disallowing all movement
    //  ie PLACE ACTOR AT EDGE OF BOX

    if (PlayerActor.WantsInputEvent(Events::KeyPressed)) {
      PlayerActor.Handler.HandleKeyPress(key);
    }

  }

  void Level::CorrectActorMovement(const std::size_t &boxIndex)
  {

    sf::FloatRect FR = CollisionBoxes[boxIndex].GetBox();

    sf::FloatRect AC = PlayerActor.Collsion.GetBox();

    //TODO finish
    //For now, place actor at old position


  }
}
