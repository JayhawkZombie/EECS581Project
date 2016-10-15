#ifndef SFENGINE_CONVERT_H
#define SFENGINE_CONVERT_H

#include <string>
#include <sstream>
#include <algorithm>

#include <SFML\Graphics.hpp>

namespace Engine
{
  namespace Util
  {

    /**
    * Convert given string to bool
    * @param: string, case insensitive
    */
    bool StringToBool(const std::string &s);

    template<typename T>
    sf::Vector2<T> StringToVec2(const std::string &s)
    {
      T a, b;

      std::string astr, bstr;

      std::size_t comma = s.find_first_of(',');
      std::size_t comment = s.find_first_not_of("-0123456789", comma);

      astr = s.substr(1, comma - 1);
      bstr = s.substr(comma + 1, comment);

      std::stringstream converta(astr), convertb(bstr);

      a = (converta >> a ? a : T());
      a = (convertb >> b ? b : T());

      return sf::Vector2<T>(a, b);
    }

    template<typename T>
    T StringToType(const std::string &s)
    {
      T a;
      std::string scpy;
      std::size_t comment = s.find_first_of(';');

      scpy = s.substr(0, comment);
      std::cerr << "Init string to convert: " << scpy << std::endl;

      std::stringstream ss(scpy);

      return (ss >> a ? a : T());
    }
  }
}


#endif
