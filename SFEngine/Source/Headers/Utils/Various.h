#ifndef SFENGINE_UTILS_VARIOUS_H
#define SFENGINE_UTILS_VARIOUS_H

#include <SFML/Graphics.hpp>

namespace Engine
{


  template<typename _ListType>
  inline void BringItemToFrontOfContainer(_ListType &ListType, std::size_t Index) {
    if (Index >= ListType.size())
      throw std::runtime_error("Index out of bounds of ListType");

    auto ptr = ListType[Index];
    ListType.erase(ListType.begin() + Index);
    ListType.insert(ListType.begin() + 0, ptr);
  }

  

  namespace Util
  {
    void Normalize(sf::Vector2f &v);

    float DistanceBetween(const sf::Vector2f &v1, const sf::Vector2f &v2);

    float Cross2D(const sf::Vector2f &v1, const sf::Vector2f &v2);
  }


}

#endif
