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

      void AddRenderTarget(std::string &ID, sf::Drawable *item);

      template<typename EVENTS, typename CALLBACK, typename... OTHERS>
      void AddMouseTarget(std::string &ID, const sf::FloatRect &rect, EVENTS, CALLBACK, OTHERS...);

    protected:
      std::unordered_map<std::string, RenderTarget> RenderTargets;
      std::unordered_map<std::string, MouseTarget> MouseTargets;

      std::bitset<32> State;
    };
  }
}

#endif
