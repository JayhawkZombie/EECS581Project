#include "../../Headers/Engine/Engine.h"

Engine::SFEngine *CurrentEngine = nullptr;

void TerminateHandler()
{
  if (CurrentEngine) {
    CurrentEngine->HandleEngineCrash();
  }
  else {
    std::cerr << "The terminate handler was unable to invoke an engine recovery method" << std::endl;
  }
}

namespace Engine
{
#if !defined(__cplusplus)
#error A C++ Compiler must be used. Please compile using a C++14 compliant compiler
#endif

  UINT32 SFEngine::Go(int argc, char **argv)
  {
    CurrentEngine = this;
    std::set_terminate(TerminateHandler);

    UINT32 result = 0;
    try
    {
      result = Init(argc, argv);
      return result;
    }
    catch (std::runtime_error &e)
    {
      std::cerr << "There was a critical error, and it could not be recovered from\n";
      std::cerr << "The following message was provided: " << e.what() << std::endl;
      return Error::RUNTIME_UNKNOWN_ERROR;
    }
  }
}
