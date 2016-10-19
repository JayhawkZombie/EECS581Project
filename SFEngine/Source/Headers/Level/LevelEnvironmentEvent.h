#ifndef SFENGINE_LEVEL_ENVIRONMENT_EVENT_H
#define SFENGINE_LEVEL_ENVIRONMENT_EVENT_H

#include "LevelEnvironment.h"
#include "LevelEventSequences.h"

namespace Engine
{

  struct LevelEnvironmentEvent : public GenericEvent {
    LevelEnvironmentEvent() :  GenericEvent(0) {}


  };

}

#endif
