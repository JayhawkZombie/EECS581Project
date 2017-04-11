#include "../../Headers/Objects/ProjectileBase.h"
#include "../../Headers/Physics/Collider.h"

namespace Engine
{

  ProjectileBase::ProjectileBase()
    : m_Origin({ 0,0 }), m_Direction({ 0,0 }), m_Velocity({ 0,0 })
  {
  }

  ProjectileBase::~ProjectileBase()
  {
  }

  void ProjectileBase::OnObjectHit(LevelObject * objectHit)
  {
  }

  void ProjectileBase::SetOrigin(const sf::Vector2f & Point)
  {
  }

  void ProjectileBase::SetDirection(const sf::Vector2f & Dir)
  {
  }

  void ProjectileBase::SetVelocity(const sf::Vector2f & Vel)
  {
  }

  void ProjectileBase::TickUpdate(const double & delta)
  {
  }

  void ProjectileBase::Render(std::shared_ptr<sf::RenderTarget> Target)
  {
  }

  void ProjectileBase::Kill()
  {
  }

  void ProjectileBase::SerializeOut(std::ofstream & out)
  {
  }

  void ProjectileBase::SerializeIn(std::ifstream & in)
  {
  }

  void ProjectileBase::SetPosition(const sf::Vector2f & pos)
  {
  }

  void ProjectileBase::SetTexture(std::shared_ptr<sf::Texture> Texture)
  {
  }

  void ProjectileBase::SetCollisionCallback(std::function<void(std::weak_ptr<Collider2D>)> Callback)
  {
  }

  sf::Vector2f ProjectileBase::GetOrigin() const
  {
    return m_Origin;
  }

  sf::Vector2f ProjectileBase::GetDirection() const
  {
    return m_Direction;
  }

  sf::Vector2f ProjectileBase::GetVelocity() const
  {
    return m_Velocity;
  }

}
