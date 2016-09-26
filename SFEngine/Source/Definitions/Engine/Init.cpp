#include "../../Headers/Engine/Engine.h"

namespace Engine
{
  UINT32 SFEngine::Init(int argc, char **argv)
  {
    std::cerr << "[Command Line Arguments]\n";
    for (int i = 0; i < argc; i++) {
      std::cout << "\t" << i << ": " << argv[i] << std::endl;
    }

    Callback_HandleWindowClosed = std::bind(&SFEngine::HandleWindowClosed, this);
    Callback_HandleWindowResized = std::bind(&SFEngine::HandleWindowResized, this);
    Callback_HandleWindowGainedFocus = std::bind(&SFEngine::HandleWindowGainedFocus, this);
    Callback_HandleWindowLostFocus = std::bind(&SFEngine::HandleWindowLostFocus, this);
    Callback_HandleMousePress = std::bind(&SFEngine::HandleMousePress, this, std::placeholders::_1, std::placeholders::_2);
    Callback_HandleMouseRelease = std::bind(&SFEngine::HandleMouseRelease, this, std::placeholders::_1, std::placeholders::_2);
    Callback_HandleMouseMovement = std::bind(&SFEngine::HandleMouseMovement, this, std::placeholders::_1);

    return Startup();
  }
}