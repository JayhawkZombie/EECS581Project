#ifndef SFENGINE_UI_LIST_H
#define SFENGINE_UI_LIST_H

#include "../Widget.h"
#include "../Buttons/ClickButtonBase.h"
#include "../Theme.h"
#include "../Draggables/StickyBar.h"

namespace Engine
{

  namespace UI
  {
    class ClickButtonBase;

    constexpr std::uint32_t InitReserveRenTexHeight = 1000U;

    class ListWidget : public WidgetBase
    {
    public:
      static std::shared_ptr<ListWidget> Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper, const sf::Vector2f &Position, const sf::Vector2f &Size, const Theme &theme);

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
      virtual void AddItem(std::shared_ptr<WidgetBase> Widget);
      virtual std::size_t GetNumberOfItems() const {
        return Items.size();
      }

      virtual std::int32_t GetCurrentlySelectedIndex() const {
        return CurrentlySelected;
      }

      virtual void ScrollUpOne();
      virtual void ScrollDownOne();
      //virtual void ScrollToTop();
      //virtual void ScrollToBottom();

      virtual ~ListWidget() = default;
    protected:
      ListWidget() = default;
      std::shared_ptr<UILayer> ButtonsLayer;
      std::shared_ptr<sf::RenderTexture> ItemsTexture;
      sf::Sprite ItemsSprite;

      //We keep a button on top of this item and use those to intercept collisions
      //We will render the items list, but won't do collisions with it UNLESS the button that occupies the same space
      //detects the hit
      std::shared_ptr<ClickButtonBase> ItemButtons;
      std::vector<std::shared_ptr<WidgetBase>> Items;
      sf::FloatRect TotalVisibleArea = { 0, 0, 0, 0 };
      sf::FloatRect TotalRegion = { 0, 0, 0, 0 };
      sf::IntRect CurrentTextureView = { 0, 0, 0, 0 };
      std::int32_t CurrentlySelected = -1;
      std::uint32_t TopItem = 0;
      std::uint32_t BottomItem = 0;
      bool IsScrolled = false;
      bool ItemIsSelected = 0;
      sf::Vector2f ScrollOffset = { 0, 0 };
    };

  }

}

#endif
