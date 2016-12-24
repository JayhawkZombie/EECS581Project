#ifndef SFENGINE_TEXT_READER_H
#define SFENGINE_TEXT_READER_H

#include <string>
#include <regex>
#include <iterator>
#include <sstream>

namespace Engine
{

  namespace Text
  {

    int ReadInteger(std::string RawString, bool Unsigned = false);
    float ReadDecimal(std::string RawString);
  }

}


#endif

