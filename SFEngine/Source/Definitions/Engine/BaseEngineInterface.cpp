#include "Engine\BaseEngineInterface.h"

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
    Handler.ftnCallback_MouseScroll = [this](auto v, auto w, auto d) {};
    Handler.ftnCallback_TextEntered = [this](auto t) {};
    Handler.ftnCallback_WindowClosed = [this]() {};
    Handler.ftnCallback_WindowResized = [this]() {};

    try
    {
      std::uint32_t id = GenerateID();
      InternalID = id;
    }
    catch (IDException &err)
    {
      err.AddCause(ExceptionCause::IDGenerationError);
      err.AddMessage(EXCEPTION_MESSAGE("Failed to generate ID for item"));
    }
  }

  BaseEngineInterface::BaseEngineInterface(const BaseEngineInterface & b)
    : InternalID(b.InternalID), ItemID(b.ItemID)
  {
    try
    {
      ItemID = b.ItemID + "_Copy";
      InternalID = GenerateID();
    }
    catch (EngineRuntimeError& e)
    {
      e.AddCause(ExceptionCause::ConstructionError);
      e.AddMessage(EXCEPTION_MESSAGE("Failed to create InternalID for BaseEngineInterface copy"));

      throw;
    }
  }

  void BaseEngineInterface::SerializeOut(std::ofstream &out)
  {
    //need to write the item ID to the binary file
    //first write how many characters are in the ID
    std::size_t count = ItemID.size();
    out.write((char *)(&count), sizeof(std::size_t));

    //then write out the id itself
    out.write(ItemID.c_str(), count);
  }

  void BaseEngineInterface::SerializeIn(std::ifstream &in)
  {
    //need to read the item ID from the binary file
    std::size_t strl{ 0 };
    in.read((char *)(&strl), sizeof(std::size_t));

    if (strl >= ItemID.max_size())
      throw std::runtime_error("ItemID exceeds maximum length");
  }

  void BaseEngineInterface::EventUpdate(sf::Event event)
  {
  }

  void BaseEngineInterface::HandleInputEvent(const UserEvent & evnt)
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
