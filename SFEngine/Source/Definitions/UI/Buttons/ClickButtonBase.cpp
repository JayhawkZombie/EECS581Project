#include "../../../Headers/UI/Buttons/ClickButtonBase.h"
#include "../../../Headers/UI/WIdgetHelper.h"
#include "../../../Headers/UI/Text/TextLabel.h"

#include "../../../Headers/UI/Theme.h"
namespace Engine
{

  namespace UI
  {

    ClickButtonBase::ClickButtonBase()
      : ButtonBase()
    {
      //enable dragging for this item
      CanBeDragged = false;
    }

    std::shared_ptr<ClickButtonBase> ClickButtonBase::Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper, const sf::Vector2f &Position, const sf::Vector2f &Size, std::shared_ptr<sf::Texture> OverlayTexture)
    {
      //DEBUG_ONLY std::cerr << "ClickButtonBase::Create" << std::endl;

      if (!ThisLayer.lock() || !ThisLayer.lock()->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer, ExceptionCause::ConstructionError },
                                     EXCEPTION_MESSAGE("Created WidgetHelper is invalid or cannot accept any widgets"));

      std::shared_ptr<ClickButtonBase> Widget(new ClickButtonBase());
      Widget->Helper = ThisHelper.lock();
      Widget->MyLayer = ThisLayer.lock();
      ThisLayer.lock()->RegisterWidget(Widget);

      assert(Widget->Helper.lock() && Widget->MyLayer.lock());

      //button overlay textures not working
      if (false) {
        Widget->BGRect.setPosition(Position);
        Widget->BGRect.setSize(Size);
        Widget->BGRect.setFillColor(sf::Color::Transparent);
        Widget->BGRect.setTexture(OverlayTexture.get());
        Widget->BGRect.setTextureRect(DefaultDarkTheme.ButtonOverlayNormal);
        Widget->Overlay = OverlayTexture;
        Widget->OverlayNormalRect = DefaultDarkTheme.ButtonOverlayNormal;
        Widget->OverlayHighlightedRect = DefaultDarkTheme.ButtonOverlayHighlighted;
        Widget->OverlayPressedRect = DefaultDarkTheme.ButtonOverlayPressed;

      }
      else {
        //OK, gonna set up a base drawable
        Widget->BGColorNormal = DefaultDarkTheme.ButtonColorNormal;
        Widget->BGColorHighlighted = DefaultDarkTheme.ButtonColorHighlighted;
        Widget->BGColorPressed = DefaultDarkTheme.ButtonColorPressed;

        Widget->BGRect.setFillColor(DefaultDarkTheme.ButtonColorNormal);
        Widget->BGRect.setPosition(Position);
        Widget->BGRect.setSize(Size);
        Widget->BGOutlineColorNormal = sf::Color(DefaultDarkTheme.ButtonOutlineColorNormal);
        Widget->BGOutlineColorHighlighted = sf::Color(DefaultDarkTheme.ButtonOutlineColorHighlighted);
        Widget->BGRect.setOutlineColor(DefaultDarkTheme.ButtonOutlineColorNormal);
        Widget->BGRect.setOutlineThickness(-1);
      }

      std::shared_ptr<ColoredQuad> Quad(new ColoredQuad(Position, Size));

      Widget->GlobalWidgetBounds.ForceRegion({ Position, Size });

      Widget->Drawables.push_back(Quad);

