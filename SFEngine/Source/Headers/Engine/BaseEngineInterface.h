#ifndef SFENGINE_BASE_ENGINE_INTERFACE_H
#define SFENGINE_BASE_ENGINE_INTERFACE_H

#include "../BasicIncludes.h"
#include "../Events/EventHandler.h"

namespace Engine
{
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

  };
}

#endif