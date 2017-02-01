#ifndef SFENGINE_UI_SPINNER_H
#define SFENGINE_UI_SPINNER_H

#include "TextInput.h"

namespace Engine
{

  namespace UI
  {

    class IntSpinner : public WidgetBase
    {
    public:
      static std::shared_ptr<IntSpinner> Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper, const sf::Vector2f &Position, const sf::Vector2f &Size, std::shared_ptr<sf::Font> _Font, std::shared_ptr<sf::Texture> IconTexture);

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

      virtual void ChangeData(std::int32_t delta);

      std::int32_t GetValue() const {
        return Data;
      }

      virtual ~IntSpinner() = default;
    protected:
      bool CanInteract = false;
      IntSpinner() = default;

      void ValueChanged(const std::string &data);

      std::shared_ptr<TextInput> InputArea;
      std::shared_ptr<ClickButtonBase> UpButton;
      std::shared_ptr<ClickButtonBase> DownButton;

      std::int32_t Data = 0;

      std::shared_ptr<sf::Font> DataFont;
    };

  }

}

#endif
