#include "../../../Headers/UI/List/List.h"

#include "../../../Headers/UI/WIdgetHelper.h"
#include "../../../Headers/UI/Text/TextLabel.h"
#include "../../../Headers/UI/Theme.h"

namespace Engine
{

  namespace UI
  {

    std::shared_ptr<ListWidget> ListWidget::Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper, std::shared_ptr<sf::Font> Font, const sf::Vector2f &Position, const sf::Vector2f &Size, const sf::Vector2f &ItemSize)
    {
      if (!ThisLayer.lock() || !ThisLayer.lock()->CanAcceptWidget()) 
        throw InvalidObjectException({ ExceptionCause::InvalidContainer, ExceptionCause::ConstructionError },
                                     EXCEPTION_MESSAGE("Given WidgetHelper is NULL or cannot accept a widget"));

      try
      {
        std::shared_ptr<ListWidget> List(new ListWidget);
        List->Helper = ThisHelper.lock();
        List->MyLayer = ThisLayer.lock();
        ThisLayer.lock()->RegisterWidget(List);

        assert(List->Helper.lock() && List->MyLayer.lock());

        List->ChildLayer = UI::UILayer::Create(List->Helper.lock());
        List->OptionsLayer = UI::UILayer::Create(List->Helper.lock());
        List->Position = Position;
        List->Size = Size;
        List->OptionsLayer->LayerRegisterDebugOutputFunction =
          [List](auto ID)
        {
          DEBUG_ONLY std::cerr << "ListWidget::OptionsLayer Registered Item ID : " << ID << std::endl;
        };

        List->ListSize = Size;
        List->ItemFont = Font;
        //Create the open/close button
        //and initially set the button to "close" the list
        //  whenever it opens, it'll switch the callback to close it. Whenever it gets closed, it'll switch to
        //  have the CB open it instead
        sf::Vector2f ButtonPosition;
        sf::Vector2f ButtonSize;

        //auto Button = UI::ClickButtonBase::Create(List->OptionsLayer, { Position.x, Position.y }, { Size.x, 15 });
        //Button->MouseReleaseCB = [List]() {List->CloseList(); };

        sf::FloatRect ButtonBounds = { ButtonPosition, ButtonSize };
        sf::FloatRect ListBounds = { Position, Size };

        sf::FloatRect GlobalBounds;
        GlobalBounds.left = std::min(ButtonBounds.left, ListBounds.left);
        GlobalBounds.top = std::min(ButtonBounds.top, ListBounds.top);
        GlobalBounds.width = std::max(ListBounds.width, ButtonPosition.x + ButtonSize.x - Position.x);
        GlobalBounds.height = std::max(ListBounds.height, ButtonPosition.y + ButtonSize.y - Position.y);

        List->ListFont = Font;

        //just a test appearance
        List->GlobalWidgetBounds.ForceRegion(GlobalBounds);
        List->OpenRect = GlobalBounds;

        //Fudge a fake testing appearance
        List->Outline.setPosition(Position);
        List->Outline.setSize(Size);
        List->Outline.setFillColor(sf::Color(89, 89, 89, 100));
        List->Outline.setOutlineColor(sf::Color::Blue);
        List->Outline.setOutlineThickness(-2);

        //Add some text to the button
        WIDGET_DEBUG_ONLY std::cerr << "ListWidget::Create : Creating OpenCloseButtonText" << std::endl;

        float ScrollBarHeight = 15.f;
        float ScrollVertBarWidth = 3.f;
        float ScrollVertBarHeight = 10.f;

        WIDGET_DEBUG_ONLY std::cerr << "Listwidget::Create : Creating ScollingBar" << std::endl;
        List->ScrollingBar = UI::StickyBar::Create(List->ChildLayer, List->Helper, { Position.x, Position.y + Size.y - ScrollBarHeight }, { Size.x, 35.f }, { ScrollVertBarWidth, ScrollVertBarHeight }, { Size.x, 10.f }, { 50.f, ScrollBarHeight });

        List->ScrollingBar->OnScroll = 
          [List](auto Delta)
        {
          List->Scroll(Delta);
        };

        sf::Vector2f Pos = Position;
        sf::Vector2f Siz = { Size.y - 10.f, Size.y - 10.f };
      

        List->TestShapes.push_back(sf::RectangleShape());
        List->TestShapes.back().setPosition(Pos);
        List->TestShapes.back().setSize(Siz);
        List->TestShapes.back().setFillColor(sf::Color(70, 108, 122, 150));
        List->TestShapes.back().setOutlineColor(sf::Color::White);
        List->TestShapes.back().setOutlineThickness(-1);

        Pos.x += Size.y + 5.f;
        List->TestShapes.push_back(sf::RectangleShape());
        List->TestShapes.back().setPosition(Pos);
        List->TestShapes.back().setSize(Siz);
        List->TestShapes.back().setFillColor(sf::Color(70, 108, 122, 150));
        List->TestShapes.back().setOutlineColor(sf::Color::White);
        List->TestShapes.back().setOutlineThickness(-1);

        return List;
      }
      catch (EngineRuntimeError &err)
      {
        err.AddCause(ExceptionCause::ConstructionError);
        err.AddMessage(EXCEPTION_MESSAGE("Failed to create ListWidget"));

        throw;
      }

    }

