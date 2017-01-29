#ifndef SFENGINE_UI_MENU_BASE_H
#define SFENGINE_UI_MENU_BASE_H

#include "../Widget.h"

namespace Engine
{

  namespace UI
  {
    class UILayer;
    class WidgetHelper;

    class MenuWidgetBase : public WidgetBase
    {
    public:
      friend class UILayer;
      friend class WidgetHelper;

      static std::shared_ptr<MenuWidgetBase> Create(std::weak_ptr<UILayer> Layer, std::weak_ptr<WidgetHelper> ThisHelper, const sf::Vector2f &Position, const sf::Vector2f &Size);

      virtual void ConsumeEvent(const InputEvent &IEvent) override;
      virtual void OnFocusGained(const FocusChangeEvent &FEvent) override;
      virtual void OnFocusLost(const FocusChangeEvent &FEvent) override;
      virtual void OnKeyPress(const InputEvent &IEvent) override;
      virtual void OnKeyRelease(const InputEvent &IEvent) override;
      virtual void OnMousePress(const InputEvent &IEvent) override;
      virtual void OnMouseRelease(const InputEvent &IEvent) override;
      virtual void OnMouseScroll(const InputEvent &IEvent) override;
      virtual void OnMouseOver(const InputEvent &IEvent) override;
      virtual void OnMouseLeave(const InputEvent &IEvent) override;
      virtual void OnMouseMove(const InputEvent &IEvent) override;
      virtual void OnDragBegin(const InputEvent &IEvent) override;
      virtual void OnDragEnd(const InputEvent &IEvent) override;
      virtual void OnDragContinue(const InputEvent &IEvent) override;
      virtual void TickUpdate(const double &delta) override;
      virtual void Render(std::shared_ptr<sf::RenderTexture> Texture) override;

      virtual ~MenuWidgetBase();
    protected:
      MenuWidgetBase();
    };

  }

}

#endif
