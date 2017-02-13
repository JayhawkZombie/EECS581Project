#include "../../Headers/Objects/ProjectileBase.h"

namespace Engine
{

  ProjectileBase::ProjectileBase()
    : Origin({ 0,0 }), Direction({ 0,0 }), Velocity({ 0,0 })
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

  void ProjectileBase::OnShutDown()
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

  void ProjectileBase::UpdateMesh()
  {
  }

  void ProjectileBase::UpdateSegments()
  {
  }

  sf::Vector2f ProjectileBase::GetOrigin() const
  {
    return Origin;
  }

  sf::Vector2f ProjectileBase::GetDirection() const
  {
    return Direction;
  }

  sf::Vector2f ProjectileBase::GetVelocity() const
  {
    return Velocity;
  }

}
