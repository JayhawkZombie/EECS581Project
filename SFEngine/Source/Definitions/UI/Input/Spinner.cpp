#include "../../../Headers/UI/Input/Spinner.h"
#include "../../../Headers/UI/Input/TextInput.h"
#include "../../../Headers/UI/WIdgetHelper.h"
#include "../../../Headers/UI/Theme.h"
#include "../../../Headers/UI/UIIconSheet.h"

namespace Engine
{

  namespace UI
  {



    std::shared_ptr<IntSpinner> IntSpinner::Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper, const sf::Vector2f & Position, 
                                                   const sf::Vector2f & TextSize, std::shared_ptr<sf::Font> _Font, std::shared_ptr<sf::Texture> IconTexture)
    {
      if (!ThisLayer.lock() || !ThisLayer.lock()->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer }, EXCEPTION_MESSAGE("Layer is NULL or cannot accept a widget"));

      if (!ThisHelper.lock() || !ThisHelper.lock()->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer }, EXCEPTION_MESSAGE("Helper is NULL or cannot accept a widget"));

      try
      {
        std::shared_ptr<IntSpinner> Spinner(new IntSpinner);
        
        Spinner->MyLayer = ThisLayer.lock();
        Spinner->Helper = ThisHelper.lock();
        assert(Spinner->MyLayer.lock() && Spinner->Helper.lock());

        ThisLayer.lock()->RegisterWidget(Spinner);
        Spinner->ChildHelper = WidgetHelper::Create();
        Spinner->ChildLayer = UILayer::Create(Spinner->ChildHelper);

        Spinner->InputArea = TextInput::Create(Spinner->ChildLayer, Spinner->ChildHelper, Position, TextSize, _Font, "0");
        Spinner->UpButton = ClickButtonBase::Create(Spinner->ChildLayer, Spinner->ChildHelper, { Position.x + TextSize.x, Position.y }, { (TextSize.y), (TextSize.y / 2.f) }, nullptr);
        Spinner->DownButton = ClickButtonBase::Create(Spinner->ChildLayer, Spinner->ChildHelper, { Position.x + TextSize.x, Position.y + (TextSize.y / 2.f)}, { (TextSize.y), (TextSize.y / 2.f) }, nullptr);
        Spinner->BGColor = DefaultDarkTheme.ButtonColorNormal;        Spinner->BGColorPressed = DefaultDarkTheme.ButtonColorPressed;

        Spinner->BGColorNormal = DefaultDarkTheme.ButtonColorNormal;
        Spinner->BGColorHighlighted = DefaultDarkTheme.ButtonColorHighlighted;

        Spinner->UpButton->SetTexture(IconTexture);
        Spinner->UpButton->SetTextureRect(IconSheetRects["uparrow_medium"]);

        Spinner->DownButton->SetTexture(IconTexture);
        Spinner->DownButton->SetTextureRect(IconSheetRects["downarrow_medium"]);
        Spinner->GlobalWidgetBounds.ForceRegion({ Position.x, Position.y, TextSize.x + 20, TextSize.y });
        Spinner->UpButton->MouseOverCB = 
          [Spinner]()
        {
          std::cerr << "SpinnerUp Moused Over" << std::endl;
        };

        Spinner->UpButton->MouseReleaseCB =
          [Spinner]()
        {
          Spinner->ChangeData(1);
        };
        Spinner->DownButton->MouseReleaseCB =
          [Spinner]()
        {
          Spinner->ChangeData(-1);
        };

        Spinner->InputArea->TextEnteredCB =
          [Spinner]()
        {
          Spinner->ValueChanged(Spinner->InputArea->GetString());
        };

        return Spinner;
      }
      catch (EngineRuntimeError &err)
      {
        throw;
      }
    }

    void IntSpinner::ConsumeEvent(const InputEvent & IEvent)
    {
      if (ChildLayer->HandleEvent(IEvent)) {

      }
      //ChildHelper->ConsumeEvent(IEvent);
    }

    void IntSpinner::OnFocusGained(const FocusChangeEvent & FEvent)
    {
      WidgetBase::OnFocusGained(FEvent);
    }

    void IntSpinner::OnFocusLost(const FocusChangeEvent & FEvent)
    {
      WidgetBase::OnFocusLost(FEvent);
    }

    void IntSpinner::OnKeyPress(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void IntSpinner::OnKeyRelease(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void IntSpinner::OnMousePress(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void IntSpinner::OnMouseRelease(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void IntSpinner::OnMouseScroll(const InputEvent & IEvent)
    {
    }

    void IntSpinner::OnMouseOver(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void IntSpinner::OnMouseLeave(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void IntSpinner::OnMouseMove(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void IntSpinner::OnDragBegin(const InputEvent & IEvent)
    {
    }

    void IntSpinner::OnDragEnd(const InputEvent & IEvent)
    {
    }

    void IntSpinner::OnDragContinue(const InputEvent & IEvent)
    {
    }

    void IntSpinner::TickUpdate(const double & delta)
    {
      ChildHelper->TickUpdate(delta);
    }

    void IntSpinner::Render(std::shared_ptr<sf::RenderTexture> Texture)
    {
      ChildLayer->Render(Texture);
    }

    void IntSpinner::Move(const sf::Vector2f & Delta)
    {
    }

    void IntSpinner::Resize(const sf::Vector2f & Size)
    {
    }

    void IntSpinner::ResetAppearance()
    {
    }

    void IntSpinner::ChangeData(std::int32_t delta)
    {
      Data += delta;
      InputArea->SetString(std::to_string(Data));
      std::cerr << "Changed data to : " << Data << std::endl;
    }

    void IntSpinner::ValueChanged(const std::string & data)
    {
      if (data.find_first_not_of("-0123456789") != std::string::npos) {
        //invalid data
        //Mark it as invalid, change the text to RED
        InputArea->SetTextColor(sf::Color::Red);
      }
      else if (data.length() > 0) {
        InputArea->SetTextColor(DefaultDarkTheme.TextColorNormal);
        Data = std::stol(data);
        std::cerr << "Data : " << Data << std::endl;
      }
    }

  }

}
