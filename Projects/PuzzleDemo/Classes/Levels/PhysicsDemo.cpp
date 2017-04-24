#include "PhysicsDemo.h"


PhysicsDemoLevel::PhysicsDemoLevel()
  :
  m_PColorAnimation1(m_PColorGradient1),
  m_PFadeAnimation1(0.1f, 0.1f),
  m_PTorqueAffector1(100.f),
  m_PGravityAffector1(sf::Vector2f(0.f, 5.f)),
  BasicLevel(sf::Vector2u(1700, 900), sf::FloatRect(0, 0, 1700, 900))
{

}

PhysicsDemoLevel::~PhysicsDemoLevel()
{

}

void PhysicsDemoLevel::CleanUp()
{

}

void PhysicsDemoLevel::OnEnd()
{

}

void PhysicsDemoLevel::OnBegin()
{

}

void PhysicsDemoLevel::OnShutDown()
{

}

void PhysicsDemoLevel::EventUpdate(sf::Event event)
{

}

void PhysicsDemoLevel::TickUpdate(const double &delta)
{

}

void PhysicsDemoLevel::HandleInputEvent(const Engine::UserEvent &evnt)
{

}

void PhysicsDemoLevel::Render(std::shared_ptr<sf::RenderTarget> Target)
{

}

void PhysicsDemoLevel::RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture)
{

}

void PhysicsDemoLevel::SetNextLevel(std::shared_ptr<Engine::BasicLevel> NextLevel)
{

}

std::string PhysicsDemoLevel::GetClass() const
{

}
