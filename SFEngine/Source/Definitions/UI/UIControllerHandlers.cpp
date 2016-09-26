#include "../../Headers/UI/UIController.h"

namespace Engine
{
  namespace UI
  {

    void UIController::HandleMouseMovement(const sf::Vector2i &pos)
    {
      //std::cerr << "Mouse Moved!" << std::endl;
    }

    void UIController::HandleMouseOver(const sf::Vector2i &pos)
    {

    }

    void UIController::HandleMouseExit(const sf::Vector2i &pos)
    {

    }

    void UIController::HandleMousePress(const sf::Vector2i &pos, const sf::Mouse::Button &which)
    {
      std::cerr << "Mouse pressed!" << std::endl;
    }

    void UIController::HandleMouseRelease(const sf::Vector2i &pos, const sf::Mouse::Button &which)
    {
      std::cerr << "Mouse released!" << std::endl;
    }

    void UIController::HandleMouseScroll(const sf::Vector2i &pos)
    {

    }

    void UIController::HandleKeyPress(const sf::Keyboard::Key &which)
    {

    }

    void UIController::HandleKeyRelease(const sf::Keyboard::Key &which)
    {

    }

    void UIController::HandleTextEntered(const sf::Keyboard::Key &which)
    {

    }

  }
}