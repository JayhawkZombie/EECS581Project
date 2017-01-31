#include "../../../Headers/UI/Input/ComboBox.h"
#include "../../../Headers/UI/WIdgetHelper.h"

namespace Engine
{

  namespace UI
  {
    void ComboBox::ConsumeEvent(const InputEvent & IEvent)
    {
      if (ChildHelper)
        ChildHelper->ConsumeEvent(IEvent);
    }

    void ComboBox::OnFocusGained(const FocusChangeEvent & FEvent)
    {
      
    }

    void ComboBox::OnFocusLost(const FocusChangeEvent & FEvent)
    {
    }

    void ComboBox::OnKeyPress(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void ComboBox::OnKeyRelease(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void ComboBox::OnMousePress(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void ComboBox::OnMouseRelease(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void ComboBox::OnMouseScroll(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void ComboBox::OnMouseOver(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void ComboBox::OnMouseLeave(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void ComboBox::OnMouseMove(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void ComboBox::OnDragBegin(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void ComboBox::OnDragContinue(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
    }

    void ComboBox::OnDragEnd(const InputEvent & IEvent)
    {
      ConsumeEvent(IEvent);
    }

    ComboBox::ComboBox()
    {
    }

  }

}