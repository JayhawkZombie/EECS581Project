#ifndef SFENGINE_WIDGET_HELPER_H
#define SFENGINE_WIDGET_HELPER_H

#include "../Globals/GlobalHooks.h"
#include "Events\Events.h"
#include "../Exceptions/Exceptions.h"

#include "WidgetCollisionHelpers.h"
#include "../Utils/CollisionHelpers.h"
#include "Widget.h"

#include <list>

#ifndef REVERSE_ITERATE

#define REVERSE_ITERATE(Member,Varname)\
for(auto Varname = Member.rbegin(); Varname != Member.rend(); ++Varname)\

#endif


#ifndef BRING_TO_FRONT

#define BRING_TO_FRONT(Member,Index)\
auto ptr = Member[Index];\
Member.erase(Member.begin() + Index);\
Member.insert(Member.begin() + 0, ptr);

#endif

namespace Engine
{


  namespace UI
  {

    
    typedef std::shared_ptr<WidgetBase> SharedWidgetPointer;
    class WidgetHelper;

    enum class InteractionType : std::uint32_t
    {
      NoFocusChange = 0,
      FocusChange,
      NoInteraction,
      BeginDrag,
      ContinueDrag,
      EndDrag
    };

    //Small struct to keep UI layered
    class UILayer
    {
    public:
      friend class WidgetHelper;

      UILayer() = default;
      ~UILayer() = default;
      static std::shared_ptr<UILayer> Create(std::shared_ptr<WidgetHelper> ThisHelper);
      
      void TickUpdate(const double &delta);
      void Render(std::shared_ptr<sf::RenderTexture> &Texture);

      bool CanAcceptWidget() const;
      bool HandleEvent(const InputEvent &IEvent);
      bool IsValid() const;

      void Move(const sf::Vector2f &Delta);

      std::uint32_t GetID() const {
        return LayerID;
      }

      void RegisterWidget(SharedWidgetPointer Widget);

      std::function<void(std::uint32_t)> LayerRegisterDebugOutputFunction = [](auto t) {};

    protected:
      void BringItemToFront(std::size_t index);

      std::uint32_t LayerID;

      void BeginWidgetDrag(SharedWidgetPointer Widget, const InputEvent &IEvent);
      void ContinueWidgetDrag(SharedWidgetPointer Widget, const InputEvent &IEvent);
      void EndWidgetDrag(SharedWidgetPointer Widget, const InputEvent &IEVent);

      InteractionType TestEvent(SharedWidgetPointer Widget, const InputEvent &IEvent);
      void NonFocusChecks(SharedWidgetPointer Widget, const InputEvent &IEvent); //things like mouse moving off items, etc, but no focus changes

      void SwitchFocusTo(std::vector<SharedWidgetPointer>::iterator it, const InputEvent &IEvent);
      void RevokeFocus(SharedWidgetPointer Widget, const InputEvent &IEvent);

      std::vector<SharedWidgetPointer> Items;
      SharedWidgetPointer FocusedItem;
      bool HasFocus = false;
      bool IsActive = true;
      sf::FloatRect GlobalBounds; //The global area you don't want interaction to go outside of
    };

    class WidgetHelper
    {
    public:
      static std::shared_ptr<WidgetHelper> Create();
      ~WidgetHelper() = default;
      WidgetHelper() = default;

      void AddUILayer();
      void AddUILayer(std::shared_ptr<UILayer> Layer);
      void RegisterWidget(std::shared_ptr<WidgetBase> Widget, std::size_t layer = 0);
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

      void TakeFocus(WidgetBase *Ptr) {
        FocusStack.push_back(Ptr);
      }

      void ReleaseFocus(WidgetBase *Ptr) {
        if (!Ptr)
          return;

        auto ptr = std::find(FocusStack.begin(), FocusStack.end(), Ptr);
        if (ptr != FocusStack.end())
          FocusStack.erase(ptr);
      }

    protected:
      bool ConsumeMouseMovementEvent(SharedWidgetPointer Widget,  const InputEvent &IEvent);
      bool ConsumeMousePressEvent(SharedWidgetPointer Widget, const InputEvent &IEvent);
      bool ConsumeMouseReleaseEvent(SharedWidgetPointer Widget, const InputEvent &IEvent);
      bool ConsumeKeyPressEvent(SharedWidgetPointer Widget, const InputEvent &IEvent);
      bool ConsumeKeyReleaseEvent(SharedWidgetPointer Widget, const InputEvent &IEvent);

      std::vector<WidgetBase*> FocusStack; //used for stacking focus requests

      std::vector<std::shared_ptr<UILayer>> Layers;

      //New testing methods
      bool TestEvent(std::size_t layer);
      void BringToFront(std::size_t layer);
      static void DoWidgetSetup(SharedWidgetPointer &Widget);
      

      //std::list<SharedWidgetPointer> UIItems;
      //std::vector<SharedWidgetPointer> Items;

      bool WasInvalidated = true;

      std::list<SharedWidgetPointer>::iterator FocusedItem;

      //std::map<std::uint32_t, std::shared_ptr<WidgetBase>> RegisteredWidgets;
      
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
      static bool TestEvent(SharedWidgetPointer Item, const InputEvent &IEvent, SharedWidgetPointer &Focused);

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
      static void PotentiallySwitchFocus(SharedWidgetPointer Interacted, SharedWidgetPointer &Focus, const FocusChangeEvent &FEvent);

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
