#include "../../../Headers/UI/Input/TextInput.h"
#include "../../../Headers/UI/WIdgetHelper.h"
#include "../../../Headers/UI/Theme.h"

namespace Engine
{

  namespace UI
  {


    std::shared_ptr<TextInput> TextInput::Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper, const sf::Vector2f & Position, const sf::Vector2f & Size, std::shared_ptr<sf::Font> _Font, const std::string &DefaultText)
    {
      if (!ThisLayer.lock() || !ThisLayer.lock()->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer }, EXCEPTION_MESSAGE("Layer is NULL or cannot accept a widget"));

      if (!ThisHelper.lock() || !ThisHelper.lock()->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer }, EXCEPTION_MESSAGE("Helper is NULL or cannot accept a widget"));

      try
      {
        std::shared_ptr<TextInput> Input(new TextInput);

        assert(ThisLayer.lock() && ThisHelper.lock());

        Input->MyLayer = ThisLayer.lock();
        Input->Helper = ThisHelper.lock();

        ThisLayer.lock()->RegisterWidget(Input);

        assert(Input->MyLayer.lock() && Input->Helper.lock());

        Input->RenderString.setFillColor(DefaultDarkTheme.TextColorNormal);
        Input->RenderString.setCharacterSize(DefaultDarkTheme.TextSizeNormal);
        Input->RawString = DefaultText;
        Input->RenderString.setString(DefaultText);
        Input->Font = _Font;
        Input->RenderString.setFont(*_Font);

        Input->SetBGColorNormal(DefaultDarkTheme.ButtonColorNormal);
        Input->SetBGColor(DefaultDarkTheme.ButtonColorNormal);
        Input->SetBGPosition(Position);
        Input->BGColor = DefaultDarkTheme.ButtonColorNormal;
        Input->BGColorHighlighted = DefaultDarkTheme.ButtonColorHighlighted;
        Input->BGColorPressed = DefaultDarkTheme.ButtonColorPressed;
        Input-> BGColorNormal = DefaultDarkTheme.ButtonColorNormal;
        Input->BGColorHighlighted = DefaultDarkTheme.ButtonColorHighlighted;
        Input->BGColorPressed = DefaultDarkTheme.ButtonColorPressed;
        Input->BGRect.setFillColor(DefaultDarkTheme.ButtonColorNormal);
        Input->SetBGSize(Size);
        Input->RenderString.setPosition(Position);
        Input->Position = Position;
        Input->Size = Size;
        std::shared_ptr<ColoredQuad> Quad(new ColoredQuad(Position, Size));
        Input->GlobalWidgetBounds.ForceRegion({ Position, Size });
        Input->Drawables.push_back(Quad);

        sf::FloatRect Bounds{ Position, Size };
        sf::FloatRect Padded = { Position.x + DefaultDarkTheme.TextInputPadding, Position.y + DefaultDarkTheme.TextInputPadding, Size.x - (DefaultDarkTheme.TextInputPadding * 2), Size.y - (DefaultDarkTheme.TextInputPadding * 2) };

        Input->GlobalWidgetBounds.ForceRegion(Bounds);
        Input->PaddedBounds = Padded;

        float SizeOfAGlyph = _Font->getGlyph(0x0041, DefaultDarkTheme.TextSizeLarge, false).bounds.height;
        float yDiff = Bounds.height - SizeOfAGlyph;
        Input->AlignedYPos = Position.y + (yDiff / 2.f);

        Input->BoundsRect.setPosition({ Bounds.left, Bounds.top });
        Input->BoundsRect.setSize({ Bounds.width, Bounds.height });
        Input->BoundsRect.setFillColor(sf::Color::Transparent);
        Input->BoundsRect.setOutlineColor(sf::Color::Red);
        Input->BoundsRect.setOutlineThickness(-1);

        Input->RenderString.setPosition({ Padded.left, Input->AlignedYPos });

        return Input;
      }
      catch (EngineRuntimeError &err)
      {
        throw;
      }

    }

    void TextInput::AlignText()
    {
      auto Bounds = RenderString.getGlobalBounds();
      float PaddedLeft = PaddedBounds.left;
      float PaddedRight = PaddedLeft + PaddedBounds.width;

      float TextLeft = Bounds.left;
      float TextRight = TextLeft + Bounds.width;
      float yDiff = Size.y - Bounds.height;
      float left = Position.x;
      float top = Position.y;

      if (TextRight < PaddedRight && TextLeft >= PaddedLeft) {
        //just align it with the padded left side
        left = PaddedLeft;
        top = Position.y + (yDiff / 2.f);
        RenderString.setPosition({ left, top });
      }
      else if (TextRight >= PaddedRight) {
        //we are sticking out over the right side
        float delta = TextRight - PaddedRight;
        RenderString.move({ -delta, 0 });
      }
      else if (TextLeft <= PaddedLeft && TextRight <= PaddedRight) {
        //we made room by deleting a character, now we need to scoot over
        float delta = PaddedRight - TextRight;
        RenderString.move({ delta, 0 });
      }
      else {
        RenderString.setPosition({ PaddedLeft, AlignedYPos });
      }

      //AlignY
      float posY = Position.y + (yDiff / 2.f);
      auto pos = RenderString.getPosition();

      RenderString.setPosition({ pos.x, AlignedYPos });
    }

    void TextInput::ConsumeEvent(const InputEvent & IEvent)
    {
      if (IEvent.TextWasEntered) {
        OnTextEntered(IEvent);
      }
    }

    void TextInput::OnFocusGained(const FocusChangeEvent & FEvent)
    {
      ClickButtonBase::OnFocusGained(FEvent);

      SetKeyRepeatEnabled(true);
    }

    void TextInput::OnFocusLost(const FocusChangeEvent & FEvent)
    {
      ClickButtonBase::OnFocusLost(FEvent);

      SetKeyRepeatEnabled(false);
    }

    void TextInput::OnKeyPress(const InputEvent & IEvent)
    {
    }

    void TextInput::OnKeyRelease(const InputEvent & IEvent)
    {
    }

    void TextInput::OnMousePress(const InputEvent & IEvent)
    {
      ClickButtonBase::OnMousePress(IEvent);
    }

    void TextInput::OnMouseRelease(const InputEvent & IEvent)
    {
      ClickButtonBase::OnMouseRelease(IEvent);

      Helper.lock()->TakeFocus(SelfWeakPtr);
    }

    void TextInput::OnMouseScroll(const InputEvent & IEvent)
    {
    }

    void TextInput::OnMouseOver(const InputEvent & IEvent)
    {
      ClickButtonBase::OnMouseOver(IEvent);
    }

    void TextInput::OnMouseLeave(const InputEvent & IEvent)
    {
      ClickButtonBase::OnMouseLeave(IEvent);
    }

    void TextInput::OnMouseMove(const InputEvent & IEvent)
    {
    }

    void TextInput::OnDragBegin(const InputEvent & IEvent)
    {
    }

    void TextInput::OnDragEnd(const InputEvent & IEvent)
    {
    }

    void TextInput::OnDragContinue(const InputEvent & IEvent)
    {
    }

    void TextInput::TickUpdate(const double & delta)
    {
    }

    void TextInput::Render(std::shared_ptr<sf::RenderTexture> Texture)
    {
      Texture->draw(BGRect);

      auto view = MakeView(PaddedBounds);
      auto oldview = Texture->getView();
      
      Texture->setView(view);
      Texture->draw(RenderString);

      Texture->setView(oldview);

      Texture->draw(BoundsRect);
    }

    void TextInput::Move(const sf::Vector2f & Delta)
    {
      ClickButtonBase::Move(Delta);
    }

    void TextInput::Resize(const sf::Vector2f & Size)
    {
    }

    void TextInput::ResetAppearance()
    {
    }

    void TextInput::OnTextEntered(const InputEvent & IEvent)
    {
      if (IsPrintable(IEvent.TextUnicode)) {
        RawString += static_cast<char>(IEvent.TextUnicode);
        RenderString.setString(RawString);
        AlignText();
      }
      else {
        if (IsBackspace(IEvent.TextUnicode) && RawString.length() > 0 ) { 
          RawString.erase(RawString.end() - 1);
          RenderString.setString(RawString);
          AlignText();
        }
      }
    }

    void TextInput::SetTexture(std::shared_ptr<sf::Texture> Texture)
    {
    }

    void TextInput::SetTextureRect(sf::IntRect & Rect)
    {
    }

    void TextInput::SetBGColorNormal(const sf::Color & Color)
    {
    }

    void TextInput::SetBGColorHighlighted(const sf::Color & Color)
    {
    }

    void TextInput::SetBGColorPressed(const sf::Color & Color)
    {
    }

    void TextInput::SetBGColor(const sf::Color & Color)
    {
    }

    TextInput::TextInput()
    {
    }

  }

}
