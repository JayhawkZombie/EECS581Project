#include "../../Headers/Utils/Decoders.h"

namespace Engine
{

  namespace Decode
  {

    std::shared_ptr<sf::Image> Image(std::ifstream &in)
    {
      //get the size of the image
      sf::Vector2u size;
      in.read((char *)(&size.x), sizeof(size.x));
      in.read((char *)(&size.y), sizeof(size.y));

      std::shared_ptr<sf::Image> image(new sf::Image);
      image->create(size.x, size.y);

      //now read in the actual image
      sf::Color PixelColor;
      for (std::size_t y = 0; y < size.y; ++y) {
        for (std::size_t x = 0; x < size.x; ++x) {
          PixelColor = Decode::Color(in);
          image->setPixel(x, y, PixelColor);
        }
      }

      return image;
    }

    sf::Vector2f Vector2f(std::ifstream &in)
    {
      sf::Vector2f f{ 0, 0 };
      in.read((char *)(&f.x), sizeof(f.x));
      in.read((char *)(&f.y), sizeof(f.y));

      return f;
    }

    std::string String(std::ifstream &in)
    {
      std::size_t strl{ 0 };
      std::string str{ "" };

      in.read((char *)(&strl), sizeof(strl));
      str.resize(strl);
      in.read(&str[0], strl);
      return str;
    }

    sf::Color Color(std::ifstream & in)
    {
      sf::Color c{ 0,0,0 };
      in.read((char *)(&c.r), sizeof(c.r));
      in.read((char *)(&c.g), sizeof(c.g));
      in.read((char *)(&c.b), sizeof(c.b));
      in.read((char *)(&c.a), sizeof(c.a));

      return c;
    }

  }

}
