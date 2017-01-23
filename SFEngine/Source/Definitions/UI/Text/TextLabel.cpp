#include "../../../Headers/UI/Text/TextLabel.h"

#include "../../../Headers/UI/WIdgetHelper.h"

namespace Engine
{

  namespace UI
  {

    std::shared_ptr<TextLabel> TextLabel::Create(std::shared_ptr<UILayer> ThisLayer, TextAlignment Align, const std::string & String, 
                                                             const sf::Color & Color, std::shared_ptr<sf::Font> _Font, unsigned int TextSize, const sf::FloatRect &RenderBounds, const sf::Vector2f &Position)
    {
      if (!ThisLayer || !ThisLayer->CanAcceptWidget()) 
        throw InvalidObjectException({ ExceptionCause::InvalidContainer, ExceptionCause::ConstructionError },
                                     EXCEPTION_MESSAGE("Given WidgetHelper is NULL or cannot accept a widget"));

      try
      {

        std::shared_ptr<TextLabel> Label(new TextLabel);

        Label->Alignment = Align;
        Label->Bounds = RenderBounds;
        Label->Font = _Font;
        Label->RawString = String;
        Label->RenderString.setFont(*_Font);
        Label->RenderString.setString(String);
        Label->RenderString.setCharacterSize(TextSize);
        Label->RenderString.setFillColor(Color);
        Label->TextPosition = Position;

        Label->RenderString.setPosition(Position);

        ThisLayer->RegisterWidget(Label);
        Label->MyLayer = ThisLayer;

        return Label;
      }
      catch (EngineRuntimeError &err)
      {
        err.AddCause(ExceptionCause::ConstructionError);
        err.AddMessage(EXCEPTION_MESSAGE("Could not construct TextLabel"));

        throw;
      }
    }

    std::shared_ptr<TextLabel> TextLabel::Create(std::shared_ptr<WidgetBase> Widget, TextAlignment Align, const std::string &String, const sf::Color &Color,
                                                 std::shared_ptr<sf::Font> _Font, unsigned int TextSize, const sf::FloatRect &RenderBounds, const sf::Vector2f &Offset)
    {
      if (!Widget)
        throw InvalidObjectException({ ExceptionCause::InvalidContainer, ExceptionCause::ConstructionError },
                                     EXCEPTION_MESSAGE("Widget is NULL"));

      try
      {
        std::shared_ptr<TextLabel> Label(new TextLabel);

        Label->Alignment = Align;
        Label->Font = _Font;
        Label->RawString = String;
        Label->RenderString.setFont(*_Font);
        Label->RenderString.setString(String);
        Label->RenderString.setCharacterSize(TextSize);
        Label->RenderString.setFillColor(Color);
        Label->Parent = Widget;

        //Need to align the text within the widget
        sf::Vector2f Pos = { Widget->GlobalWidgetBounds.GlobalBounds.left, Widget->GlobalWidgetBounds.GlobalBounds.top };
        Pos += Offset;

        Label->GlobalWidgetBounds.ForceRegion({ Pos.x, Pos.y, RenderBounds.width, RenderBounds.height });

        Label->Bounds = { Pos.x, Pos.y, RenderBounds.width, RenderBounds.height };

        Label->TextPosition = Pos;
        Label->RenderString.setPosition(Pos);
        Label->AlignText();

        Widget->AddTextLabel(Label);

        return Label;
      }
      catch (EngineRuntimeError &err)
      {
        err.AddCause(ExceptionCause::ConstructionError);
        err.AddMessage(EXCEPTION_MESSAGE("Could not construct TextLabel"));

        throw;
      }
    }

    TextLabel::~TextLabel()
    {

    }

    TextLabel::TextLabel()
    {

    }

    void TextLabel::AlignText()
    {
      sf::FloatRect ParentBounds = Parent->GlobalWidgetBounds.GlobalBounds;
      sf::FloatRect TextBounds = RenderString.getGlobalBounds();

      float MaxWidth = Parent->GlobalWidgetBounds.GlobalBounds.width;
      float DesiredWidth = TextBounds.width;
      float xDiff = MaxWidth - DesiredWidth;

      float MaxHeight = Parent->GlobalWidgetBounds.GlobalBounds.height;
      float DesiredHeight = Bounds.height;

      float yDiff = MaxHeight - DesiredHeight;

      TextPosition.x = ParentBounds.left + (xDiff / 2.f);
      TextPosition.y = ParentBounds.top + yDiff;

      RenderString.setPosition(TextPosition);
      
      sf::FloatRect NewBounds = { TextPosition.x, TextPosition.y, Bounds.width, Bounds.height };
      Bounds = NewBounds;
      GlobalWidgetBounds.ForceRegion(Bounds);
    }

    void TextLabel::TickUpdate(const double & Delta)
    {
    }

    void TextLabel::Render(std::shared_ptr<sf::RenderTexture>& Target)
    {
      auto View = MakeView(Bounds);

      Target->setView(View);
      Target->draw(RenderString);
      Target->setView(Target->getDefaultView());
    }

    void TextLabel::SetString(const std::string & String)
    {
    }

    std::string TextLabel::GetString() const
    {
      return std::string();
    }

    void TextLabel::SetStringColor(const sf::Color & Color)
    {
    }

    sf::Color TextLabel::GetStringColor() const
    {
      return sf::Color();
    }

    void TextLabel::SetTextSize(unsigned int Size)
    {
    }

    unsigned int TextLabel::GetTextSize() const
    {
      return 0;
    }

    void TextLabel::ConsumeEvent(const InputEvent & IEvent)
    {
    }

    void TextLabel::OnFocusGained(const FocusChangeEvent & FEvent)
    {
    }

    void TextLabel::OnFocusLost(const FocusChangeEvent & FEvent)
    {
    }

    void TextLabel::OnKeyPress(const InputEvent & IEvent)
    {
    }

    void TextLabel::OnKeyRelease(const InputEvent & IEvent)
    {
    }

    void TextLabel::OnMousePress(const InputEvent & IEvent)
    {
    }

    void TextLabel::OnMouseRelease(const InputEvent & IEvent)
    {
    }

    void TextLabel::OnMouseScroll(const InputEvent & IEvent)
    {
    }

    void TextLabel::OnMouseOver(const InputEvent & IEvent)
    {
    }

    void TextLabel::OnMouseLeave(const InputEvent & IEvent)
    {
    }

    void TextLabel::OnMouseMove(const InputEvent & IEvent)
    {
    }

    void TextLabel::OnDragBegin(const InputEvent & IEvent)
    {
    }

    void TextLabel::OnDragContinue(const InputEvent & IEvent)
    {
    }

    void TextLabel::OnDragEnd(const InputEvent & IEvent)
    {
    }

    void TextLabel::Move(const sf::Vector2f & Delta)
    {
      Bounds.left += Delta.x;
      Bounds.top += Delta.y;
      TextPosition += Delta;
      GlobalWidgetBounds.MoveRegion(Delta);

      AlignText();

      RenderString.setPosition(TextPosition);
    }

    void TextLabel::CreateHelper()
    {
    }

  }

}