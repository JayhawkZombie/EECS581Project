#include "../../Headers/UI/WIdgetHelper.h"
#include "../../Headers/UI/Widget.h"

#include "../../Headers/Utils/Various.h"

namespace Engine
{

  namespace UI
  {

    bool UILayer::HandleEvent(const InputEvent &IEvent)
    {
      InteractionType Interaction;
      bool Interacted = false;

      //Do we have a focused element?
      if (FocusedItem && !FocusedItem->IsHidden) {
        //Do collision tests for the focused element
        Interaction = TestEvent(FocusedItem, IEvent);
        if (Interaction == InteractionType::FocusChange)
          RevokeFocus(FocusedItem, IEvent);
        
        if (Interaction != InteractionType::NoInteraction)
          return true;
        else
          RevokeFocus(FocusedItem, IEvent);
      }
      if (Items.empty())
        return false;

      //Check for all other items
      for (auto it = Items.begin(); it != Items.end(); ++it) {
        //OH THE SYNTAX, IT'S SO UGLY!! 
        Interaction = !(*it)->IsHidden ? TestEvent(*it, IEvent) : InteractionType::NoInteraction;

        if (Interaction == InteractionType::FocusChange) {
          SwitchFocusTo(it, IEvent);
          Interacted = true;
          break;
        }

        if (Interaction != InteractionType::NoInteraction)
          Interacted = true;
      }

      return Interacted;
    }

    void UILayer::RevokeFocus(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      FocusChangeEvent FEvent;
      FEvent.CurrentMousePosition = IEvent.CurrentMousePosition;
      FEvent.PreviousMousePosition = IEvent.PreviousMousePosition;
      FEvent.ChangeType = FocusChangeType::ItemForced;

      Widget->OnFocusLost(FEvent);
      Widget->HasFocus = false;
      FocusedItem = nullptr;
    }

    void UILayer::Move(const sf::Vector2f &Delta)
    {
      for (auto & item : Items)
        item->Move(Delta);
    }

    void UILayer::NonFocusChecks(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      if (DidMouseOver(Widget, IEvent))
        Widget->OnMouseOver(IEvent);
      else if (DidMouseLeave(Widget, IEvent))
        Widget->OnMouseLeave(IEvent);
      else if (DidMouseMove(Widget, IEvent))
        Widget->OnMouseMove(IEvent);
    }

