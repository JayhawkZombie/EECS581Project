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

      UIController();
      UIController(const UIController &) = delete;
      ~UIController();

      void AddElement(BaseUIElement *);
      void TickUpdate(const double &delta);
      void Render();
      void OnShutDown();

    protected:
      std::vector<std::shared_ptr<BaseUIElement>> Elements;

      void HandleMouseMovement(const sf::Vector2i &pos);
      void HandleMouseOver(const sf::Vector2i &pos);
      void HandleMouseExit(const sf::Vector2i &pos);
      void HandleMousePress(const sf::Vector2i &pos, const sf::Mouse::Button &which);
      void HandleMouseRelease(const sf::Vector2i &pos, const sf::Mouse::Button &which);
      void HandleMouseScroll(const sf::Vector2i &pos);
      void HandleKeyPress(const sf::Keyboard::Key &which);
      void HandleKeyRelease(const sf::Keyboard::Key &which);
      void HandleTextEntered(const sf::Keyboard::Key &which);

    };
  }
}


#endif