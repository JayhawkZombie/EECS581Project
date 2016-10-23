#ifndef SFENGINE_STRING_H
#define SFENGINE_STRING_H
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>

#include <cassert>

#include "ListTemplates.h" //LinkedList.h"


class STRING
{
public:
  STRING();
  STRING(const STRING &s);
  STRING(const std::string &s);
  STRING(const char *s);
  STRING& operator=(const STRING &str);
  STRING& operator=(const std::string &str);
  STRING& operator=(const char *str);

  ~STRING();

  std::size_t Length() const;
  void Clear();

  bool operator==(const STRING &s);
  bool operator==(const std::string &s);
  bool operator==(const char *str);

  friend std::ostream& operator<<(std::ostream &out, const STRING &s);
  friend std::istream& operator >> (std::istream &in, STRING &s);

  operator std::string();
  operator bool();

  const char* str() const;


private:
  char *rawstring;
  std::size_t *length;

  std::size_t *refcount;

};

namespace std
{
  template<> struct less<STRING>
  {
    bool operator() (const STRING &lhs, const STRING &rhs) const
    {
      return (strcmp(lhs.str(), rhs.str()) < 0);
    }
  };
}


#endif