    InteractionType UILayer::TestEvent(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {

      InteractionType Interaction{ InteractionType::NoInteraction };

      if (Widget->IsHidden)
        return Interaction;

      if (DidMouseMove(Widget, IEvent)) {
        Widget->OnMouseMove(IEvent);
        Interaction = InteractionType::NoFocusChange;
      }
      if (DidMouseOver(Widget, IEvent)) {
        Widget->OnMouseOver(IEvent);
        Interaction = InteractionType::NoFocusChange;
      }
      if (DidMouseLeave(Widget, IEvent)) {
        Widget->OnMouseLeave(IEvent);
        Interaction = InteractionType::NoFocusChange;
      }
      //Pressing changes focus
      else if (DidMousePress(Widget, IEvent)) {
        Widget->OnMousePress(IEvent);
        //But we should only signal a change of focus if the user didn't press on a given element already
        Interaction = (Widget->HasFocus ? 
                       InteractionType::NoFocusChange : InteractionType::FocusChange);
      }
      else if (DidMouseRelease(Widget, IEvent)) {
        Widget->OnMouseRelease(IEvent);
        Interaction = InteractionType::NoFocusChange;
      }
      if (DidBeginDrag(Widget, IEvent)) {
        Widget->OnDragBegin(IEvent);
        BeginWidgetDrag(Widget, IEvent);
        Interaction = InteractionType::BeginDrag;
      }
      else if (DidContinueDrag(Widget, IEvent)) {
        Widget->OnDragContinue(IEvent);
        ContinueWidgetDrag(Widget, IEvent);
        Interaction = InteractionType::ContinueDrag;
      }
      else if (DidEndDrag(Widget, IEvent)) {
        Widget->OnDragEnd(IEvent);
        EndWidgetDrag(Widget, IEvent);
        Interaction = InteractionType::EndDrag;
      }

      return Interaction;
    }

    void UILayer::SwitchFocusTo(std::vector<SharedWidgetPointer>::iterator it, const InputEvent &IEvent)
    {
      FocusChangeEvent FEvent;
      FEvent.CurrentMousePosition = IEvent.CurrentMousePosition;
      FEvent.PreviousMousePosition = IEvent.PreviousMousePosition;
      FEvent.ChangeType = FocusChangeType::ItemForced;

      auto ptr = *it;

      if (FocusedItem) {
        DEBUG_ONLY std::cerr << "Widget " << FocusedItem->WidgetID << " lost focus " << std::endl;
        FocusedItem->OnFocusLost(FEvent);
        FocusedItem->HasFocus = false;
      }

      //We should check about MouseLeave events for other elements, since they can sometimes be missed
      for (auto & item : Items) {
        if (DidMouseLeave(item, IEvent))
          item->OnMouseLeave(IEvent);
      }

      FocusedItem = *it;

      Items.erase(it);
      Items.insert(Items.begin() + 0, ptr);

      FocusedItem->OnFocusGained(FEvent);
      FocusedItem->HasFocus = true;

      DEBUG_ONLY std::cerr << "Widget " << FocusedItem->WidgetID << " gained focus " << std::endl;
    }

    void UILayer::BeginWidgetDrag(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      Widget->IsBeingDragged = true;
      
      auto dMovement = static_cast<sf::Vector2f>(IEvent.CurrentMousePosition - IEvent.PreviousMousePosition);
      //Widget->GlobalWidgetBounds.MoveRegion(dMovement);
    }

    void UILayer::ContinueWidgetDrag(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      auto dMovement = static_cast<sf::Vector2f>(IEvent.CurrentMousePosition - IEvent.PreviousMousePosition);
      //Widget->GlobalWidgetBounds.MoveRegion(dMovement);
    }

    void UILayer::EndWidgetDrag(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      Widget->IsBeingDragged = false;
      Widget->HasFocus = false;

      auto dMovement = static_cast<sf::Vector2f>(IEvent.CurrentMousePosition - IEvent.PreviousMousePosition);
      //Widget->GlobalWidgetBounds.MoveRegion(dMovement);
    }

    std::shared_ptr<UILayer> UILayer::Create(std::shared_ptr<WidgetHelper> ThisHelper)
    {
      auto ptr = std::make_shared<UILayer>();
      ptr->FocusedItem = nullptr;

      try {
        ptr->LayerID = GenerateID();
      }
      catch (IDException &err) {
        err.AddCause({ ExceptionCause::ConstructionError });
        err.AddMessage(EXCEPTION_MESSAGE("Widget UILayer invalid, cannot generate ID"));

        throw;
      }

      DEBUG_ONLY std::cerr << "UILayer created : ID " << ptr->LayerID << std::endl;

      return ptr;
    }

    void UILayer::RegisterWidget(SharedWidgetPointer Widget)
    {
      if (!Widget) {
        throw NullPointerException({ ExceptionCause::NullPointer }, EXCEPTION_MESSAGE("Widget is NULL"));
      }

      //First make sure the widget hasn't already been setup
      if (Widget->WidgetID != 0) {
        throw InvalidObjectException({ ExceptionCause::InitializationError }, EXCEPTION_MESSAGE("Widget has already been set up"));
      }

      try {
        Widget->SetUpWidget();

        //Test to make sure the widget isn't already added (avoid duplication)
        for (auto & item : Items) {
          if (item->WidgetID == Widget->WidgetID)
            return; //already in here
        }

        Items.insert(Items.begin() + 0,  Widget);

        DEBUG_ONLY std::cerr << "Layer " << LayerID << " : Widget Registered " << Widget->WidgetID << std::endl;

        if (LayerRegisterDebugOutputFunction)
          LayerRegisterDebugOutputFunction(Widget->WidgetID);
      }
      catch (EngineRuntimeError &err) {
        err.AddCause({ ExceptionCause::IDGenerationError });
        throw;
      }
    }

    void UILayer::RegisterLayerlessWidget(SharedWidgetPointer Widget)
    {
      if (!Widget)
        throw InvalidObjectException({ ExceptionCause::InvalidObjectUsed },
                                     EXCEPTION_MESSAGE("Widget is NULL"));

      DEBUG_ONLY std::cerr << "UILayer::RegisterLayerlessWidget : ID " << Widget->WidgetID << std::endl;
      Items.push_back(Widget);
    }

    void UILayer::RemoveWidget(SharedWidgetPointer Widget)
    {
      //Gotta try to find the widget

      for (auto it = Items.begin(); it != Items.end(); ++it) {
        if ((*it)->WidgetID == Widget->WidgetID) {
          DEBUG_ONLY std::cerr << "UILayer::RemoveWidget : Removing ID " << Widget->WidgetID << std::endl;
          Items.erase(it);
          return;
        }
      }

      throw InvalidParameter({ ExceptionCause::InvalidParameter },
                             EXCEPTION_MESSAGE("Tried to remove widget, but widget did not exist in container"));
    }

    void UILayer::ClearAllWidgets()
    {
      DEBUG_ONLY std::cerr << "UILayer : WARNING -> CLEARING ALL WIDGETS FROM LAYER" << std::endl;
      Items.clear();
    }

    bool UILayer::CanAcceptWidget() const
    {
      return true;
    }

    bool UILayer::IsValid() const
    {
      return true;
    }

    void UILayer::TickUpdate(const double &delta)
    {
      for (auto & item : Items) {
        if (item->IsBeingUpdated)
          item->TickUpdate(delta);
      }
    }

    void UILayer::Render(std::shared_ptr<sf::RenderTexture> &Texture)
    {
      for (auto & item : Items) {
        item->Render(Texture);
      }
    }

    void UILayer::BringItemToFront(std::size_t index)
    {
      if (index >= Items.size())
        throw InvalidParameter({ ExceptionCause::InvalidParameter }, EXCEPTION_MESSAGE("Widget item index out of bounds"));

      BringItemToFrontOfContainer(Items, index);
    }























    /**
    
    
                   UIHELPER MEMBER FUNCTIONS
    
    
    */

    std::shared_ptr<WidgetHelper> WidgetHelper::Create()
    {
      std::shared_ptr<WidgetHelper> Help = std::make_shared<WidgetHelper>();
      Help->Layers.insert(Help->Layers.begin() + 0, UILayer::Create(Help));

      DEBUG_ONLY assert(Help->Layers.front().get());

      DEBUG_ONLY std::cerr << "WidgetHelper::Create()" << std::endl;

      return Help;
    }

    void WidgetHelper::AddUILayer()
    {
      Layers.insert(Layers.begin() + 0, UILayer::Create(std::shared_ptr<WidgetHelper>(this)));
      DEBUG_ONLY assert(Layers.front().get());

      DEBUG_ONLY std::cerr << "WidgetHelper::AddUILayer() : There are " << Layers.size() << " layers" << std::endl;
    }

    void WidgetHelper::AddUILayer(std::shared_ptr<UILayer> Layer)
    {
      DEBUG_ONLY assert(Layer);
      for (auto & layer : Layers)
        layer->HasFocus = false;

      Layer->HasFocus = true;
      Layers.insert(Layers.begin() + 0, Layer);


      for (auto & item : Layers[0]->Items) {
        item->SetUpWidget();
      }

      DEBUG_ONLY assert(Layers.front().get());

      DEBUG_ONLY std::cerr << "WidgetHelper::AddUILayer() : There are " << Layers.size() << " layers" << std::endl;
    }

    void WidgetHelper::DoWidgetSetup(SharedWidgetPointer &Widget)
    {
      //First make sure the widget hasn't already been setup
      if (Widget->WidgetID != 0) {
        throw InvalidObjectException({ ExceptionCause::InitializationError }, EXCEPTION_MESSAGE("Widget has already been setup"));
      }

      try {
        Widget->SetUpWidget();
      }
      catch (EngineRuntimeError &err) {
        err.AddCause({ ExceptionCause::IDGenerationError });
        throw;
      }


    }

    void WidgetHelper::TickUpdate(const double &delta)
    {
      //shorthand of : for(auto layer = Layers.rbegin(); layer != Layers.rend(); ++layer)
      for (auto & it : Layers) {
        (*it).TickUpdate(delta);
      }
    }

    void WidgetHelper::Render(std::shared_ptr<sf::RenderTexture> &Target)
    {
      //Render the widgets from back to front
      //  Ugh, why isn't there a reverse range-based for loop?
      for (auto it = Layers.rbegin(); it != Layers.rend(); ++it) {
        (*it)->Render(Target);
      }

      if (!FocusStack.empty()) {
        FocusStack.top().lock()->Render(Target);
      }
    }

    void WidgetHelper::RegisterWidget(std::shared_ptr<WidgetBase> Widget, std::size_t layer)
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
        DEBUG_ONLY std::cerr << "WidgetHelper::RegisterWidget : Layer : " << layer << " : WidgetID : " << Widget->WidgetID << std::endl;
      }
      catch (IDException &err) {
        //UGHHHH WHY
        //We can't really handle this. We can tell the item to clean itself up, but then what?
        err.AddCause(ExceptionCause::ObjectWasInvalidated);
        throw;
      }

