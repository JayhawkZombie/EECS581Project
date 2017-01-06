#include "../../Headers/Utils/Encoders.h"

namespace Engine
{

  namespace Encode
  {

    void Image(const sf::Image &image, std::ofstream &out)
    {
      //write the size of the image
      auto size = image.getSize();
      Encode::Vector2<>(size, out);
      //out.write((char *)(&size.x), sizeof(size.x));
      //out.write((char *)(&size.y), sizeof(size.y));

      //write out the image itself
      sf::Color PixelColor;
      for (std::size_t y = 0; y < size.y; ++y) {
        for (std::size_t x = 0; x < size.x; ++x) {
          PixelColor = image.getPixel(x, y);
          Encode::Color(PixelColor, out);
        }
      }
    }

    void String(const std::string &str, std::ofstream &out)
    {
      std::size_t strl = str.length();
      out.write((char *)(&strl), sizeof(strl));
      out.write(str.c_str(), strl);
    }

    void Color(const sf::Color & c, std::ofstream & out)
    {
      out.write((char *)(&c.r), sizeof(c.r));
      out.write((char *)(&c.g), sizeof(c.g));
      out.write((char *)(&c.b), sizeof(c.b));
      out.write((char *)(&c.a), sizeof(c.a));
    }

  }

}

