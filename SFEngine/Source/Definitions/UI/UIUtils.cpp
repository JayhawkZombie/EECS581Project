#include "../../Headers/UI/UIUtils.h"

namespace Engine
{
  namespace UI
  {
    bool IsMouseOverRect(const sf::Vector2i &pos, const sf::FloatRect &rect)
    {
      return rect.contains(sf::Vector2f(pos));
    }
  }
}