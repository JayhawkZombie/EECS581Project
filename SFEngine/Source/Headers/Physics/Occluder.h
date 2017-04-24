#ifndef SFENGINE_PHYSICS_OCCLUDER_H
#define SFENGINE_PHYSICS_OCCLUDER_H

#include "BasicIncludes.h"
#include "PhysicsEngine.h"

namespace Engine
{
  class LightSystem;

  struct Point {
    ::vec2d pt;
    float angle;
  };

  class Occluder2D
  {
  public:
    friend class LightSystem;

    Occluder2D() = default;
    ~Occluder2D() = default;

    void SetOccluder(SPtrShared<PhysicsEngineBaseMeshType> Mesh) {
      m_OccluderMesh = Mesh;
    }

    std::vector<::vec2d> GetVertices() {
      return m_OccluderMesh->get_verts();
    }

    void Move(const sf::Vector2f &delta) {
      if (m_OccluderMesh)
        m_OccluderMesh->pos += ::vec2d(delta.x, delta.y);
    }

    void SetPosition(const sf::Vector2f &Position) {
      if (m_OccluderMesh)
        m_OccluderMesh->pos = ::vec2d(Position.x, Position.y);
    }

    std::weak_ptr<PhysicsEngineBaseMeshType> GetMesh() {
      return m_OccluderMesh;
    }

    bool HandleCollision(std::weak_ptr<Collider2D> Collider) {
      return false;
    }

  protected:
    bool m_CastSoftShadow = false;
    SPtrShared<PhysicsEngineBaseMeshType> m_OccluderMesh;

    std::vector<::vec2d> m_SortingPoints;

  };

}

#endif
