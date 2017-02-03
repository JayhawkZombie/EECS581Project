#include "../../../Headers/UI/Game/LevelWidget.h"
#include "../../../Headers/UI/WIdgetHelper.h"

#ifdef WITH_EDITOR

namespace Engine
{

  namespace UI
  {

    std::shared_ptr<LevelWidget> LevelWidget::Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper, const sf::Vector2f &Position, const sf::Vector2f &Size, std::shared_ptr<sf::Font> _Font)
    {

      if (!ThisLayer.lock() || !ThisLayer.lock()->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer }, EXCEPTION_MESSAGE("Layer is NULL or cannot accept a widget"));

      if (!ThisHelper.lock() || !ThisHelper.lock()->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer }, EXCEPTION_MESSAGE("Helper is NULL or cannot accept a widget"));

      try
      {
        std::shared_ptr<LevelWidget> Level(new LevelWidget);

        Level->ChildHelper = UI::WidgetHelper::Create();
        Level->ChildLayer = UILayer::Create(Level->ChildHelper);
        Level->MyLayer = ThisLayer.lock();
        Level->Helper = ThisHelper.lock();

        assert(Level && Level->MyLayer.lock() && Level->Helper.lock());

        Level->BGRect.setFillColor(sf::Color::Black);
        Level->SetBGColor(sf::Color::Black);
        Level->SetBGColorHighlighted(sf::Color(38, 38, 38));
        Level->SetBGColorNormal(sf::Color::Black);
        Level->SetBGColorPressed(sf::Color::Black);
        Level->SetBGOutlineColor(sf::Color(142, 142, 142));
        Level->SetBGOutlineColorHighlighted(sf::Color(186, 186, 186));
        Level->SetBGOutlineThickness(-1);
        Level->BGRect.setPosition(Position);
        Level->BGRect.setSize(Size);
        Level->BGRect.setFillColor(Level->BGColorNormal);
        Level->BGRect.setOutlineColor(Level->BGOutlineColorNormal);

        Level->GlobalWidgetBounds.ForceRegion({ Position, Size });

        return Level;
      }
      catch (EngineRuntimeError &err)
      {
        throw;
      }

    }

    void LevelWidget::GenerateEmptyLevel(std::uint32_t NumTilesWide, std::uint32_t NumTilesHigh)
    {
    }

    void LevelWidget::ShowGridLines(bool show)
    {
    }

    void LevelWidget::ConsumeEvent(const InputEvent & IEvent)
    {
    }

    void LevelWidget::OnFocusGained(const FocusChangeEvent & FEvent)
    {
    }

    void LevelWidget::OnFocusLost(const FocusChangeEvent & FEvent)
    {
    }

    void LevelWidget::OnKeyPress(const InputEvent & IEvent)
    {
    }

    void LevelWidget::OnKeyRelease(const InputEvent & IEvent)
    {
    }

    void LevelWidget::OnMousePress(const InputEvent & IEvent)
    {
    }

    void LevelWidget::OnMouseRelease(const InputEvent & IEvent)
    {
    }

    void LevelWidget::OnMouseScroll(const InputEvent & IEvent)
    {
    }

    void LevelWidget::OnMouseOver(const InputEvent & IEvent)
    {
    }

    void LevelWidget::OnMouseLeave(const InputEvent & IEvent)
    {
    }

    void LevelWidget::OnMouseMove(const InputEvent & IEvent)
    {
    }

    void LevelWidget::OnDragBegin(const InputEvent & IEvent)
    {
    }

    void LevelWidget::OnDragEnd(const InputEvent & IEvent)
    {
    }

    void LevelWidget::OnDragContinue(const InputEvent & IEvent)
    {
    }

    void LevelWidget::TickUpdate(const double & delta)
    {
    }

    void LevelWidget::Render(std::shared_ptr<sf::RenderTexture> Texture)
    {
    }

    void LevelWidget::Move(const sf::Vector2f & Delta)
    {
    }

    void LevelWidget::Resize(const sf::Vector2f & Size)
    {
    }

    void LevelWidget::ResetAppearance()
    {
    }

    LevelWidget::LevelWidget()
    {

    }

  }

}

#endif

