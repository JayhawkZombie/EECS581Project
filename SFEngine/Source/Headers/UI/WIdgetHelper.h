#ifndef SFENGINE_WIDGET_HELPER_H
#define SFENGINE_WIDGET_HELPER_H

#include "../Globals/GlobalHooks.h"
#include "Events\Events.h"
#include "../Exceptions/Exceptions.h"

#include "../Utils/CollisionHelpers.h"
#include "Widget.h"

namespace Engine
{


  namespace UI
  {

    
    typedef std::shared_ptr<WidgetBase> SharedWidgetPointer;

    class WidgetHelper
    {
    public:
      static std::shared_ptr<WidgetHelper> Create();
      ~WidgetHelper() = default;
      WidgetHelper() = default;

      void RegisterWidget(std::shared_ptr<WidgetBase> Widget);
      void Render(std::shared_ptr<sf::RenderTexture> &Target);
      void TickUpdate(const double &delta);

      //since widgets can ALSO contain a WidgetHelper, we want to be able to pass events from the widget to its helper
      void HandleDragBegin(const InputEvent &IEvent);
      void HandleDragContinue(const InputEvent &IEvent);
      void HandleDragEnd(const InputEvent &IEvent);

      bool ConsumeEvent(const InputEvent &event);
      bool ConsumeEvent(const FocusChangeEvent &event);

      bool IsValid() const {
        return WasInvalidated;
      }

      bool CanAcceptWidget() const {
        return true;
      }

      void RequestDelete(WidgetBase *Base);

    protected:
      bool ConsumeMouseMovementEvent(SharedWidgetPointer Widget,  const InputEvent &IEvent);
      bool ConsumeMousePressEvent(SharedWidgetPointer Widget, const InputEvent &IEvent);
      bool ConsumeMouseReleaseEvent(SharedWidgetPointer Widget, const InputEvent &IEvent);
      bool ConsumeKeyPressEvent(SharedWidgetPointer Widget, const InputEvent &IEvent);
      bool ConsumeKeyReleaseEvent(SharedWidgetPointer Widget, const InputEvent &IEvent);



      bool WasInvalidated = true;

      std::map<std::uint32_t, std::shared_ptr<WidgetBase>> RegisteredWidgets;
      
      std::shared_ptr<WidgetBase> Focus = nullptr;

      std::map<std::uint32_t,
        std::vector<ExceptionCause>> FailedRegistrations;

      //static helper functions
      /**
       *  Determine if an event was a MouseOver in relation to a specific Widget
       */
      static bool DidMouseOver(SharedWidgetPointer Widget, const InputEvent &IEvent);

      /**
      *  Determine if an event was a MouseLeave in relation to a specific Widget
      */
      static bool DidMouseLeave(SharedWidgetPointer Widget, const InputEvent &IEvent);

      /**
      *  Determine if an event was a MouseMove in relation to a specific Widget
      *    - ie The mouse moved from one spot inside the widget to some other position inside the widget
      */
      static bool DidMouseMove(SharedWidgetPointer Widget, const InputEvent &IEvent);

      /**
      *  Determine if an event started a dragging sequence
      *    ie the mouse was pressed down on an item that has CanBeDragged set to TRUE
      */
      static bool DidMouseDrag(SharedWidgetPointer Widget, const InputEvent &IEvent);

      /**
      *  Determine if the mouse pressed down in relation to a specific widget
      */
      static bool DidMousePress(SharedWidgetPointer Widget, const InputEvent &IEvent);

      /**
      *  Determine if the mouse was released while on a widget
      */
      static bool DidMouseRelease(SharedWidgetPointer Widget, const InputEvent &IEvent);

      /**
      *  Determine if the event could be consumed by a particular widget
      *    Focused CAN be changed by this method if an event caused the focus to switch
      */
      static bool TestEvent(SharedWidgetPointer Widget, const InputEvent &IEvent, SharedWidgetPointer Focused);

      /**
      *  Determine if an event began a drag on a Widget (this will give focus to the widget)
      */
      static bool DidBeginDrag(SharedWidgetPointer Widget, const InputEvent &IEvent);

      /**
      *  Determine if an event is continuing a drag of an element
      */
      static bool DidContinueDrag(SharedWidgetPointer Widget, const InputEvent &IEvent);

      /**
      *  Determine if an event ended a drag (this will NOT take focus away from the widget)
      */
      static bool DidEndDrag(SharedWidgetPointer Widget, const InputEvent &IEvent);

      /**
      *  Used to
      *   (1) : Test to see if the focus should be switched from CurrentFocus to Interacted.
      *   (2) : If the focus did in fact change, the appropriate callbacks are called and states changed
      */
      static void PotentiallySwitchFocus(SharedWidgetPointer Interacted, SharedWidgetPointer Focus, const FocusChangeEvent &FEvent);

      /**
      *  Used to set the widget states for begin dragging and invoke callbacks
      */
      static void BeginWidgetDrag(SharedWidgetPointer Interacted, const FocusChangeEvent &FEvent);

      /**
      *  Used to set the widget states for begin dragging and invoke callbacks
      */
      static void EndWidgetDrag(SharedWidgetPointer Interacted, const FocusChangeEvent &IEvent);

      /**
      *  Used to set the widget states for end dragging and invoke callbacks
      */
      static void BeginWidgetDrag(SharedWidgetPointer Interacted, const InputEvent &FEvent);

      /**
      *  Used to set the widget states for end dragging and invoke callbacks
      */
      static void EndWidgetDrag(SharedWidgetPointer Interacted, const InputEvent &IEvent);
    };


  }


}


#endif
