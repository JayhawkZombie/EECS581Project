#include "../../../Headers/UI/Draggables/StickyBar.h"

#include "../../../Headers/UI/WIdgetHelper.h"

namespace Engine
{

  namespace UI
  {



    std::shared_ptr<StickyBar> StickyBar::Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper, const sf::Vector2f & Position,
                                                 const sf::Vector2f & Size, const sf::Vector2f & VertBarSize, const sf::Vector2f & HorizBarSize, const sf::Vector2f &DragBarSize)
    {
      if (!ThisLayer.lock() || !ThisLayer.lock()->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer, ExceptionCause::ConstructionError },
                                     EXCEPTION_MESSAGE("Given UILayer is NULL or cannot accept a widget"));

      try
      {
        std::shared_ptr<StickyBar> Bar(new StickyBar);
        Bar->CanBeDragged = false;
        Bar->Helper = ThisHelper.lock();
        Bar->ChildLayer = UI::UILayer::Create(Bar->Helper.lock());
        WIDGET_IDINFO_DEBUG("StickyBar : ChildLayer", Bar->ChildLayer)

        Bar->MyLayer = ThisLayer.lock();
        ThisLayer.lock()->RegisterWidget(Bar);
        assert(Bar->Helper.lock() && Bar->MyLayer.lock());

        Bar->DragRect = DraggableRect::Create(Bar->ChildLayer, Bar->Helper, Position, DragBarSize);
        Bar->DragRect->SetDraggingEnabled(true);
        Bar->DragRect->Shape.setPosition(Position);
        Bar->DragRect->Shape.setSize(DragBarSize);

        Bar->BarSize = VertBarSize;
        Bar->DragBarSize = DragBarSize;
        Bar->HorizontalBarSize = HorizBarSize;

        Bar->LeftBarPosition = Position;
        Bar->RightBarPosition = { Position.x + Size.x - VertBarSize.x, Position.y };
        Bar->LeftVertBar.setPosition(Bar->LeftBarPosition);
        Bar->LeftVertBar.setSize(Bar->BarSize);
        Bar->LeftVertBar.setFillColor(sf::Color(104, 82, 142, 100));

        Bar->RightVertBar.setPosition(Bar->RightBarPosition);
        Bar->RightVertBar.setSize(Bar->BarSize);
        Bar->RightVertBar.setFillColor(sf::Color(104, 82, 142, 100));

        Bar->HorizontalBar.setPosition(Position);
        Bar->HorizontalBar.setSize(HorizBarSize);
        Bar->HorizontalBar.setFillColor(sf::Color(142, 82, 119, 100));
        Bar->HorizontalBar.setOutlineColor(sf::Color(79, 45, 66, 100));
        Bar->HorizontalBar.setOutlineThickness(-2);

        Bar->GlobalWidgetBounds.ForceRegion({ Position.x, Position.y, Size.x, DragBarSize.y });

        Bar->DragRect->OnDragged = 
          [Bar](auto delta)
        {
          Bar->ScrollList(delta);
        };

        return Bar;
      }
      catch (EngineRuntimeError &err)
      {
        err.AddCause(ExceptionCause::ConstructionError);
        err.AddMessage(EXCEPTION_MESSAGE("Could not construct StickyBar"));

        throw;
      }

    }

    void StickyBar::ConsumeEvent(const InputEvent & IEvent)
    {
      if (!IsHidden && ChildLayer && ChildLayer->HandleEvent(IEvent)) {

      }
      else {

      }
    }

    void StickyBar::OnFocusGained(const FocusChangeEvent & FEvent)
    {
    }

    void StickyBar::OnFocusLost(const FocusChangeEvent & FEvent)
    {
    }

    void StickyBar::OnKeyPress(const InputEvent & IEvent)
    {
    }

    void StickyBar::OnKeyRelease(const InputEvent & IEvent)
    {
    }

    void StickyBar::OnMousePress(const InputEvent & IEvent)
    {
      WidgetBase::OnMousePress(IEvent);
      ConsumeEvent(IEvent);
    }

    void StickyBar::OnMouseRelease(const InputEvent & IEvent)
    {
      WidgetBase::OnMouseRelease(IEvent);
      ConsumeEvent(IEvent);
    }

    void StickyBar::OnMouseScroll(const InputEvent & IEvent)
    {
    }

    void StickyBar::OnMouseOver(const InputEvent & IEvent)
    {
      WidgetBase::OnMouseOver(IEvent);

      ConsumeEvent(IEvent);
    }

    void StickyBar::OnMouseLeave(const InputEvent & IEvent)
    {
      WidgetBase::OnMouseLeave(IEvent);

      ConsumeEvent(IEvent);
    }

    void StickyBar::OnMouseMove(const InputEvent & IEvent)
    {
      WidgetBase::OnMouseMove(IEvent);
      ConsumeEvent(IEvent);
    }

    void StickyBar::AlignBar()
    {
      //But now make sure the y coordinate aligns with the horizontal dragging bar
      sf::Vector2f BarPos;

      float HeightDiff = DragRect->GlobalWidgetBounds.GlobalBounds.height - HorizontalBarSize.y;

      sf::FloatRect DragRectBounds = DragRect->GlobalWidgetBounds.GlobalBounds;
      float OverlapRight = (DragRectBounds.left + DragRectBounds.width) - (GlobalWidgetBounds.GlobalBounds.left + GlobalWidgetBounds.GlobalBounds.width);
      float OverlapLeft = (DragRectBounds.left) - (GlobalWidgetBounds.GlobalBounds.left);

      if (OverlapLeft < std::numeric_limits<float>::epsilon()) {
        DragRectBounds.left += OverlapLeft;
      }
      else if (OverlapRight > std::numeric_limits<float>::epsilon()) {
        DragRectBounds.left -= OverlapRight;
      }

      DragRectBounds.top = HorizontalBarPosition.y - (HeightDiff / 2.f);

      DragRect->GlobalWidgetBounds.ForceRegion(DragRectBounds);
      DragRect->Shape.setPosition({ DragRectBounds.left, DragRectBounds.top });
    }

    void StickyBar::ScrollList(const sf::Vector2f & Delta)
    {
      if (IsVertical) {
        //scroll up/down
        OnScroll({ 0, Delta.y });
      }
      else {
        //scroll left/right
        OnScroll({ Delta.x, 0 });
      }
    }

    void StickyBar::OnDragBegin(const InputEvent & IEvent)
    {
      DragRect->OnDragBegin(IEvent);

      //AlignBar();
    }

    void StickyBar::OnDragEnd(const InputEvent & IEvent)
    {
      DragRect->OnDragEnd(IEvent);

      //AlignBar();
    }

    void StickyBar::OnDragContinue(const InputEvent & IEvent)
    {
      //DragRect->OnDragContinue(IEvent);

      if (OnScroll) {
        sf::Vector2f Delta = static_cast<sf::Vector2f>(IEvent.CurrentMousePosition) - static_cast<sf::Vector2f>(IEvent.PreviousMousePosition);
        OnScroll(Delta);
      }

      //AlignBar();
    }

    void StickyBar::TickUpdate(const double & delta)
    {
    }

    void StickyBar::Render(std::shared_ptr<sf::RenderTexture> Texture)
    {
      auto View = MakeView(GlobalWidgetBounds.GlobalBounds);

      Texture->setView(View);

      Texture->draw(HorizontalBar);
      Texture->draw(LeftVertBar);
      Texture->draw(RightVertBar);

      DragRect->Render(Texture);

      Texture->setView(Texture->getDefaultView());
    }

    void StickyBar::Move(const sf::Vector2f & Delta)
    {

      HorizontalBar.move(Delta);
      RightVertBar.move(Delta);
      LeftVertBar.move(Delta);

      DragRect->Move(Delta);
    }

    StickyBar::StickyBar()
    {
    }

  }

}
