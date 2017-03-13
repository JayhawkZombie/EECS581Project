#ifndef SFENGINE_MESH_H
#define SFENGINE_MESH_H

#include "../../../ThirdParty/PhysicsEngine.h"


namespace Engine
{

  enum class MeshType : std::uint32_t
  {
    Base,
    Ball,
    BallGo,
    Polygon,
    Block,
    ExpandPolygon
  };

  class ComponentCollider2D
  {
  public:
    ComponentCollider2D();
    ~ComponentCollider2D();

    std::shared_ptr<PhysicsEngineBaseMeshType> GetMesh();
    void SetMesh(std::shared_ptr<PhysicsEngineBaseMeshType> Mesh);

    void CreateMesh();

  protected:

    std::shared_ptr<PhysicsEngineBaseMeshType> ColliderMesh;
  };

}

#endif
