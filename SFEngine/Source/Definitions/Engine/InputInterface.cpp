#include "../../Headers/Engine/InputInterface.h"
#include "../../../ThirdParty/chaiscript/chaiscript.hpp"

namespace Engine
{



  void InputInterface::BindMethods(chaiscript::ModulePtr mptr)
  {
    mptr->add(chaiscript::fun(&IsKeyDown), "IsKeyDown");
    mptr->add(chaiscript::fun(&IsKeyUp), "IsKeyUp");
    mptr->add(chaiscript::fun(&IsMouseDown), "IsMouseDown");
    mptr->add(chaiscript::fun(&IsMouseUp), "IsMouseUp");
    mptr->add(chaiscript::fun(&GetMousePosition), "GetMousePosition");
  }

  bool InputInterface::IsKeyDown(const sf::Keyboard::Key & key)
  {
    return sf::Keyboard::isKeyPressed(key);
  }

  bool InputInterface::IsKeyUp(const sf::Keyboard::Key & key)
  {
    return !IsKeyDown(key);
  }

  bool InputInterface::IsMouseDown(const sf::Mouse::Button & btn)
  {
    return sf::Mouse::isButtonPressed(btn);
  }

  bool InputInterface::IsMouseUp(const sf::Mouse::Button & btn)
  {
    return !IsMouseDown(btn);
  }

  sf::Vector2f InputInterface::GetMousePosition()
  {
    return static_cast<sf::Vector2f>(sf::Mouse::getPosition(*currentRenderWindow));
  }

}