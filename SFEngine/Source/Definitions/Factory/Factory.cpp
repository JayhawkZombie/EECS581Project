#include "../../Headers/Factory/Factory.h"


namespace Engine
{
  namespace Factory
  {

    std::shared_ptr<Engine::GenericActor> GenericActor(ActorInfo *info, std::ifstream &infile, chaiscript::ChaiScript *engine)
    {
      std::shared_ptr<Engine::GenericActor> Actor(new Engine::GenericActor);

      
      return Actor;
    }

    std::shared_ptr<Engine::GenericActor> GenericActor(const Engine::GenericActor &actor)
    {
      std::shared_ptr<Engine::GenericActor> Actor(new Engine::GenericActor);

      return Actor;
    }

    std::shared_ptr<Engine::GenericActor> Actor(ActorInfo *info, std::ifstream &infile, chaiscript::ChaiScript *engine)
    {
      std::shared_ptr<Engine::GenericActor> Actor(new Engine::GenericActor(info->TexturePath, info->TextureID));
      Actor->CurrentPhysicsState = info->ActorState;

      chaiscript::ModulePtr mptr(new chaiscript::Module);
      chaiscript::utility::add_class<Engine::GenericActor>(*mptr, info->ID,
      { chaiscript::constructor<Engine::GenericActor()>() },
      { {chaiscript::fun(&GenericActor::GetActorPosition), "GetPosition"},
      {chaiscript::fun(&GenericActor::GetID), "GetID"},
      {chaiscript::fun(&GenericActor::SetID), "SetID"}
      });
      
      engine->add(chaiscript::var(std::ref(*Actor)), info->ID);

      return Actor;
    }

    std::shared_ptr<Engine::GenericActor> Actor(std::string ID)
    {
      std::shared_ptr<Engine::GenericActor> Actor(new Engine::GenericActor);
      Actor->SetID(ID);
      return Actor;
    }

    std::shared_ptr<Engine::Animation> Animation(AnimationInfo *info, chaiscript::ChaiScript *engine)
    {
      std::shared_ptr<Engine::Animation> Anim(new Engine::Animation);

      return Anim;
    }

    std::shared_ptr<Engine::Animation> Animation(std::string ID)
    {
      std::shared_ptr<Engine::Animation> Anim(new Engine::Animation);

      return Anim;
    }

    std::shared_ptr<Engine::LevelTile> Tile(const Engine::LevelTile &tile)
    {
      std::shared_ptr<Engine::LevelTile> Tile(new Engine::LevelTile(tile));

      return Tile;
    }

    std::shared_ptr<Engine::LevelTile> Tile(std::string ID)
    {
      std::shared_ptr<Engine::LevelTile> Tile(new Engine::LevelTile);
      Tile->SetID(ID);
      return Tile;
    }
  }
}
