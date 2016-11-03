#include "../../Headers/Utils/String.h"

STRING::STRING()
{
  rawstring = (char *)malloc(1);
  rawstring[0] = '\0';

  refcount = (std::size_t *)malloc(sizeof(std::size_t));
  *refcount = 1;

  length = (std::size_t *)malloc(sizeof(std::size_t));
  *length = 0;
}

STRING::STRING(const STRING &str)
  : rawstring(str.rawstring), refcount(str.refcount), length(str.length)
{
  ++(*refcount);
}

STRING::STRING(const std::string &str)
{
  rawstring = (char *)malloc(str.length() + 1);
  memcpy(rawstring, str.c_str(), str.length());
  rawstring[*length] = '\0';

  length = (std::size_t *)malloc(sizeof(std::size_t));
  *length = str.length();

  refcount = (std::size_t *)malloc(sizeof(std::size_t));
  *refcount = 1;
}

STRING::STRING(const char *str)
{
  std::size_t len = strlen(str);

  rawstring = (char *)malloc(len + 1);
  memcpy(rawstring, str, len);
  rawstring[len] = '\0';

  refcount = (std::size_t *)malloc(sizeof(std::size_t));
  *refcount = 1;

  length = (std::size_t *)malloc(sizeof(std::size_t));
  *length = len;
}

STRING& STRING::operator=(const STRING &str)
{
  --(*refcount);
  if (*refcount == 0) {
    free(refcount);
    free(length);
    free(rawstring);
  }

  rawstring = str.rawstring;
  length = str.length;
  refcount = str.refcount;
  ++(*refcount);
  return *this;
}

STRING& STRING::operator=(const std::string &str)
{
  --(*refcount);
  if (*refcount == 0) {
    free(rawstring);
    free(refcount);
    free(length);
  }

  std::size_t len = str.length();

  rawstring = (char *)malloc(len + 1);
  memcpy(rawstring, str.c_str(), len);
  rawstring[len] = '\0';

  length = (std::size_t *)malloc(sizeof(std::size_t));
  *length = len;

  refcount = (std::size_t *)malloc(sizeof(std::size_t));
  *refcount = 1;

  return *this;
}

STRING& STRING::operator=(const char *str)
{
  --(*refcount);
  if (*refcount == 0) {
    free(refcount);
    free(length);
    free(rawstring);
  }

  std::size_t len = strlen(str);

  rawstring = (char *)malloc(len + 1);
  memcpy(rawstring, str, len);
  rawstring[len] = '\0';

  length = (std::size_t *)malloc(sizeof(std::size_t));
  *length = len;

  refcount = (std::size_t *)malloc(sizeof(std::size_t));
  *refcount = 1;

  return *this;
}

STRING::~STRING()
{
  if (*refcount > 1) {
    --(*refcount);
  }
  else {
    free(refcount);
    free(length);
    free(rawstring);
  }
}

std::size_t STRING::Length() const
{
  return (*length);
}

void STRING::Clear()
{
  delete[] rawstring;
  *length = 0;
}


std::ostream& operator<<(std::ostream &out, const STRING &str)
{
  char *f = str.rawstring;
  while (*f != '\0') {
    out << *f++;
  }

  return out;
}

std::istream& operator >> (std::istream &in, STRING &str)
{
  return in;
}

bool STRING::operator==(const STRING &str)
{
  if (!rawstring || !str.rawstring)
    return false;

  return (memcmp(rawstring, str.rawstring, *length) == 0);
}

bool STRING::operator==(const std::string &str)
{
  if (!length || !refcount || !rawstring)
    return false;

  if (*length != str.length())
    return false;

  char *f = rawstring;
  for (auto c : str) {
    if (*f != c)
      return false;
    f++;
  }
  return true;
}

bool STRING::operator==(const char *str)
{
  if (!rawstring || !length || !refcount)
    return false;

  return (strcmp(rawstring, str) == 0);
}

STRING::operator std::string()
{
  return std::string(rawstring);
}

STRING::operator bool()
{
  return (rawstring != nullptr);
}

const char* STRING::str() const
{
  return rawstring;
}
