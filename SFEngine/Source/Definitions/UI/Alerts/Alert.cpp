#include "../../../Headers/UI/Alerts/Alert.h"

#include "../../../Headers/UI/Buttons/ClickButtonBase.h"
#include "../../../Headers/UI/Text/TextLabel.h"
#include "../../../Headers/UI/WIdgetHelper.h"


namespace Engine
{

  namespace UI
  {

    std::shared_ptr<Alert> Alert::Create(std::weak_ptr<UILayer> Layer, std::weak_ptr<WidgetHelper> Helper, const std::string &Message, std::shared_ptr<sf::Font> Font,
                                         const sf::Vector2f &Position, const sf::Vector2f &Size, const sf::Vector2f &OKButtonSize)
    {
      if (!Helper.lock() || !Helper.lock()->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer },
                                     EXCEPTION_MESSAGE("Helper is NULL or cannot accept a widget"));

      if (!Layer.lock() || !Layer.lock()->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer },
                                     EXCEPTION_MESSAGE("Layer is NULL or cannot accept a widget"));


      try
      {
        std::shared_ptr<Alert> AL(new Alert);

        AL->Helper = Helper.lock();
        AL->ChildHelper = WidgetHelper::Create();
        AL->ChildLayer = UILayer::Create(AL->Helper.lock());
        AL->MyLayer = Layer.lock();

        assert(AL->MyLayer.lock() && AL->Helper.lock());
        try
        {
          AL->SetUpWidget();
        }
        catch (EngineRuntimeError &err)
        {
          err.AddCause(ExceptionCause::InitializationError);
          err.AddMessage(EXCEPTION_MESSAGE("Alert failed SetUp()"));

          throw;
        }


        AL->BGRect.setPosition(Position);

        AL->CanBeDragged = false;
        AL->Position = Position;

        AL->Font = Font;
        AL->AlertMessage = std::make_shared<sf::Text>();
        AL->AlertMessage->setFont(*(AL->Font));
        AL->AlertMessage->setString("SampleAlert!");
        AL->AlertMessage->setCharacterSize(14);

        sf::FloatRect AlertTextRegion = AL->AlertMessage->getGlobalBounds();
        AL->AcknowledgeButton = UI::ClickButtonBase::Create(AL->ChildLayer, AL->ChildHelper, {Position.x + (Size.x - OKButtonSize.x)/2.f, Position.y + PaddingTop + AlertTextRegion.height + PaddingBottom}, OKButtonSize, nullptr);
        AL->AcknowledgeButton->SetBGColor(sf::Color(38, 38, 38));
        AL->OKText = UI::TextLabel::Create(AL->AcknowledgeButton, AL->ChildHelper, TextAlignment::CenterJustified, "OK", sf::Color::White, Font, 14, { 0,0,0,0 }, { 0,0 });

        sf::FloatRect OKTextRegion = AL->OKText->GetTextGlobalBounds();

        sf::FloatRect TrueRegion =
        {
          Position.x, Position.y,
          PaddingLeft + AlertTextRegion.width + PaddingRight,
          PaddingTop + AlertTextRegion.height + PaddingBottom + OKTextRegion.height + PaddingButtonBottom
        };

        sf::Vector2f OKButtonSize = { OKTextRegion.width + 20.f, OKTextRegion.height + 20.f };
        sf::Vector2f AlertPosition = { PaddingLeft, PaddingTop };
        sf::Vector2f OKPosition =
        {
          (AlertTextRegion.width - OKButtonSize.x),
          PaddingTop + AlertTextRegion.height + PaddingBottom
        };

        AL->BGRect.setPosition(Position);
        AL->BGRect.setSize(Size);
        AL->BGRect.setFillColor(sf::Color(66, 66, 66));
        //Center the text on the screen
        float xDiffLeft = (Size.x - AlertTextRegion.width) / 2.f;

        AL->AlertMessage->setPosition({ xDiffLeft, Position.y + PaddingTop });

        //Close the popup when the user releases the mouse on it
        AL->AcknowledgeButton->MouseReleaseCB =
          [ AL ]()
        {
          AL->OnAcknowledged();
          AL->CloseWasPressed();
          UI::Alert::ClosePopup(AL);
        };

        return AL;
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
      ChildLayer->HandleEvent(IEvent);
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

    void Alert::Render(std::shared_ptr<sf::RenderTexture> Texture)
    {
      Texture->draw(BGRect);

      Texture->draw(*AlertMessage);
      AlertText->Render(Texture);

      AcknowledgeButton->Render(Texture);
    }

    void Alert::Move(const sf::Vector2f & Delta)
    {
    }

    void Alert::ShowAlert(std::shared_ptr<Alert> Message)
    {
      DEBUG_ONLY std::cerr << "Popup ID : " << Message->WidgetID << " Showing" << std::endl;
      Message->IsOnAlert = true;
      Message->Helper.lock()->TakeFocus(Message);
    }

    void Alert::HideAlert(std::shared_ptr<Alert> Message)
    {
      DEBUG_ONLY std::cerr << "Popup ID : " << Message->WidgetID << " Hiding" << std::endl;
      Message->IsOnAlert = false;
      Message->Helper.lock()->ReleaseTopFocus();
    }

    Alert::~Alert()
    {
    }

    Alert::Alert()
    {
    }

    void Alert::OnAcknowledged()
    {
      DEBUG_ONLY std::cerr << "ACKNOWLEDGED ALERT" << std::endl;
    }

  }

}
