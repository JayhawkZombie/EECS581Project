#include "../../Headers/Physics/Collider.h"
#include "../../../ThirdParty/PhysicsEngine.h"

namespace Engine
{
  /*
    Collider2D
  */

  Collider2D::Collider2D()
  {
    m_Status.set(ColliderProp::HasPhysicalResponse);
    m_Status.set(ColliderProp::Enabled);
    m_Status.set(ColliderProp::NotifyEveryFrame);
  }

  Collider2D::~Collider2D()
  {
    m_Mesh.reset();
  }

  void Collider2D::SetMesh(std::shared_ptr<PhysicsEngineBaseMeshType> MeshPtr)
  {
    m_Mesh = MeshPtr;
  }

  sf::FloatRect Collider2D::GetGlobalBounds() const
  {
    return sf::FloatRect(
      m_Mesh->pos.x, m_Mesh->pos.y,
      m_Mesh->siz.x, m_Mesh->siz.y
    );
  }

  std::shared_ptr<Collider2D> Collider2D::CreateCircularMesh
  (
    MeshType type, 
    const sf::Vector2f & position, 
    const sf::Vector2f & velocity, 
    unsigned int radius, 
    float mass, 
    float coeffOfRest, 
    sf::Color color
  )
  {
    char bType;
    switch (type)
    {
      case MeshType::Ball:
        bType = 'B'; break;
      case MeshType::BallGo:
        bType = 'G'; break;
      default:
        bType = 'B'; break;
    }

    std::shared_ptr<PhysicsEngineBaseMeshType> Mesh 
      = BuildBallMesh(bType, position, velocity, radius, mass, coeffOfRest, color);

    std::shared_ptr<Collider2D> Collider = std::make_shared<Collider2D>();
    Collider->m_Mesh = Mesh;

    return Collider;
  }

  std::shared_ptr<Collider2D> Collider2D::CreatePolygonMesh
  (
    unsigned int num_sides, 
    float radius, 
    float init_rotation, 
    const sf::Vector2f & InitialPosition, 
    const sf::Vector2f & InitialVelocity, 
    float mass, 
    float CoeffOfRest, 
    sf::Color color
  )
  {
    std::shared_ptr<PhysicsEngineBaseMeshType> Mesh
      = BuildPolygonMesh(num_sides, radius, init_rotation, InitialPosition, InitialVelocity, mass, CoeffOfRest, color);

    std::shared_ptr<Collider2D> Collider = std::make_shared<Collider2D>();
    Collider->m_Mesh = Mesh;

    return Collider;
  }

  void Collider2D::SetCollisionCallback(std::function<void(std::weak_ptr<Collider2D>)> Callback, bool NotifyEveryFrame)
  {
    m_NotifyOfCollisionEveryFrame = NotifyEveryFrame;
    m_Status |= (m_NotifyOfCollisionEveryFrame ?
                 ColliderProp::NotifyEveryFrame :
                 ColliderProp::SingleResponsePerObj
                 );
    m_CollisionCallback = Callback;
  }

  void Collider2D::SetPositionChangeCallback(std::function<void(sf::Vector2f delta)> Callback)
  {
    m_PositionChangeCallback = Callback;
  }

  void Collider2D::SetSleepCallback(std::function<void(void)> Callback)
  {
    m_SleepCallback = Callback;
  }

  void Collider2D::SetAwakenCallback(std::function<void(void)> Callback)
  {
    m_AwakenCallback = Callback;
  }

  void Collider2D::SetOverlapCallback(std::function<void(std::weak_ptr<Collider2D>)> Callback)
  {
  }

  void Collider2D::SetColliderStatus(ColliderProp Status)
  {
    m_Status = Status;
  }

  void Collider2D::Update(const::vec2d & gravity)
  {
    if (m_Mesh)
      m_Mesh->update(gravity);
  }

  void Collider2D::Sleep()
  {
    m_Status.set(ColliderProp::Sleeping);
  }

  void Collider2D::Awaken()
  {
    m_Status.set(ColliderProp::Active);
    m_Status.reset(ColliderProp::Sleeping);
  }

  void Collider2D::EnableCollisions()
  {
    m_Status.set(ColliderProp::Enabled);
  }

  void Collider2D::DisableCollision()
  {
    m_Status.reset(ColliderProp::Enabled);
  }

  bool Collider2D::IsAwake() const
  {
    return !m_Status.test(ColliderProp::Sleeping);
  }

  bool Collider2D::IsEnabled() const
  {
    return m_Status.test(ColliderProp::Enabled);
  }

  bool Collider2D::HasPhyicalResponse() const
  {
    return m_Status.test(ColliderProp::HasPhysicalResponse);
  }

  bool Collider2D::IsActive() const
  {
    return m_Status.test(ColliderProp::Active);
  }

  void Collider2D::Move(const sf::Vector2f & Delta)
  {
    if (m_Mesh) {
      m_Mesh->pos += ::vec2d(Delta.x, Delta.y);
    }
  }

  void Collider2D::SetPosition(const sf::Vector2f & Position)
  {
    if (m_Mesh) {
      m_Mesh->pos = { Position.x, Position.y };
    }
  }

  void Collider2D::SetRespondsToOverlaps(bool b)
  {
    if (b) {
      m_Status.set(ColliderProp::NotifyOfOverlap);
      m_Status.reset(ColliderProp::HasPhysicalResponse);
    }
    else {
      m_Status.set(ColliderProp::HasPhysicalResponse);
      m_Status.reset(ColliderProp::NotifyOfOverlap);
    }
  }

  bool Collider2D::HandleCollision(std::weak_ptr<Collider2D> Collider)
  {
    if (m_Status.test(ColliderProp::Active) && m_Status.test(ColliderProp::Enabled)) {
      m_CollisionCallback(Collider);
    }

    return m_Status.test(ColliderProp::HasPhysicalResponse);
  }

  std::weak_ptr<PhysicsEngineBaseMeshType> Collider2D::GetMesh()
  {
    return m_Mesh;
  }

  void Collider2D::PhysicsUpdate()
  {
  }

}
