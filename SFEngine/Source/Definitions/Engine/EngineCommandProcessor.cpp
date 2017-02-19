#include "../../Headers/Engine/Engine.h"

namespace Engine
{
  /*
    Syntax:

    cmd_string :: comm | null
    comm       :: tag "::" comm | immed_comm
    tag        :: <string>
    comm       :: func_call | assignment
    immed_comm :: Quit | Exit | SimCrash

    eg - Disable VSync
      cmd("r::disable_vsync");
       - enable key repeats
      cmd("e::enable_key_repeat");
  */
  void SFEngine::CommandProcessor(const std::string &command)
  {
    //first see if there was a tag
    auto pos = command.find("::");
    if (pos != std::string::npos) {
      //we need to get the sub-category and process that command
      std::string category = command.substr(0, pos);
      if (category == "r") {
        ProcessRenderCommand(command.substr(pos + 2));
      }
      else if (category == "e") {
        ProcessEventCommand(command.substr(pos + 2));
      }
    }
  }

  void SFEngine::ProcessRenderCommand(const std::string & command)
  {
  }

  void SFEngine::ProcessImmediateCommand(const std::string & command)
  {
  }

  void SFEngine::ProcessEventCommand(const std::string & command)
  {
  }

}
