#include "../../../Headers/UI/Menu/MenuWidget.h"
#include "../../../Headers/UI/Menu/MenuScreen.h"
#include "../../../Headers/UI/WIdgetHelper.h"
#include "../../../Headers/UI/Theme.h"
#include <algorithm>
#include <iterator>

namespace Engine
{

  namespace UI
  {

    std::shared_ptr<MenuWidget> MenuWidget::Create(std::shared_ptr<UILayer> TopLayer, std::shared_ptr<WidgetHelper> TopHelper, const sf::Vector2f & Position, const sf::Vector2f & Size)
    {
      if (!TopLayer || !TopHelper || !TopHelper->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer },
                                     EXCEPTION_MESSAGE("TopLayer is NULL or cannot appect a widget"));

      try
      {
        std::shared_ptr<MenuWidget> Menu(new MenuWidget);

        Menu->MenuHelper = WidgetHelper::Create();
        Menu->ChildLayer = UILayer::Create(Menu->MenuHelper);
        Menu->MyLayer = TopLayer;
        Menu->Helper = TopHelper;

        assert(Menu->MyLayer.lock() && Menu->Helper.lock());
        assert(Menu->ChildLayer && Menu->MenuHelper);

        Menu->SetUpWidget();
        Menu->SetBGColor(DefaultDarkTheme.MenuBackgroundColorNormal);
        Menu->SetBGColorNormal(DefaultDarkTheme.MenuBackgroundColorNormal);
        Menu->SetBGColorPressed(DefaultDarkTheme.ButtonColorPressed);
        Menu->SetBGColorHighlighted(DefaultDarkTheme.ButtonColorHighlighted);
        Menu->BGRect.setPosition(Position);
        Menu->BGRect.setSize(Size);
        Menu->GlobalWidgetBounds.ForceRegion({ Position, Size });

        return Menu;
      }
      catch (EngineRuntimeError &err)
      {
        err.AddCause(ExceptionCause::ConstructionError);
        err.AddMessage(EXCEPTION_MESSAGE("Failed to create MenuWidget"));

        throw;
      }
    }

    void MenuWidget::Open()
    {

    }

    void MenuWidget::SetDefaultScreen(std::weak_ptr<MenuScreen> Screen, std::shared_ptr<MenuWidget> Menu)
    {
      auto ptr = Screen.lock();
      if (ptr) {
        Menu->DefaultScreen = Screen;
        ptr->MyLayer = Menu->ChildLayer;
        ptr->TopMenu = Menu;
        ptr->Helper = Menu->MenuHelper;
        Menu->Screens[ptr->WidgetID] = Screen;
        Menu->ScreenStack.push(Screen);
      }
    }

    void MenuWidget::AddScreen(std::weak_ptr<MenuScreen> Screen)
    {
      auto ptr = Screen.lock();

      assert(this && DefaultScreen.lock() && ptr);
    }

    void MenuWidget::AddScreen(std::weak_ptr<MenuScreen> Screen, std::shared_ptr<MenuWidget> Menu)
    {
      auto ptr = Screen.lock();

      assert(ptr && Menu->DefaultScreen.lock());

      if (!Menu->DefaultScreen.lock()) {
        Menu->DefaultScreen = Screen;
      }

      if (ptr) {
        ptr->MyLayer = Menu->ChildLayer;
        ptr->TopMenu = Menu;
        ptr->SetBGPosition(Menu->Position);
        ptr->SetBGSize(Menu->Size);
        ptr->Helper = Menu->MenuHelper;
        Menu->Screens[ptr->WidgetID] = Screen;
      }

    }

    void MenuWidget::SetFont(std::shared_ptr<MenuWidget> Menu, std::shared_ptr<sf::Font> Font)
    {
      Menu->MenuFont = Font;
      Menu->MenuText.setFont(*Font);
    }

    void MenuWidget::SetTitle(std::shared_ptr<MenuWidget> Menu, const std::string & string, unsigned int size, const sf::Color & Color)
    {
      Menu->MenuText.setString(string);
      Menu->MenuText.setCharacterSize(size);
      Menu->MenuText.setFillColor(Color);

      //Try to align the text to be centered?
      sf::FloatRect WidgetBounds = Menu->GlobalWidgetBounds.GlobalBounds;
      sf::FloatRect TextBounds = Menu->MenuText.getGlobalBounds();

      float xDiff = std::abs(WidgetBounds.width - TextBounds.width);
      Menu->MenuText.setPosition({ WidgetBounds.left + (xDiff / 2.f), WidgetBounds.height + 10.f });
    }

    void MenuWidget::ShowScreen(std::weak_ptr<MenuScreen> Screen)
    {
      auto ptr = Screen.lock();

      if (ptr) {
        auto it = Screens.find(ptr->WidgetID);
        if (it != Screens.end()) {
          ScreenStack.push(ptr);
        }
      }
    }

