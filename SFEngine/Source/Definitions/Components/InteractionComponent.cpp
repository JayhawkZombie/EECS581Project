#include "../../Headers/Components/InteractionComponent.h"
#include "../../Headers/Components/ComponentManager.h"
#include "../../Headers/Level/LevelObject.h"

namespace Engine
{



  InteractionComponent::InteractionComponent()
  {
  }

  InteractionComponent::~InteractionComponent()
  {
  }

  void InteractionComponent::AttachedTo(ComponentManager *newManager)
  {
  }

  void InteractionComponent::AttachedTo(LevelObject *Object)
  {

  }

  void InteractionComponent::Detach()
  {
  }

  void InteractionComponent::Update()
  {
  }

  void InteractionComponent::Enable()
  {
  }

  void InteractionComponent::Disable()
  {
  }

  std::string InteractionComponent::GetComponentName() const
  {
    return std::string();
  }

}
