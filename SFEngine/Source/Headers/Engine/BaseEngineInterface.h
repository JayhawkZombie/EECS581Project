#ifndef SFENGINE_BASE_ENGINE_INTERFACE_H
#define SFENGINE_BASE_ENGINE_INTERFACE_H

#include "BasicIncludes.h"
#include "Events\EventHandler.h"
#include "Exceptions\Exceptions.h"

#include "cereal\cereal.hpp"

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
    BaseEngineInterface& operator=(const BaseEngineInterface &) = delete;
    virtual ~BaseEngineInterface();


    //************************************
    // Method:    Clone
    // FullName:  Engine::BaseEngineInterface::Clone
    // Access:    virtual public 
    // Returns:   std::shared_ptr<Engine::BaseEngineInterface>
    // Qualifier: const
    // Purpose:   Create a clone of the object 
    //              ItemID and InternalID will *not* be copied
    //              New IDs will be generated
    //************************************
    virtual std::shared_ptr<BaseEngineInterface> Clone() const = 0;

    //************************************
    // Method:    TickUpdate
    // FullName:  Engine::BaseEngineInterface::TickUpdate
    // Access:    virtual public 
    // Returns:   void
    // Qualifier:
    // Parameter: const double & delta
    // Purpose:   Call every game tick update
    //************************************
    virtual void TickUpdate(const double &delta) = 0;


    //************************************
    // Method:    Render
    // FullName:  Engine::BaseEngineInterface::Render
    // Access:    virtual public 
    // Returns:   void
    // Qualifier:
    // Parameter: std::shared_ptr<sf::RenderTarget> Target
    // Purpose:   Direct the object to render itself onto the Target
    //************************************
    virtual void Render(std::shared_ptr<sf::RenderTarget> Target) = 0;


    //************************************
    // Method:    OnShutDown
    // FullName:  Engine::BaseEngineInterface::OnShutDown
    // Access:    virtual public 
    // Returns:   void
    // Qualifier:
    // Parameter: None
    // Purpose:   Called if object is alive during the shutdown process
    //            Use to clean up any allocated resources that cannot
    //            Clean themselves up (including any OpenGL resources)
    //************************************
    virtual void OnShutDown() = 0;


    //************************************
    // Method:    SerializeOut
    // FullName:  Engine::BaseEngineInterface::SerializeOut
    // Access:    virtual public 
    // Returns:   void
    // Qualifier:
    // Parameter: std::ofstream & out
    // Purpose:   Serialize the object to a file. Class must
    //             be able to reconstruct itself from only 
    //             the information provided in the file
    //************************************
    virtual void SerializeOut(std::ofstream &out) = 0;


    //************************************
    // Method:    SerializeIn
    // FullName:  Engine::BaseEngineInterface::SerializeIn
    // Access:    virtual public 
    // Returns:   void
    // Qualifier:
    // Parameter: std::ifstream & in
    // Purpose:   Create a copy of the object in the state as defined in the serialized file
    //************************************
    virtual void SerializeIn(std::ifstream &in) = 0;


    //************************************
    // Method:    EventUpdate
    // FullName:  Engine::BaseEngineInterface::EventUpdate
    // Access:    virtual public 
    // Returns:   void
    // Qualifier:
    // Parameter: sf::Event event
    // Purpose:   Menually request the object react to an sf::Event
    //************************************
    virtual void EventUpdate(sf::Event event);


    //************************************
    // Method:    HandleInputEvent
    // FullName:  Engine::BaseEngineInterface::HandleInputEvent
    // Access:    virtual public 
    // Returns:   void
    // Qualifier:
    // Parameter: const UserEvent & evnt
    // Purpose:   
    //************************************
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

    virtual std::string GetClass() const = 0 {
      return "BaseEngineInterface";
    }
  protected:
    static void NO_ACTION(BaseEngineInterface *item, const sf::Vector2i &i);
    static void NO_ACTION(BaseEngineInterface *item, const sf::Mouse::Button &);
    static void NO_ACTION(BaseEngineInterface *item, const sf::Keyboard::Key &);
    static void NO_ACTION(BaseEngineInterface *item);

    std::string ItemID = "";
    std::uint32_t InternalID = 0;
  };
}

#endif