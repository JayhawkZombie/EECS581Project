#include "../../../Headers/UI/List/List.h"

#include "../../../Headers/UI/Text/TextLabel.h"
#include "../../../Headers/UI/Theme.h"
#include "../../../Headers/UI/UICreationMacros.h"
#include "../../../Headers/UI/WIdgetHelper.h"
namespace Engine
{

  namespace UI
  {

    std::shared_ptr<ListWidget> ListWidget::Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper, const sf::Vector2f & Position, 
                                                   const sf::Vector2f & Size, const sf::Vector2f &MaxDropdownSize, const sf::Vector2f &ItemSize, std::shared_ptr<sf::Font> _Font, 
                                                   std::shared_ptr<sf::Texture> Icons, const Theme & theme)
    {
      if (!ThisLayer.lock() || !ThisLayer.lock()->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer }, EXCEPTION_MESSAGE("Layer is NULL or cannot accept a widget"));

      if (!ThisHelper.lock() || !ThisHelper.lock()->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer }, EXCEPTION_MESSAGE("Helper is NULL or cannot accept a widget"));

      try
      {
        std::shared_ptr<ListWidget> List(new ListWidget);

        List->Helper = ThisHelper.lock();
        List->MyLayer = ThisLayer.lock();
        ThisLayer.lock()->RegisterWidget(List);

        List->ChildHelper = WidgetHelper::Create();
        List->ChildLayer = UILayer::Create(List->ChildHelper);
        List->ButtonsLayer = UILayer::Create(List->ChildHelper);

        assert(List->Helper.lock() && List->MyLayer.lock());
        assert(List->ChildHelper && List->ChildLayer);
        assert(List->ButtonsLayer);

        List->DropDownButton = UI::SimpleToggle::Create(ThisLayer, ThisHelper, { Position.x + Size.x, Position.y }, 
        { Size.y, Size.y }, { Size.y, Size.y }, Icons, "uparrow_medium", "downarrow_medium", false);
        List->ListItemSize.x = Size.x + ItemSize.x;
        List->ListItemSize.y = ItemSize.y;
        List->ListSize.y = 0;
        List->DropDownButton->CheckedCB = [List]() {List->OpenList(); };
        List->DropDownButton->UnCheckedCB = [List]() {List->CloseList(); };
        List->CurrentTextureView.width = __TO_INT__(Size.x);
        List->MaximumDropdownSize = MaxDropdownSize;
        //List->ListItemSize = ItemSize;
        List->SetBGColorNormal(theme.ButtonColorNormal);
        List->SetBGColorHighlighted(theme.ButtonColorHighlighted);
        List->SetBGColorPressed(theme.ButtonColorPressed);
        List->SetBGOutlineColor(theme.ButtonOutlineColorNormal);
        List->SetBGColor(theme.ButtonColorNormal);
        List->SetBGOutlineColorHighlighted(theme.ButtonOutlineColorHighlighted);
        List->SetBGOutlineThickness(-1);
        List->ItemsTexture = std::make_shared<sf::RenderTexture>();
        List->ItemsTexture->create(__INT_FROM_FLOAT__(MaxDropdownSize.x), __INT_FROM_FLOAT__(MaxDropdownSize.y));
        List->ItemsSprite.setTexture(List->ItemsTexture->getTexture());
        List->ItemsSprite.setPosition({ Position.x, Position.y + Size.y });
        List->ChildHelper = WidgetHelper::Create();
        List->ChildLayer = UILayer::Create(List->ChildHelper);
        List->Size = Size;
        List->Position = Position;
        List->BGRect.setFillColor(theme.ButtonColorNormal);
        List->BGRect.setOutlineColor(theme.ButtonOutlineColorNormal);
        List->BGRect.setOutlineThickness(-1);
        List->BGRect.setPosition(Position);
        List->BGRect.setSize(Size);
        List->GlobalWidgetBounds.ForceRegion({ Position, Size });

        List->AddItem("TestItem");
        List->AddItem("TestItem2");
        List->AddItem("TestItem3");

        return List;
      }
      catch (EngineRuntimeError &err)
      {
        err.AddCause({ ExceptionCause::ConstructionError });
        err.AddMessage(EXCEPTION_MESSAGE("Failed to construct ListWidget"));

        throw;
      }
    }

    void ListWidget::ConsumeEvent(const InputEvent & IEvent)
    {
      auto copy = IEvent;
      copy.CurrentMousePosition = IEvent.CurrentMousePosition - static_cast<sf::Vector2i>(sf::Vector2f{ Position.x, Position.y + Size.y });
      copy.PreviousMousePosition = IEvent.PreviousMousePosition - static_cast<sf::Vector2i>(sf::Vector2f{ Position.x, Position.y + Size.y });
      if (IsOpen && ChildLayer->HandleEvent(copy)) {

      }
      else {

      }
    }

    void ListWidget::OnFocusGained(const FocusChangeEvent & FEvent)
    {
    }

    void ListWidget::OnFocusLost(const FocusChangeEvent & FEvent)
    {
    }

    void ListWidget::OnKeyPress(const InputEvent & IEvent)
    {
    }

    void ListWidget::OnKeyRelease(const InputEvent & IEvent)
    {
    }

    void ListWidget::OnMousePress(const InputEvent & IEvent)
    {
      //ChildLayer->HandleEvent(IEvent);
      ConsumeEvent(IEvent);
    }

    void ListWidget::OnMouseRelease(const InputEvent & IEvent)
    {
      //ChildLayer->HandleEvent(IEvent);
      ConsumeEvent(IEvent);
    }

    void ListWidget::OnMouseScroll(const InputEvent & IEvent)
    {
      //ChildLayer->HandleEvent(IEvent);
      ConsumeEvent(IEvent);
    }

    void ListWidget::OnMouseOver(const InputEvent & IEvent)
    {
      //ChildLayer->HandleEvent(IEvent);
      ConsumeEvent(IEvent);
      BGRect.setOutlineColor(BGOutlineColorHighlighted);
    }

    void ListWidget::OnMouseLeave(const InputEvent & IEvent)
    {
      //ChildLayer->HandleEvent(IEvent);
      ConsumeEvent(IEvent);
      BGRect.setOutlineColor(BGOutlineColorNormal);
    }

    void ListWidget::OnMouseMove(const InputEvent & IEvent)
    {
     // ChildLayer->HandleEvent(IEvent);
      ConsumeEvent(IEvent);
    }

    void ListWidget::OnDragBegin(const InputEvent & IEvent)
    {

    }

    void ListWidget::OnDragEnd(const InputEvent & IEvent)
    {
    }

    void ListWidget::OnDragContinue(const InputEvent & IEvent)
    {
    }

    void ListWidget::TickUpdate(const double & delta)
    {
    }

    void ListWidget::Render(std::shared_ptr<sf::RenderTexture> Texture)
    {  
      static sf::IntRect ChildView = { 0,0,0,0 };
      Texture->draw(BGRect);
      /*for (auto & item : Items) {
        item->Render(Texture);
      }*/
      if (IsOpen) {
        ItemsTexture->clear(sf::Color::Transparent);
        ChildLayer->Render(ItemsTexture);
        ItemsTexture->display();
        ItemsSprite.setTextureRect(CurrentTextureView);
        Texture->draw(ItemsSprite);
      }
      //ButtonsLayer->Render(Texture);
      //Texture->draw(ItemsSprite);
    }

    void ListWidget::Move(const sf::Vector2f & Delta)
    {
    }

    void ListWidget::Resize(const sf::Vector2f & Size)
    {
    }

    void ListWidget::ResetAppearance()
    {
    }

    void ListWidget::AddItem(const std::string &ItemText)
    {
      std::shared_ptr<ClickButtonBase> ButtonToAdd;
      sf::Vector2f pos = { 0, ListSize.y };

      MakeButtonWithText(ButtonToAdd, ChildLayer, ChildHelper, pos, ListItemSize, ItemText, TextFont, UI::DefaultDarkTheme);
      auto label = UI::TextLabel::Create(ButtonToAdd, Helper, TextAlignment::CenterJustified, ItemText, UI::DefaultDarkTheme.TextColorNormal, 
                                         TextFont, UI::DefaultDarkTheme.TextSizeSmall, { 0,0,WindowSize.x, WindowSize.y }, { 0,0 });
      ButtonToAdd->SetBGColor(sf::Color(96, 96, 96));
      ButtonToAdd->SetBGColorNormal(sf::Color(96, 96, 96));
      ButtonToAdd->SetBGColorHighlighted(sf::Color(64, 86, 122));
      ButtonToAdd->SetBGColorPressed(sf::Color(36, 49, 71));
      Items.push_back(ButtonToAdd);

      ListSize.y += ListItemSize.y;
      CurrentTextureView.width = Size.x;
      if (ListSize.y < MaximumDropdownSize.y) {
        CurrentTextureView.height = __TO_INT__(ListSize.y);
      }

      std::cerr << "Added button at : " << pos.x << ", " << pos.y << std::endl;
      std::cerr << "ButtonSize: " << ListItemSize.x << " " << ListItemSize.y << std::endl;
      std::cerr << "ListSize: " << ListSize.x << ", " << ListSize.y << std::endl;
      std::cerr << "CurrentListView: " << CurrentTextureView.left << " " << CurrentTextureView.top << " " << CurrentTextureView.width << " " << CurrentTextureView.height << std::endl;
      /*Widget->ChangeHelper(ChildHelper);
      Widget->ChangeLayer(ChildLayer);

      auto size = Widget->GetSize();
      auto pos = Widget->GetPosition();

      sf::Vector2f toPos = { Position.x, Position.y + ListSize.y };
      auto pdiff = toPos - pos;
      ListSize.y += size.y;
      Items.push_back(Widget);
      Widget->Move(pdiff);
      if (ListSize.y < MaximumDropdownSize.y) {
        CurrentTextureView.height = __INT_FROM_FLOAT__(ListSize.y);
      }
      ItemsTexture->create(static_cast<unsigned int>(std::ceil(ListSize.x)), static_cast<unsigned int>(std::ceil(ListSize.y)));*/

  //    float texSizeDiff = TotalRegion.height + Widget->GlobalWidgetBounds.GlobalBounds.height;
  //    sf::FloatRect __bounds = Widget->GlobalWidgetBounds.GlobalBounds;
  //    std::uint32_t NewTexWidth = __UINT_FROM_FLOAT__(Size.x);
  //    std::uint32_t NewTexHeight = __UINT_FROM_FLOAT__(TotalRegion.height) + NewTexWidth;
  //    try {
  //      //ChildLayer->RegisterPremadeWidget(Widget);
  //      ButtonsLayer->RegisterPremadeWidget(UI::ClickButtonBase::Create(ButtonsLayer, ChildHelper, Widget->GetPosition(), Widget->GetSize(), nullptr));
  ///*      if (Items.empty()) {
  //        Items.push_back(UI::ClickButtonBase::Create(ChildLayer, ChildHelper, Widget->GetPosition(), Widget->GetSize(), nullptr));
  //        sf::Vector2f PosDiff = Position - sf::Vector2f(__bounds.left, __bounds.top);
  //        Widget->Move(PosDiff);
  //        Items.back()->Move(PosDiff);
  //      }
  //      else {
  //        Items.push_back(UI::ClickButtonBase::Create(ChildLayer, ChildHelper, Widget->GetPosition(), Widget->GetSize(), nullptr));
  //        sf::FloatRect __bottombounds = Items.back()->GlobalWidgetBounds.GlobalBounds;
  //        sf::Vector2f _posdiff = Position - sf::Vector2f(__bottombounds.left, __bottombounds.top);
  //        Widget->Move(_posdiff);
  //        Items.back()->Move(_posdiff);
  //      }*/
  //    }
  //    catch (EngineRuntimeError &err) {
  //      //Fuck
  //      throw;
  //    }
  //    //Force the item to the bottom of the list
    }

    void ListWidget::ScrollUpOne()
    {
      std::cerr << "Scroll up one" << std::endl;

      float deltaY = 25.f;

      if (CurrentTextureView.top > 0) {
        CurrentTextureView.top += std::min(__TO_FLOAT__(CurrentTextureView.top), deltaY);
      }
    }

    void ListWidget::ScrollDownOne()
    {
      std::cerr << "Scroll down one" << std::endl;

      float deltaY = 25.f;

      float fromBottom = __TO_FLOAT__(CurrentTextureView.top + CurrentTextureView.height) - (ListSize.y);
      if (fromBottom > 0) {
        CurrentTextureView.top -= std::min(fromBottom, deltaY);
      }
    }

    void ListWidget::OpenList()
    {
      IsOpen = true;
      sf::FloatRect Bounds =
      {
        Position.x, Position.y,
        Size.x,
        Size.y + ListSize.y
      };
      GlobalWidgetBounds.ForceRegion(Bounds);
    }

    void ListWidget::CloseList()
    {
      IsOpen = false;
      GlobalWidgetBounds.ForceRegion({ Position, Size });
    }

  }

}
