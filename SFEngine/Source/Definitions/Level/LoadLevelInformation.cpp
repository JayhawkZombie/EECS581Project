#include "../../Headers/Level/Level.h"
#include <regex>

std::string RegexString_BracedText("(?<=\\{)[^\\}]*(?=\\})");

namespace Engine
{

  void Level::LoadLevelInformation()
  {
    try
    {
      std::regex BracedText(RegexString_BracedText);

    }
    catch (std::exception &e)
    {
      std::cerr << "There was an error loading the level information from the file: \"" << LevelFile << "\"" << std::endl;
      std::cerr << "The following message was reported: " << e.what() << std::endl;
    }
  }

}
