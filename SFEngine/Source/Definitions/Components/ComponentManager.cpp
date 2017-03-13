#include "../../Headers/Components/ComponentManager.h"
#include "../../Headers/Components/CollisionComponent.h"
#include "../../Headers/Components/InteractionComponent.h"
#include "../../Headers/Components/ScriptComponent.h"

namespace Engine
{



  ComponentManager::ComponentManager()
  {
  }

  ComponentManager::~ComponentManager()
  {
  }

  void ComponentManager::Update(const double & delta)
  {
  }

  void ComponentManager::AttachComponent(std::shared_ptr<ComponentBase> Component)
  {
    try
    {
      auto ID = GenerateID();
      Component->ComponentID = ID;

      if (Component->GetComponentName() == "CollisionComponent")
      {
        auto ptr = std::dynamic_pointer_cast<CollisionComponent>(Component);
        assert(ptr);
        AttachedCollisionComponents[ID] = ptr;
        Component->AttachedTo(this);
      }
      else if (Component->GetComponentName() == "ScriptComponent")
      {
        auto ptr = std::dynamic_pointer_cast<ScriptComponent>(Component);
        assert(ptr);
        AttachedScriptComponents[ID] = ptr;
        Component->AttachedTo(this);
      }
      else if (Component->GetComponentName() == "InteractionComponent")
      {
        auto ptr = std::dynamic_pointer_cast<InteractionComponent>(Component);
        assert(ptr);
        AttachedInteractionComponents[ID] = ptr;
        Component->AttachedTo(this);
      }
    }
    catch (IDException &ide)
    {
      ide.AddCause(ExceptionCause::ConstructionError);
      ide.AddMessage("Failed to construct Component");

      throw;
    }
  }

  void ComponentManager::DetachComponent(std::shared_ptr<ComponentBase> Component, bool DeleteComponent)
  {
  }

  void ComponentManager::DetachComponent(std::uint32_t ID)
  {
    
  }

  std::vector<std::shared_ptr<CollisionComponent>> ComponentManager::GetCollisionComponents()
  {
    return std::vector<std::shared_ptr<CollisionComponent>>();
  }

  std::vector<std::shared_ptr<ScriptComponent>> ComponentManager::GetScriptComponents()
  {
    return std::vector<std::shared_ptr<ScriptComponent>>();
  }

  std::vector<std::shared_ptr<InteractionComponent>> ComponentManager::GetInteractionComponents()
  {
    return std::vector<std::shared_ptr<InteractionComponent>>();
  }

}
