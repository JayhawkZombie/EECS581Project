#ifndef SFENGINE_UI_BUTTONBASE_H
#define SFENGINE_UI_BUTTONBASE_H


#include "../Widget.h"

namespace Engine
{

  namespace UI
  {

    enum class ButtonPlacement : std::uint32_t
    {
      TopLeft = 0,
      TopCenter,
      TopRight,
      LeftCenter,
      RightCenter,
      BottomLeft,
      BottomRight,
      BottomCenter
    };

    class ButtonBase : public WidgetBase
    {
    public:
      EDITOR_FRIEND

      friend class WidgetHelper;

      //assign the WidgetHelper that created this object
      //widgets CANNOT be created without this **ie DO NOT create a class that constructs the widget without this**
      static std::shared_ptr<ButtonBase> Create(std::weak_ptr<UILayer> ThisLayer, std::weak_ptr<WidgetHelper> ThisHelper);

      /**
      * Base level event handlers
      */
      virtual void ConsumeEvent(const InputEvent &event) override;
      virtual void OnFocusGained(const FocusChangeEvent &event) override;
      virtual void OnFocusLost(const FocusChangeEvent &event) override;
      virtual void OnKeyPress(const InputEvent &event) override;
      virtual void OnKeyRelease(const InputEvent &event) override;
      virtual void OnMousePress(const InputEvent &event) override;
      virtual void OnMouseRelease(const InputEvent &event) override;
      virtual void OnMouseScroll(const InputEvent &event) override;
      virtual void OnMouseOver(const InputEvent &event) override;
      virtual void OnMouseLeave(const InputEvent &event) override;
      virtual void OnMouseMove(const InputEvent &event) override;
      virtual void OnDragBegin(const InputEvent &event) override;
      virtual void OnDragContinue(const InputEvent &IEvent) override;
      virtual void OnDragEnd(const InputEvent &event) override;
      virtual void TickUpdate(const double &delta) override;
      virtual void Render(std::shared_ptr<sf::RenderTexture> &Texture) override;

      virtual void Move(const sf::Vector2f &Delta) override;

      virtual ~ButtonBase() = default;
    protected:
      ButtonBase();



    };

  }

}


#endif
