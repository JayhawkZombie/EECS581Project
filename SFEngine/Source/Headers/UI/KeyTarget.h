#ifndef SFENGINE_KEY_TARGET_H
#define SFENGINE_KEY_TARGET_H

#include "../BasicIncludes.h"

namespace Engine
{


  struct KeyTarget
  {
    KeyTarget();
    KeyTarget(const KeyTarget &);
    ~KeyTarget();

    std::function<void(const sf::Keyboard::Key &k)> OnKeyPress;
    std::function<void(const sf::Keyboard::Key &k)> OnKeyRelease;
    std::bitset<sf::Keyboard::KeyCount> Keys;
  };
}


#endif
