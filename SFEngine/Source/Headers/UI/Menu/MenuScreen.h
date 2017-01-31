#ifndef SFENGINE_UI_MENU_TREE_H
#define SFENGINE_UI_MENU_TREE_H

#include "../Widget.h"

#include <stack>

namespace Engine
{
  namespace UI
  {

    class Menu;
    class MenuWidget;

    class MenuScreen : public WidgetBase
    {
    public:
      friend class MenuWidget;
      EDITOR_FRIEND

      static std::shared_ptr<MenuScreen> Create();

      void AssignToMenu(std::shared_ptr<MenuWidget> Menu);

      void ChangeScreenTo(std::weak_ptr<MenuScreen> ToScreen);

      void AddItem(std::weak_ptr<WidgetBase> Widget);

      void MakeInactive();
      void MakeActive();
      void CenterElement();
      void CloseScreen();

      virtual std::string ClassName() override {
        return "MenuScreen";
      }

      virtual void ConsumeEvent(const InputEvent &IEvent) override;
      virtual void OnFocusGained(const FocusChangeEvent &FEvent) override;
      virtual void OnFocusLost(const FocusChangeEvent &FEvent) override;
      virtual void OnKeyPress(const InputEvent &IEvent) override;
      virtual void OnKeyRelease(const InputEvent &IEvent) override;
      virtual void OnMousePress(const InputEvent &IEvent) override;
      virtual void OnMouseRelease(const InputEvent &IEvent) override;
      virtual void OnMouseScroll(const InputEvent &IEvent) override;
      virtual void OnMouseOver(const InputEvent &IEvent) override;
      virtual void OnMouseLeave(const InputEvent &IEvent) override;
      virtual void OnMouseMove(const InputEvent &IEvent) override;
      virtual void OnDragBegin(const InputEvent &IEvent) override;
      virtual void OnDragEnd(const InputEvent &IEvent) override;
      virtual void OnDragContinue(const InputEvent &IEvent) override;
      virtual void TickUpdate(const double &delta) override;
      virtual void Render(std::shared_ptr<sf::RenderTexture> Texture) override;
      virtual void Move(const sf::Vector2f &Delta) override;
      virtual void Resize(const sf::Vector2f &Size) override;

      virtual ~MenuScreen() = default;

      std::shared_ptr<WidgetHelper> ScreenHelper;
      std::shared_ptr<UILayer> ScreenLayer;
    protected:
      MenuScreen() = default;

      bool IsActive = true;

      std::vector<std::weak_ptr<WidgetBase>> Items;

      std::weak_ptr<MenuWidget> TopMenu;
    };

  }
}


#endif
