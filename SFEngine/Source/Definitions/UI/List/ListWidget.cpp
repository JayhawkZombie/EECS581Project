#include "../../../Headers/UI/List/List.h"

#include "../../../Headers/UI/WIdgetHelper.h"

namespace Engine
{

  namespace UI
  {

    std::shared_ptr<ListWidget> ListWidget::Create(std::shared_ptr<WidgetHelper> Helper, const sf::Vector2f &Position, const sf::Vector2f &Size)
    {
      try
      {
        std::shared_ptr<ListWidget> List(new ListWidget);

        List->Creator = Helper;
        Helper->RegisterWidget(List);

        List->Helper = UI::WidgetHelper::Create();
        
        //Create the open/close button
        //and initially set the button to "close" the list
        //  whenever it opens, it'll switch the callback to close it. Whenever it gets closed, it'll switch to
        //  have the CB open it instead
        List->OpenCloseButton = UI::ClickButtonBase::Create(List->Helper, { Position.x + Size.x - 35, Position.y }, { 35, 35 });
        List->OpenCloseButton->MouseReleaseCB = [List]() {List->CloseList(); };

        //just a test appearance
        List->GlobalWidgetBounds.ForceRegion({ Position, Size });

        //Fudge a fake testing appearance
        List->Outline.setPosition(Position);
        List->Outline.setSize(Size);
        List->Outline.setFillColor(sf::Color::Transparent);
        List->Outline.setOutlineColor(sf::Color::Blue);
        List->Outline.setOutlineThickness(-2);

        return List;
      }
      catch (EngineRuntimeError &err)
      {
        err.AddCause(ExceptionCause::ConstructionError);
        err.AddMessage(EXCEPTION_MESSAGE("Failed to create ListWidget"));

        throw;
      }

    }

    ListWidget::ListWidget()
    {
      CanBeDragged = false; //ListWidget cannot be dragged
    }

    void ListWidget::OpenList()
    {

    }

    void ListWidget::CloseList()
    {

    }

    void ListWidget::ConsumeEvent(const InputEvent &IEvent)
    {

    }

    void ListWidget::OnFocusGained(const FocusChangeEvent &FEvent)
    {

    }

    void ListWidget::OnFocusLost(const FocusChangeEvent &FEvent)
    {

    }

    void ListWidget::OnKeyPress(const InputEvent &IEvent)
    {

    }

    void ListWidget::OnKeyRelease(const InputEvent &IEvent)
    {

    }

    void ListWidget::OnMousePress(const InputEvent &IEvent)
    {

    }

    void ListWidget::OnMouseRelease(const InputEvent &IEvent)
    {

    }

    void ListWidget::OnMouseScroll(const InputEvent &IEvent)
    {

    }

    void ListWidget::OnMouseOver(const InputEvent &IEvent)
    {
      Outline.setOutlineColor(sf::Color::Green);
    }

    void ListWidget::OnMouseLeave(const InputEvent &IEvent)
    {
      Outline.setOutlineColor(sf::Color::Blue);
    }

    void ListWidget::OnMouseMove(const InputEvent &IEvent)
    {

    }

    void ListWidget::OnDragBegin(const InputEvent &IEvent)
    {

    }

    void ListWidget::OnDragContinue(const InputEvent &IEvent)
    {

    }

    void ListWidget::OnDragEnd(const InputEvent &IEvent)
    {

    }

    void ListWidget::AddListItem(std::shared_ptr<ListItem> &Item)
    {

    }

    void ListWidget::DeleteItem(const std::uint32_t ItemID)
    {
    
    }

    void ListWidget::TickUpdate(const double &delta)
    {

    }

    void ListWidget::Render(std::shared_ptr<sf::RenderTexture> &Target)
    {

      for (auto & item : Items)
        item->Render(Target);


      Target->draw(Outline);
    }

  }

}
