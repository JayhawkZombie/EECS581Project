#ifndef SFENGINE_LEVEL_ENV_H
#define SFENGINE_LEVEL_ENV_H

#include "LevelObject.h"
#include "../Lights/GlobalLightSource.h"
#include "../Actor/Actor.h"

namespace Engine
{

  namespace LevelEnvironment
  {

    extern GlobalLightSource *GlobalLight;
    extern GenericActor **Actors;
    extern GenericLightSource **Lights;

    class GenericActor;
  }

}

#endif
