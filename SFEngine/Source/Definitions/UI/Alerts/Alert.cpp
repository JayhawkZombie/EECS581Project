#include "../../../Headers/UI/Alerts/Alert.h"

#include "../../../Headers/UI/Buttons/ClickButtonBase.h"
#include "../../../Headers/UI/Text/TextLabel.h"
#include "../../../Headers/UI/WIdgetHelper.h"


namespace Engine
{

  namespace UI
  {

    std::shared_ptr<Alert> Alert::Create(std::shared_ptr<WidgetHelper> Helper, std::shared_ptr<UILayer> Layer, const std::string &Message, std::shared_ptr<sf::Font> Font, const sf::Vector2f &Position)
    {
      if (!Helper || !Helper->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer },
                                     EXCEPTION_MESSAGE("Helper is NULL or cannot accept a widget"));

      if (!Layer || !Layer->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer },
                                     EXCEPTION_MESSAGE("Layer is NULL or cannot accept a widget"));


      try
      {
        std::shared_ptr<Alert> AL(new Alert);

        AL->Helper = Helper;
        AL->ChildHelper = WidgetHelper::Create();
        AL->ChildLayer = UILayer::Create(AL->Helper);

        AL->BGRect.setPosition(Position);

        AL->CanBeDragged = false;
        AL->Position = Position;
        
        AL->Font = Font;
        AL->AlertMessage.setFont(*(AL->Font));
        AL->AlertMessage.setString(Message);

        auto Rect = AL->AlertMessage.getGlobalBounds();
        
        
      }
      catch (EngineRuntimeError &err)
      {
        err.AddCause(ExceptionCause::ConstructionError);
        err.AddMessage(EXCEPTION_MESSAGE("Failed to create Alert"));

        throw;
      }

    }

    void Alert::ConsumeEvent(const InputEvent & IEvent)
    {
    }

    void Alert::OnFocusGained(const FocusChangeEvent & FEvent)
    {
    }

    void Alert::OnFocusLost(const FocusChangeEvent & FEvent)
    {
    }

    void Alert::OnKeyPress(const InputEvent & IEvent)
    {
    }

    void Alert::OnKeyRelease(const InputEvent & IEvent)
    {
    }

    void Alert::OnMousePress(const InputEvent & IEvent)
    {
    }

    void Alert::OnMouseRelease(const InputEvent & IEvent)
    {
    }

    void Alert::OnMouseScroll(const InputEvent & IEvent)
    {
    }

    void Alert::OnMouseOver(const InputEvent & IEvent)
    {
    }

    void Alert::OnMouseLeave(const InputEvent & IEvent)
    {
    }

    void Alert::OnMouseMove(const InputEvent & IEvent)
    {
    }

    void Alert::OnDragBegin(const InputEvent & IEvent)
    {
    }

    void Alert::OnDragEnd(const InputEvent & IEvent)
    {
    }

    void Alert::OnDragContinue(const InputEvent & IEvent)
    {
    }

    void Alert::TickUpdate(const double & delta)
    {
    }

    void Alert::Render(std::shared_ptr<sf::RenderTexture>& Texture)
    {
    }

    void Alert::Move(const sf::Vector2f & Delta)
    {
    }

    void Alert::ShowAlert(std::shared_ptr<Alert> Message)
    {
    }

    void Alert::HideAlert(std::shared_ptr<Alert> Message)
    {
    }

    Alert::~Alert()
    {
    }

    Alert::Alert()
    {
    }

    void Alert::OnAcknowledged()
    {
    }

  }

}
