#ifndef SFENGINE_UI_CONTROLLER_H
#define SFENGINE_UI_CONTROLLER_H

#include "../BasicIncludes.h"
#include "../Engine/BaseEngineInterface.h"

#include "BaseUIElement.h"
#include "UIUtils.h"

namespace Engine
{
  namespace UI
  {
    class UIController : public BaseEngineInterface
    {
    public:
      friend class SFEngine;

      TYPEDEF_PARENT_CLASS(Engine::BaseEngineInterface);

      UIController();
      UIController(const UIController &) = delete;
      ~UIController();

      void AddElement(std::shared_ptr<BaseUIElement>);
      void TickUpdate(const double &delta);
      void Render();
      void OnShutDown();
      void SerializeOut(std::ofstream &out);
      void SerializeIn(std::ifstream &in);

      void Show();
      void Hide();
      void ToggleShown();

      bool IsShown() const;

      void ShowBoundsRect();
      void HideBoundsRect();

      sf::FloatRect GetBounds() const;
      void SetBounds(const sf::FloatRect &bnds);

    protected:
      std::vector<std::shared_ptr<BaseUIElement>> Elements;

      BaseUIElement *FocusedElement;
      bool Shown;
      bool DisplayBoundsRect;
      sf::RectangleShape BoundsRect;

      sf::FloatRect UIBounds;

      void HandleMouseMovement(const sf::Vector2i &pos);
      void HandleMouseOver(const sf::Vector2i &pos);
      void HandleMouseExit(const sf::Vector2i &pos);
      void HandleMousePress(const sf::Vector2i &pos, const sf::Mouse::Button &which);
      void HandleMouseRelease(const sf::Vector2i &pos, const sf::Mouse::Button &which);
      void HandleMouseScroll(const sf::Vector2i &pos);
      void HandleKeyPress(const sf::Keyboard::Key &which);
      void HandleKeyRelease(const sf::Keyboard::Key &which);
      void HandleTextEntered(const sf::Keyboard::Key &which);

      sf::Vector2i curMousePos;
      static bool TestDidMouseOver(MouseTarget &tgt, const sf::Vector2i &mousePos);
      static bool TestDidMouseLeave(MouseTarget &tgt, const sf::Vector2i &mousePos);
      static bool TestDidMouseMoveOn(MouseTarget &tgt, const sf::Vector2i &mousePos);
      static void GiveFocus(BaseUIElement *newelem);
      static void TakeFocus(BaseUIElement *newelem);
    };
  }
}


#endif
