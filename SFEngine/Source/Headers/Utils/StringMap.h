#ifndef SF_STRING_MAP_H
#define SF_STRING_MAP_H

#include "STRING.h"

template<typename FIRST, typename SECOND>
struct SimplePair {
  SimplePair() = default;
  SimplePair(const FIRST &f, const SECOND &s) : first(f), second(s) {

  }
  FIRST first;
  SECOND second;
};

template<typename T>
struct MinimalNode {
  MinimalNode() : Next(nullptr) {}
  MinimalNode(const T& v) : value(v), Next(nullptr), Previous(nullptr) {}
  MinimalNode(const T& v, MinimalNode<T> *p) : value(v), Previous(p), Next(nullptr) {}

  T value;
  MinimalNode<T> *Next;
  MinimalNode<T> *Previous;
};

template<typename Item>
class LinkedList
{
public:
  LinkedList() : Front(nullptr) {}
  ~LinkedList() {
    MinimalNode<Item> *Temp = Front;

    while (Front != nullptr) {
      Temp = Front;
      Front = Front->Next;
      delete Temp;
    }
  }

  void AddItem(const Item &item) {
    if (Front == nullptr) {
      Front = new MinimalNode<Item>(item);
      Back = Front;
    }
    else {
      Back->Next = new MinimalNode<Item>(item);
      Back->Previous = Back;
      Back = Back->Next;
    }
  }

  MinimalNode<Item> *Front;
  MinimalNode<Item> *Back;
};

template<typename TO>
class STRINGMAP
{
public:
  STRINGMAP() {

  }
  ~STRINGMAP() {

  }

  void Emplace(const STRING &str, TO &value) {
    SimplePair<STRING, TO> pair(str, value);
    Map.AddItem(pair);
  }

  TO& operator[](const STRING &str) {
    MinimalNode<SimplePair<STRING, TO>> *Front = Map.Front;
    while (Front != nullptr) {
      if (Front->value.first == str) {
        return Front->value.second;
      }
      Front = Front->Next;
    }

    Emplace(str, TO());
    return (Map.Back->value.second);
  }

private:
  LinkedList<SimplePair<STRING, TO>> Map;

};


#endif
