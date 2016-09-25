#include "../../Headers/Engine/Engine.h"

namespace Engine
{
  UINT32 SFEngine::Startup()
  {

    //Delegate event handlers to the event handler object
    Handler.BindCallback(Events::GainedFocus, Callback_HandleWindowGainedFocus);
    Handler.BindCallback(Events::LostFocus, Callback_HandleWindowLostFocus);
    Handler.BindCallback(Events::WindowClosed, Callback_HandleWindowClosed);
    Handler.BindCallback(Events::WindowResized, Callback_HandleWindowResized);
    Handler.BindCallback(Events::MouseDown, Callback_HandleMousePress);


    return GameLoop();
  }
}