#include "../../Headers/Engine/BaseEngineInterface.h"

namespace Engine
{
  BaseEngineInterface::BaseEngineInterface()
  {
    Handler.ftnCallback_KeyPress = [this](auto k) {};
    Handler.ftnCallback_KeyRelease = [this](auto k) {};
    Handler.ftnCallback_MouseExit = [this](auto p) {};
    Handler.ftnCallback_MouseMovement = [this](auto p) {};
    Handler.ftnCallback_MouseOver = [this](auto p) {};
    Handler.ftnCallback_MousePress = [this](auto b, auto p) {};
    Handler.ftnCallback_MouseRelease = [this](auto b, auto p) {};
    Handler.ftnCallback_MouseScroll = [this](auto p) {};
    Handler.ftnCallback_TextEntered = [this](auto t) {};
    Handler.ftnCallback_WindowClosed = [this]() {};
    Handler.ftnCallback_WindowResized = [this]() {};
  }

  void BaseEngineInterface::SerializeOut(std::ostream &out)
  {

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

  std::string BaseEngineInterface::GetID() const
  {
    return ItemID;
  }

  void BaseEngineInterface::SetID(const std::string &ID)
  {
    ItemID = ID;
  }
}
