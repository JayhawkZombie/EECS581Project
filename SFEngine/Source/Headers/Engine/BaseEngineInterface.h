#ifndef SFENGINE_BASE_ENGINE_INTERFACE_H
#define SFENGINE_BASE_ENGINE_INTERFACE_H

#include "../BasicIncludes.h"
#include "../Events/EventHandler.h"

namespace Engine
{
  /**
   * Necessary forward declaration
   *  to allow this to be seen by the BaseClass and avoid circular includes
   *  will work on fixing later and getting GlobalHooks in better shape
   */
  class Level;
  extern std::shared_ptr<Level> CurrentLevel;



  class BaseEngineInterface
  {
  public:
    BaseEngineInterface();
    BaseEngineInterface(const BaseEngineInterface &b);
    ~BaseEngineInterface();

    virtual void TickUpdate(const double &delta) = 0;

    virtual void Render() = 0;

    virtual void OnShutDown() = 0;

    EventHandler Handler;

  protected:

  private:
    static void NO_ACTION(BaseEngineInterface *item, const sf::Vector2i &i);
    static void NO_ACTION(BaseEngineInterface *item, const sf::Mouse::Button &);
    static void NO_ACTION(BaseEngineInterface *item, const sf::Keyboard::Key &);
    static void NO_ACTION(BaseEngineInterface *item);

  };
}

#endif
