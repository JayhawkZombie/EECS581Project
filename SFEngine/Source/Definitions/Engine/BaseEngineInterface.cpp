#include "../../Headers/Engine/BaseEngineInterface.h"

namespace Engine
{
  BaseEngineInterface::BaseEngineInterface()
  {
    Callback_HandleWindowClosed = [this]() {};
    Callback_HandleWindowResized = [this]() {};
    Callback_HandleWindowLostFocus = [this]() {};
    Callback_HandleWindowGainedFocus = [this]() {};
    Callback_HandleMouseMovement = [this](const sf::Vector2i &) {};
    Callback_HandleMousePress = [this](const sf::Vector2i &, const sf::Mouse::Button &) {};
    Callback_HandleMouseRelease = [this](const sf::Vector2i &, const sf::Mouse::Button &) {};
    Callback_HandleKeyPress = [this](const sf::Keyboard::Key &) {};
    Callback_HandleKeyRelease = [this](const sf::Keyboard::Key &) {};
  }

  BaseEngineInterface::BaseEngineInterface(const BaseEngineInterface &b)
  {

  }
  BaseEngineInterface::~BaseEngineInterface()
  {

  }
  void BaseEngineInterface::NO_ACTION(BaseEngineInterface *item, const sf::Vector2i &i)
  {

  }

  void BaseEngineInterface::NO_ACTION(BaseEngineInterface *item, const sf::Mouse::Button &)
  {

  }

  void BaseEngineInterface::NO_ACTION(BaseEngineInterface *item, const sf::Keyboard::Key &)
  {

  }

  void BaseEngineInterface::NO_ACTION(BaseEngineInterface *item)
  {

  }
}