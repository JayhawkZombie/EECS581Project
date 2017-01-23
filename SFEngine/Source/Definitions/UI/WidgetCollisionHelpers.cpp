#include "../../Headers/UI/WidgetCollisionHelpers.h"

namespace Engine
{
  namespace UI
  {

    //Mouse moved over it if the previous mouse pos isn't over it but this one is
    bool DidMouseOver(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      return (
        IsPointInsideRect(Widget->GlobalWidgetBounds.GlobalBounds, IEvent.CurrentMousePosition) &&
        !(IsPointInsideRect(Widget->GlobalWidgetBounds.GlobalBounds, IEvent.PreviousMousePosition))
      );
    }

    //Left is the previous mouse pos is over it but the current one isn't
    bool DidMouseLeave(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      return (
        IsPointInsideRect(Widget->GlobalWidgetBounds.GlobalBounds, IEvent.PreviousMousePosition) &&
        !(IsPointInsideRect(Widget->GlobalWidgetBounds.GlobalBounds, IEvent.CurrentMousePosition))
      );
    }

    //True if both the current and previous mouse position are over this element
    bool DidMouseMove(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      return (
        IsPointInsideRect(Widget->GlobalWidgetBounds.GlobalBounds, IEvent.PreviousMousePosition) &&
        IsPointInsideRect(Widget->GlobalWidgetBounds.GlobalBounds, IEvent.CurrentMousePosition)
      );
    }

    bool DidMousePress(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      return (
        IsPointInsideRect(Widget->GlobalWidgetBounds.GlobalBounds, IEvent.CurrentMousePosition) &&
        IEvent.MouseButtonWasPressed
      );
    }

    bool DidMouseRelease(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      return (
        IsPointInsideRect(Widget->GlobalWidgetBounds.GlobalBounds, IEvent.CurrentMousePosition) &&
        IEvent.MouseButtonWasReleased
      );
    }

    /**
    * You can begin a drag by pressing down on an item and then beginning to drag the mouse
    *
    */
    bool DidBeginDrag(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      //True if the item is in focus and the mouse moved AND the mouse is held down, otherwise false
      return (
        Widget->CanDrag() &&
        Widget->IsInFocus() && !Widget->IsCurrentlyInDrag() &&
        (IEvent.EventType == InputEventType::MouseMovement) &&
        IEvent.IsMouseButtonDown(sf::Mouse::Button::Left)
      );
    }

    //True if the item is in focus, is currently in drag, the mosue moved, and the button is held down
    bool DidContinueDrag(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      return (
        Widget->CanDrag() &&
        Widget->IsInFocus() && Widget->IsCurrentlyInDrag() &&
        (IEvent.EventType == InputEventType::MouseMovement) &&
        IEvent.IsMouseButtonDown(sf::Mouse::Button::Left)
      );
    }

    //True if the item is in focus, is currently in drag and the mouse was released
    bool DidEndDrag(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      return (
        Widget->CanDrag() &&
        Widget->IsInFocus() && Widget->IsCurrentlyInDrag() &&
        (IEvent.EventType == InputEventType::MouseRelease) && 
        (IEvent.Button == sf::Mouse::Button::Left)
      );
    }

  }
}
