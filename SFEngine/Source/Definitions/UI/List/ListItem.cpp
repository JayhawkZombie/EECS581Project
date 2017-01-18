#include "../../../Headers/UI/List/List.h"

#include "../../../Headers/UI/WIdgetHelper.h"

namespace Engine
{

  namespace UI
  {
    std::shared_ptr<ListItem> ListItem::Create(std::shared_ptr<WidgetHelper> ThisHelper, std::shared_ptr<ListWidget> Parent, const sf::Vector2f &Position, const sf::Vector2f &Size)
    {
      try
      {
        std::shared_ptr<ListItem> Item(new ListItem);
        ThisHelper->RegisterWidget(Item);
        Item->Creator = ThisHelper;
        Item->ParentList = Parent;

        Item->ParentList->AddListItem(Item);

        //the Position is relative to the parent widget

        return Item;
      }
      catch (EngineRuntimeError &err)
      {
        err.AddCause(ExceptionCause::ConstructionError);
        err.AddMessage(EXCEPTION_MESSAGE("Unable to construct ListItem"));

        throw;
      }
    }

    std::shared_ptr<ListItem> ListItem::Create(std::shared_ptr<ListItem> ToCopy)
    {
      try
      {
        std::shared_ptr<ListItem> Item(new ListItem);


        Item->ButtonFont = ToCopy->ButtonFont;
        Item->ButtonText = ToCopy->ButtonText;
        Item->CanBeDragged = ToCopy->CanBeDragged;
        Item->Children = ToCopy->Children;
        Item->CleanedUpAfterInvalidation = ToCopy->CleanedUpAfterInvalidation;
        Item->Creator = ToCopy->Creator;


        return Item;
      }
      catch (EngineRuntimeError &err)
      {
        err.AddCause(ExceptionCause::ConstructionError);
        err.AddMessage(EXCEPTION_MESSAGE("Cannot create copy of ListItem"));

        throw;
      }


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

    void ListItem::Render(std::shared_ptr<sf::RenderTexture> &Target)
    {

    }

  }

}
