#include "ComboBox.h"
#include "../WIdgetHelper.h"
#include "../Text/TextLabel.h"
#include "../Theme.h"
#include "../UIIconSheet.h"

namespace Engine
{

  namespace UI
  {

    class NumericComboBox : public ComboBox
    {
    public:
      static std::shared_ptr<NumericComboBox> Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper,
                                                              const sf::Vector2f & Position, const sf::Vector2f & TextAreaSize, const sf::Vector2f & ButtonsSize, const int &Delta, const int &InitialValue,
                                                              std::shared_ptr<sf::Font> _Font, std::shared_ptr<sf::Texture> IconTexture);

      std::uint32_t GetValue() const {
        return CurrentValue;
      }

      void SetValue(const std::uint32_t &val) {
        CurrentValue = val;
      }

      virtual void OnUpButtonPressed() override;
      virtual void OnDownButtonPressed() override;
      virtual void OnUpButtonReleased() override;
      virtual void OnDownButtonReleased() override;
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
      virtual void OnDragContinue(const InputEvent &IEvent) override;
      virtual void OnDragEnd(const InputEvent &IEvent) override;

      virtual void Render(std::shared_ptr<sf::RenderTexture> Texture) override {
        Texture->draw(BGRect);
        
        UpButton->Render(Texture);
        DownButton->Render(Texture);

        for (auto & label : TextLabels)
          label->Render(Texture);
      }

      virtual ~NumericComboBox() = default;
    protected:
      NumericComboBox() = default;

      std::shared_ptr<TextLabel> ValueText;
      std::shared_ptr<sf::Font> Font;

      int ValueDelta;
      int CurrentValue;
    };

  }

}
