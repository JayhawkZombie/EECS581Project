#include "../../../Headers/UI/Draggables/DraggableRect.h"
#include "../../../Headers/UI/WIdgetHelper.h"

namespace Engine
{

  namespace UI
  {

    std::shared_ptr<DraggableRect> DraggableRect::Create(std::shared_ptr<UILayer> ThisLayer, const sf::Vector2f & Position, const sf::Vector2f & Size)
    {
      if (!ThisLayer || !ThisLayer->CanAcceptWidget()) 
        throw InvalidObjectException({ ExceptionCause::InvalidContainer, ExceptionCause::ConstructionError },
                                     EXCEPTION_MESSAGE("Given UILayer is NULL or cannot accept a widget"));

      try
      {
        std::shared_ptr<DraggableRect> Rect(new DraggableRect);

        Rect->Shape.setPosition(Position);
        Rect->Shape.setSize(Size);
        Rect->Shape.setFillColor(sf::Color(43, 43, 43, 150));
        Rect->Shape.setOutlineColor(sf::Color(167, 167, 170, 150));
        Rect->Shape.setOutlineThickness(-2);

        Rect->MyLayer = ThisLayer;
        ThisLayer->RegisterWidget(Rect);

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
    }

    void DraggableRect::OnFocusLost(const FocusChangeEvent & FEvent)
    {
    }

    void DraggableRect::OnKeyPress(const InputEvent & IEvent)
    {
    }

    void DraggableRect::OnKeyRelease(const InputEvent & IEvent)
    {
    }

    void DraggableRect::OnMousePress(const InputEvent & IEvent)
    {
    }

    void DraggableRect::OnMouseRelease(const InputEvent & IEvent)
    {
    }

    void DraggableRect::OnMouseScroll(const InputEvent & IEvent)
    {
    }

    void DraggableRect::OnMouseOver(const InputEvent & IEvent)
    {
      Shape.setOutlineColor(sf::Color(82, 105, 142, 150));
    }

    void DraggableRect::OnMouseLeave(const InputEvent & IEvent)
    {
      Shape.setOutlineColor(sf::Color(167, 167, 170, 150));
    }

    void DraggableRect::OnMouseMove(const InputEvent & IEvent)
    {
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
    }

    void DraggableRect::OnDragEnd(const InputEvent & IEvent)
    {
      sf::FloatRect NewBounds = GlobalWidgetBounds.GlobalBounds;
      WidgetBase::OnDragEnd(IEvent);

      float xDiff = IEvent.CurrentMousePosition.x - IEvent.PreviousMousePosition.x;

      NewBounds.left += xDiff;

      GlobalWidgetBounds.ForceRegion(NewBounds);
      Shape.setPosition({ NewBounds.left, NewBounds.top });

      Shape.setOutlineColor(sf::Color(167, 167, 170, 150));;
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