      //OK, we can register this
      //RegisteredWidgets[Widget->WidgetID] = Widget;
      //UIItems.push_front(Widget);
      //Items.push_back(Widget);

      if (layer >= Layers.size())
        throw InvalidParameter({ ExceptionCause::InvalidParameter }, EXCEPTION_MESSAGE("layer is out of Layers range"));

      Layers[layer]->Items.push_back(Widget);

      DEBUG_ONLY std::cerr << "WidgetHelper::RegisterWidget : Layer " << layer << " has " << Layers[layer]->Items.size() << " registered widgets" << std::endl;
    }

    void WidgetHelper::RemoveWidget(std::shared_ptr<WidgetBase> Widget)
    {
    }

    void WidgetHelper::BringToFront(std::size_t layer)
    {
      if (layer >= Layers.size()) {
        throw InvalidParameter({ ExceptionCause::InvalidParameter }, EXCEPTION_MESSAGE("layer index out of bounds"));
      }

      auto ptr = Layers[layer];
      Layers.erase(Layers.begin() + layer);

      Layers.insert(Layers.begin() + 0, ptr);
    }

    //STATIC HELPER FUNCTION
    bool WidgetHelper::DidMouseOver(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      auto Rect = Widget->GlobalWidgetBounds.GlobalBounds;

      return (!Widget->IsHidden && IsPointInsideRect(Rect, IEvent.CurrentMousePosition) &&
              !IsPointInsideRect(Rect, IEvent.PreviousMousePosition) );
    }

