#include <SFML\Graphics.hpp>

namespace
{

  sf::Vector2f __i = sf::Vector2f(1, 0);
  sf::Vector2f __j = sf::Vector2f(0, 1);
  float __eps = 1E-4f;
}

namespace Engine
{
  namespace Physics
  {

    bool BoxesOverlap(const sf::FloatRect &FR1, const sf::FloatRect &FR2)
    {
      return(FR1.intersects(FR2));
    }

    sf::Vector2f PointOfIntersection(const sf::Vector2f start, const sf::Vector2f end, const sf::Vector2f &P1, const sf::Vector2f &P2)
    {
      sf::Vector2f u = end - start;
      sf::Vector2f v = P2 - P1;
      sf::Vector2f w = P1 - start;

      float s = (v.y * w.x - v.x * w.y) / (v.x * u.y - v.y * u.x);
      return sf::Vector2f(start + s * u);
    }

    float Dot(const sf::Vector2f &a, const sf::Vector2f &b)
    {
      return (a.x * b.x + a.y * a.y);
    }

    unsigned int Dot(const sf::Vector2u &a, const sf::Vector2u &b)
    {
      return (a.x * b.x + a.y * a.y);
    }

    int Dot(const sf::Vector2i &a, const sf::Vector2i &b)
    {
      return (a.x * b.x + a.y * a.y);
    }

    float Mag(const sf::Vector2f &a)
    {
      return std::sqrt(a.x * a.x + a.y * a.y);
    }

    float Mag(const sf::Vector2u &a)
    {
      return static_cast<float>(std::sqrt(a.x * a.x + a.y * a.y));
    }

    float Mag(const sf::Vector2i &a)
    {
      return static_cast<float>(std::sqrt(a.x * a.x + a.y * a.y));
    }

  }
}
