#include "../../../Headers/UI/Text/TextLabel.h"

#include "../../../Headers/UI/WIdgetHelper.h"

namespace Engine
{

  namespace UI
  {

    std::shared_ptr<TextLabel> TextLabel::Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper, TextAlignment Align, const std::string & String,
                                                             const sf::Color & Color, std::shared_ptr<sf::Font> _Font, unsigned int TextSize, const sf::FloatRect &RenderBounds, const sf::Vector2f &Position)
    {
      if (!ThisLayer.lock() || !ThisLayer.lock()->CanAcceptWidget()) 
        throw InvalidObjectException({ ExceptionCause::InvalidContainer, ExceptionCause::ConstructionError },
                                     EXCEPTION_MESSAGE("Given WidgetHelper is NULL or cannot accept a widget"));

      try
      {

        std::shared_ptr<TextLabel> Label(new TextLabel);
        Label->Helper = ThisHelper.lock();
        Label->Alignment = Align;
        Label->Bounds = RenderBounds;
        Label->Font = _Font;
        Label->RawString = String;
        Label->RenderString.setFont(*_Font);
        Label->RenderString.setString(String);
        Label->RenderString.setCharacterSize(TextSize);
        Label->RenderString.setFillColor(Color);
        Label->TextPosition = Position;
        if (RenderBounds.width == 0 || RenderBounds.height == 0) {
          auto frect = Label->RenderString.getGlobalBounds();
          Label->Bounds = frect;
        }

        Label->RenderString.setPosition(Position);

        ThisLayer.lock()->RegisterWidget(Label);
        Label->MyLayer = ThisLayer.lock();

        assert(Label->Helper.lock() && Label->MyLayer.lock());

        return Label;
      }
      catch (EngineRuntimeError &err)
      {
        err.AddCause(ExceptionCause::ConstructionError);
        err.AddMessage(EXCEPTION_MESSAGE("Could not construct TextLabel"));

        throw;
      }
    }

    std::shared_ptr<TextLabel> TextLabel::Create(std::weak_ptr<WidgetBase> Widget, std::weak_ptr<WidgetHelper> ThisHelper, TextAlignment Align, const std::string &String, const sf::Color &Color,
                                                 std::shared_ptr<sf::Font> _Font, unsigned int TextSize, const sf::FloatRect &RenderBounds, const sf::Vector2f &Offset)
    {
      if (!Widget.lock())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer, ExceptionCause::ConstructionError },
                                     EXCEPTION_MESSAGE("Widget is NULL"));

      try
      {
        std::shared_ptr<TextLabel> Label(new TextLabel);
        Label->Helper = ThisHelper;
        Label->Alignment = Align;
        Label->Font = _Font;
        Label->RawString = String;
        Label->RenderString.setFont(*_Font);
        Label->RenderString.setString(String);
        Label->RenderString.setCharacterSize(TextSize);
        Label->RenderString.setFillColor(Color);
        Label->Parent = Widget.lock();

        //Need to align the text within the widget
        float xDiff = (Widget.lock()->GlobalWidgetBounds.GlobalBounds.width - Label->RenderString.getGlobalBounds().width) / 2.f;
        float yDiff = (Widget.lock()->GlobalWidgetBounds.GlobalBounds.height - Label->RenderString.getGlobalBounds().height) / 2.f;
        sf::Vector2f Pos = { Widget.lock()->GlobalWidgetBounds.GlobalBounds.left + xDiff, Widget.lock()->GlobalWidgetBounds.GlobalBounds.top + yDiff };
        Pos += Offset;

        Label->MoveTo({ Pos.x, Pos.y, RenderBounds.width, RenderBounds.height });
        //Label->GlobalWidgetBounds.ForceRegion({ Pos.x, Pos.y, RenderBounds.width, RenderBounds.height });

        //Label->Bounds = { Pos.x, Pos.y, RenderBounds.width, RenderBounds.height };

        //Label->TextPosition = Pos;
        //Label->RenderString.setPosition(Pos);
        //Label->AlignText();

        Widget.lock()->AddTextLabel(Label);

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

    void TextLabel::Render(std::shared_ptr<sf::RenderTexture> Target)
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

    void TextLabel::MoveTo(const sf::FloatRect &Region)
    {
      TextPosition = { Region.left, Region.top };
      RenderString.setPosition(TextPosition);
      Bounds = Region;
      GlobalWidgetBounds.ForceRegion(Bounds);
    }

    void TextLabel::SetPosition(const sf::Vector2f & Position)
    {
      TextPosition = Position;
      RenderString.setPosition(Position);

      Bounds.left = Position.x;
      Bounds.top = Position.y;

      GlobalWidgetBounds.ForceRegion(Bounds);
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