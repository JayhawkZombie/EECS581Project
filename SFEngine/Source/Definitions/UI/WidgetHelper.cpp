#include "../../Headers/UI/WIdgetHelper.h"
#include "../../Headers/UI/Widget.h"

namespace Engine
{

  namespace UI
  {

    std::shared_ptr<WidgetHelper> WidgetHelper::Create()
    {
      std::shared_ptr<WidgetHelper> Help = std::make_shared<WidgetHelper>();
      DEBUG_ONLY std::cerr << "WidgetHelper::Create()" << std::endl;

      return Help;
    }

    void WidgetHelper::TickUpdate(const double &delta)
    {
      for (auto & item : RegisteredWidgets)
        item.second->TickUpdate(delta);
    }

    void WidgetHelper::Render(std::shared_ptr<sf::RenderTexture> &Target)
    {
      for (auto & item : RegisteredWidgets)
        item.second->Render(Target);
    }

    void WidgetHelper::RegisterWidget(std::shared_ptr<WidgetBase> Widget)
    {
      DEBUG_ONLY std::cerr << "WidgetHelper::RegisterWidget" << std::endl;

      //First, the widget should NOT be initialized yet
      if (Widget->WidgetID != 0) {
        Widget->WidgetID = 0;
        throw InvalidObjectException( 
        {ExceptionCause::ObjectWasInvalidated}, 
          EXCEPTION_MESSAGE("Widget has already been initialized with a non-zero ID, cannot register Widget")
        );
      }

      //OK, we can try to initialize the widget now
      try {
        Widget->SetUpWidget();
        DEBUG_ONLY std::cerr << "WidgetHelper::RegisterWidget : WidgetID : " << Widget->WidgetID << std::endl;
      }
      catch (IDException &err) {
        //UGHHHH WHY
        //We can't really handle this. We can tell the item to clean itself up, but then what?
        err.AddCause(ExceptionCause::ObjectWasInvalidated);
        throw;
      }

      //OK, we can register this
      RegisteredWidgets[Widget->WidgetID] = Widget;

      DEBUG_ONLY std::cerr << "WidgetHelper::RegisterWidget : Registered " << RegisteredWidgets.size() << " widgets" << std::endl;
    }

    //STATIC HELPER FUNCTION
    bool WidgetHelper::DidMouseOver(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      auto Rect = Widget->GlobalWidgetBounds.GlobalBounds;

      return ( IsPointInsideRect(Rect, IEvent.CurrentMousePosition) &&
              !IsPointInsideRect(Rect, IEvent.PreviousMousePosition) );
    }

    bool WidgetHelper::DidMouseLeave(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      auto Rect = Widget->GlobalWidgetBounds.GlobalBounds;

      return (!IsPointInsideRect(Rect, IEvent.CurrentMousePosition) &&
              IsPointInsideRect(Rect, IEvent.PreviousMousePosition));
    }


    bool WidgetHelper::DidMouseMove(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      auto Rect = Widget->GlobalWidgetBounds.GlobalBounds;

      return ((IEvent.CurrentMousePosition != IEvent.PreviousMousePosition) &&
              IsPointInsideRect(Rect, IEvent.CurrentMousePosition) &&
              IsPointInsideRect(Rect, IEvent.PreviousMousePosition));
    }


    bool WidgetHelper::DidMouseDrag(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      //We will let the item itself control this
      //If it wants to be able to be dragged, it must set Widget::CanBeDragged = true after being pressed on
      auto Rect = Widget->GlobalWidgetBounds.GlobalBounds;

      return (IsPointInsideRect(Rect, IEvent.CurrentMousePosition) &&
              !(IEvent.EventType == InputEventType::MouseRelease) &&
              Widget->CanBeDragged);
    }

    bool WidgetHelper::DidMousePress(SharedWidgetPointer Widget, const InputEvent &event)
    {
      //Did the mouse press down on the item?
      auto Rect = Widget->GlobalWidgetBounds.GlobalBounds;

      return (IsPointInsideRect(Rect, event.CurrentMousePosition) &&
              event.MouseButtonWasPressed);
    }

    bool WidgetHelper::DidMouseRelease(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      //Did the mouse release on the item?
      auto Rect = Widget->GlobalWidgetBounds.GlobalBounds;

      return (IsPointInsideRect(Rect, IEvent.CurrentMousePosition) &&
              IEvent.MouseButtonWasReleased);
    }

