#include "../../Headers/Factory/Factory.h"


namespace Engine
{
  namespace Factory
  {

    std::shared_ptr<GenericActor> CreateGenericActor(ActorInfo *info, std::ifstream &infile, chaiscript::ChaiScript *engine)
    {
      std::shared_ptr<GenericActor> Actor(new GenericActor(info->TexturePath, info->TextureID));
      Actor->CurrentPhysicsState = info->ActorState;

      chaiscript::ModulePtr mptr(new chaiscript::Module);
      chaiscript::utility::add_class<GenericActor>(*mptr, info->ID,
      { chaiscript::constructor<GenericActor()>() },
      { {chaiscript::fun(&GenericActor::GetActorPosition), "GetPosition"},
      {chaiscript::fun(&GenericActor::GetID), "GetID"},
      {chaiscript::fun(&GenericActor::SetID), "SetID"}
      });
      
      engine->add(chaiscript::var(std::ref(*Actor)), info->ID);

      return Actor;
    }

    std::shared_ptr<GenericActor> CreateActor(std::string ID)
    {
      std::shared_ptr<GenericActor> Actor(new GenericActor);
      Actor->SetID(ID);
      return Actor;
    }

    std::shared_ptr<Animation> CreateAnimation(AnimationInfo *info, chaiscript::ChaiScript *engine)
    {
      std::shared_ptr<Animation> Ani(new Animation);
      
      for (std::size_t i = 0; i < info->NumberFrames; ++i) {
        Ani->AddFrame(info->Frames[i]);
      }
      Ani->SetFrameTime(info->Duration / info->NumberFrames);
      ResourceManager->RequestTexture(info->TexturePath, info->TextureID,
                                      [Ani](std::shared_ptr<sf::Texture> t, const std::string &s)
                                      {
                                        Ani->SetSpriteSheet(t, s);
                                      }
      );

      return Ani;
    }

    std::shared_ptr<Animation> CreateAnimation(std::string ID)
    {
      std::shared_ptr<Animation> Ani(new Animation);
      Ani->SetID(ID);
      return Ani;
    }
  }
}
