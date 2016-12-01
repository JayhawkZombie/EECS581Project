#ifndef SFENGINE_FACTORY_CLASS_CREATE_BIND_H
#define SFENGINE_FACTORY_CLASS_CREATE_BIND_H


#include "../BasicIncludes.h"

#include "../Actor/Actor.h"
#include "../Actor/Player.h"

namespace Engine
{

  namespace Factory
  {
    std::shared_ptr<GenericActor> CreateGenericActor(ActorInfo *info, std::ifstream &infile, chaiscript::ChaiScript *engine);
    std::shared_ptr<GenericActor> CreateActor(std::string ID = "");
    std::shared_ptr<Animation> CreateAnimation(AnimationInfo *info, chaiscript::ChaiScript *engine);
    std::shared_ptr<Animation> CreateAnimation(std::string ID = "");
  }

}


#endif
