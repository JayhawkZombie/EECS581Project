#include "Utils\Convert.h"

namespace Engine
{
  namespace Util
  {

    bool StringToBool(const std::string &s)
    {
      std::string _s = s;
      std::transform(_s.begin(), _s.end(), _s.begin(), ::tolower);

      return (_s == "true" ? true : false);
    }
  }
}