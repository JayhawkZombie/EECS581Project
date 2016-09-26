#include "../../Headers/UI/MouseTarget.h"

namespace Engine
{
  MouseTarget::MouseTarget()
  {
    MouseOver = false;
    MouseWasOver = false;
  }

  MouseTarget::MouseTarget(const MouseTarget &tgt)
  {
    this->Enabled = tgt.Enabled;
    this->MouseBounds = tgt.MouseBounds;
    this->MouseExitCallback = tgt.MouseExitCallback;
    this->MouseMovementCallback = tgt.MouseMovementCallback;
    this->MouseOver = tgt.MouseOver;
    this->MouseOverCallback = tgt.MouseOverCallback;
    this->MousePressCallback = tgt.MousePressCallback;
    this->MouseReleaseCallback = tgt.MouseReleaseCallback;
    this->FocusGainedCallback = tgt.FocusGainedCallback;
    this->FocusLostCallback = tgt.FocusLostCallback;
    this->MouseWasOver = tgt.MouseWasOver;
  }
}
