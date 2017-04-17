#include "Streams\DataStream.h"

namespace Engine
{

  template<typename T>
  inline DataStream<T>::~DataStream()
  {

  }

  template<typename T>
  inline void DataStream<T>::operator<<(const T &copy)
  {
    Stream.insert(Stream.begin() + 0, ToCopy);
  }

  template<typename T>
  inline void DataStream<T>::operator >> (T &Target)
  {
    if (Stream.size() > 0) {
      Target = Stream.top();
      Stream.pop();
    }
    else {
      throw StreamException({ ExceptionCause::StreamError }, EXCEPTION_MESSAGE("Stream is empty"));
    }
  }

  template<typename T>
  inline bool DataStream<T>::IsEmpty() const
  {
    return (Stream.empty());
  }

  template<typename T>
  inline void DataStream<T>::Clear()
  {
    Stream.clear();
  }

}
