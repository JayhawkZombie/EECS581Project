#ifndef SFENGINE_MESH_H
#define SFENGINE_MESH_H

#include "PhysicsEngine.h"

#include <functional>
#include <bitset>

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

  enum ColliderProp : std::uint32_t
  {
    Active               = 0,
    Sleeping             = 1,
    Enabled              = 2,
    CanBeAwoken          = 3,
    HasPhysicalResponse  = 4,
    NotifyEveryFrame     = 5,
    SingleResponsePerObj = 6,
    NotifyOfOverlap      = 7,
    CastShadows          = 8
  };

  class LevelObject;
  class Occluder2D;

  class Collider2D
  {
  public:
    Collider2D();
    Collider2D(const Collider2D &Copy) = delete;
    ~Collider2D();

    std::shared_ptr<Collider2D> Clone();

    void SetMesh(std::shared_ptr<PhysicsEngineBaseMeshType> MeshPtr);
    sf::FloatRect GetGlobalBounds() const;

    static std::shared_ptr<Collider2D> CreateCircularMesh
    (
      MeshType type,
      const sf::Vector2f &position,
      const sf::Vector2f &velocity,
      unsigned int radius,
      float mass,
      float coeffOfRest,
      sf::Color color = sf::Color::Transparent
    );

    static std::shared_ptr<Collider2D> CreatePolygonMesh
    (
      unsigned int num_sides,
      float radius,
      float init_rotation,
      const sf::Vector2f & InitialPosition,
      const sf::Vector2f & InitialVelocity,
      float mass,
      float CoeffOfRest,
      sf::Color color = sf::Color::Transparent,
      bool CastShadows = false
    );

    void SetCollisionCallback(std::function<void(LevelObject*)> Callback, bool NotifyEveryFrame = true);
    void SetSegmentCallback(std::function<void(PhysicsEngineSegmentType *)> Callback);
    void SetPositionChangeCallback(std::function<void(sf::Vector2f delta)> Callback);
    void SetSleepCallback(std::function<void(void)> Callback);
    void SetAwakenCallback(std::function<void(void)> Callback);
    void SetOverlapCallback(std::function<void(std::weak_ptr<Collider2D>)> Callback);
    void SetColliderStatus(ColliderProp Status);

    void Update(const ::vec2d &gravity);

    void Sleep();
    void Awaken();
    void EnableCollisions();
    void DisableCollision();

    bool IsAwake() const;
    bool IsEnabled() const;
    bool HasPhyicalResponse() const;
    bool IsActive() const;
    bool DoesCastShadows() const;

    void Move(const sf::Vector2f &Delta);
    void SetPosition(const sf::Vector2f &Position);
    void SetRespondsToOverlaps(bool b);

    sf::Vector2f GetPosition() const;

    bool HandleCollision(std::weak_ptr<Collider2D> Collider);
    bool HandleCollision(std::weak_ptr<Occluder2D> Occluder);
    bool HandleCollisionWithSegment(PhysicsEngineSegmentType* Collider);

    std::vector<::vec2d> GetVertices();

    std::weak_ptr<PhysicsEngineBaseMeshType> GetMesh();
    void SetObjectPtr(LevelObject *Object);
    LevelObject* GetObjectPtr() const;
    void PhysicsUpdate();

  protected:
    std::shared_ptr<PhysicsEngineBaseMeshType> m_Mesh;
    bool m_NotifyOfCollisionEveryFrame = true; //If true, a notification will be issues every frame two objects are overlapping
    std::bitset<32> m_Status;
    LevelObject *m_MyObject;
    std::function<void(LevelObject*)> m_CollisionCallback;
    std::function<void(PhysicsEngineSegmentType *)> m_HitSegmentCallback;
    std::function<void(std::weak_ptr<Collider2D>)> m_OverlapCallback;
    std::function<void(sf::Vector2f)> m_PositionChangeCallback;
    std::function<void(void)> m_SleepCallback;
    std::function<void(void)> m_AwakenCallback;
  };

}

#endif
