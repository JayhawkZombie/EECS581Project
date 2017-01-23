#include "../../../Headers/UI/Buttons/ButtonBase.h"
#include "../../../Headers/UI/WIdgetHelper.h"


namespace Engine
{

  namespace UI
  {

    ButtonBase::ButtonBase()
      : WidgetBase()
    {
      
    }

    std::shared_ptr<ButtonBase> ButtonBase::Create(std::shared_ptr<UILayer> ThisLayer)
    {
      if (!ThisLayer || !ThisLayer->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer, ExceptionCause::ConstructionError }, EXCEPTION_MESSAGE("Created WidgetHelper is invalid or cannot accept any widgets"));


      //Create button
      std::shared_ptr<ButtonBase> Widget(new ButtonBase());

      Widget->MyLayer = ThisLayer;

      ThisLayer->RegisterWidget(Widget);

      return Widget;
    }

    void ButtonBase::Move(const sf::Vector2f &Delta)
    {
      
    }

    void ButtonBase::ConsumeEvent(const InputEvent &event)
    {
      WidgetBase::ConsumeEvent(event);
    }

    void ButtonBase::OnFocusGained(const FocusChangeEvent &event)
    {
      WidgetBase::OnFocusGained(event);
    }

    void ButtonBase::OnFocusLost(const FocusChangeEvent &event)
    {
      WidgetBase::OnFocusLost(event);
    }

    void ButtonBase::OnKeyPress(const InputEvent &event)
    {
      WidgetBase::OnKeyPress(event);
    }

    void ButtonBase::OnKeyRelease(const InputEvent &event)
    {
      WidgetBase::OnKeyRelease(event);
    }

    void ButtonBase::OnMousePress(const InputEvent &event)
    {
      WidgetBase::OnMousePress(event);
    }

    void ButtonBase::OnMouseRelease(const InputEvent &event)
    {
      WidgetBase::OnMouseRelease(event);
    }

    void ButtonBase::OnMouseScroll(const InputEvent &event)
    {
      WidgetBase::OnMouseScroll(event);
    }

    void ButtonBase::OnMouseOver(const InputEvent &event)
    {
      WidgetBase::OnMouseOver(event);
    }

    void ButtonBase::OnMouseLeave(const InputEvent &event)
    {
      WidgetBase::OnMouseLeave(event);
    }

    void ButtonBase::OnMouseMove(const InputEvent &event)
    {
      WidgetBase::OnMouseMove(event);
    }

    void ButtonBase::OnDragBegin(const InputEvent &event)
    {
      WidgetBase::OnDragBegin(event);
    }

    void ButtonBase::OnDragContinue(const InputEvent &IEvent)
    {
      WidgetBase::OnDragContinue(IEvent);

    }//OnDragContinue

    void ButtonBase::OnDragEnd(const InputEvent &event)
    {
      WidgetBase::OnDragEnd(event);
    }

    void ButtonBase::TickUpdate(const double &delta)
    {
      WidgetBase::TickUpdate(delta);
    }

    void ButtonBase::Render(std::shared_ptr<sf::RenderTexture> &Texture)
    {
      WidgetBase::Render(Texture);
    }

  }

}