    bool WidgetHelper::ConsumeEvent(const InputEvent &IEvent)
    {
      //Let's see if any of our elements were hit
      FocusChangeEvent FEvent;
      FEvent.ChangeType = FocusChangeType::UserForced;
      FEvent.CurrentMousePosition = IEvent.CurrentMousePosition;
      FEvent.PreviousMousePosition = IEvent.PreviousMousePosition;

      //first check to see if there is a focused element
      if (Focus) {
        if (Focus->IsBeingDragged && IEvent.IsMouseButtonDown(sf::Mouse::Button::Left)) {
          //The mouse could have flown out of the bounds of the focused element between event fires, so we have to check for that
          Focus->OnDragContinue(IEvent);
          return true;
        }
        else if (TestEvent(Focus, IEvent, Focus)) //If it didn't interact with the focused element, that doesn't mean it should lose focus
          return true;
      }

      //If an item isn't focused, it shouldn't be able to get "mouseMoved" events
      bool Consumed = false;

      for (auto & widget : RegisteredWidgets) {
        //See if something happened on this widget
        Consumed = TestEvent(widget.second, IEvent, Focus);
        if (Consumed) break;
      }

      return Consumed;
    }

    bool WidgetHelper::ConsumeMouseMovementEvent(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      //test for mouse movement

      return false;
    }

