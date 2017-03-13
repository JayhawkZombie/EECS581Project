#include "../../Headers/Components/CollisionComponent.h"
#include "../../Headers/Components/ComponentManager.h"
#include "../../../ThirdParty/PhysicsEngine.h"


namespace Engine
{
  CollisionComponent::CollisionComponent()
  {
    ComponentName = "CollisionComponent";
  }

  CollisionComponent::~CollisionComponent()
  {
  }

  void CollisionComponent::AttachedTo(ComponentManager *newManager)
  {
    Manager = newManager;
  }

  void CollisionComponent::AttachedTo(LevelObject *Object)
  {

  }

  void CollisionComponent::Detach()
  {
    //We may detch from the manager, but we might still exist if something retains a refernece to us
    Manager->DetachComponent(ComponentID);
  }

  void CollisionComponent::Update()
  {

  }

  void CollisionComponent::Enable()
  {
    Enabled = true;
  }

  void CollisionComponent::Disable()
  {
    Enabled = false;
  }

  std::string CollisionComponent::GetComponentName() const
  {
    return std::string("CollisionComponent");
  }

  void CollisionComponent::CreateMesh(std::shared_ptr<PhysicsEngineBaseMeshType> Mesh)
  {
    CollisionMesh = Mesh;
  }

  std::shared_ptr<PhysicsEngineBaseMeshType> CollisionComponent::GetMesh()
  {
    return
      Enabled ? CollisionMesh : nullptr;
  }

}
