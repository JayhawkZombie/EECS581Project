#ifndef SFENGINE_ENCODERS_H
#define SFENGINE_ENCODERS_H

#include <SFML\Graphics.hpp>

#include <fstream>
#include <iostream>
#include <memory>
#include <string>

namespace Engine
{

  namespace Encode
  {

    const std::size_t EncodeBit[8] = { 
      0b010000000, 
      0b001000000, 
      0b000100000, 
      0b000010000, 
      0b000001000, 
      0b000000100, 
      0b000000010, 
      0b000000001 
    };

    void Image(const sf::Image &image, std::ofstream &out);

    template<typename T>
    void Rect(const sf::Rect<T> &rect, std::ofstream &out)
    {
      out.write((char *)(&rect.left), sizeof(rect.left));
      out.write((char *)(&rect.top), sizeof(rect.top));
      out.write((char *)(&rect.width), sizeof(rect.width));
      out.write((char *)(&rect.height), sizeof(rect.height));
    }
   
    template<typename T>
    void Vector2(const sf::Vector2<T> &vec, std::ofstream &out)
    {
      out.write((char *)(&vec.x), sizeof(vec.x));
      out.write((char *)(&vec.y), sizeof(vec.y));
    }

    void String(const std::string &str, std::ofstream &out);
    void Color(const sf::Color &c, std::ofstream &out);

  }

}


#endif
