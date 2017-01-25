#ifndef SFENGINE_UI_TEXT_LABEL_H
#define SFENGINE_UI_TEXT_LABEL_H

#include "../Widget.h"

namespace Engine
{

  namespace UI
  {
    enum class TextAlignment : std::uint32_t
    {
      LeftJustified = 0,
      RightJustified,
      CenterJustified
    };

    class TextLabel : public WidgetBase
    {
    public:
      static std::shared_ptr<TextLabel> Create(std::shared_ptr<UILayer> Layer, std::shared_ptr<WidgetHelper> ThisHelper, TextAlignment Align, const std::string &String, const sf::Color &Color,
                                               std::shared_ptr<sf::Font> _Font, unsigned int TextSize, const sf::FloatRect &RenderBounds, const sf::Vector2f &Position);

      static std::shared_ptr<TextLabel> Create(std::shared_ptr<WidgetBase> Widget, std::shared_ptr<WidgetHelper> ThisHelper, TextAlignment Align, const std::string &String, const sf::Color &Color,
                                               std::shared_ptr<sf::Font> _Font, unsigned int TextSize, const sf::FloatRect &RenderBounds, const sf::Vector2f &Offset);

      void SetString(const std::string &String);
      std::string GetString() const;

      void SetStringColor(const sf::Color &Color);
      sf::Color GetStringColor() const;

      void SetTextSize(unsigned int Size);
      unsigned int GetTextSize() const;

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

      virtual void Move(const sf::Vector2f &Delta) override;

      virtual void CreateHelper() override;

      virtual void TickUpdate(const double &delta) override;
      virtual void Render(std::shared_ptr<sf::RenderTexture> &Target) override;

      virtual void AlignText();

      sf::FloatRect GetTextGlobalBounds() {
        return RenderString.getGlobalBounds();
      }

      virtual ~TextLabel();
    protected:
      TextLabel();

      std::shared_ptr<WidgetBase> Parent; //The widget containing this text label

      sf::Vector2f TextPosition;
      sf::FloatRect Bounds;
      std::string RawString;
      sf::Text RenderString;
      std::shared_ptr<sf::Font> Font;
      TextAlignment Alignment;
      sf::Color TextColor;
      unsigned int TextSize;
    };

  }

}

#endif
