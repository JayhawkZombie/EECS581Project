#include "../../../Headers/UI/Alerts/PopupObject.h"
#include "../../../Headers/UI/Buttons/ClickButtonBase.h"
#include "../../../Headers/UI/WIdgetHelper.h"
#include "../../../Headers/UI/Text/TextLabel.h"

namespace Engine
{

  namespace UI
  {

    std::shared_ptr<PopupObject> PopupObject::Create(std::shared_ptr<UILayer> ThisLayer, std::shared_ptr<WidgetHelper> Helper, const sf::Vector2f &Position, const sf::Vector2f &Size, std::shared_ptr<sf::Font> _Font)
    {
      if (!Helper || !Helper->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer },
                                     EXCEPTION_MESSAGE("Helper is NULL or cannot accept a widget"));

      try
      {
        std::shared_ptr<PopupObject> Popup(new PopupObject);

        Popup->Position = Position;
        Popup->Size = Size;

        Popup->CanBeDragged = false;
        Popup->Font = _Font;
        Popup->Helper = Helper;
        Popup->ChildHelper = WidgetHelper::Create();
        Popup->ChildLayer = UILayer::Create(Popup->ChildHelper);
        Popup->MyLayer = ThisLayer;

        //Normally, we would register this object, but here we aren't going to until we actually steal focus from the helper
        //The UIHelper/Layer normallt does this for us
        try {
          Popup->SetUpWidget();
        }
        catch (EngineRuntimeError &err) {
          err.AddCause(ExceptionCause::InitializationError);
          err.AddMessage(EXCEPTION_MESSAGE("Popup failed SetUpWidget()"));

          DEBUG_ONLY std::cerr << "Popul failed SetUpWidget()" << std::endl;
          throw;
        }

        Popup->BGRect.setFillColor(sf::Color(96, 96, 96, 100));
        Popup->BGRect.setPosition({ 100, 100 });
        Popup->BGRect.setSize({ 900, 700 });

        //Popup->OKButton = ClickButtonBase::Create(Popup->ChildLayer, Popup->ChildHelper, Position + sf::Vector2f(100, 0), { 100, 35 });
        //Popup->CancelButton = ClickButtonBase::Create(Popup->ChildLayer, Popup->ChildHelper, Position + sf::Vector2f(300, 0), { 100, 35 });

        //Popup->OKLabel = TextLabel::Create(Popup->OKButton, Popup->ChildHelper, TextAlignment::CenterJustified, "OK", sf::Color::White, _Font, 14, { Position, Size }, { 0, 0 });
        //Popup->CancelLabel = TextLabel::Create(Popup->CancelButton, Popup->ChildHelper, TextAlignment::CenterJustified, "Cancel", sf::Color::White, _Font, 14, { Position, Size }, { 0, 0 });

        Popup->SampleText.setFont(*(Popup->Font));
        Popup->SampleText.setString("Sample Popup String");
        Popup->SampleText.setFillColor(sf::Color::Yellow);
        Popup->SampleText.setCharacterSize(24);
        Popup->SampleText.setPosition({ 200, 200 });

        //Popup->OKButton->MouseReleaseCB = 
        //  [Popup]()
        //{
        //  Popup->CloseWasPressed();
        //  UI::PopupObject::ClosePopup(Popup);
        //};

        //Popup->CancelButton->MouseReleaseCB = 
        //  [Popup]()
        //{
        //  Popup->CloseWasPressed();
        //  UI::PopupObject::ClosePopup(Popup);
        //};

        return Popup;
      }
      catch (EngineRuntimeError &err)
      {
        err.AddCause({ ExceptionCause::ConstructionError });
        err.AddMessage(EXCEPTION_MESSAGE("Could not construct popup"));

        throw;
      }
    }

    void PopupObject::ConsumeEvent(const InputEvent & IEvent)
    {
      ChildLayer->HandleEvent(IEvent);
    }

    void PopupObject::OnFocusGained(const FocusChangeEvent & FEvent)
    {
    }

    void PopupObject::OnFocusLost(const FocusChangeEvent & FEvent)
    {
    }

    void PopupObject::OnKeyPress(const InputEvent & IEvent)
    {
    }

    void PopupObject::OnKeyRelease(const InputEvent & IEvent)
    {
    }

    void PopupObject::OnMousePress(const InputEvent & IEvent)
    {
    }

    void PopupObject::OnMouseRelease(const InputEvent & IEvent)
    {
    }

    void PopupObject::OnMouseScroll(const InputEvent & IEvent)
    {
    }

    void PopupObject::OnMouseOver(const InputEvent & IEvent)
    {
    }

    void PopupObject::OnMouseLeave(const InputEvent & IEvent)
    {
    }

    void PopupObject::OnMouseMove(const InputEvent & IEvent)
    {
    }

    void PopupObject::OnDragBegin(const InputEvent & IEvent)
    {
    }

    void PopupObject::OnDragEnd(const InputEvent & IEvent)
    {
    }

    void PopupObject::OnDragContinue(const InputEvent & IEvent)
    {
    }

    void PopupObject::TickUpdate(const double & delta)
    {
    }

    void PopupObject::Render(std::shared_ptr<sf::RenderTexture>& Texture)
    {
      Texture->draw(BGRect);
      Texture->draw(SampleText);

      //OKLabel->Render(Texture);
      //CancelLabel->Render(Texture);

      ChildLayer->Render(Texture);
    }

    void PopupObject::Move(const sf::Vector2f & Delta)
    {
    }

    void PopupObject::ShowPopup(std::shared_ptr<PopupObject> Popup)
    {
      DEBUG_ONLY std::cerr << "Popup ID : " << Popup->WidgetID << " Showing" << std::endl;
      Popup->IsOnAlert = true;
      Popup->Helper->TakeFocus(Popup);
    }

    void PopupObject::ClosePopup(std::shared_ptr<PopupObject> Popup)
    {
      DEBUG_ONLY std::cerr << "Popup ID : " << Popup->WidgetID << " Closing" << std::endl;
      Popup->IsOnAlert = false;
      Popup->Helper->ReleaseFocus(Popup);
    }

    PopupObject::PopupObject()
    {
    }

    PopupObject::~PopupObject()
    {
    }

    void PopupObject::CloseWasPressed()
    {
      DEBUG_ONLY std::cerr << "PopupObject : CloseWasPressed on " << WidgetID << std::endl;
      IsOnAlert = false;
    }

  }

}