    void ListWidget::AddListItem(const std::string &String, const sf::Color &NormalBGColor)
    {

      //the position is relative to the upper left-hand corner of ourselves
      sf::Vector2f RealPos = { GlobalWidgetBounds.GlobalBounds.left + Position.x, GlobalWidgetBounds.GlobalBounds.top + Position.y };
      
      auto Item = UI::ClickButtonBase::Create(OptionsLayer, Helper.lock(), { Position.x, OccupiedSpace.top + OccupiedSpace.height + 3 }, ListItemSize, nullptr);
      auto label = UI::TextLabel::Create(Item, Helper.lock(), TextAlignment::CenterJustified, String, DefaultDarkTheme.TextColorNormal, ItemFont, DefaultDarkTheme.TextSizeSmall, { 0,0,1000,1000 }, { 0,0 });
      //Force the widget to exist within this space
      Item->GlobalWidgetBounds.ForceRegion({ RealPos, Size });

      auto bounds = Item->GlobalWidgetBounds.GlobalBounds;
      OccupiedSpace.height += 3 + ListItemSize.y;

      Items.push_back(Item);
      //Make test appearance for it
      ChildLayer->RegisterWidget(Item);

      //Items.push_back(Item);
    }

    ListWidget::ListWidget()
    {
      CanBeDragged = false; //ListWidget cannot be dragged
    }

    void ListWidget::OpenList()
    {
      DEBUG_ONLY std::cerr << "Showing ListWidget" << std::endl;

      ScrollingBar->Move(ButtonCloseMove);
      ScrollingBar->SetIsHidden(false);

      GlobalWidgetBounds.ForceRegion(OpenRect);

      Hidden = false;
    }

    void ListWidget::CloseList()
    {
      //Just hide the widget
      DEBUG_ONLY std::cerr << "Hiding ListWidget" << std::endl;

      OpenRect = GlobalWidgetBounds.GlobalBounds;

      ScrollingBar->Move(-ButtonCloseMove);
      ScrollingBar->SetIsHidden(true);

      Hidden = true;
    }

    void ListWidget::Scroll(const sf::Vector2f & Delta)
    {
      for (auto & item : TestShapes)
        item.move(Delta);
    }

    void ListWidget::Move(const sf::Vector2f &Delta)
    {
      OptionsLayer->Move(Delta);

      WidgetBase::Move(Delta);
    }

    void ListWidget::ConsumeEvent(const InputEvent &IEvent)
    {
      if (OptionsLayer->HandleEvent(IEvent)) {
        
      }
      else if (!Hidden && ChildLayer->HandleEvent(IEvent)) {
        //some crap
        
      }

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
      DEBUG_ONLY std::cerr << "ListWidget::MousePress" << std::endl;

      ConsumeEvent(IEvent);

    }

    void ListWidget::OnMouseRelease(const InputEvent &IEvent)
    {
      //ConsumeEvent(IEvent);
    }

    void ListWidget::OnMouseScroll(const InputEvent &IEvent)
    {
      //ConsumeEvent(IEvent);
    }

    void ListWidget::OnMouseOver(const InputEvent &IEvent)
    {
      Outline.setOutlineColor(sf::Color::Green);
      ConsumeEvent(IEvent);
    }

    void ListWidget::OnMouseLeave(const InputEvent &IEvent)
    {
      Outline.setOutlineColor(sf::Color::Blue);
      ConsumeEvent(IEvent);
    }

    void ListWidget::OnMouseMove(const InputEvent &IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void ListWidget::OnDragBegin(const InputEvent &IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void ListWidget::OnDragContinue(const InputEvent &IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void ListWidget::OnDragEnd(const InputEvent &IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void ListWidget::DeleteItem(const std::uint32_t ItemID)
    {
      
    }

    void ListWidget::TickUpdate(const double &delta)
    {

    }

    void ListWidget::Render(std::shared_ptr<sf::RenderTexture> Target)
    {

      if (!Hidden) {
        auto View = MakeView(GlobalWidgetBounds.GlobalBounds);

        Target->setView(View);
        
        for (auto & item : Items)
          item->Render(Target);

        ChildLayer->Render(Target);
        //OpenCloseButton->Render(Target);

        for (auto & test : TestShapes)
          Target->draw(test);

        Target->draw(Outline);

        Target->setView(Target->getDefaultView());
      }

      OptionsLayer->Render(Target);
    }

  }

}
