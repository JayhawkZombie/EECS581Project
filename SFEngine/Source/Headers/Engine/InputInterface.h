#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "../Globals/GlobalHooks.h"

namespace Engine
{

  class InputInterface
  {
  public:
    static void BindMethods(chaiscript::ModulePtr mptr);

    static bool IsKeyDown(const sf::Keyboard::Key &key);
    static bool IsKeyUp(const sf::Keyboard::Key &key);
    static bool IsMouseDown(const sf::Mouse::Button &btn);
    static bool IsMouseUp(const sf::Mouse::Button &btn);
    static sf::Vector2f GetMousePosition();

  };

}