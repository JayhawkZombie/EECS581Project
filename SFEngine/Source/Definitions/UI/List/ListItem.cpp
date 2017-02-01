#include "../../../Headers/UI/List/List.h"

#include "../../../Headers/UI/WIdgetHelper.h"

namespace Engine
{

  namespace UI
  {
    std::shared_ptr<ListItem> ListItem::Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper, std::weak_ptr<ListWidget> Parent, const sf::Vector2f &Position, const sf::Vector2f &Size)
    {
      try
      {
        std::shared_ptr<ListItem> Item(new ListItem);
        Item->MyLayer = ThisLayer.lock();
        Item->ParentList = Parent.lock();
        Item->Helper = ThisHelper.lock();
        ThisLayer.lock()->RegisterWidget(Item);

        assert(Item->MyLayer.lock() && Item->ParentList.lock() && Item->Helper.lock());

        //The ListWidget should take care of placing us properly
        //Item->ParentList.lock()->AddListItem(Item, Position, Size);

        return Item;
      }
      catch (EngineRuntimeError &err)
      {
        err.AddCause(ExceptionCause::ConstructionError);
        err.AddMessage(EXCEPTION_MESSAGE("Unable to construct ListItem"));

        throw;
      }
    }

    std::shared_ptr<ListItem> ListItem::Create(std::weak_ptr<ListItem> ToCopy)
    {
      try
      {
        std::shared_ptr<ListItem> Item(new ListItem);


        Item->ButtonFont = ToCopy.lock()->ButtonFont;
        Item->ButtonText = ToCopy.lock()->ButtonText;
        Item->CanBeDragged = ToCopy.lock()->CanBeDragged;
        Item->Children = ToCopy.lock()->Children;
        Item->CleanedUpAfterInvalidation = ToCopy.lock()->CleanedUpAfterInvalidation;
        Item->MyLayer = ToCopy.lock()->MyLayer;


        return Item;
      }
      catch (EngineRuntimeError &err)
      {
        err.AddCause(ExceptionCause::ConstructionError);
        err.AddMessage(EXCEPTION_MESSAGE("Cannot create copy of ListItem"));

        throw;
      }


    }

    void ListItem::Move(const sf::Vector2f &Delta)
    {
      ClickButtonBase::Move(Delta);

    }


    ListItem::ListItem()
    {

    }

    void ListItem::ConsumeEvent(const InputEvent &IEvent)
    {

    }

    void ListItem::OnFocusGained(const FocusChangeEvent &FEvent)
    {

    }

    void ListItem::OnFocusLost(const FocusChangeEvent &FEvent)
    {

    }

    void ListItem::OnKeyPress(const InputEvent &IEvent)
    {

    }

    void ListItem::OnKeyRelease(const InputEvent &IEvent)
    {

    }

    void ListItem::OnMousePress(const InputEvent &IEvent)
    {

    }

    void ListItem::OnMouseRelease(const InputEvent &IEvent)
    {

    }

    void ListItem::OnMouseScroll(const InputEvent &IEvent)
    {

    }

    void ListItem::OnMouseOver(const InputEvent &IEvent)
    {

    }

    void ListItem::OnMouseLeave(const InputEvent &IEvent)
    {

    }

    void ListItem::OnMouseMove(const InputEvent &IEvent)
    {

    }

    void ListItem::OnDragBegin(const InputEvent &IEvent)
    {

    }

    void ListItem::OnDragContinue(const InputEvent &IEvent)
    {

    }

    void ListItem::OnDragEnd(const InputEvent &IEvent)
    {

    }

    void ListItem::TickUpdate(const double &delta)
    {

    }

    void ListItem::Render(std::shared_ptr<sf::RenderTexture> Target)
    {

    }

  }

}
