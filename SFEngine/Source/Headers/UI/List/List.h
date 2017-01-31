#ifndef SFENGINE_UI_LIST_H
#define SFENGINE_UI_LIST_H

#include "../Widget.h"
#include "../Buttons/ClickButtonBase.h"

#include "../Draggables/StickyBar.h"

namespace Engine
{

  namespace UI
  {
    class ListWidget;
    class ClickButtonBase;

    class ListItem : public ClickButtonBase
    {
    public:
      friend class ListWidget;

      static std::shared_ptr<ListItem> Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper, std::weak_ptr<ListWidget> Parent, const sf::Vector2f &Position, const sf::Vector2f &Size);
      static std::shared_ptr<ListItem> Create(std::weak_ptr<ListItem> ToCopy);

      virtual void ConsumeEvent(const InputEvent &IEvent);
      virtual void OnFocusGained(const FocusChangeEvent &FEvent);
      virtual void OnFocusLost(const FocusChangeEvent &FEvent);
      virtual void OnKeyPress(const InputEvent &IEvent);
      virtual void OnKeyRelease(const InputEvent &IEvent);
      virtual void OnMousePress(const InputEvent &IEvent);
      virtual void OnMouseRelease(const InputEvent &IEvent);
      virtual void OnMouseScroll(const InputEvent &IEvent);
      virtual void OnMouseOver(const InputEvent &IEvent);
      virtual void OnMouseLeave(const InputEvent &IEvent);
      virtual void OnMouseMove(const InputEvent &IEvent);
      virtual void OnDragBegin(const InputEvent &IEvent);
      virtual void OnDragContinue(const InputEvent &IEvent);
      virtual void OnDragEnd(const InputEvent &IEvent);

      virtual void TickUpdate(const double &delta);
      virtual void Render(std::shared_ptr<sf::RenderTexture> Target);

      virtual void Move(const sf::Vector2f &Delta) override;

      virtual ~ListItem() = default;
    protected:
      ListItem();

      sf::RectangleShape Outline;

      std::weak_ptr<ListWidget> ParentList;
    };


    

    class ListWidget : public WidgetBase
    {
    public:
      static std::shared_ptr<ListWidget> Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper, std::shared_ptr<sf::Font> Font, const sf::Vector2f &Position, const sf::Vector2f &Size,
                                                ButtonPlacement CloseButtonPlacement = ButtonPlacement::TopCenter, const sf::Vector2f ButtonOfffset = { 0, 0 }, const sf::Vector2f &ButtonSize = { 0, 0 }, std::shared_ptr<sf::Texture> Tex = nullptr);
      virtual void ConsumeEvent(const InputEvent &IEvent);
      virtual void OnFocusGained(const FocusChangeEvent &FEvent);
      virtual void OnFocusLost(const FocusChangeEvent &FEvent);
      virtual void OnKeyPress(const InputEvent &IEvent);
      virtual void OnKeyRelease(const InputEvent &IEvent);
      virtual void OnMousePress(const InputEvent &IEvent);
      virtual void OnMouseRelease(const InputEvent &IEvent);
      virtual void OnMouseScroll(const InputEvent &IEvent);
      virtual void OnMouseOver(const InputEvent &IEvent);
      virtual void OnMouseLeave(const InputEvent &IEvent);
      virtual void OnMouseMove(const InputEvent &IEvent);
      virtual void OnDragBegin(const InputEvent &IEvent);
      virtual void OnDragContinue(const InputEvent &IEvent);
      virtual void OnDragEnd(const InputEvent &IEvent);

      virtual void AddListItem(std::shared_ptr<ListItem> Item, const sf::Vector2f &Position, const sf::Vector2f &Size);
      virtual void DeleteItem(const std::uint32_t ItemID);

      virtual void TickUpdate(const double &delta);
      virtual void Render(std::shared_ptr<sf::RenderTexture> Target);

      virtual void Move(const sf::Vector2f &Delta) override;

      virtual void OpenList();
      virtual void CloseList();

      virtual void Scroll(const sf::Vector2f &Delta);

      virtual ~ListWidget() = default;
    protected:
      ListWidget();

      sf::FloatRect OpenRect = { 0,0,0,0 };

      std::shared_ptr<StickyBar> ScrollingBar;
      std::shared_ptr<sf::Texture> ButtonOverlayTexture;

      //test items
      std::vector<sf::RectangleShape> TestShapes;

      //An extra layer
      std::shared_ptr<UILayer> OptionsLayer; //for stuff like the close button, etc
      bool Hidden = false;

      sf::Vector2f ListSize = { 0, 0 };
      sf::Vector2f ButtonCloseMove = { 0, 0 };

      std::shared_ptr<sf::Font> ListFont;

      std::shared_ptr<TextLabel> OpenCloseButtonText;
      std::shared_ptr<ClickButtonBase> OpenCloseButton;
      sf::Vector2f OpenCloseButtonOffset = { 0, 0 };
      sf::RectangleShape Outline;
      std::vector<std::shared_ptr<ListItem>> Items;

      //Keep track of what the offset is that the list is scrolled by
      sf::Vector2u ListScrollOffset = sf::Vector2u{ 0, 0 };

      //We will just scroll the TextureRect as the list is scrolled, and adjust the offset
      //to get to what the mouse pos should be and do collision testing with that
      sf::IntRect WidgetTextureRect;
    };

  }

}

#endif
