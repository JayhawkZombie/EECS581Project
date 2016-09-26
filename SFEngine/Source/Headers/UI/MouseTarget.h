#ifndef SFENGINE_MOUSE_TARGET_H
#define SFENGINE_MOUSE_TARGET_H

#include "../BasicIncludes.h"
#include "../Events/EventHandler.h"

namespace Engine
{
  /**
   * A target to which mouse events can be passed
   * Bound callbacks will be triggered when a specific action is done
   *  and the mouse target is enabled

   * To use: Set the rectangular region to do collision testing with
   * and bind callbacks for any events you wish to receive
   * Example: target.MouseBounds = SomeRectangle.getGlobalBounds();
              target.MouseReleaseCallback = [this](const sf::Vector2i &mousePosition) { std::cout << "Pressed me!" << std::endl; };
              or
              target.MouseReleaseCallback = std::bind(&ClickButton::HandleMouseRelease, this, std::placeholders::_1);
   */
  struct MouseTarget {
    MouseTarget();
    MouseTarget(const MouseTarget &tgt);

    sf::FloatRect MouseBounds;

    bool MouseOver, MouseWasOver, Enabled;

    std::function<void(const sf::Vector2i &pos)> MouseOverCallback;
    std::function<void(const sf::Vector2i &pos)> MouseExitCallback;
    std::function<void(const sf::Vector2i &pos)> MouseMovementCallback;
    std::function<void(const sf::Vector2i &pos, const sf::Mouse::Button &which)> MousePressCallback;
    std::function<void(const sf::Vector2i &pos, const sf::Mouse::Button &which)> MouseReleaseCallback;
    std::function<void(const sf::Vector2i &pos)> FocusGainedCallback;
    std::function<void(const sf::Vector2i &pos)> FocusLostCallback;

  };
}

#endif
