#ifndef SFENGINE_BASE_ENGINE_INTERFACE_H
#define SFENGINE_BASE_ENGINE_INTERFACE_H

#include "../BasicIncludes.h"
#include "../Events/EventHandler.h"
#include "../Exceptions/Exceptions.h"

#include "../../../ThirdParty/cereal/cereal.hpp"

namespace Engine
{
  /**
  * Necessary forward declaration
  *  to allow this to be seen by the BaseClass and avoid circular includes
  *  will work on fixing later and getting GlobalHooks in better shape
  */
  class Level;

#define TYPEDEF_PARENT_CLASS(PARENTCLASS) \
  typedef PARENTCLASS Super; 


  class BaseEngineInterface
  {
  public:
    BaseEngineInterface();
    BaseEngineInterface(const BaseEngineInterface &b);
    virtual ~BaseEngineInterface();

    virtual void TickUpdate(const double &delta) = 0;

    virtual void Render(std::shared_ptr<sf::RenderTarget> Target) = 0;

    virtual void OnShutDown() = 0;

    /**
    * Beginning of object serialization
    *   this will be REQUIRED to be overridden by base classes
    *   if they want to be able to be encoded/decoded
    */

    virtual void SerializeOut(std::ofstream &out) = 0;
    virtual void SerializeIn(std::ifstream &in) = 0;

    virtual void EventUpdate(sf::Event event);

    virtual void HandleInputEvent(const UserEvent &evnt);

    EventHandler Handler;
    virtual std::string GetID() const;
    virtual void SetID(const std::string &ID);

    virtual std::uint32_t GetInternalID() const {
      return InternalID;
    }
    virtual void SetInternalD(const std::uint32_t &ID) {
      InternalID = ID;
    }
  protected:
    static void NO_ACTION(BaseEngineInterface *item, const sf::Vector2i &i);
    static void NO_ACTION(BaseEngineInterface *item, const sf::Mouse::Button &);
    static void NO_ACTION(BaseEngineInterface *item, const sf::Keyboard::Key &);
    static void NO_ACTION(BaseEngineInterface *item);

    std::string ItemID;
    std::uint32_t InternalID;
  };
}

#endif