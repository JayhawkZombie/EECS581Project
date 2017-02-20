#ifndef SFENGINE_DATA_STREAM_H
#define SFENGINE_DATA_STREAM_H

#include "../Exceptions/Exceptions.h"

#include <vector>
#include <string>

template<typename T>
class DataStream
{
public:
  DataStream() = default;
  ~DataStream() {

  }

  void operator << (const T &ToCopy) {
    Stream.insert(Stream.begin() + 0, ToCopy);
  }

  void operator >> (T &Target) {
    if (Stream.size() > 0) {
      Target = Stream.front();
      Stream.erase(Stream.begin() + 0);
    }
    else {
      throw StreamException({ ExceptionCause::StreamError }, EXCEPTION_MESSAGE("Stream is empty"));
    }
  }

protected:
  std::vector<T> Stream;
};


#endif
