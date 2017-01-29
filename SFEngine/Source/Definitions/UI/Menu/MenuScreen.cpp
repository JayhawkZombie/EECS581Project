#include "../../../Headers/UI/Menu/MenuScreen.h"

#include "../../../Headers/UI/WidgetHelper.h"
#include "../../../Headers/UI/Menu/MenuWidget.h"

namespace Engine
{

  namespace UI
  {
    std::shared_ptr<MenuScreen> MenuScreen::Create()
    {
      std::shared_ptr<MenuScreen> Screen(new MenuScreen);

      Screen->ScreenHelper = WidgetHelper::Create();
      
      Screen->ScreenLayer = UILayer::Create(Screen->ScreenHelper);
      
      try
      {
        Screen->SetUpLayerless();
      }
      catch (EngineRuntimeError &err)
      {
        err.AddCause(ExceptionCause::ConstructionError);
        err.AddMessage(EXCEPTION_MESSAGE("Failed to construct MenuScreen"));

        throw;
      }

      return Screen;
    }
    void MenuScreen::AssignToMenu(std::shared_ptr<MenuWidget> Menu)
    {
      TopMenu = Menu;
      
    }
    void MenuScreen::ChangeScreenTo(std::weak_ptr<MenuScreen> ToScreen)
    {
      auto ptr = TopMenu.lock();

      if (ptr) {
        ptr->ShowScreen(ToScreen);
      }
    }
    void MenuScreen::AddItem(std::weak_ptr<WidgetBase> Widget)
    {
    }
    void MenuScreen::MakeInactive()
    {
    }
    void MenuScreen::MakeActive()
    {
      for (auto & item : Items) {
        auto ptr = item.lock();
        if (ptr)
          ptr->ResetAppearance();
      }
    }
    void MenuScreen::CloseScreen()
    {
      auto ptr = TopMenu.lock();
      if (ptr) {
        ptr->Back();
      }
    }
    void MenuScreen::ConsumeEvent(const InputEvent & IEvent)
    {
      if (ScreenLayer->HandleEvent(IEvent)) {

      }
      else {

      }
    }
    void MenuScreen::OnFocusGained(const FocusChangeEvent & FEvent)
    {
    }
    void MenuScreen::OnFocusLost(const FocusChangeEvent & FEvent)
    {
    }
    void MenuScreen::OnKeyPress(const InputEvent & IEvent)
    {
    }
    void MenuScreen::OnKeyRelease(const InputEvent & IEvent)
    {
    }
    void MenuScreen::OnMousePress(const InputEvent & IEvent)
    {
    }
    void MenuScreen::OnMouseRelease(const InputEvent & IEvent)
    {
    }
    void MenuScreen::OnMouseScroll(const InputEvent & IEvent)
    {
    }
    void MenuScreen::OnMouseOver(const InputEvent & IEvent)
    {
    }
    void MenuScreen::OnMouseLeave(const InputEvent & IEvent)
    {
    }
    void MenuScreen::OnMouseMove(const InputEvent & IEvent)
    {
    }
    void MenuScreen::OnDragBegin(const InputEvent & IEvent)
    {
    }
    void MenuScreen::OnDragEnd(const InputEvent & IEvent)
    {
    }
    void MenuScreen::OnDragContinue(const InputEvent & IEvent)
    {
    }
    void MenuScreen::TickUpdate(const double & delta)
    {
    }
    void MenuScreen::Render(std::shared_ptr<sf::RenderTexture> &Texture)
    {
      Texture->draw(BGRect);
      ScreenLayer->Render(Texture);
    }
    void MenuScreen::Move(const sf::Vector2f & Delta)
    {
    }
    void MenuScreen::Resize(const sf::Vector2f & Size)
    {
    }
  }

}