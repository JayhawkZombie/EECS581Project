#include "../../Headers/UI/UIController.h"

namespace
{
  sf::Vector2i Mpos;
}

namespace Engine
{
  namespace UI
  {
    bool UIController::TestDidMouseOver(MouseTarget &tgt, const sf::Vector2i &mousePos)
    {
      if (!tgt.Enabled)
        return false;

      if (!tgt.MouseOver && IsMouseOverRect(mousePos, tgt.MouseBounds)) {
        tgt.MouseOver = true;
        tgt.MouseOverCallback(Mpos - sf::Vector2i(tgt.MouseBounds.left, tgt.MouseBounds.top));
        return true;
      }

      return false;
    }

    bool UIController::TestDidMouseMoveOn(MouseTarget &tgt, const sf::Vector2i &pos)
    {
      if (!tgt.Enabled)
        return false;

      if (tgt.MouseOver && IsMouseOverRect(pos, tgt.MouseBounds)) {
        tgt.MouseOver = true;
        tgt.MouseMovementCallback(pos - sf::Vector2i(tgt.MouseBounds.left, tgt.MouseBounds.top));
        return true;
      }

      return false;
    }

    bool UIController::TestDidMouseLeave(MouseTarget &tgt, const sf::Vector2i &mousePos)
    {
      if (!tgt.Enabled)
        return false;

      if (!IsMouseOverRect(mousePos, tgt.MouseBounds) && tgt.MouseOver) {
        tgt.MouseOver = false;
        tgt.MouseExitCallback(Mpos - sf::Vector2i(tgt.MouseBounds.left, tgt.MouseBounds.top));
        return true;
      }
    }

    void UIController::HandleMouseMovement(const sf::Vector2i &pos)
    {
      //std::cerr << "Mouse Moved!" << std::endl;
      curMousePos = pos;
      Mpos = pos;
      sf::Vector2i offset;

      if (FocusedElement && FocusedElement->State.test(Active)) {
        for (auto & tgt : FocusedElement->MouseTargets) {
          if (TestDidMouseOver(tgt.second, pos) || TestDidMouseLeave(tgt.second, pos) || TestDidMouseMoveOn(tgt.second, pos))
            return;
        }
      }

      //OK, so nothing moved moved over the active element (or there is no active element)

      for (auto & element : Elements) {
        if (element->State.test(Active)) {
          
          for (auto & tgt : element->MouseTargets) {

            //We do not pass "MouseMoved" events if the given element hasn't been given focus, so TestDidMouseMoveOn isn't tested
            if (TestDidMouseOver(tgt.second, pos) || TestDidMouseLeave(tgt.second, pos))
              return;
          } //end for tgt

        } //if state.test(Active)
      }//for element : Elements

     //K, well nothing happened, or they didn't move the mouse on any element
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

      if (FocusedElement && FocusedElement->State.test(Active)) {
        for (auto & tgt : FocusedElement->MouseTargets) {
          if (IsMouseOverRect(pos, tgt.second.MouseBounds)) {
            tgt.second.MouseOver = true;
            tgt.second.MousePressCallback(pos - sf::Vector2i(tgt.second.MouseBounds.left, tgt.second.MouseBounds.height), which);
            return;
          }
        }
      } //if (Focused Element)

      for (auto & element : Elements) {
        for (auto & tgt : element->MouseTargets) {
          if (IsMouseOverRect(pos, tgt.second.MouseBounds)) {
            if (FocusedElement)
              FocusedElement->HandleFocusLost(pos);

            tgt.second.FocusGainedCallback(pos - sf::Vector2i(tgt.second.MouseBounds.left, tgt.second.MouseBounds.top));
            tgt.second.MousePressCallback(pos - sf::Vector2i(tgt.second.MouseBounds.left, tgt.second.MouseBounds.top), which);
            FocusedElement = element.get();
            return;
          }
        }
      }

      //Hmm... They pressed outside of any element
      if (FocusedElement)
        FocusedElement->HandleFocusLost(pos);
      FocusedElement = nullptr;
      std::cerr << "Did not press on an element" << std::endl;
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
