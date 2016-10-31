#include "../../Headers/Level/Level.h"

namespace Engine
{

  void Level::HandleKeyPress(const sf::Keyboard::Key &key)
  {
    Environment.HandleKeyPress(key);
  }

  void Level::HandleKeyRelease(const sf::Keyboard::Key &key)
  {
    Environment.HandleKeyRelease(key);
  }

}
