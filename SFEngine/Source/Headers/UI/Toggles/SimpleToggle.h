#ifndef SFENGINE_UI_SIMPLE_TOGGLE_H
#define SFENGINE_UI_SIMPLE_TOGGLE_H

#include "../Buttons/ClickButtonBase.h"

namespace Engine
{

  namespace UI
  {

    class SimpleToggle : public ClickButtonBase
    {
    public:
      static std::shared_ptr<SimpleToggle> Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper, const sf::Vector2f &Position, const sf::Vector2f &Size, 
                                                  const sf::Vector2f &CheckSize, std::shared_ptr<sf::Texture> Icons, const std::string &toggle_icon_on, const std::string &toggle_icon_off, bool DefaultChecked = false);

      virtual void ConsumeEvent(const InputEvent &IEvent) override;
      virtual void OnFocusGained(const FocusChangeEvent &FEvent) override;
      virtual void OnFocusLost(const FocusChangeEvent &FEvent) override;
      virtual void OnKeyPress(const InputEvent &IEvent) override;
      virtual void OnKeyRelease(const InputEvent &IEvent) override;
      virtual void OnMousePress(const InputEvent &IEvent) override;
      virtual void OnMouseRelease(const InputEvent &IEvent) override;
      virtual void OnMouseScroll(const InputEvent &IEvent) override;
      virtual void OnMouseOver(const InputEvent &IEvent) override;
      virtual void OnMouseLeave(const InputEvent &IEvent) override;
      virtual void OnMouseMove(const InputEvent &IEvent) override;
      virtual void OnDragBegin(const InputEvent &IEvent) override;
      virtual void OnDragEnd(const InputEvent &IEvent) override;
      virtual void OnDragContinue(const InputEvent &IEvent) override;
      virtual void TickUpdate(const double &delta) override;
      virtual void Render(std::shared_ptr<sf::RenderTexture> Texture) override;
      virtual void Move(const sf::Vector2f &Delta) override;
      virtual void Resize(const sf::Vector2f &Size) override;
      virtual void ResetAppearance() override;
      virtual void SetBGColorNormal(const sf::Color &Color) override;
      virtual void SetBGColorHighlighted(const sf::Color &Color) override;
      virtual void SetBGColorPressed(const sf::Color &Color) override;
      virtual void SetBGColor(const sf::Color &Color) override;
      virtual void AddTextLabel(std::shared_ptr<TextLabel> Label) override;
      virtual void AlignTextLabel();


      std::function<void(void)> CheckedCB = []() {};
      std::function<void(void)> UnCheckedCB = []() {};

      virtual ~SimpleToggle() = default;
    protected:
      SimpleToggle();

      sf::RectangleShape Check;
      sf::IntRect FrameOn;
      sf::IntRect FrameOff;

      bool IsChecked;
      bool IsDefaultChecked;
    };

  }

}

#endif
