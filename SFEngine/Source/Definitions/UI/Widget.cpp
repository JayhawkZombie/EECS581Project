#include "../../Headers/UI/Widget.h"
#include "../../Headers/UI/WIdgetHelper.h"

#include <random>

namespace Engine
{

  std::uint32_t MaxIDGenerationAttempts = 50;

  namespace UI
  {

    WidgetBase::WidgetBase()
      : WidgetID(0U) //This ID better be 0 before being set up
    {

    }

    WidgetBase::~WidgetBase()
    {

    }

    void WidgetBase::SetUpWidget()
    {
      DEBUG_ONLY std::cerr << "WidgetBase::SetUpWidget()" << std::endl;

      //Has this widget already been initialized?
      //Just ignore and return. Should we throw an exception instead?
      //Someone/something might have already tried to use this...
      if (WidgetID != 0)
        return;

      //This widget should now have a valid Creator set
      //If it isn't what happened?
      //This exceptions shouldn't ever actually happen, but
      //  in the off-chance that a classes uses this and tries to call 
      //  SetUpWidget() any time after the Creator became invalid, then this is bad
      if (!Creator || !Creator->IsValid())
        throw InvalidObjectException(
          { ExceptionCause::InvalidContainer },
          EXCEPTION_MESSAGE("Widget does not have a valid Creator set. Is this widget rogue?")
        );

      //generate a unique ID based on the current epoch
      //doesn't that just look beautiful? /s
      std::uint32_t ItemID = 0;

      try
      {
        ItemID = GenerateID();
        WidgetID = ItemID;
        DEBUG_ONLY std::cerr << "WidgetBase::WidgetID : " << WidgetID << std::endl;
      }
      catch (IDException &err)
      {
        DEBUG_ONLY std::cerr << "WidgetBase::SetUpWidget() : Failed to generate ID" << std::endl;

        //Errrrr, well that sucks
        InvalidationCause = "Unable to generate unique ID";
        InvalidateWidget();
        err.AddCause(ExceptionCause::IDGenerationError);
        err.AddMessage(EXCEPTION_MESSAGE("Widget could not generate ID"));

        throw; //throw the same exception back up, should be caught by the WidgetHelper
      }
    }

    void WidgetBase::InvalidateWidget()
    {
      //Sooooo, something blew up. This widget is no longer valid. Our helper should know about this
      //and place us in the correct structure to be taken care of

      //This sucks
      WasInvalidated = true;
      IsValid = false;
    }

    void WidgetBase::ForceCleanUp()
    {
      //this far down, nothing should have to be done
      //smart pointers will clean themselves up

      return;
    }

    std::shared_ptr<WidgetBase> WidgetBase::Create(std::shared_ptr<WidgetHelper> ThisCreator)
    {
      //Throw an excption if ThisCreator isn't valid, or cannot accept another widget for some reason
      //We can't create this, something is wrong with the container. Register ConstructionError since this object did not get constructed properly
      if (!ThisCreator || !ThisCreator->CanAcceptWidget())
        throw InvalidObjectException(
          { ExceptionCause::InvalidContainer, ExceptionCause::ConstructionError }, 
          EXCEPTION_MESSAGE("Created WidgetHelper is invalid or cannot accept any widgets")
        );

      //OK, we can create it
      std::shared_ptr<WidgetBase> Widget(new WidgetBase());

      //assign the WidgetHelper that created this object
      //widgets CANNOT be created without this **ie DO NOT create a class that constructs the widget without this**
      Widget->Creator = ThisCreator; 

      //Inform the creator of this new widget
      //This WidgetHelper obejct should make sure that this Widget is properly initialized
      //*****IT SHOULD NOT BE INITIALIZED ANYWHERE ELSE BUT FROM INSIDE THE WIDGET HELPER******
      ThisCreator->RegisterWidget(Widget);

      return Widget;
    }

    void WidgetBase::CreateHelper()
    {
      if (Helper)
        return;

      Helper = UI::WidgetHelper::Create();
    }

    void WidgetBase::AssignHelper(std::shared_ptr<WidgetHelper> __Helper) 
    {
      Helper = __Helper;
    }

    std::vector<std::shared_ptr<WidgetBase>>& WidgetBase::GetChildren() 
    {
      return Children;
    }

    void WidgetBase::NotifyHelperOfClose()
    {
      if (!Helper)
        throw InvalidObjectException({ ExceptionCause::InvalidObjectUsed },  
                                     EXCEPTION_MESSAGE("Widget helper is NULL - cannot notify of close"));
    }

    void WidgetBase::TickUpdate(const double &delta) {}
    void WidgetBase::Render(std::shared_ptr<sf::RenderTexture> &Texture) {}

    void WidgetBase::ConsumeEvent(const InputEvent &IEvent) {}
    void WidgetBase::OnFocusGained(const FocusChangeEvent &FEvent) {}
    void WidgetBase::OnFocusLost(const FocusChangeEvent &FEvent) {}
    void WidgetBase::OnKeyPress(const InputEvent &IEvent) {}
    void WidgetBase::OnKeyRelease(const InputEvent &IEvent) {}
    void WidgetBase::OnMousePress(const InputEvent &IEvent) {}
    void WidgetBase::OnMouseRelease(const InputEvent &IEvent) {}
    void WidgetBase::OnMouseScroll(const InputEvent &IEvent) {}
    void WidgetBase::OnMouseOver(const InputEvent &IEvent) {}
    void WidgetBase::OnMouseLeave(const InputEvent &IEvent) {}
    void WidgetBase::OnMouseMove(const InputEvent &IEvent) {}
    void WidgetBase::OnDragBegin(const InputEvent &IEvent) {}

    void WidgetBase::OnDragContinue(const InputEvent &IEvent)
    {
      if (CanBeDragged) {
        //move the global bounds, as well as all of the drawables with is
        //get the delta for the movement
        auto dMovement = IEvent.CurrentMousePosition - IEvent.PreviousMousePosition;

        GlobalWidgetBounds.MoveRegion(dMovement);
        for (auto & item : Drawables) {
          item->DrawBounds.MoveRegion(dMovement);
        }

        ButtonText.move(sf::Vector2f(dMovement));
      }//if (CanBeDragged)
    }

    void WidgetBase::OnDragEnd(const InputEvent &IEvent) {}
  }

}