    bool WidgetHelper::ConsumeMousePressEvent(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {

      return false;
    }

    bool WidgetHelper::ConsumeMouseReleaseEvent(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {

      return false;
    }

    bool WidgetHelper::ConsumeKeyPressEvent(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {

      return false;
    }

    bool WidgetHelper::ConsumeKeyReleaseEvent(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {

      return false;
    }

    //STATIC COLLISION TESTING METHOD
    bool WidgetHelper::TestEvent(SharedWidgetPointer Widget, const InputEvent &IEvent, SharedWidgetPointer Focused)
    {
      if (!Widget)
        return false;

      bool Interacted = false;

      FocusChangeEvent FEvent;
      FEvent.ChangeType = FocusChangeType::UserForced;
      FEvent.CurrentMousePosition = IEvent.CurrentMousePosition;
      FEvent.PreviousMousePosition = IEvent.PreviousMousePosition;

      //Mouse moved over
      if (DidMouseMove(Widget, IEvent)) {
        Interacted = true;
        //check for dragging
        //  Should not need to give focus to this item, it should already have it
        //    (have to first press LEFT mouse down
        //    on it and THEN start dragging)
        if (Widget->HasFocus && Widget->CanBeDragged && !(Widget->IsBeingDragged) && IEvent.IsMouseButtonDown(sf::Mouse::Button::Left)) {
          BeginWidgetDrag(Widget, IEvent);
        }
        else if (Widget->HasFocus && Widget->IsBeingDragged && IEvent.IsMouseButtonDown(sf::Mouse::Button::Left)) {
          Widget->OnDragContinue(IEvent);
        }
        Widget->OnMouseMove(IEvent);
      }
      else if (DidMouseOver(Widget, IEvent)) {
        Interacted = true;
        Widget->OnMouseOver(IEvent);
      }
      else if (DidMouseLeave(Widget, IEvent)) {
        Interacted = true;
        //check to make sure the mouse didn't just move really fast while dragging the item
        if (Widget->HasFocus && Widget->IsBeingDragged)
          Widget->OnDragContinue(IEvent);
        else
          Widget->OnMouseLeave(IEvent);
      }
      else if (DidMousePress(Widget, IEvent)) {
        Interacted = true;
        //OK, if Focused is NULL then give this element Focus
        DEBUG_ONLY std::cerr << "WidgetHelper::TestEvent : MousePressed" << std::endl;
        if (!Focused) {
          //Focus switched
          PotentiallySwitchFocus(Widget, Focused, FEvent);
        } //If there is a focused element BUT its ID does not match the ID of the element just pressed down on, switch focus
        else if (Focused && !(Focused->WidgetID == Widget->WidgetID)) {
          PotentiallySwitchFocus(Widget, Focused, FEvent);
        }
        Widget->OnMousePress(IEvent);
      }
      else if (DidMouseRelease(Widget, IEvent)) {
        DEBUG_ONLY std::cerr << "WidgetHelper::TestEvent : MouseReleased" << std::endl;
        Interacted = true;
        if (Widget->IsBeingDragged && IEvent.MouseButtonWasReleased && (IEvent.Button == sf::Mouse::Button::Left)) {
          DEBUG_ONLY std::cerr << "Widged End Drag" << std::endl;
          EndWidgetDrag(Widget, IEvent);
          Widget->OnDragEnd(IEvent);
        }
        Widget->OnMouseRelease(IEvent);
      }

      return Interacted;
    }

    void WidgetHelper::PotentiallySwitchFocus(SharedWidgetPointer Interacted, SharedWidgetPointer CurrentFocus, const FocusChangeEvent &FEvent)
    {
      //if focused is not null, Interacted is not null, and the IDs do not match between the two widgets
      //then we invoke the FocusLost callback for the currently focused element, switch focus, then ivoke the FocusGained callback for the new element
      if (CurrentFocus && !(CurrentFocus->WidgetID == Interacted->WidgetID)) {
        CurrentFocus->HasFocus = false;
        CurrentFocus->OnFocusLost(FEvent);
        CurrentFocus = Interacted;
        CurrentFocus->HasFocus = true;
        CurrentFocus->OnFocusGained(FEvent);
      }
      //If focused is null, then give focus to the element
      else if (!CurrentFocus) {
        CurrentFocus = Interacted;
        CurrentFocus->HasFocus = true;
        CurrentFocus->OnFocusGained(FEvent);
      }
      //if interacted is null and current focus isn't null, then just take focus away from CurrentFocus
      else if (!Interacted) {
        CurrentFocus->HasFocus = false;
        CurrentFocus->OnFocusLost(FEvent);
        CurrentFocus = nullptr;
      }
      //Interacted is not null, CurrentFocus is not null, and the IDs match, so no switch should be made
      else {
        DEBUG_ONLY std::cerr << "WidgetHelper::PotentiallySwitchFocus : No focus change" << std::endl;
      }
    }

    bool WidgetHelper::DidBeginDrag(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      //A drag event can begin ONLY when a widget has focus, the mouse was pressed, and Widget::CanBeDragged is set to TRUE
      
      //Usual nullptr check
      if (!Widget) {
        throw NullPointerException({ ExceptionCause::NullPointer }, EXCEPTION_MESSAGE("Widget is NULL"));
      }

      //So first make sure the widget has focus (Dragging and giving focus will NEVER begin in the same event
      //  since a click and a movement are completely separate events)
      //  AND make sure the LEFT mouse was pressed

      //if the event was a mouse button Left being pressed, the item has focus, AND it ISN'T being dragged, then TRUE
      //otherwise FALSE
      return (IEvent.MouseButtonWasPressed &&
              IEvent.Button == sf::Mouse::Left &&
              Widget->HasFocus &&
              !Widget->IsBeingDragged);
    }

    bool WidgetHelper::DidContinueDrag(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      //usual nullptr check
      if (!Widget) {
        throw NullPointerException({ ExceptionCause::NullPointer }, EXCEPTION_MESSAGE("Widget is NULL"));
      }

      //If this is the case, then the current mouse should be over it and Widget->IsBeingDragged should be TRUE
      //  AND the LEFT mouse should be down

      //If the Left mouse button is pressed, the item is in focus, and the item is being dragged, then TRUE
      //otherwise FALSE
      return (IEvent.IsMouseButtonDown(sf::Mouse::Left) &&
              Widget->HasFocus &&
              Widget->IsBeingDragged);
    }

    bool WidgetHelper::DidEndDrag(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      //usual nullptr check
      if (!Widget) {
        throw NullPointerException({ ExceptionCause::NullPointer }, EXCEPTION_MESSAGE("Widget is NULL"));
      }

      //If this is the case, then the current mouse should be over it and Widget->IsBeingDragged should be TRUE
      //  AND the left mouse should NOT be down  (ie, the IEvent.WasButtonReleased should be TRUE)

      //If the mouse LEFT was released, the item currently has focus, and it is currently being dragged, then TRUE
      //otherwise FALSE
      return (IEvent.MouseButtonWasReleased &&
              IEvent.Button == sf::Mouse::Left &&
              Widget->HasFocus &&
              Widget->IsBeingDragged);
    }
    
    void WidgetHelper::BeginWidgetDrag(SharedWidgetPointer Widget, const FocusChangeEvent &FEvent)
    {

    }

    void WidgetHelper::EndWidgetDrag(SharedWidgetPointer Widget, const FocusChangeEvent &IEvent)
    {

    }

    void WidgetHelper::BeginWidgetDrag(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      //Begin dragging the widget
      Widget->IsBeingDragged = true;
      Widget->HasFocus = true;

      Widget->OnDragBegin(IEvent);
    }

    void WidgetHelper::EndWidgetDrag(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      //Invoke the callback BEFORE change value of state vars
      Widget->OnDragEnd(IEvent);

      Widget->HasFocus = false;
      Widget->IsBeingDragged = false;
    }

    bool WidgetHelper::ConsumeEvent(const FocusChangeEvent &event)
    {

      return true;
    }

    void WidgetHelper::RequestDelete(WidgetBase *Base)
    {
      //So, SOMETHING wants us to delete this. Why?
    }

    void WidgetHelper::HandleDragBegin(const InputEvent &IEvent)
    {

    }

    void WidgetHelper::HandleDragContinue(const InputEvent &IEvent)
    {

    }

    void WidgetHelper::HandleDragEnd(const InputEvent &IEvent)
    {

    }


  }

}

