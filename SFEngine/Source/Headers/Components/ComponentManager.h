#ifndef SFENGINE_COMPONENT_MANAGER_H
#define SFENGINE_COMPONENT_MANAGER_H

#include <unordered_map>
#include <memory>

namespace Engine
{
  class ComponentBase;
  class CollisionComponent;
  class ScriptComponent;
  class InteractionComponent;

  class ComponentManager
  {
  public:
    ComponentManager();
    ~ComponentManager();

    void Update(const double &delta);
    void UpdateCollisionComponent();

    void AttachComponent(std::shared_ptr<ComponentBase> Component);
    void DetachComponent(std::shared_ptr<ComponentBase> Component, bool DeleteComponent = true);
    void DetachComponent(std::uint32_t ID);

    std::vector<std::shared_ptr<ScriptComponent>> GetScriptComponents();
    std::vector<std::shared_ptr<CollisionComponent>> GetCollisionComponents();
    std::vector<std::shared_ptr<InteractionComponent>> GetInteractionComponents();
  private:
    std::unordered_map<std::uint32_t, std::shared_ptr<ScriptComponent>> AttachedScriptComponents;
    std::unordered_map<std::uint32_t, std::shared_ptr<CollisionComponent>> AttachedCollisionComponents;
    std::unordered_map<std::uint32_t, std::shared_ptr<InteractionComponent>> AttachedInteractionComponents;
  };

}

#endif
