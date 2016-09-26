#ifndef SFENGINE_MOUSE_TARGET_H
#define SFENGINE_MOUSE_TARGET_H

#include "../BasicIncludes.h"
#include "../Events/EventHandler.h"

namespace Engine
{
  struct MouseTarget {
    template<typename Events, typename CALLBACK>
    MouseTarget(Events evnt, CALLBACK &cb);

    template<typename Events, typename CALLBACK, typename... others>
    MouseTarget(const sf::FloatRect &bds ,Events evnt, CALLBACK &cb, others...);

    sf::FloatRect MouseBounds;

    bool MouseOver, MouseWasOver, Enabled;

    std::function<void(const sf::Vector2i &pos)> MouseOverCallback;
    std::function<void(const sf::Vector2i &pos)> MouseExitCallback;
    std::function<void(const sf::Vector2i &pos)> MouseMovementCallback;
  };
}

#endif
