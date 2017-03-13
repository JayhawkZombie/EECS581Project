#include "../../Headers/Physics/Collider.h"

namespace Engine
{



  ComponentCollider2D::ComponentCollider2D()
  {
  }

  ComponentCollider2D::~ComponentCollider2D()
  {
  }

  std::shared_ptr<PhysicsEngineBaseMeshType> ComponentCollider2D::GetMesh()
  {
    return std::shared_ptr<PhysicsEngineBaseMeshType>();
  }

  void ComponentCollider2D::SetMesh(std::shared_ptr<PhysicsEngineBaseMeshType> Mesh)
  {
  }

  void ComponentCollider2D::CreateMesh()
  {
  }

}
