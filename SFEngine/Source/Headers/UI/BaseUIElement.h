#ifndef SFENGINE_BASE_UI_ELEMENT_H
#define SFENGINE_BASE_UI_ELEMENT_H

#include "../Engine/BaseEngineInterface.h"
#include "UIAttributes.h"

#include "RenderTarget.h"
#include "MouseTarget.h"
#include "KeyTarget.h"

#include <bitset>

namespace Engine
{
#ifdef WITH_EDITOR
  class Editor;
#endif;

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
      friend class SFEngine;
#ifdef WITH_EDITOR
      friend class Editor;
#endif
      TYPEDEF_PARENT_CLASS(Engine::BaseEngineInterface);

      BaseUIElement();
      BaseUIElement(const BaseUIElement &b) = delete;
      virtual ~BaseUIElement();

      virtual void TickUpdate(const double &delta) = 0;
      virtual void Render();
      virtual void OnShutDown() = 0;
      virtual void SerializeOut(std::ofstream &out) = 0;
      virtual void SerializeIn(std::ifstream &in) = 0;
      
      virtual bool RespondsTo(const Events &evnt) const;
      virtual void Align();

      void AddRenderTarget(std::string &ID, std::shared_ptr<sf::Drawable> item);

      virtual void SetPosition(const sf::Vector2f &v);
      virtual void SetSize(const sf::Vector2f &v);

      virtual void SetFont(std::shared_ptr<sf::Font> fnt);

      virtual sf::Vector2f GetSize() const;
      virtual sf::Vector2f GetPosition() const;

      sf::FloatRect GetClickBounds() const;

      void AddMouseTarget(std::string &ID, MouseTarget &tgt);
      void AddKeyTarget(std::string &ID, KeyTarget &tgt);

      std::function<void(const sf::Vector2i &pos)> OnMouseOver;
      std::function<void(const sf::Vector2i &pos)> OnMouseExit;
      std::function<void(const sf::Vector2i &pos)> OnMouseMove;
      std::function<void(const sf::Vector2i &pos, const sf::Mouse::Button &which)> OnMousePress;
      std::function<void(const sf::Vector2i &pos, const sf::Mouse::Button &which)> OnMouseRelease;
      std::function<void(const sf::Vector2i &pos)> OnFocusGained;
      std::function<void(const sf::Vector2i &pos)> OnFocusLost;

      std::shared_ptr<BaseUIElement> Internal_Shared_Ptr;

    protected:
      //Internal methods used
      //Not intended to be used by the end-user to custom actions
      virtual void HandleMouseOver(const sf::Vector2i &pos);
      virtual void HandleMouseExit(const sf::Vector2i &pos);
      virtual void HandleMouseMovement(const sf::Vector2i &pos);
      virtual void HandleMousePress(const sf::Vector2i &pos, const sf::Mouse::Button &b);
      virtual void HandleMouseRelease(const sf::Vector2i &pos, const sf::Mouse::Button &b);
      virtual void HandleFocusGained(const sf::Vector2i &pos);
      virtual void HandleFocusLost(const sf::Vector2i &pos);
      virtual void HandleKeyPress(const sf::Keyboard::Key &key);
      virtual void HandleKeyRelease(const sf::Keyboard::Key &key);
      virtual void HandleTextEntered(const sf::Keyboard::Key &key);

      virtual void MakeRequests();

      std::map<std::string, RenderTarget> RenderTargets;
      std::map<std::string, MouseTarget> MouseTargets;
      std::map<std::string, KeyTarget> KeyTargets;

      std::shared_ptr<sf::Font> ItemFont;
      sf::FloatRect ClickBounds;
      sf::Vector2f v2fPostion;
      sf::Vector2f v2fSize;
      bool ReadyToRender;
      bool InFocus;
      std::bitset<32> State;
    };
  }
}

#endif
