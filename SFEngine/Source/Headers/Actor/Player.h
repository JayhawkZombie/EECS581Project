#ifndef SFENGINE_PLAYER_H
#define SFENGINE_PLAYER_H

#include "Actor.h"

namespace Engine
{
  class Player : public GenericActor
  {
  public:
    Player();
    ~Player();


  protected:
    void KeyWasPressed(const sf::Keyboard::Key &k);

  };
}


#endif
