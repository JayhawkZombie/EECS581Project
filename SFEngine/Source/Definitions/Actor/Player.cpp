#include "../../Headers/Actor/Player.h"

namespace Engine
{

  Player::Player()
  {
    Handler.BindCallback(Events::KeyPressed,
    [this](const sf::Keyboard::Key &key)
    {
      this->KeyWasPressed(key);
    });
  }

  Player::~Player()
  {

  }

  void Player::KeyWasPressed(const sf::Keyboard::Key &k)
  {
    if (k == sf::Keyboard::Right) {

    }
  }

}
