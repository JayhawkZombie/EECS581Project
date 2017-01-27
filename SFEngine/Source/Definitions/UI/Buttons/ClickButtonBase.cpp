#include "../../../Headers/UI/Buttons/ClickButtonBase.h"
#include "../../../Headers/UI/WIdgetHelper.h"
#include "../../../Headers/UI/Text/TextLabel.h"

namespace Engine
{

  namespace UI
  {

    ClickButtonBase::ClickButtonBase()
      : ButtonBase()
    {
      //enable dragging for this item
      CanBeDragged = true;
    }

    std::shared_ptr<ClickButtonBase> ClickButtonBase::Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper, const sf::Vector2f &Position, const sf::Vector2f &Size)
    {
      DEBUG_ONLY std::cerr << "ClickButtonBase::Create" << std::endl;

      if (!ThisLayer.lock() || !ThisLayer.lock()->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer, ExceptionCause::ConstructionError },
                                     EXCEPTION_MESSAGE("Created WidgetHelper is invalid or cannot accept any widgets"));

      std::shared_ptr<ClickButtonBase> Widget(new ClickButtonBase());
      Widget->Helper = ThisHelper.lock();
      Widget->MyLayer = ThisLayer.lock();
      ThisLayer.lock()->RegisterWidget(Widget);

      assert(Widget->Helper.lock() && Widget->MyLayer.lock());

      //OK, gonna set up a base drawable
      Widget->Background.setFillColor(sf::Color(33, 33, 33, 100));
      Widget->Background.setPosition(Position);
      Widget->Background.setSize(Size);
      Widget->Background.setOutlineColor(sf::Color(66, 66, 66, 100));
      Widget->Background.setOutlineThickness(-1);

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
      Background.move(Delta);

      for (auto & dr : Drawables) {
        dr->DrawBounds.MoveRegion(Delta);
      }
    }

    void ClickButtonBase::Resize(const sf::Vector2f & Size)
    {
      sf::FloatRect Rect;

      Background.setSize(Size);
    }

    void ClickButtonBase::SetBGColor(const sf::Color & Color)
    {
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
      ButtonBase::OnMousePress(event);
      
      DEBUG_ONLY std::cerr << "ClickButtonBase::OnMousePress" << std::endl;

      if (MousePressCB)
        MousePressCB();
    }

    void ClickButtonBase::OnMouseRelease(const InputEvent &event)
    {
      ButtonBase::OnMouseRelease(event);

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

      Drawables[0]->DrawBounds.DrawQuad.setOutlineColor(sf::Color::Red);
      Drawables[0]->DrawBounds.DrawQuad.setOutlineThickness(-2);

      if (MouseOverCB)
        MouseOverCB();
    }

    void ClickButtonBase::OnMouseLeave(const InputEvent &event)
    {
      ButtonBase::OnMouseLeave(event);
      Drawables[0]->DrawBounds.DrawQuad.setOutlineColor(sf::Color::Transparent);
      Drawables[0]->DrawBounds.DrawQuad.setOutlineThickness(-2);

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

    void ClickButtonBase::Render(std::shared_ptr<sf::RenderTexture> &Texture)
    {
      for (auto & item : Drawables)
        item->Render(Texture); 
      Texture->draw(Background);
      Texture->draw(ButtonText);
      for (auto & label : TextLabels)
        label->Render(Texture);
    }

  }

}

