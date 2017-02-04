#include "../../Headers/UI/ObjectView.h"
#include "../../Headers/UI/WIdgetHelper.h"
#include "../../Headers/UI/Theme.h"

namespace Engine
{

  namespace UI
  {

    std::shared_ptr<ObjectView> ObjectView::Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper, const sf::Vector2f &Position, const sf::Vector2f &Size, std::shared_ptr<BaseEngineInterface> __Object)
    {
      if (!ThisLayer.lock() || !ThisLayer.lock()->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer }, EXCEPTION_MESSAGE("Layer is NULL or cannot accept a widget"));

      if (!ThisHelper.lock() || !ThisHelper.lock()->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer }, EXCEPTION_MESSAGE("Helper is NULL or cannot accept a widget"));

      try
      {
        std::shared_ptr<ObjectView> Object(new ObjectView);

        Object->MyLayer = ThisLayer.lock();
        Object->Helper = ThisHelper.lock();
        Object->CanBeDragged = false;

        assert(Object);
        assert(Object->MyLayer.lock() && Object->Helper.lock());

        ThisLayer.lock()->RegisterWidget(Object);
        auto __size = currentRenderWindow->getSize();

        Object->RawObject = __Object;
        Object->BGRect.setPosition(Position);
        Object->BGRect.setSize(Size);
        Object->Position = Position;
        Object->ObjectTarget = std::make_shared<sf::RenderTexture>();
        Object->ObjectTarget->create(__size.x, __size.y);
        Object->ObjectSprite.setTexture(Object->ObjectTarget->getTexture());
        Object->SetBGColor(DefaultDarkTheme.ButtonColorNormal);
        Object->SetBGColorHighlighted(DefaultDarkTheme.ButtonColorHighlighted);
        Object->SetBGColorPressed(DefaultDarkTheme.ButtonColorPressed);
        Object->SetBGOutlineColor(DefaultDarkTheme.ButtonOutlineColorNormal);
        Object->SetBGOutlineColorHighlighted(DefaultDarkTheme.ButtonOutlineColorHighlighted);
        Object->SetBGOutlineThickness(-1);
        Object->Shape.setPosition(Position);
        Object->Shape.setSize(Size);
        Object->Shape.setTexture(&(Object->ObjectTarget->getTexture()));
        Object->GlobalWidgetBounds.ForceRegion({ Position, Size });

        return Object;
      }
      catch (EngineRuntimeError &err)
      {
        throw;
      }
    }

    ObjectView::ObjectView()
    {
    }

    void ObjectView::ConsumeEvent(const InputEvent & IEvent)
    {
    }

    void ObjectView::OnFocusGained(const FocusChangeEvent & FEvent)
    {
    }

    void ObjectView::OnFocusLost(const FocusChangeEvent & FEvent)
    {
    }

    void ObjectView::OnKeyPress(const InputEvent & IEvent)
    {
    }

    void ObjectView::OnKeyRelease(const InputEvent & IEvent)
    {
    }

    void ObjectView::OnMousePress(const InputEvent & IEvent)
    {
      WidgetBase::OnMousePress(IEvent);
    }

    void ObjectView::OnTextEntered(const InputEvent & IEvent)
    {

    }

    void ObjectView::OnMouseRelease(const InputEvent & IEvent)
    {
      WidgetBase::OnMouseRelease(IEvent);
    }

    void ObjectView::OnMouseScroll(const InputEvent & IEvent)
    {
      
    }

    void ObjectView::OnMouseOver(const InputEvent & IEvent)
    {
      WidgetBase::OnMouseOver(IEvent);
    }

    void ObjectView::OnMouseLeave(const InputEvent & IEvent)
    {
      WidgetBase::OnMouseLeave(IEvent);
    }

    void ObjectView::OnMouseMove(const InputEvent & IEvent)
    {
      WidgetBase::OnMouseMove(IEvent);
    }

    void ObjectView::OnDragBegin(const InputEvent & IEvent)
    {
    }

    void ObjectView::OnDragContinue(const InputEvent & IEvent)
    {
    }

    void ObjectView::OnDragEnd(const InputEvent & IEvent)
    {
    }

    void ObjectView::AddTextLabel(std::shared_ptr<TextLabel> Label)
    {
    }

    void ObjectView::SetSpriteScale(float originalsize, float desiredsize)
    {
      ObjectSprite.setScale({ desiredsize / originalsize, desiredsize / originalsize });
    }

    void ObjectView::TickUpdate(const double & delta)
    {
      RawObject->TickUpdate(delta);
    }

    void ObjectView::Render(std::shared_ptr<sf::RenderTexture> Target)
    {
      auto OldView = Target->getView();

      Target->setView(MakeView(GlobalWidgetBounds.GlobalBounds));
      ObjectTarget->clear(sf::Color::Transparent);
      Target->draw(BGRect);

      ObjectTarget->setView(MakeView(GlobalWidgetBounds.GlobalBounds));
      RawObject->Render(ObjectTarget);
      ObjectTarget->setView(ObjectTarget->getDefaultView());
      ObjectTarget->display();
      Target->draw(ObjectSprite);
      Target->setView(OldView);
      //RawObject->Render(Target);
    }

    void ObjectView::Move(const sf::Vector2f & Delta)
    {
    }

    void ObjectView::SetAnimationSize(const sf::Vector2f & Size)
    {
      
    }

  }

}