#include "../../Headers/UI/MouseTarget.h"

namespace Engine
{
  MouseTarget::MouseTarget()
  {
    MouseOver = false;
    MouseWasOver = false;

    this->Enabled = true;
    this->FocusGainedCallback = [this](const sf::Vector2i &) {};
    this->FocusLostCallback = [this](const sf::Vector2i &) {};
    this->MouseBounds = sf::FloatRect(0, 0, 0, 0);
    this->MouseExitCallback = [this](const sf::Vector2i &) {};
    this->MouseMovementCallback = [this](const sf::Vector2i &) {};
    this->MouseOver = false;
    this->MouseOverCallback = [this](const sf::Vector2i &) {};
    this->MousePressCallback = [this](const sf::Vector2i &, const sf::Mouse::Button &) {};
    this->MouseReleaseCallback = [this](const sf::Vector2i &, const sf::Mouse::Button &) {};
  }

  MouseTarget::MouseTarget(const MouseTarget &tgt)
  {
    this->Enabled = tgt.Enabled;
    this->MouseBounds = tgt.MouseBounds;
    this->MouseExitCallback = tgt.MouseExitCallback;
    this->MouseMovementCallback = tgt.MouseMovementCallback;
    this->MouseOver = tgt.MouseOver;
    this->MouseOverCallback = tgt.MouseOverCallback;
    this->MousePressCallback = tgt.MousePressCallback;
    this->MouseReleaseCallback = tgt.MouseReleaseCallback;
    this->FocusGainedCallback = tgt.FocusGainedCallback;
    this->FocusLostCallback = tgt.FocusLostCallback;
    this->MouseWasOver = tgt.MouseWasOver;
  }
}
