#ifndef SFENGINE_UI_LIST_H
#define SFENGINE_UI_LIST_H

#include "../Widget.h"


#include "../Buttons/ClickButtonBase.h"

namespace Engine
{

  namespace UI
  {
    class ListWidget;
    class ClickButtonBase;

    class ListItem : public ClickButtonBase
    {
    public:
      static std::shared_ptr<ListItem> Create(std::shared_ptr<WidgetHelper> Helper, std::shared_ptr<ListWidget> Parent, const sf::Vector2f &Position, const sf::Vector2f &Size);
      static std::shared_ptr<ListItem> Create(std::shared_ptr<ListItem> ToCopy);

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
      virtual void Render(std::shared_ptr<sf::RenderTexture> &Target);

      virtual ~ListItem() = default;
    protected:
      ListItem();

      sf::RectangleShape Outline;

      std::shared_ptr<ListWidget> ParentList;
    };

    class ListWidget : public WidgetBase
    {
    public:
      static std::shared_ptr<ListWidget> Create(std::shared_ptr<WidgetHelper> Helper, const sf::Vector2f &Position, const sf::Vector2f &Size);
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

      virtual void AddListItem(std::shared_ptr<ListItem> &Item);
      virtual void DeleteItem(const std::uint32_t ItemID);

      virtual void TickUpdate(const double &delta);
      virtual void Render(std::shared_ptr<sf::RenderTexture> &Target);

      virtual void OpenList();
      virtual void CloseList();

      virtual ~ListWidget() = default;
    protected:
      ListWidget();

      std::shared_ptr<ClickButtonBase> OpenCloseButton;
      sf::RectangleShape Outline;
      std::vector<std::shared_ptr<ListItem>> Items;
    };

  }

}

#endif
