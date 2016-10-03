#include "../../Headers/UI/KeyTarget.h"

namespace Engine
{

  KeyTarget::KeyTarget()
  {
    OnKeyPress = [this](const sf::Keyboard::Key &) {};
    OnKeyRelease = [this](const sf::Keyboard::Key &) {};
  }

  KeyTarget::~KeyTarget()
  {

  }

  KeyTarget::KeyTarget(const KeyTarget &k)
  {
    OnKeyPress = k.OnKeyPress;
    OnKeyRelease = k.OnKeyRelease;

    Keys = k.Keys;
  }

}
