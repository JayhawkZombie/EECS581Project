#ifndef SFENGINE_FACTORY_CLASS_CREATE_BIND_H
#define SFENGINE_FACTORY_CLASS_CREATE_BIND_H

#include "../BasicIncludes.h"
#include <Thor\Animations.hpp>
#include <Thor\Particles.hpp>
#include <Thor\Time.hpp>
#include <Aurora\Tools.hpp>

namespace Engine
{

  class GenericActor;
  class Player;
  class Level;
  class LevelObject;
  class TileSheet;
  class LevelTile;
  class Animation;


  namespace Factory
  {

    std::shared_ptr<GenericActor> MakeActor(std::string Name);
    std::shared_ptr<thor::ParticleSystem> MakeParticleSystem(std::string Name);

    std::shared_ptr<thor::FrameAnimation> CreateAnimation(std::shared_ptr<LevelObject> Object, std::string Name);
    void AddAnimationFrame(std::shared_ptr<thor::FrameAnimation> Anim, float Duration, int left, int top, int height, int width);
    void AddStaticAnimationFrame(std::shared_ptr<thor::FrameAnimation>, int left, int top, int width, int height);
  }


}


#endif
