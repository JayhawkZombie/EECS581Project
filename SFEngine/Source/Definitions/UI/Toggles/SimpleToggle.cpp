#include "../../../Headers/UI/Toggles/SimpleToggle.h"
#include "../../../Headers/UI/WIdgetHelper.h"
#include "../../../Headers/UI/UIIconSheet.h"
#include "../../../Headers/UI/Theme.h"
namespace Engine
{

  namespace UI
  {

    std::shared_ptr<SimpleToggle> SimpleToggle::Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper, const sf::Vector2f &Position, 
                                                       const sf::Vector2f &Size, const sf::Vector2f &CheckSize, std::shared_ptr<sf::Texture> Icons, const std::string &toggle_icon, const std::string &toggle_icon_off, bool DefaultChecked)
    {
      if (!ThisLayer.lock() || !ThisLayer.lock()->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer }, EXCEPTION_MESSAGE("Layer is NULL or cannot accept a widget"));

      if (!ThisHelper.lock() || !ThisHelper.lock()->CanAcceptWidget())
        throw InvalidObjectException({ ExceptionCause::InvalidContainer }, EXCEPTION_MESSAGE("Helper is NULL or cannot accept a widget"));

      try
      {
        assert(ThisLayer.lock() && ThisHelper.lock());

        std::shared_ptr<SimpleToggle> Toggle(new SimpleToggle);
        Toggle->Position = Position;
        Toggle->Size = Size;
        Toggle->MyLayer = ThisLayer.lock();
        Toggle->Helper = ThisHelper.lock();

        ThisLayer.lock()->RegisterWidget(Toggle);

        //Set up the theme
        Toggle->IconSheetTexture = Icons;
        Toggle->IconSheetFrame = IconSheetRects[toggle_icon];
        Toggle->FrameOff = IconSheetRects[toggle_icon_off];
        Toggle->FrameOn = IconSheetRects[toggle_icon];
        Toggle->BGRect.setPosition(Position);
        Toggle->BGRect.setSize(Size);
        Toggle->SetBGColor(DefaultDarkTheme.CheckBoxBackgroundColor);
        Toggle->SetBGOutlineColor(DefaultDarkTheme.ButtonOutlineColorNormal);
        Toggle->SetBGOutlineColorHighlighted(DefaultDarkTheme.ButtonOutlineColorHighlighted);
        Toggle->SetBGColorHighlighted(DefaultDarkTheme.ButtonColorHighlighted);
        Toggle->SetBGColorPressed(DefaultDarkTheme.ButtonColorPressed);
        Toggle->BGRect.setOutlineThickness(-1);
        Toggle->BGColorNormal = DefaultDarkTheme.CheckBoxBackgroundColor;

        //Align the check texture with the box it has
        float xDiff = Size.x - CheckSize.x;
        float yDiff = Size.y - CheckSize.y;

        Toggle->Check.setPosition(Position);
        
        Toggle->Check.setTexture(Icons.get());
        if (DefaultChecked)
          Toggle->Check.setTextureRect(Toggle->FrameOn);
        else
          Toggle->Check.setTextureRect(Toggle->FrameOff);

        Toggle->Check.setSize(Size);

        Toggle->GlobalWidgetBounds.ForceRegion({ Position, Size });
        Toggle->IsChecked = DefaultChecked;
        Toggle->IsDefaultChecked = DefaultChecked;
        Toggle->CanBeDragged = false;

        return Toggle;
      }
      catch (EngineRuntimeError &err)
      {
        err.AddCause(ExceptionCause::ConstructionError);
        err.AddMessage(EXCEPTION_MESSAGE("Failed to create SimpleToggle"));

        throw;
      }

    }

    SimpleToggle::SimpleToggle()
      : ClickButtonBase()
    {
    }

    void SimpleToggle::ConsumeEvent(const InputEvent & IEvent)
    {
    }

    void SimpleToggle::OnFocusGained(const FocusChangeEvent & FEvent)
    {
    }

    void SimpleToggle::OnFocusLost(const FocusChangeEvent & FEvent)
    {
    }

    void SimpleToggle::OnKeyPress(const InputEvent & IEvent)
    {
    }

    void SimpleToggle::OnKeyRelease(const InputEvent & IEvent)
    {
    }

    void SimpleToggle::OnMousePress(const InputEvent & IEvent)
    {
      BGRect.setFillColor(BGColorPressed);
      BGRect.setOutlineColor(BGOutlineColorHighlighted);
    }

    void SimpleToggle::OnMouseRelease(const InputEvent & IEvent)
    {
      BGRect.setFillColor(BGColorNormal);
      BGRect.setOutlineColor(BGOutlineColorNormal);

      if (!IsChecked) {
        IsChecked = true;
        CheckedCB();
        std::cerr << "CheckBox::IsChecked = true" << std::endl;
        BGRect.setFillColor(BGColorNormal);
        Check.setTextureRect(FrameOn);
      }
      else {
        IsChecked = false;
        UnCheckedCB();
        std::cerr << "CheckBox::IsChecked = false" << std::endl;
        BGRect.setFillColor(BGColorNormal);
        Check.setTextureRect(FrameOff);
      }
    }

    void SimpleToggle::OnMouseScroll(const InputEvent & IEvent)
    {
    }

    void SimpleToggle::OnMouseOver(const InputEvent & IEvent)
    {
      BGRect.setFillColor(BGColorHighlighted);
      BGRect.setOutlineColor(BGOutlineColorHighlighted);
    }

    void SimpleToggle::OnMouseLeave(const InputEvent & IEvent)
    {
      BGRect.setFillColor(BGColorNormal);
      BGRect.setOutlineColor(BGOutlineColorNormal);
    }

    void SimpleToggle::OnMouseMove(const InputEvent & IEvent)
    {
    }

    void SimpleToggle::OnDragBegin(const InputEvent & IEvent)
    {
    }

    void SimpleToggle::OnDragEnd(const InputEvent & IEvent)
    {
    }

    void SimpleToggle::OnDragContinue(const InputEvent & IEvent)
    {
    }

    void SimpleToggle::TickUpdate(const double & delta)
    {
    }

    void SimpleToggle::Render(std::shared_ptr<sf::RenderTexture> Texture)
    {
      //auto view = MakeView(GlobalWidgetBounds.GlobalBounds);
      //auto oldview = Texture->getView();

      Texture->draw(BGRect);
      
      Texture->draw(Check);

      for (auto & label : TextLabels)
        label->Render(Texture);

      //Texture->setView(oldview);
    }

    void SimpleToggle::Move(const sf::Vector2f & Delta)
    {
    }

    void SimpleToggle::Resize(const sf::Vector2f & Size)
    {
    }

    void SimpleToggle::ResetAppearance()
    {
    }

    void SimpleToggle::SetBGColorNormal(const sf::Color & Color)
    {
      BGColorNormal = Color;
      BGRect.setFillColor(Color);
    }

    void SimpleToggle::SetBGColorHighlighted(const sf::Color & Color)
    {
      BGColorHighlighted = Color;
    }

    void SimpleToggle::SetBGColorPressed(const sf::Color & Color)
    {
      BGColorPressed = Color;
    }

    void SimpleToggle::SetBGColor(const sf::Color & Color)
    {
      BGColor = Color;
      BGRect.setFillColor(Color);
    }

    void SimpleToggle::AlignTextLabel()
    {
      //for (auto & label : TextLabels) {
      //  label->Move({ label->GetTextGlobalBounds().width + 10, 0 });
      //}
    }

    void SimpleToggle::AddTextLabel(std::shared_ptr<TextLabel> Label)
    {
      //figure out what the new bounds would need to be
      sf::FloatRect Bounds = GlobalWidgetBounds.GlobalBounds;
      sf::FloatRect TextBounds = Label->GetTextGlobalBounds();
      float xDiff = std::abs(Bounds.width - TextBounds.width);
      float yDiff = std::abs(Bounds.height - TextBounds.height);
      
      sf::FloatRect NewBounds =
      {
        Bounds.left - TextBounds.width - 10, Bounds.top, Bounds.width + TextBounds.width, Bounds.height
      };

      sf::Vector2f LabelPosDelta = { Bounds.left - (Bounds.left - TextBounds.width - 10), Bounds.top };

      Label->SetPosition({Position.x - TextBounds.width - 10, Position.y + (yDiff / 2.f)});
    
      //Label->GlobalWidgetBounds.ForceRegion(NewBounds);
      //GlobalWidgetBounds.ForceRegion(NewBounds);
      TextLabels.push_back(Label);
    }

  }

}