      return Widget;
    }

    void ClickButtonBase::SetFont(std::shared_ptr<ClickButtonBase> Button, std::shared_ptr<sf::Font> Font)
    {
      Button->ButtonFont = Font;
      Button->ButtonText.setFont(*Font);
    }

    void ClickButtonBase::SetText(std::shared_ptr<ClickButtonBase> Button, const std::string & string, unsigned int size, const sf::Color & Color)
    {
      Button->ButtonText.setString(string);
      Button->ButtonText.setCharacterSize(size);
      Button->ButtonText.setFillColor(Color);
    }

    void ClickButtonBase::Move(const sf::Vector2f &Delta)
    {
      WidgetBase::Move(Delta);

      for (auto & dr : Drawables) {
        dr->DrawBounds.MoveRegion(Delta);
      }
    }

    void ClickButtonBase::Resize(const sf::Vector2f & Size)
    {
      sf::FloatRect Rect;

      BGRect.setSize(Size);
    }

    void ClickButtonBase::ResetAppearance()
    {
      BGRect.setOutlineColor(BGOutlineColorNormal);
      BGRect.setOutlineThickness(-2);
    }

    void ClickButtonBase::SetTexture(std::shared_ptr<sf::Texture> Texture)
    {
      BGTexture = Texture;
      BGRect.setTexture(Texture.get());
    }

    void ClickButtonBase::SetTextureRect(sf::IntRect & Rect)
    {
      BGRect.setTextureRect(Rect);
      BGTextureRect = Rect;
    }

    void ClickButtonBase::SetOverlayTexture(std::shared_ptr<sf::Texture> Texture)
    {
      Overlay = Texture;
    }

    void ClickButtonBase::SetOverlayHighlightedTextureRect(const sf::IntRect & Rect)
    {
      OverlayHighlightedRect = Rect;
    }

    void ClickButtonBase::SetOverlayPressedTextureRect(const sf::IntRect & Rect)
    {
      OverlayPressedRect = Rect;
    }

    void ClickButtonBase::SetOverlayNormalTextureRect(const sf::IntRect & Rect)
    {
      OverlayNormalRect = Rect;
    }

    void ClickButtonBase::SetBGColorNormal(const sf::Color & Color)
    {
      BGColorNormal = Color;
    }

    void ClickButtonBase::SetBGColorHighlighted(const sf::Color & Color)
    {
      BGColorHighlighted = Color;
    }

    void ClickButtonBase::SetBGColorPressed(const sf::Color & Color)
    {
      BGColorPressed = Color;
    }

    void ClickButtonBase::SetBGColor(const sf::Color & Color)
    {
      BGColorNormal = Color;
      BGColor = Color;
      BGRect.setFillColor(BGColorNormal);
      Drawables[0]->DrawBounds.DrawQuad.setFillColor(Color);
    }

    void ClickButtonBase::ConsumeEvent(const InputEvent &event)
    {

    }

    void ClickButtonBase::OnFocusGained(const FocusChangeEvent &event)
    {
      ButtonBase::OnFocusGained(event);

      DEBUG_ONLY std::cerr << "ClickButtonBase::OnFocusGained" << std::endl;
    }

    void ClickButtonBase::OnFocusLost(const FocusChangeEvent &event)
    {
      ButtonBase::OnFocusLost(event);

      DEBUG_ONLY std::cerr << "ClickButtonBase::OnFocusLost" << std::endl;
    }

    void ClickButtonBase::OnKeyPress(const InputEvent &event)
    {
      ButtonBase::OnKeyPress(event);
      if (KeyPressCB)
        KeyPressCB();
    }

    void ClickButtonBase::OnKeyRelease(const InputEvent &event)
    {
      ButtonBase::OnKeyRelease(event);
      if (KeyReleaseCB)
        KeyReleaseCB();
    }

    void ClickButtonBase::OnMousePress(const InputEvent &event)
    {
      //BGRect.setFillColor(BGColorPressed);
      BGRect.setTextureRect(OverlayPressedRect);
      DEBUG_ONLY std::cerr << "ClickButtonBase::OnMousePress" << std::endl;

      if (MousePressCB)
        MousePressCB();
    }

    void ClickButtonBase::OnMouseRelease(const InputEvent &event)
    {
      BGRect.setFillColor(BGColorNormal);
      //BGRect.setTextureRect(OverlayNormalRect);
      if (MouseReleaseCB)
        MouseReleaseCB();
    }

    void ClickButtonBase::OnMouseScroll(const InputEvent &event)
    {
      ButtonBase::OnMouseScroll(event);
    }

    void ClickButtonBase::OnMouseOver(const InputEvent &event)
    {
      ButtonBase::OnMouseOver(event);
      BGRect.setFillColor(BGColorHighlighted);
      //BGRect.setTextureRect(OverlayHighlightedRect);
      //Drawables[0]->DrawBounds.DrawQuad.setOutlineColor(BGOutlineColorHighlighted);
      //Drawables[0]->DrawBounds.DrawQuad.setOutlineThickness(-2);

      BGRect.setOutlineColor(BGOutlineColorHighlighted);

      if (MouseOverCB)
        MouseOverCB();
    }

    void ClickButtonBase::OnMouseLeave(const InputEvent &event)
    {
      BGRect.setFillColor(BGColorNormal);
      //BGRect.setTextureRect(OverlayNormalRect);
      ButtonBase::OnMouseLeave(event);
      Drawables[0]->DrawBounds.DrawQuad.setOutlineColor(BGOutlineColorNormal);
      Drawables[0]->DrawBounds.DrawQuad.setOutlineThickness(-2);

      BGRect.setOutlineColor(BGOutlineColorNormal);

      if (MouseLeaveCB)
        MouseLeaveCB();
    }

    void ClickButtonBase::OnMouseMove(const InputEvent &event)
    {
      ButtonBase::OnMouseMove(event);
      
      if (MouseMoveCB)
        MouseMoveCB();
    }

    void ClickButtonBase::OnDragBegin(const InputEvent &event)
    {
      ButtonBase::OnDragBegin(event);

      if (DragBeginCB)
        DragBeginCB();
    }

    void ClickButtonBase::OnDragEnd(const InputEvent &event)
    {
      ButtonBase::OnDragEnd(event);
      
      if (DragEndCB)
        DragEndCB();
    }

    void ClickButtonBase::OnDragContinue(const InputEvent &IEvent)
    {
      ButtonBase::OnDragContinue(IEvent);

      if (DragContinueCB)
        DragContinueCB();
    }

    void ClickButtonBase::TickUpdate(const double &delta)
    {
      WidgetBase::TickUpdate(delta);
    }

    void ClickButtonBase::Render(std::shared_ptr<sf::RenderTexture> Texture)
    {
      //for (auto & item : Drawables)
      //  item->Render(Texture); 
      Texture->draw(BGRect);
      if (DrawTextureAndBG)
        Texture->draw(IconShape);

      //Texture->draw(ButtonText);
      for (auto & label : TextLabels)
        label->Render(Texture);
    }

  }

}

