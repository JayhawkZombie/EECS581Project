#include "../../Headers/Level/ExposedLevelApi.h"

namespace Engine
{

  void SetCurrentLevel(Level *lvl)
  {
    Api_CurrentLevel = lvl;
    if (Api_CurrentLevel)
      Api_CurrentEnvironment = Api_CurrentLevel->GetEnvironment();
  }

  void BindLevelMethods(chaiscript::ChaiScript *Engine)
  {
    if (Engine) {
      Engine->add(chaiscript::fun(&AddActor), "AddActor");
      Engine->add(chaiscript::fun(&KillActor), "KillActor");
      Engine->add(chaiscript::fun(&GetTileName), "GetTileName");
      Engine->add(chaiscript::fun(&LoadLevelInformation), "LoadLevelInformation");
    }
  }

  void AddActor(std::string Name, float x, float y)
  {
    if (Api_CurrentEnvironment) {
      Api_CurrentEnvironment->AddActor(Name, std::shared_ptr<GenericActor>(new GenericActor));
      
      auto actor = Api_CurrentEnvironment->GetActor(Name);
      if (actor) {
        actor->SetActorPosition({ x, y });
        actor->SetID(Name);
      }
    }
  }

  void KillActor(std::string Name)
  {

  }

  std::string GetTileName(float x, float y)
  {
    return{};
  }

  void LoadLevelInformation(std::string Filename)
  {

  }

}
