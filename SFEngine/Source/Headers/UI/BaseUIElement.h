#ifndef SFENGINE_BASE_UI_ELEMENT_H
#define SFENGINE_BASE_UI_ELEMENT_H

#include "../Engine/BaseEngineInterface.h"
#include "UIAttributes.h"

#include "RenderTarget.h"
#include "MouseTarget.h"

#include <bitset>

namespace Engine
{
  namespace UI
  {
    /**
     * Base class to create UI elements
     * To properly interface with the UI controller, UI elements should be derived from this class
     */
    class BaseUIElement : public BaseEngineInterface
    {
    public:
      friend class UIController;

      BaseUIElement();
      BaseUIElement(const BaseUIElement &b) = delete;
      ~BaseUIElement();

      virtual void TickUpdate(const double &delta) = 0;
      virtual void Render();
      virtual void OnShutDown() = 0;
      
      virtual bool RespondsTo(const Events &evnt) const;
      virtual void Align();

      void AddRenderTarget(std::string &ID, std::shared_ptr<sf::Drawable> item);

      virtual void SetPosition(const sf::Vector2f &v);
      virtual void SetSize(const sf::Vector2f &v);

      virtual sf::Vector2f GetSize() const;
      virtual sf::Vector2f GetPosition() const;

      void AddMouseTarget(std::string &ID, MouseTarget &tgt);

    protected:
      virtual void HandleMouseOver(const sf::Vector2i &pos);
      virtual void HandleMouseExit(const sf::Vector2i &pos);
      virtual void HandleMouseMovement(const sf::Vector2i &pos);
      virtual void HandleMousePress(const sf::Vector2i &pos, const sf::Mouse::Button &b);
      virtual void HandleMouseRelease(const sf::Vector2i &pos, const sf::Mouse::Button &b);
      virtual void HandleFocusGained(const sf::Vector2i &pos);
      virtual void HandleFocusLost(const sf::Vector2i &pos);

      std::unordered_map<std::string, RenderTarget> RenderTargets;
      std::unordered_map<std::string, MouseTarget> MouseTargets;

      sf::Vector2f v2fPostion;
      sf::Vector2f v2fSize;

      std::bitset<32> State;
    };
  }
}

#endif
