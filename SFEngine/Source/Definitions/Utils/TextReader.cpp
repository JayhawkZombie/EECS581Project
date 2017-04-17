#include "Utils\TextReader.h"

namespace Engine
{

  namespace Text
  {

    int ReadInteger(std::string RawString, bool Unsigned)
    {
      static std::string ReadInteger("-?[1-9][0-9]*");
      static std::regex IntegerRegex(ReadInteger);

      //Does the string contain anything it isn't supposed to?
      auto pos = RawString.find_first_not_of("0123456789-");
      if (pos != std::string::npos)
        return 0;

      std::smatch match;
      int ToReturn = 0;
      if (std::regex_search(RawString, match, IntegerRegex)) {
        std::stringstream SS(match.str());
        SS >> ToReturn;
      }

      return ToReturn;
    }

    float ReadDecimal(std::string RawString)
    {
      //Read a decimal
      static std::string ReadDecimal("-?[1-9][0-9]*(\\.?[0-9]*)?");
      static std::regex DecimalRegex(ReadDecimal);

      //Does the string contain anything it isn't supposed to?
      auto pos = RawString.find_first_not_of("0123456789-.");
      if (pos != std::string::npos)
        return 0;

      std::smatch match;
      float ToReturn = 0.f;
      if (std::regex_search(RawString, match, DecimalRegex)) {
        std::stringstream SS(match.str());
        SS >> ToReturn;
      }

      return ToReturn;
    }

  }

}
