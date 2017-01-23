#ifndef SFENGINE_DECODERS_H
#define SFENGINE_DECODERS_H

#include <fstream>
#include <iostream>
#include <string>
#include <memory>

#include <SFML\Graphics.hpp>

namespace Engine
{


  namespace Decode
  {

    std::shared_ptr<sf::Image> Image(std::ifstream &in);
    template<typename T>
    sf::Rect<T> Rect(std::ifstream &in)
    {
      sf::Rect<T> rect{ 0,0,0,0 };
      in.read((char *)(&rect.left), sizeof(rect.left));
      in.read((char *)(&rect.top), sizeof(rect.top));
      in.read((char *)(&rect.width), sizeof(rect.width));
      in.read((char *)(&rect.height), sizeof(rect.height));

      return rect;
    }

    template<typename T>
    sf::Vector2<T> Vector2(std::ifstream &in)
    {
      sf::Vector2<T> rect{ 0, 0 };
      in.read((char *)(&rect.x), sizeof(rect.x));
      in.read((char *)(&rect.y), sizeof(rect.y));

      return rect;
    }
    sf::Vector2f Vector2f(std::ifstream &in);
    std::string String(std::ifstream &in);
    sf::Color Color(std::ifstream &in);

  }


}


#endif
