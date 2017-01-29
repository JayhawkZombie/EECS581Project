#ifndef SFENGINE_UI_ALERT_H
#define SFENGINE_UI_ALERT_H

#include "PopupObject.h"

namespace Engine
{

  namespace UI
  {

    static float PaddingLeft = 10.f;
    static float PaddingTop = 10.f;
    static float PaddingRight = 10.f;
    static float PaddingBottom = 5.f;
    static float PaddingButtonBottom = 5.f;

    

    class Alert : public PopupObject
    {
    public:
      static std::shared_ptr<Alert> Create(std::weak_ptr<UILayer> Layer, std::weak_ptr<WidgetHelper> Helper, const std::string &Message, std::shared_ptr<sf::Font> Font, const sf::Vector2f &Position, const sf::Vector2f &Size, const sf::Vector2f &OKButtonSize);

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

      static void ShowAlert(std::shared_ptr<Alert> Message);
      static void HideAlert(std::shared_ptr<Alert> Message);

      ~Alert();
    protected:
      Alert();

      void OnAcknowledged();

      std::shared_ptr<ClickButtonBase> AcknowledgeButton;

      std::shared_ptr<sf::Text> AlertMessage;
      std::shared_ptr<sf::Font> Font;
      std::shared_ptr<TextLabel> AlertText;

      std::shared_ptr<TextLabel> OKText;

    };

  }
  
}

#endif
