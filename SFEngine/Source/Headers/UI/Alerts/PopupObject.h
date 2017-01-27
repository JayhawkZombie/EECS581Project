#ifndef SFENGINE_UI_POPUP_OBJECT_H
#define SFENGINE_UI_POPUP_OBJECT_H

#include "../Widget.h"

namespace Engine
{

  namespace UI
  {
    
    class ClickButtonBase;
    class TextLabel;

    class PopupObject : public WidgetBase
    {
    public:
      static std::shared_ptr<PopupObject> Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> Helper, const sf::Vector2f &Size, const sf::Vector2f &Position, std::shared_ptr<sf::Font> Font);

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
      virtual void Render(std::shared_ptr<sf::RenderTexture> &Texture) override;
      virtual void Move(const sf::Vector2f &Delta) override;

      static void ShowPopup(std::shared_ptr<PopupObject> Popup);
      static void ClosePopup(std::shared_ptr<PopupObject> Popup);

      ~PopupObject();
    protected:
      PopupObject();

      bool IsOnAlert = false;

      void CloseWasPressed();

      std::shared_ptr<WidgetHelper> ChildHelper;
      std::shared_ptr<sf::Font> Font;

      sf::RectangleShape BGRect;

      //std::shared_ptr<ClickButtonBase> OKButton;
      //std::shared_ptr<ClickButtonBase> CancelButton;

      //std::shared_ptr<TextLabel> OKLabel;
      //std::shared_ptr<TextLabel> CancelLabel;

      sf::Text SampleText;

      sf::Vector2f Position;
      sf::Vector2f Size;



    };

  }

}

#endif
