#include "../../../Headers/UI/List/List.h"

#include "../../../Headers/UI/Text/TextLabel.h"
#include "../../../Headers/UI/Theme.h"

#include "../../../Headers/UI/WIdgetHelper.h"
namespace Engine
{

  namespace UI
  {

    std::shared_ptr<ListWidget> ListWidget::Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper, const sf::Vector2f & Position, const sf::Vector2f & Size, const Theme & theme)
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

        List->CurrentTextureView = { 0, 0, __INT_FROM_FLOAT__(Size.x), __INT_FROM_FLOAT__(Size.y)};
        List->TotalVisibleArea = { 0, 0, __TO_FLOAT__(Size.x), __TO_FLOAT__(Size.y) }; 
        
        List->SetBGColorNormal(theme.ButtonColorNormal);
        List->SetBGColorHighlighted(theme.ButtonColorHighlighted);
        List->SetBGColorPressed(theme.ButtonColorPressed);
        List->SetBGOutlineColor(theme.ButtonOutlineColorNormal);
        List->SetBGColor(theme.ButtonColorNormal);
        List->SetBGOutlineColorHighlighted(theme.ButtonOutlineColorHighlighted);
        List->SetBGOutlineThickness(-1);
        List->ItemsTexture = std::make_shared<sf::RenderTexture>();
        List->ItemsTexture->create(__INT_FROM_FLOAT__(Size.x), __INT_FROM_FLOAT__(Size.y));
        List->ItemsSprite.setTexture(List->ItemsTexture->getTexture());
        List->ChildHelper = WidgetHelper::Create();
        List->ChildLayer = UILayer::Create(List->ChildHelper);

        List->BGRect.setFillColor(theme.ButtonColorNormal);
        List->BGRect.setOutlineColor(theme.ButtonOutlineColorNormal);
        List->BGRect.setOutlineThickness(-1);
        List->BGRect.setPosition(Position);
        List->BGRect.setSize(Size);

        List->GlobalWidgetBounds.ForceRegion({ Position, Size });

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
      //ButtonsLayer->HandleEvent(IEvent);
      //std::cerr << "\n\nListWidget::ConsumEvent\n\n" << std::endl;
      if (ChildLayer->HandleEvent(IEvent)) {

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
      Texture->draw(BGRect);
      /*for (auto & item : Items) {
        item->Render(Texture);
      }*/
      ChildLayer->Render(Texture);
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

    void ListWidget::AddItem(std::shared_ptr<WidgetBase> Widget)
    {
      Widget->ChangeHelper(ChildHelper);
      Widget->ChangeLayer(ChildLayer);
      BottomItem++;
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

      ChildLayer->Move({ 0, deltaY });

      CurrentTextureView.top += deltaY;
    }

    //void ListWidget::ScrollToTop()
    //{
    //  ScrollOffset = { 0, 0 };
    //  TopItem = 0;
    //  CurrentTextureView = { 0, 0, __INT_FROM_FLOAT__(Size.x), __INT_FROM_FLOAT__(Size.y) };
    //}

    //void ListWidget::ScrollToBottom()
    //{
    //  //We have moved the entirty of the way down (so the height of the TotalRegion - the list's height
    //  ScrollOffset.y = TotalRegion.height - Size.y;

    //}

    void ListWidget::ScrollDownOne()
    {
      std::cerr << "Scroll down one" << std::endl;

      float deltaY = 25.f;

      ChildLayer->Move({ 0, -deltaY });

      CurrentTextureView.top += deltaY;

      //if (TopItem < Items.size() && BottomItem < Items.size() - 1) {
      //  TopItem++;
      //  BottomItem++;
      //  float deltaY = Items[TopItem]->GlobalWidgetBounds.GlobalBounds.height;

      //  for (auto & item : Items)
      //    item->Move({ 0, -deltaY });
      //}
    }

  }

}
