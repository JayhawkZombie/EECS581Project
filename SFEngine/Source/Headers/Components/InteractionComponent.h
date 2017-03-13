#ifndef SFENGINE_INTERACTION_COMPONENT_H
#define SFENGINE_INTERACTION_COMPONENT_H

#include "CollisionComponent.h"

namespace Engine
{

  class LevelObject;

  class InteractionComponent : protected ComponentBase
  {
  public:
    InteractionComponent();
    ~InteractionComponent();

    void AttachedTo(ComponentManager *newManager) override;
    void AttachedTo(LevelObject *Object) override;
    void Detach() override;
    void Update() override;
    void Enable() override;
    void Disable() override;
    std::string GetComponentName() const override;
  protected:

  };

}

#endif