    void MenuWidget::RemoveScreen(std::weak_ptr<MenuScreen> Screen)
    {
      auto ptr = Screen.lock();
      if (!ptr)
        return;

      //Assume the screen isn't currently on the stack??
      for (auto it = Screens.begin(); it != Screens.end();) {
        auto _ptr = (*it).second.lock();
        if (_ptr && _ptr->WidgetID == ptr->WidgetID) {
          Screens.erase(it);
          return;
        }
        else {
          ++it;
        }
      }


    }

    void MenuWidget::Back()
    {
      //Pop top off stack
      if (ScreenStack.size() > 1) {
        auto ptr = ScreenStack.top().lock();
        if (ptr) {
          ptr->MakeInactive();
        }
        ScreenStack.pop();

        ptr = ScreenStack.top().lock();
        if (ptr) {
          ptr->MakeActive();
        }
      }
      else {
        _IsInFocus = false;
        if (Helper.lock())
          (Helper.lock())->ReleaseTopFocus();
      }
    }

    void MenuWidget::Close()
    {
      //Pop everything off the stack except the default? Or pop that off too?
      while (ScreenStack.size() > 1)
        Back();

      if (Helper.lock()) {
        (Helper.lock())->ReleaseTopFocus();
        _IsInFocus = false;
      }
    }

    void MenuWidget::Hide()
    {
    }

    void MenuWidget::Disable()
    {
    }

    void MenuWidget::Clear()
    {
      //Not sure why I'd ever do this

      Screens.clear();
    }

    void MenuWidget::ShowDefaultScreen(std::weak_ptr<MenuWidget> Menu)
    {
      auto _Menu = Menu.lock();
      if (!_Menu)
        return;

      auto ptr = _Menu->DefaultScreen.lock();

      if (ptr) {
        auto help = ptr->Helper.lock();
        if (help) {
          help->TakeFocus(_Menu);
          _Menu->_IsInFocus = true;
        }
        if (_Menu->ScreenStack.empty())
          _Menu->ShowScreen(_Menu->DefaultScreen);
      }
    }

    void MenuWidget::OpenMenu(std::weak_ptr<MenuWidget> Menu)
    {
      auto ptr = Menu.lock();

      assert(ptr);

      std::weak_ptr<MenuScreen> Default = ptr->DefaultScreen;
      if (Default.lock()) {
        if (ptr->ScreenStack.empty())
          ptr->ShowScreen(Default);

        ptr->Helper.lock()->TakeFocus(Menu);
        ptr->_IsInFocus = true;
      }
    }

    void MenuWidget::ConsumeEvent(const InputEvent & IEvent)
    {
      if (ScreenStack.empty())
        throw EngineRuntimeError({ ExceptionCause::InvalidContainer, ExceptionCause::InvalidObjectUsed },
                                 EXCEPTION_MESSAGE("Menu stack is empty"));

      auto ptr = ScreenStack.top().lock();
      if (ptr) {
        ptr->ConsumeEvent(IEvent);
      }
    }

    void MenuWidget::OnFocusGained(const FocusChangeEvent & FEvent)
    {
      
    }

    void MenuWidget::OnFocusLost(const FocusChangeEvent & FEvent)
    {
    }

    void MenuWidget::OnKeyPress(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void MenuWidget::OnKeyRelease(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void MenuWidget::OnMousePress(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void MenuWidget::OnMouseRelease(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void MenuWidget::OnMouseScroll(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void MenuWidget::OnMouseOver(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
      BGRect.setOutlineColor(sf::Color::White);
    }

    void MenuWidget::OnMouseLeave(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
      BGRect.setOutlineColor(sf::Color(135, 0, 130));
    }

    void MenuWidget::OnMouseMove(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void MenuWidget::OnDragBegin(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void MenuWidget::OnDragEnd(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void MenuWidget::OnDragContinue(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void MenuWidget::TickUpdate(const double & delta)
    {
      assert(!ScreenStack.empty());

      auto ptr = ScreenStack.top().lock();

      if (ptr) {
        ptr->TickUpdate(delta);
      }
    }

    void MenuWidget::Render(std::shared_ptr<sf::RenderTexture> Texture)
    {
      if (!_IsInFocus)
        return;

      auto View = MakeView(GlobalWidgetBounds.GlobalBounds);
      Texture->setView(View);
      Texture->draw(BGRect);
      auto ptr = ScreenStack.top().lock();
      if (ptr) {
        ptr->Render(Texture);
      }
      Texture->draw(MenuText);

      Texture->setView(Texture->getDefaultView());
    }

    void MenuWidget::Move(const sf::Vector2f & Delta)
    {
    }

    void MenuWidget::Resize(const sf::Vector2f & Size)
    {
    }

    void MenuWidget::IntakeEvent(const InputEvent & IEvent)
    {
    }

    void MenuWidget::CloseMenu()
    {
      auto ptr = Helper.lock();
      if (ptr) {
        ptr->ReleaseTopFocus();
        _IsInFocus = false;
        DEBUG_ONLY std::cerr << "Closing Menu" << std::endl;

        //assert(ScreenStack.size() == 1);
      }
    }

  }

}