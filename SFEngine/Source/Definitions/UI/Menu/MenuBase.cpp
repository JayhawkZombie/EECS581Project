#include "../../../Headers/UI/Menu/MenuBase.h"

#include "../../../Headers/UI/WIdgetHelper.h"

namespace Engine
{

  namespace UI
  {

    std::shared_ptr<MenuWidgetBase> MenuWidgetBase::Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper, const sf::Vector2f &Position, const sf::Vector2f &Size)
    {
      if (!ThisLayer.lock() || !ThisLayer.lock()->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer, ExceptionCause::ConstructionError },
                                     EXCEPTION_MESSAGE("Layer is NULL or cannot accept a widget"));

      std::shared_ptr<MenuWidgetBase> Widget(new MenuWidgetBase);
      Widget->Helper = ThisHelper.lock();
      Widget->MyLayer = ThisLayer.lock();

      assert(Widget->Helper.lock() && Widget->MyLayer.lock());
      return Widget;

    }

    MenuWidgetBase::MenuWidgetBase()
    {

    }

    void MenuWidgetBase::ConsumeEvent(const InputEvent &IEvent)
    {

    }

    void MenuWidgetBase::OnFocusGained(const FocusChangeEvent &FEvent)
    {

    }

    void MenuWidgetBase::OnFocusLost(const FocusChangeEvent &FEvent)
    {

    }

    void MenuWidgetBase::OnKeyPress(const InputEvent &IEvent)
    {

    }

    void MenuWidgetBase::OnKeyRelease(const InputEvent &IEvent)
    {

    }

    void MenuWidgetBase::OnMousePress(const InputEvent &IEvent)
    {

    }

    void MenuWidgetBase::OnMouseRelease(const InputEvent &IEvent)
    {

    }

    void MenuWidgetBase::OnMouseScroll(const InputEvent &IEvent)
    {

    }

    void MenuWidgetBase::OnMouseOver(const InputEvent &IEvent)
    {

    }

    void MenuWidgetBase::OnMouseLeave(const InputEvent &IEvent)
    {

    }

    void MenuWidgetBase::OnMouseMove(const InputEvent &IEvent)
    {

    }

    void MenuWidgetBase::OnDragBegin(const InputEvent &IEvent)
    {

    }

    void MenuWidgetBase::OnDragEnd(const InputEvent &IEvent)
    {

    }

    void MenuWidgetBase::OnDragContinue(const InputEvent &IEvent)
    {

    }

    void MenuWidgetBase::TickUpdate(const double &delta)
    {

    }

    void MenuWidgetBase::Render(std::shared_ptr<sf::RenderTexture> Texture)
    {

    }

    MenuWidgetBase::~MenuWidgetBase()
    {

    }

  }

}
