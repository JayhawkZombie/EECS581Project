#include "../../../Headers/UI/Buttons/ClickButtonBase.h"
#include "../../../Headers/UI/WIdgetHelper.h"


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

    std::shared_ptr<ClickButtonBase> ClickButtonBase::Create(std::shared_ptr<UILayer> ThisLayer, const sf::Vector2f &Position, const sf::Vector2f &Size)
    {
      DEBUG_ONLY std::cerr << "ClickButtonBase::Create" << std::endl;

      if (!ThisLayer || !ThisLayer->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer, ExceptionCause::ConstructionError },
                                     EXCEPTION_MESSAGE("Created WidgetHelper is invalid or cannot accept any widgets"));

      std::shared_ptr<ClickButtonBase> Widget(new ClickButtonBase());

      Widget->MyLayer = ThisLayer;
      ThisLayer->RegisterWidget(Widget);

      //OK, gonna set up a base drawable
      std::shared_ptr<ColoredQuad> Quad(new ColoredQuad(Position, Size));

      Widget->GlobalWidgetBounds.ForceRegion({ Position, Size });

      Widget->Drawables.push_back(Quad);

      return Widget;
    }

    void ClickButtonBase::Move(const sf::Vector2f &Delta)
    {
      WidgetBase::Move(Delta);

      for (auto & dr : Drawables) {
        dr->DrawBounds.MoveRegion(Delta);
      }
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
    }

    void ClickButtonBase::OnKeyRelease(const InputEvent &event)
    {
      ButtonBase::OnKeyRelease(event);
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
    }

    void ClickButtonBase::OnMouseLeave(const InputEvent &event)
    {
      ButtonBase::OnMouseLeave(event);
      Drawables[0]->DrawBounds.DrawQuad.setOutlineColor(sf::Color::Transparent);
      Drawables[0]->DrawBounds.DrawQuad.setOutlineThickness(-2);
    }

    void ClickButtonBase::OnMouseMove(const InputEvent &event)
    {
      ButtonBase::OnMouseMove(event);
    }

    void ClickButtonBase::OnDragBegin(const InputEvent &event)
    {
      ButtonBase::OnDragBegin(event);
    }

    void ClickButtonBase::OnDragEnd(const InputEvent &event)
    {
      ButtonBase::OnDragEnd(event);
    }

    void ClickButtonBase::OnDragContinue(const InputEvent &IEvent)
    {
      ButtonBase::OnDragContinue(IEvent);
    }

    void ClickButtonBase::TickUpdate(const double &delta)
    {
      WidgetBase::TickUpdate(delta);
    }

    void ClickButtonBase::Render(std::shared_ptr<sf::RenderTexture> &Texture)
    {
      for (auto & item : Drawables)
        item->Render(Texture); 

      Texture->draw(ButtonText);
    }

  }

}

