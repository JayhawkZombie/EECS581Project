#include "../../Headers/Level/Level.h"

namespace Engine
{


  void Level::HandleKeyEvent(const sf::Keyboard::Key &key)
  {
    //std::cerr << "Level got key event!" << std::endl;

    for (auto & actor : Actors) {
      actor.Handler.HandleKeyPress(key);
    }

  }


}
