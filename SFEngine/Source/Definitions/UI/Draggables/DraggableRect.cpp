#include "../../../Headers/UI/Draggables/DraggableRect.h"
#include "../../../Headers/UI/WIdgetHelper.h"

namespace Engine
{

  namespace UI
  {

    std::shared_ptr<DraggableRect> DraggableRect::Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper, const sf::Vector2f & Position, const sf::Vector2f & Size)
    {
      if (!ThisLayer.lock() || !ThisLayer.lock()->CanAcceptWidget()) 
        throw InvalidObjectException({ ExceptionCause::InvalidContainer, ExceptionCause::ConstructionError },
                                     EXCEPTION_MESSAGE("Given UILayer is NULL or cannot accept a widget"));

      try
      {
        std::shared_ptr<DraggableRect> Rect(new DraggableRect);
        Rect->Helper = ThisHelper.lock();
        Rect->Shape.setPosition(Position);
        Rect->Shape.setSize(Size);
        Rect->Shape.setFillColor(sf::Color(43, 43, 43, 150));
        Rect->Shape.setOutlineColor(sf::Color(167, 167, 170, 150));
        Rect->Shape.setOutlineThickness(-2);

        Rect->MyLayer = ThisLayer.lock();
        ThisLayer.lock()->RegisterWidget(Rect);

        assert(Rect->Helper.lock() && Rect->MyLayer.lock());

        Rect->CanBeDragged = true;

        
        Rect->GlobalWidgetBounds.ForceRegion({ Position, Size });

        return Rect;
      }
      catch (EngineRuntimeError &err)
      {
        err.AddCause(ExceptionCause::ConstructionError);
        err.AddMessage(EXCEPTION_MESSAGE("Could not construct DraggableRect"));

        throw;
      }


    }

    void DraggableRect::ConsumeEvent(const InputEvent & IEvent)
    {
    }

    void DraggableRect::OnFocusGained(const FocusChangeEvent & FEvent)
    {
      if (FocusGainedCB)
        FocusGainedCB();
    }

    void DraggableRect::OnFocusLost(const FocusChangeEvent & FEvent)
    {
      if (FocusLostCB)
        FocusLostCB();
    }

    void DraggableRect::OnKeyPress(const InputEvent & IEvent)
    {
      if (KeyPressCB)
        KeyPressCB();
    }

    void DraggableRect::OnKeyRelease(const InputEvent & IEvent)
    {
      if (KeyReleaseCB)
        KeyReleaseCB();
    }

    void DraggableRect::OnMousePress(const InputEvent & IEvent)
    {
      if (MousePressCB)
        MousePressCB();
    }

    void DraggableRect::OnMouseRelease(const InputEvent & IEvent)
    {
      if (MouseReleaseCB)
        MouseReleaseCB();
    }

    void DraggableRect::OnMouseScroll(const InputEvent & IEvent)
    {
      if (MouseScrollCB)
        MouseScrollCB();
    }

    void DraggableRect::OnMouseOver(const InputEvent & IEvent)
    {
      Shape.setOutlineColor(sf::Color(82, 105, 142, 150));

      if (MouseOverCB)
        MouseOverCB();
    }

    void DraggableRect::OnMouseLeave(const InputEvent & IEvent)
    {
      Shape.setOutlineColor(sf::Color(167, 167, 170, 150));

      if (MouseLeaveCB)
        MouseLeaveCB();
    }

    void DraggableRect::OnMouseMove(const InputEvent & IEvent)
    {
      if (MouseMoveCB)
        MouseMoveCB();
    }

    void DraggableRect::OnDragBegin(const InputEvent & IEvent)
    {
      sf::FloatRect NewBounds = GlobalWidgetBounds.GlobalBounds;

      WidgetBase::OnDragBegin(IEvent);

      float xDiff = IEvent.CurrentMousePosition.x - IEvent.PreviousMousePosition.x;

      NewBounds.left += xDiff;

      GlobalWidgetBounds.ForceRegion(NewBounds);
      Shape.setPosition({ NewBounds.left, NewBounds.top });

      Shape.setOutlineColor(sf::Color::Red);

      if (DragBeginCB)
        DragBeginCB();
    }

    void DraggableRect::OnDragEnd(const InputEvent & IEvent)
    {
      sf::FloatRect NewBounds = GlobalWidgetBounds.GlobalBounds;
      WidgetBase::OnDragEnd(IEvent);

      float xDiff = IEvent.CurrentMousePosition.x - IEvent.PreviousMousePosition.x;

      NewBounds.left += xDiff;

      GlobalWidgetBounds.ForceRegion(NewBounds);
      Shape.setPosition({ NewBounds.left, NewBounds.top });

      Shape.setOutlineColor(sf::Color(167, 167, 170, 150));

      if (DragEndCB)
        DragEndCB();
    }

    void DraggableRect::OnDragContinue(const InputEvent & IEvent)
    {
      //Capture old position before widget base corrects, cuz we'll need to undo the y-coord correction it does
      sf::FloatRect NewBounds = GlobalWidgetBounds.GlobalBounds;

      WidgetBase::OnDragContinue(IEvent);

      float xDiff = IEvent.CurrentMousePosition.x - IEvent.PreviousMousePosition.x;

      NewBounds.left += xDiff;

      GlobalWidgetBounds.ForceRegion(NewBounds);
      Shape.setPosition({ NewBounds.left, NewBounds.top });

      if (OnDragged)
        OnDragged({ static_cast<sf::Vector2f>(IEvent.CurrentMousePosition) - static_cast<sf::Vector2f>(IEvent.PreviousMousePosition) });

      if (DragContinueCB)
        DragContinueCB();
    }

    void DraggableRect::TickUpdate(const double & delta)
    {
    }

    void DraggableRect::Render(std::shared_ptr<sf::RenderTexture>& Texture)
    {
      Texture->draw(Shape);
    }

    void DraggableRect::Move(const sf::Vector2f & Delta)
    {
      DraggableBase::Move(Delta);

      Shape.move(Delta);
    }

    DraggableRect::DraggableRect()
    {
    }

  }

}
