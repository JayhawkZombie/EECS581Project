#ifndef SFENGINE_UI_STICKY_BAR_H
#define SFENGINE_UI_STICKY_BAR_H

#include "DraggableRect.h"

namespace Engine
{

  namespace UI
  {

    class UILayer;
    class WidgetHelper;

    class StickyBar : public WidgetBase
    {
    public:
      static std::shared_ptr<StickyBar> Create(std::shared_ptr<UILayer> ThisLayer, std::shared_ptr<WidgetHelper> ThisHelper, const sf::Vector2f &Position, const sf::Vector2f &Size, const sf::Vector2f &VertBarSize, const sf::Vector2f &HorizBarSize, const sf::Vector2f &DragBarSize);

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
      virtual void Render(std::shared_ptr<sf::RenderTexture> &Texture) override;
      virtual void Move(const sf::Vector2f &Delta) override;

      std::function<void(const sf::Vector2f &)> OnScroll = [](const sf::Vector2f &delta) {};

      virtual ~StickyBar() = default;
    protected:
      StickyBar();

      bool IsVertical = false;

      void AlignBar();

      void ScrollList(const sf::Vector2f &Delta);

      sf::Vector2f LeftBarPosition;
      sf::Vector2f RightBarPosition;
      sf::Vector2f DragBarPosition;
      sf::Vector2f HorizontalBarPosition;

      sf::FloatRect BarBounds;

      sf::RectangleShape LeftVertBar;
      sf::RectangleShape RightVertBar;
      sf::RectangleShape HorizontalBar;

      std::shared_ptr<DraggableRect> DragRect;

      sf::Vector2f BarSize;
      sf::Vector2f HorizontalBarSize;
      sf::Vector2f DragBarSize;


    };

  }

}


#endif
