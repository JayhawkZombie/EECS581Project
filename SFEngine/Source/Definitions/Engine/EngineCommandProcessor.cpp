#include "../../Headers/Engine/Engine.h"

namespace Engine
{
  /*
    Syntax:

    cmd_string :: comm | null
    comm       :: tag " " comm | immed_comm
    tag        :: <string>
    comm       :: func_call | assignment
    immed_comm :: Quit | Exit | SimCrash

    commands:
      Core:
        "Core Quit" - Quit, normal shutdown
        "Core Shutdown" - Shutdown, do not notify other modules
        "Core Abort" - Crash
        "Core Clean" - Clean up, not implemented yet

      Render:
        "Render EnableVSync" - enable VSync
        "Render DisableVSyns" - disable VSync
        "Render EnableShaders" - enable shader
        "Render DisableShaders" - disable shader
  */
  //void SFEngine::CommandProcessor(const std::string &command)
  //{
  //  //first see if there was a tag
  //  std::cerr << "Command received: " << command << std::endl;
  //  try
  //  {
  //    ScriptEngine->eval(command);
  //  }
  //  catch (chaiscript::exception::eval_error &err)
  //  {    
  //    EngineScriptConsole->IssueResponse("Eval error : " + std::string(err.what()));
  //  }
  //}

  //void SFEngine::ProcessRenderCommand(const std::string & command)
  //{
  //}

  //void SFEngine::ProcessImmediateCommand(const std::string & command)
  //{
  //}

  //void SFEngine::ProcessEventCommand(const std::string & command)
  //{
  //}

}
