#ifndef SFENGINE_UI_LIST_H
#define SFENGINE_UI_LIST_H

#include "../Widget.h"
#include "../Buttons/ClickButtonBase.h"
#include "../Theme.h"
#include "../Draggables/StickyBar.h"
#include "../Toggles/SimpleToggle.h"

namespace Engine
{

  namespace UI
  {
    class ClickButtonBase;

    constexpr std::uint32_t InitReserveRenTexHeight = 1000U;

    class ListWidget : public WidgetBase
    {
    public:
      static std::shared_ptr<ListWidget> Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper, 
                                                const sf::Vector2f &Position, const sf::Vector2f &Size, const sf::Vector2f &MaxDropdownSize, 
                                                const sf::Vector2f &ItemSize, std::shared_ptr<sf::Font> _Font, std::shared_ptr<sf::Texture> Icons, const Theme &theme);

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
      virtual void ResetAppearance() override;
      virtual void AddItem(const std::string &ItemText);
      virtual std::size_t GetNumberOfItems() const {
        return Items.size();
      }

      virtual std::int32_t GetCurrentlySelectedIndex() const {
        return CurrentlySelected;
      }

      virtual void ScrollUpOne();
      virtual void ScrollDownOne();

      virtual ~ListWidget() = default;
    protected:
      ListWidget() = default;
      std::shared_ptr<UILayer> ButtonsLayer;
      std::shared_ptr<sf::RenderTexture> ItemsTexture;
      std::shared_ptr<sf::Font> TextFont;
      sf::Sprite ItemsSprite;
      std::shared_ptr<SimpleToggle> DropDownButton;

      void OpenList();
      void CloseList();

      //We keep a button on top of this item and use those to intercept collisions
      //We will render the items list, but won't do collisions with it UNLESS the button that occupies the same space
      //detects the hit
      std::shared_ptr<ClickButtonBase> ItemButtons;
      std::vector<std::shared_ptr<ClickButtonBase>> Items;
      sf::IntRect CurrentTextureView = { 0, 0, 0, 0 };
      sf::Vector2f ListSize = { 0,0 };
      sf::Vector2f ListItemSize;
      sf::Vector2f MaximumDropdownSize = { 0,0 };
      std::int32_t CurrentlySelected = -1;
      bool IsScrolled = false;
      bool IsOpen = false;
      bool ItemIsSelected = 0;
      sf::Vector2f ScrollOffset = { 0, 0 };
    };

  }

}

#endif
