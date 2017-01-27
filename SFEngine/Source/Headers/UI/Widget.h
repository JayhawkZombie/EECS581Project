#ifndef SFENGINE_WIDGET_BASE_H
#define SFENGINE_WIDGET_BASE_H

#include <memory>

#include "Drawables/Drawables.h"
#include "Events\Events.h"

namespace Engine
{


#ifdef WIDGET_CONSTRUCT_DEBUG_OUT

#define WIDGET_IDINFO_DEBUG(CLASSNAME, ITEMNAME)\
std::cerr << CLASSNAME << " ID " << ITEMNAME->GetID() << std::endl;
#else
#define WIDGET_IDINFO_DEBUG(CLASSNAME, ITEMNAME)
#endif

  namespace UI
  {

    class WidgetHelper;
    class UILayer;
    class TextLabel;

    class WidgetBase
    {
    public:
      EDITOR_FRIEND

        //this is necessary to be able to delegate the destructor in std::shared_ptr to the widget helper "RequestDelete"
      friend class WidgetHelper; 
      friend class UILayer;

      //assign the WidgetHelper that created this object
      //widgets CANNOT be created without this **ie DO NOT create a class that constructs the widget without this**
      static std::shared_ptr<WidgetBase> Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper);

      /**
      * Base level event handlers
      */
      virtual void ConsumeEvent(const InputEvent &IEvent);
      virtual void OnFocusGained(const FocusChangeEvent &FEvent);
      virtual void OnFocusLost(const FocusChangeEvent &FEvent);
      virtual void OnKeyPress(const InputEvent &IEvent);
      virtual void OnKeyRelease(const InputEvent &IEvent);
      virtual void OnMousePress(const InputEvent &IEvent);
      virtual void OnMouseRelease(const InputEvent &IEvent);
      virtual void OnMouseScroll(const InputEvent &IEvent);
      virtual void OnMouseOver(const InputEvent &IEvent);
      virtual void OnMouseLeave(const InputEvent &IEvent);
      virtual void OnMouseMove(const InputEvent &IEvent);
      virtual void OnDragBegin(const InputEvent &IEvent);
      virtual void OnDragContinue(const InputEvent &IEvent);
      virtual void OnDragEnd(const InputEvent &IEvent);

      virtual std::string ClassName() {
        return "WidgetBase";
      }

      virtual void MoveTo(const sf::FloatRect &Region) {}

      virtual void AddTextLabel(std::shared_ptr<TextLabel> Label);

      virtual void Move(const sf::Vector2f &Delta);

      virtual void CreateHelper();

      virtual void TickUpdate(const double &delta);
      virtual void Render(std::shared_ptr<sf::RenderTexture> &Target);

      void SetUpWidget(); //this must always be called immediately after construction
      void SetUpLayerless(); //Special widgets that do not need a layer above them, like MenuScreen objects

      virtual void InvalidateWidget(); //Invalidate this widget. It cannot be used anymore.
      virtual void ForceCleanUp(); //Clean up now, stop whatever you are doing

      std::vector<std::shared_ptr<WidgetBase>>& GetChildren();

      void AssignHelper(std::shared_ptr<WidgetHelper> Helper);

      void NotifyHelperOfClose();

      void SetDraggingEnabled(const bool &Enabled) {
        CanBeDragged = Enabled;
      }

      void SetIsHidden(bool Hidden) {
        IsHidden = Hidden;
      }

      virtual void Resize(const sf::Vector2f &Size);

      //All widgets some with SOME basic elements available
      sf::Text ButtonText;
      std::shared_ptr<sf::Font> ButtonFont;

      //some rebindable callbacks
      std::function<void(void)> MouseOverCB = [this]() {};
      std::function<void(void)> MouseLeaveCB = [this]() {};
      std::function<void(void)> MousePressCB = [this]() {};
      std::function<void(void)> MouseReleaseCB = [this]() {};
      std::function<void(void)> MouseMoveCB = [this]() {};
      std::function<void(void)> KeyPressCB = [this]() {};
      std::function<void(void)> KeyReleaseCB = [this]() {};
      std::function<void(void)> MouseScrollCB = [this]() {};
      std::function<void(void)> FocusGainedCB = [this]() {};
      std::function<void(void)> FocusLostCB = [this]() {};
      std::function<void(void)> DragBeginCB = [this]() {};
      std::function<void(void)> DragEndCB = [this]() {};
      std::function<void(void)> DragContinueCB = [this]() {};

      /**
      *  The global region in which this widget can be drawn
      *   and shoud receive events
      */
      DrawableQuad GlobalWidgetBounds;

      bool IsInFocus() const {
        return HasFocus;
      }
      bool IsCurrentlyInDrag() const {
        return IsBeingDragged;
      }
      bool CanDrag() const {
        return CanBeDragged;
      }

      virtual ~WidgetBase();
    protected:
      WidgetBase();

      //The highest-level UILayer you want to be able to steal focus from
      std::weak_ptr<WidgetHelper> Helper; 

      //The helper that is containing THIS OBJECT
      std::weak_ptr<UILayer> MyLayer;

      //The layer you can use to store your own children
      std::shared_ptr<UILayer> ChildLayer;

      //32-bit identifier (use current epoch), no 32-bit architectures sorry
      std::uint32_t WidgetID;
      bool IsValid = false; //set to TRUE after the Creator has initialized it
      bool WasInvalidated = false; //set to TRUE if InvalidateWidget() is ever called
      bool CleanedUpAfterInvalidation = false; //Set to TRUE when ForceCleanUp() is called, allowing the widget to clean up after a bad error
      bool IsBeingUpdated = true;
      bool CanBeDragged = false;
      bool IsBeingDragged = false;
      bool HasFocus = false;
      bool IsHidden = false;

      /**
      * Contain a set of drawable to be rendered to their respective canvases
      */
      std::vector<std::shared_ptr<Drawable>> Drawables;

      std::vector<std::shared_ptr<TextLabel>> TextLabels;

      std::vector<std::shared_ptr<WidgetBase>> Children;

      std::unordered_set<ExceptionCause> ExceptionsEncountered; //Keep track of exceptions. Some we can recover from, some we cannot

      std::string InvalidationCause = "Unknown";

      /**
      *  Canvas to which the widget will be rendered (as well as all children, if they are to be rendered)
      */
      std::shared_ptr<Canvas> DrawTarget;
    };

    typedef std::shared_ptr<Engine::UI::WidgetBase> SharedWidgetPointer;
  }


}
#endif
