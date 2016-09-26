#include "../../Headers/UI/MouseTarget.h"

namespace Engine
{
  template<typename Events, typename CALLBACK>
  MouseTarget::MouseTarget(Events evnt, CALLBACK &cb)
  {
    switch (evnt)
    {
      case Events::MouseOver:
        MouseOverCallback = cb; break;
      case Events::MouseMoved:
        MouseMovementCallback = cb; break;
      case Events::MouseExit:
        MouseExitCallback = cb; break;
    }
  }

  template<typename Events, typename CALLBACK, typename... others>
  MouseTarget::MouseTarget(const sf::FloatRect &bds ,Events evnt, CALLBACK &cb, others...) : MouseTarget(others...)
  {
    MouseBounds = bds;
    MouseExitCallback = [this](const sf::Vector2i &) {};
    MouseMovementCallback = [this](const sf::Vector2i &) {};
    MouseOverCallback = [this](const sf::Vector2i &) {};

    switch (evnt)
    {
      case Events::MouseOver:
        MouseOverCallback = cb; break;
      case Events::MouseMoved:
        MouseMovementCallback = cb; break;
      case Events::MouseExit:
        MouseExitCallback = cb; break;
    }
  }
}