    bool WidgetHelper::DidMouseLeave(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      auto Rect = Widget->GlobalWidgetBounds.GlobalBounds;

      return (!Widget->IsHidden && IsPointInsideRect(Rect, IEvent.CurrentMousePosition) &&
              IsPointInsideRect(Rect, IEvent.PreviousMousePosition));
    }


    bool WidgetHelper::DidMouseMove(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      auto Rect = Widget->GlobalWidgetBounds.GlobalBounds;

      return (!Widget->IsHidden &&  (IEvent.CurrentMousePosition != IEvent.PreviousMousePosition) &&
              IsPointInsideRect(Rect, IEvent.CurrentMousePosition) &&
              IsPointInsideRect(Rect, IEvent.PreviousMousePosition));
    }


    bool WidgetHelper::DidMouseDrag(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      //We will let the item itself control this
      //If it wants to be able to be dragged, it must set Widget::CanBeDragged = true after being pressed on
      auto Rect = Widget->GlobalWidgetBounds.GlobalBounds;

      return (!Widget->IsHidden && IsPointInsideRect(Rect, IEvent.CurrentMousePosition) &&
              !(IEvent.EventType == InputEventType::MouseRelease) &&
              Widget->CanBeDragged);
    }

    bool WidgetHelper::DidMousePress(SharedWidgetPointer Widget, const InputEvent &event)
    {
      //Did the mouse press down on the item?
      auto Rect = Widget->GlobalWidgetBounds.GlobalBounds;

      return (!Widget->IsHidden && IsPointInsideRect(Rect, event.CurrentMousePosition) &&
              event.MouseButtonWasPressed);
    }

    bool WidgetHelper::DidMouseRelease(SharedWidgetPointer Widget, const InputEvent &IEvent)
    {
      //Did the mouse release on the item?
      auto Rect = Widget->GlobalWidgetBounds.GlobalBounds;

      return (!Widget->IsHidden &&
              IsPointInsideRect(Rect, IEvent.CurrentMousePosition) &&
              IEvent.MouseButtonWasReleased);
    }

    bool WidgetHelper::ConsumeEvent(const InputEvent &IEvent)
    {
      //Let's see if any of our elements were hit
      FocusChangeEvent FEvent;
      FEvent.ChangeType = FocusChangeType::UserForced;
      FEvent.CurrentMousePosition = IEvent.CurrentMousePosition;
      FEvent.PreviousMousePosition = IEvent.PreviousMousePosition;

      if (!FocusStack.empty()) {
        FocusStack.top().lock()->ConsumeEvent(IEvent);
        return true;
      }

      if (Layers.front()->HandleEvent(IEvent)) {
        //DEBUG_ONLY std::cerr << "Layer.front() handled event" << std::endl;
        return true;
      }
      else {
        //DEBUG_ONLY std::cerr << "Layer.front() did not handle event" << std::endl;
        return false;
      }

      //If there is a focused layer, it should be the top layer
      //if (Layers[0]->HasFocus && Layers[0]->IsActive) {
      //  //The front layer already has focus, so we will try to do collision testing with just the top layer
      //  //But make sure the event actually occurred inside the layer
      //  if (Layers[0]->HandleEvent(IEvent))
      //    return true;
      //}
      //else {
      //  Layers[0]->HasFocus = false;
      //}

      ////So, it didn't interact with the top layer, but there was some event
      ////So we'll iterate through and find out which layer was interacted with
      //for (std::size_t layer = 1; layer < Layers.size(); ++layer) {
      //  if (Layers[layer]->IsActive && Layers[layer]->HandleEvent(IEvent)) {
      //    Layers[layer]->HasFocus = true;
      //    BringToFront(layer);
      //    return true;
      //  }
      //}
    }

    bool WidgetHelper::TestEvent(std::size_t layer)
    {
      return false;
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
    bool WidgetHelper::TestEvent(SharedWidgetPointer Widget, const InputEvent &IEvent, SharedWidgetPointer &Focused)
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

    void WidgetHelper::PotentiallySwitchFocus(SharedWidgetPointer Interacted, SharedWidgetPointer &CurrentFocus, const FocusChangeEvent &FEvent)
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

