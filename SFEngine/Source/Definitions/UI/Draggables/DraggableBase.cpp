#include "../../../Headers/UI/Draggables/DraggableBase.h"

#include "../../../Headers/UI/WIdgetHelper.h"

namespace Engine
{

  namespace UI
  {

    std::shared_ptr<DraggableBase> DraggableBase::Create(std::shared_ptr<UILayer> ThisLayer, const sf::Vector2f &Position, const sf::Vector2f &Size)
    {
      std::shared_ptr<DraggableBase> Widget(new DraggableBase);

      return Widget;
    }

    DraggableBase::DraggableBase()
      : WidgetBase()
    {
      CanBeDragged = true;
    }

    void DraggableBase::Move(const sf::Vector2f &Delta)
    {
      WidgetBase::Move(Delta);
    }

    void DraggableBase::ConsumeEvent(const InputEvent &IEvent)
    {
      WidgetBase::ConsumeEvent(IEvent);
    }

    void DraggableBase::OnFocusGained(const FocusChangeEvent &FEvent)
    {
      WidgetBase::OnFocusGained(FEvent);
    }

    void DraggableBase::OnFocusLost(const FocusChangeEvent &FEvent)
    {
      WidgetBase::OnFocusLost(FEvent);
    }

    void DraggableBase::OnKeyPress(const InputEvent &IEvent)
    {
      WidgetBase::OnKeyPress(IEvent);
    }

    void DraggableBase::OnKeyRelease(const InputEvent &IEvent)
    {
      WidgetBase::OnKeyRelease(IEvent);
    }

    void DraggableBase::OnMousePress(const InputEvent &IEvent)
    {
      WidgetBase::OnMousePress(IEvent);
    }

    void DraggableBase::OnMouseRelease(const InputEvent &IEvent)
    {
      WidgetBase::OnMouseRelease(IEvent);
    }

    void DraggableBase::OnMouseScroll(const InputEvent &IEvent)
    {
      WidgetBase::OnMouseScroll(IEvent);
    }

    void DraggableBase::OnMouseOver(const InputEvent &IEvent)
    {
      WidgetBase::OnMouseOver(IEvent);
    }

    void DraggableBase::OnMouseLeave(const InputEvent &IEvent)
    {
      WidgetBase::OnMouseLeave(IEvent);
    }

    void DraggableBase::OnMouseMove(const InputEvent &IEvent)
    {
      WidgetBase::OnMouseMove(IEvent);
    }

    void DraggableBase::OnDragBegin(const InputEvent &IEvent)
    {
      WidgetBase::OnDragBegin(IEvent);

      //We're being dragged, so we need to take all of our children with us
      if (Helper)
        Helper->HandleDragBegin(IEvent);
    }

    void DraggableBase::OnDragEnd(const InputEvent &IEvent)
    {
      WidgetBase::OnDragEnd(IEvent);

      if (Helper)
        Helper->HandleDragEnd(IEvent);
    }

    void DraggableBase::OnDragContinue(const InputEvent &IEvent)
    {
      WidgetBase::OnDragContinue(IEvent);

      if (Helper)
        Helper->HandleDragContinue(IEvent);
    }

    void DraggableBase::TickUpdate(const double &delta)
    {
      WidgetBase::TickUpdate(delta);
    }

    void DraggableBase::Render(std::shared_ptr<sf::RenderTexture> &Texture)
    {
      WidgetBase::Render(Texture);
    }

  }

}
