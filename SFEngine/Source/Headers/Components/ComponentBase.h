#ifndef SFENGINE_COMPONENT_BASE_H
#define SFENGINE_COMPONENT_BASE_H

#include "../Globals/GlobalHooks.h"

namespace Engine
{
  class ComponentManager;
  class LevelObject;

  class ComponentBase
  {
  public:
    friend class ComponentManager;

    ComponentBase();
    virtual ~ComponentBase();

    virtual void AttachedTo(ComponentManager *newManager) = 0;
    virtual void AttachedTo(LevelObject *Object) = 0;
    virtual void Detach() = 0;
    virtual void Update() = 0;
    virtual void Enable() = 0;
    virtual void Disable() = 0;
    virtual std::string GetComponentName() const = 0;
    std::uint32_t GetID() const;
  protected:
    ComponentManager *Manager;
    std::string ComponentName = "ComponentBase";
    std::uint32_t ComponentID;
  };

}

#endif
