#ifndef SFENGINE_PROJECTILE_BASE_H
#define SFENGINE_PROJECTILE_BASE_H

#include "../Level/LevelObject.h"
#include "../../../ThirdParty/PhysicsEngine.h"

namespace Engine
{
  
  class ProjectileBase
  {
  public:
    ProjectileBase();
    virtual ~ProjectileBase();

    virtual std::shared_ptr<ProjectileBase> Clone() = 0;

    virtual void OnObjectHit(LevelObject *objectHit) = 0;
    void SetOrigin(const sf::Vector2f &Point);
    void SetDirection(const sf::Vector2f &Dir);
    void SetVelocity(const sf::Vector2f &Vel);


    virtual void TickUpdate(const double &delta) = 0;
    virtual void Render(std::shared_ptr<sf::RenderTarget> Target) = 0;
    virtual void Kill() = 0;
    virtual void SerializeOut(std::ofstream &out);
    virtual void SerializeIn(std::ifstream &in);
    virtual void SetPosition(const sf::Vector2f &pos);
    virtual void SetTexture(std::shared_ptr<sf::Texture> Texture);

    virtual void SetCollisionCallback(std::function<void(std::weak_ptr<Collider2D>)> Callback);

    sf::Vector2f GetOrigin() const;
    sf::Vector2f GetDirection() const;
    sf::Vector2f GetVelocity() const;
  protected:
    sf::Sprite m_Sprite;
    sf::Vector2f m_Origin;
    sf::Vector2f m_Direction;
    sf::Vector2f m_Velocity;
    std::shared_ptr<Collider2D> m_Collider;
  };

}

#endif
