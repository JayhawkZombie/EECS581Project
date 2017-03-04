#include "..\..\Headers\Factory\Factory.h"
#include "../../../ThirdParty/json/json.h"
#include "../../Headers/Actor/Actor.h"
#include "../../Headers/Actor/Player.h"
#include "../../Headers/Animation/Animation.h"
#include "../../Headers/Level/Level.h"
#include "../../Headers/Tiles/LevelTile.h"
#include "../../Headers/Tiles/TileSheet.h"


namespace Engine
{

  std::shared_ptr<GenericActor> MakeActor(std::string Name)
  {
    try
    {
      auto ptr = std::make_shared<GenericActor>();
      ptr->SetID(Name);

      return ptr;
    }
    catch (EngineRuntimeError &err)
    {
      err.AddCause({ ExceptionCause::ConstructionError });
      err.AddMessage(EXCEPTION_MESSAGE("Factory failed to construct GenericActor object"));
    }
  }

  std::shared_ptr<thor::ParticleSystem> MakeParticleSystem(std::string Name)
  {
    try
    {
      auto ptr = std::make_shared<thor::ParticleSystem>();
      
      return ptr;
    }
    catch (std::exception &err)
    {
      throw;
    }
  }

  std::shared_ptr<thor::FrameAnimation> CreateAnimation(std::shared_ptr<LevelObject> Object, std::string Name)
  {
    try
    {
      auto Anim = std::make_shared<thor::FrameAnimation>();

      return Anim;
    }
    catch (std::exception &err)
    {
      throw;
    }
  }

  void AddAnimationFrame(std::shared_ptr<thor::FrameAnimation> Anim, float Duration, int left, int top, int height, int width)
  {

  }

  void AddStaticAnimationFrame(std::shared_ptr<thor::FrameAnimation>, int left, int top, int width, int height)
  {

  }

}
