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
    bool StringToBool(const std::string &s, bool Default);

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
    sf::Vector2<T> StringToVec2(const std::string &s, sf::Vector2<T> Default)
    {
      T a, b;

      std::string astr, bstr;

      std::size_t comma = s.find_first_of(',');
      std::size_t comment = s.find_first_not_of("-0123456789", comma);

      astr = s.substr(1, comma - 1);
      bstr = s.substr(comma + 1, comment);

      std::stringstream converta(astr), convertb(bstr);

      a = (converta >> a ? a : Default.x);
      a = (convertb >> b ? b : Default.y);

      return sf::Vector2<T>(a, b);
    }

    template<typename T>
    sf::Rect<T> StringToRect(const std::string &s)
    {
      T a, b, c, d;

      std::string astr, bstr, cstr, dstr;
      std::size_t comma1, comma2, comma3, comment;

      comma1 = s.find_first_of(',');
      comma2 = s.find_first_of(',', comma1 + 1);
      comma3 = s.find_first_of(',', comma2 + 1);
      comment = s.find_first_not_of("-0123456789.", comma3 + 1);

      astr = s.substr(1, comma1 - 1);
      bstr = s.substr(comma1 + 1, comma2 - comma1 - 1);
      cstr = s.substr(comma2 + 1, comma3 - comma2 - 1);
      dstr = s.substr(comma3 + 1, comment - comma3 - 1);

      std::stringstream converta(astr), convertb(bstr), convertc(cstr), convertd(dstr);
      a = (converta >> a ? a : T());
      b = (convertb >> b ? b : T());
      c = (convertc >> c ? c : T());
      d = (convertd >> d ? d : T());

      return sf::Rect<T>(a, b, c, d);

    }

    template<typename T>
    sf::Rect<T> StringToRect(const std::string &s, sf::Rect<T> Default)
    {
      T a, b, c, d;

      std::string astr, bstr, cstr, dstr;
      std::size_t comma1, comma2, comma3, comment;

      comma1 = s.find_first_of(',');
      comma2 = s.find_first_of(',', comma1 + 1);
      comma3 = s.find_first_of(',', comma2 + 1);
      comment = s.find_first_not_of("-0123456789.", comma3 + 1);

      astr = s.substr(1, comma1 - 1);
      bstr = s.substr(comma1 + 1, comma2 - comma1 - 1);
      cstr = s.substr(comma2 + 1, comma3 - comma2 - 1);
      dstr = s.substr(comma3 + 1, comment - comma3 - 1);

      std::stringstream converta(astr), convertb(bstr), convertc(cstr), convertd(dstr);
      a = (converta >> a ? a : Default.left);
      b = (convertb >> b ? b : Default.top);
      c = (convertc >> c ? c : Default.width);
      d = (convertd >> d ? d : Default.height);

      return sf::Rect<T>(a, b, c, d);

    }

    template<typename T>
    T StringToType(const std::string &s)
    {
      T a;
      std::string scpy;
      std::size_t comment = s.find_first_of(';');

      scpy = s.substr(0, comment);

      std::stringstream ss(scpy);

      return (ss >> a ? a : T());
    }

    template<typename T>
    T StringToType(const std::string &s, T Default)
    {
      T a;
      std::string scpy;
      std::size_t comment = s.find_first_of(';');

      scpy = s.substr(0, comment);

      std::stringstream ss(scpy);

      return (ss >> a ? a : Default);
    }
  }
}


#endif
