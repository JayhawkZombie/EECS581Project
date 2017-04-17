#ifndef SFENGINE_DATA_STREAM_H
#define SFENGINE_DATA_STREAM_H

#include "Exceptions\Exceptions.h"

#include <queue>
#include <string>

namespace Engine
{

  template<typename T>
  class DataStream
  {
  public:
    DataStream() = default;
    ~DataStream();
    void operator << (const T &ToCopy);
    void operator >> (T &Target);
    bool IsEmpty() const;
    void Clear();

  protected:
    std::queue<T> Stream;
  };

}

#include "DataStream.inl"
#endif
