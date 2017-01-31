#include "../../../Headers/UI/Input/NumericComboBox.h"

namespace Engine
{

  namespace UI
  {

    std::shared_ptr<NumericComboBox> NumericComboBox::Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper,
                                            const sf::Vector2f & Position, const sf::Vector2f & TextAreaSize, const sf::Vector2f & ButtonsSize, const int &Delta, const int &InitialValue,
                                            std::shared_ptr<sf::Font> _Font, std::shared_ptr<sf::Texture> IconTexture)
    {
      if (!ThisLayer.lock() || !ThisLayer.lock()->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer }, EXCEPTION_MESSAGE("Layer is NULL or cannot accept a widget"));

      if (!ThisHelper.lock() || !ThisHelper.lock()->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer }, EXCEPTION_MESSAGE("Helper is NULL or cannot accept a widget"));

      try
      {
        assert(ThisLayer.lock() && ThisHelper.lock());

        std::shared_ptr<NumericComboBox> Box(new NumericComboBox);

        Box->Helper = ThisHelper.lock();
        Box->MyLayer = ThisLayer.lock();
        ThisLayer.lock()->RegisterWidget(Box);

        Box->Font = _Font;
        Box->ChildHelper = WidgetHelper::Create();
        Box->ChildLayer = UILayer::Create(Box->ChildHelper);
        Box->ValueDelta = Delta;
        Box->CurrentValue = InitialValue;
        Box->ValueText->SetString(std::to_string(InitialValue));

        //Create the text label
        Box->ValueText = TextLabel::Create(Box, Box->ChildHelper, TextAlignment::CenterJustified, std::to_string(InitialValue), DefaultDarkTheme.TextColorNormal, _Font, DefaultDarkTheme.TextSizeMedium, { 0,0,1200,900 }, { 0,0 });

        //Create our bounds
        sf::FloatRect TextRegion = { Position.x, Position.y, TextAreaSize.x, TextAreaSize.y };
        sf::FloatRect ButtonsRegion = { TextRegion.left + TextRegion.width, TextRegion.top, ButtonsSize.x, ButtonsSize.y };
        sf::FloatRect TotalRegion = { TextRegion.left, TextRegion.top, TextRegion.width + ButtonsRegion.width, std::max(TextRegion.height, ButtonsRegion.height) };

        Box->ValueText->MoveTo(TextRegion);
        Box->SetBGColorNormal(DefaultDarkTheme.TextInputBackgroundColor);

        Box->UpButton = ClickButtonBase::Create(Box->ChildLayer, Box->ChildHelper, { Position.x + TextAreaSize.x, Position.y }, { ButtonsSize.x, ButtonsSize.y / 2.f });
        Box->DownButton = ClickButtonBase::Create(Box->ChildLayer, Box->ChildHelper, { Position.x + TextAreaSize.x, Position.y + (ButtonsSize.y / 2.f) }, { ButtonsSize.x, ButtonsSize.y / 2.f });
        Box->UpButton->MouseReleaseCB = [Box]() { Box->OnUpButtonReleased(); };
        Box->DownButton->MouseReleaseCB = [Box]() { Box->OnDownButtonReleased(); };
        Box->UpButton->MousePressCB = [Box]() {Box->OnUpButtonPressed(); };
        Box->DownButton->MousePressCB = [Box]() {Box->OnDownButtonPressed(); };

        Box->UpButton->SetTexture(IconTexture);
        Box->UpButton->SetTextureRect(IconSheetRects["uparrow_medium"]);
        Box->UpButton->SetBGColorNormal(DefaultDarkTheme.ButtonColorNormal);
        Box->UpButton->SetBGColorHighlighted(DefaultDarkTheme.ButtonColorHighlighted);

        Box->DownButton->SetTexture(IconTexture);
        Box->DownButton->SetTextureRect(IconSheetRects["downarrow_medium"]);
        Box->DownButton->SetBGColorNormal(DefaultDarkTheme.ButtonColorNormal);
        Box->DownButton->SetBGColorHighlighted(DefaultDarkTheme.ButtonColorHighlighted);

        Box->SetBGColorNormal(DefaultDarkTheme.TextInputBackgroundColor);
        Box->SetBGColorHighlighted(DefaultDarkTheme.TextInputBackgroundColor);
        Box->SetBGColorPressed(DefaultDarkTheme.TextInputBackgroundColor);
        Box->SetBGOutlineColor(DefaultDarkTheme.ButtonOutlineColorNormal);
        Box->SetBGOutlineColorHighlighted(DefaultDarkTheme.ButtonOutlineColorHighlighted);
        Box->SetBGPosition(Position);
        Box->SetBGSize({ TextAreaSize.x + ButtonsSize.x, TextAreaSize.y });

        return Box;
      }
      catch (EngineRuntimeError &err)
      {
        throw;
      }
    }

    void NumericComboBox::OnUpButtonPressed()
    {
    }

    void NumericComboBox::OnDownButtonPressed()
    {
    }

    void NumericComboBox::OnUpButtonReleased()
    {
    }

    void NumericComboBox::OnDownButtonReleased()
    {
    }

    void NumericComboBox::ConsumeEvent(const InputEvent & IEvent)
    {
      ChildHelper->ConsumeEvent(IEvent);
    }

    void NumericComboBox::OnFocusGained(const FocusChangeEvent & FEvent)
    {
    }

    void NumericComboBox::OnFocusLost(const FocusChangeEvent & FEvent)
    {
    }

    void NumericComboBox::OnKeyPress(const InputEvent & IEvent)
    {
    }

    void NumericComboBox::OnKeyRelease(const InputEvent & IEvent)
    {
    }

    void NumericComboBox::OnMousePress(const InputEvent & IEvent)
    {
    }

    void NumericComboBox::OnMouseRelease(const InputEvent & IEvent)
    {
    }

    void NumericComboBox::OnMouseScroll(const InputEvent & IEvent)
    {
    }

    void NumericComboBox::OnMouseOver(const InputEvent & IEvent)
    {
    }

    void NumericComboBox::OnMouseLeave(const InputEvent & IEvent)
    {
    }

    void NumericComboBox::OnMouseMove(const InputEvent & IEvent)
    {
    }

    void NumericComboBox::OnDragBegin(const InputEvent & IEvent)
    {
    }

    void NumericComboBox::OnDragContinue(const InputEvent & IEvent)
    {
    }

    void NumericComboBox::OnDragEnd(const InputEvent & IEvent)
    {
    }

  }

}