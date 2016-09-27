#include "../../Headers/Engine/Engine.h"

namespace Engine
{

  void SFEngine::HandleMouseMovement(const sf::Vector2i &mousePos)
  {

    EngineUIController.Handler.HandleMouseMovement(mousePos);
  }

  void SFEngine::HandleMousePress(const sf::Vector2i &v, const sf::Mouse::Button &b)
  {
    std::cerr << "[ENGINE]: Mouse pressed!" << std::endl;

    EngineUIController.Handler.HandleMousePress(v, b);
  }

  void SFEngine::HandleMouseRelease(const sf::Vector2i &v, const sf::Mouse::Button &b)
  {
    std::cerr << "[ENGINE]: Mouse released!" << std::endl;

    EngineUIController.Handler.HandleMouseRelease(v, b);
  }
}
