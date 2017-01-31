#ifndef SFENGINE_UI_TEXT_INPUT_H
#define SFENGINE_UI_TEXT_INPUT_H

#include "../Widget.h"
#include "../Buttons/ClickButtonBase.h"

namespace Engine
{

  namespace UI
  {

    class TextInput : public ClickButtonBase
    {
    public:
      static std::shared_ptr<TextInput> Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper, const sf::Vector2f &Position, const sf::Vector2f &Size, std::shared_ptr<sf::Font> _Font, const std::string &DefaultText);

      static bool IsPrintable(const sf::Uint32 &Unicode) {
        if (
          !(Unicode < (UINT)(0x0020)) &&
          !(Unicode > (UINT)(0x007F) && Unicode < (UINT)(0x00A0))
            )
          return true;
        return false;
      }

      static bool IsBackspace(const sf::Uint32 &unicode) {
        return (unicode == (unsigned int)(0x0008));
      }

      static bool IsDelete(const sf::Uint32 &unicode) {
        return (unicode == (unsigned int)(0x007F));
      }

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

      virtual void OnTextEntered(const InputEvent &IEvent) override;

      virtual void SetTexture(std::shared_ptr<sf::Texture> Texture);
      virtual void SetTextureRect(sf::IntRect &Rect);

      virtual void SetBGColorNormal(const sf::Color &Color);
      virtual void SetBGColorHighlighted(const sf::Color &Color);
      virtual void SetBGColorPressed(const sf::Color &Color);

      virtual void SetBGColor(const sf::Color &Color);

      virtual bool WantsTextEnteredEvent() const {
        return true;
      }

      void AlignText();

      virtual ~TextInput() = default;
    protected:
      TextInput();

      std::shared_ptr<sf::Font> Font;
      sf::Text RenderString;
      std::string RawString;

      float AlignedYPos;

      sf::RectangleShape BoundsRect;

      sf::FloatRect PaddedBounds;

      unsigned int TextSize;
      sf::Color TextColor;
    };

  }

}

#endif