#include "Engine\Engine.h"
#include "Exceptions\Exceptions.h"

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
    catch (EngineRuntimeError &err)
    {
      std::cerr << "There was a critical error, and it could not be recovered from\n";
      std::string err_string = err.UnwindTrace();

      std::cerr << "The following stack trace was provided: \n\n" << err_string << std::endl;
      return Error::RUNTIME_UNKNOWN_ERROR;
    }
  }
}
