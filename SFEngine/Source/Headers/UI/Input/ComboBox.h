#ifndef SFENGINE_UI_COMBO_BOX_H
#define SFENGINE_UI_COMBO_BOX_H

#include "../Widget.h"

#include "../Buttons/ClickButtonBase.h"

namespace Engine
{

  namespace UI
  {

    class ComboBox : public WidgetBase
    {
    public:
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

      virtual void OnUpButtonPressed() = 0;
      virtual void OnDownButtonPressed() = 0;

      virtual void OnUpButtonReleased() = 0;
      virtual void OnDownButtonReleased() = 0;

      virtual ~ComboBox() = default;
    protected:
      ComboBox();


      std::shared_ptr<ClickButtonBase> UpButton;
      std::shared_ptr<ClickButtonBase> DownButton;
    };
  }

}

#endif
