#ifndef SFENGINE_PROJECTILE_BASE_H
#define SFENGINE_PROJECTILE_BASE_H

#include "../Level/LevelObject.h"
#include "../../../ThirdParty/PhysicsEngine.h"

namespace Engine
{

  class LevelObject;

  class ProjectileBase : LevelObject
  {
  public:
    ProjectileBase();
    virtual ~ProjectileBase();

    void OnObjectHit(LevelObject *objectHit);
    void SetOrigin(const sf::Vector2f &Point);
    void SetDirection(const sf::Vector2f &Dir);
    void SetVelocity(const sf::Vector2f &Vel);


    virtual void TickUpdate(const double &delta) override;
    virtual void Render(std::shared_ptr<sf::RenderTarget> Target) override;
    virtual void OnShutDown() override;
    virtual void SerializeOut(std::ofstream &out) override;
    virtual void SerializeIn(std::ifstream &in) override;
    virtual void SetPosition(const sf::Vector2f &pos);

    virtual PhysicsEngineBaseMeshType* GetMesh() const {
      return ObjectMesh.get();
    }

    virtual PhysicsEngineSegmentType* GetSegments() const {
      return ObjectSegments.get();
    }

    virtual void UpdateMesh();
    virtual void UpdateSegments();


    sf::Vector2f GetOrigin() const;
    sf::Vector2f GetDirection() const;
    sf::Vector2f GetVelocity() const;
  protected:
    sf::Vector2f Origin;
    sf::Vector2f Direction;
    sf::Vector2f Velocity;
    
    std::shared_ptr<PhysicsEngineBaseMeshType> CollisionMesh;
  };

}

#endif
