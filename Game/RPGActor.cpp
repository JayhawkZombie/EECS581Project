#include "RPGActor.h"
//Constructors/Destructors

RPGActor::RPGActor()
{
	m_name = "";
  m_filePath = "";

  m_Colliders.push_back(Engine::Collider2D::CreatePolygonMesh(4, 32.f, 0.f, { 0, 0 }, { 0, 0 }, 1.f, 0.4f, sf::Color::Transparent));
  m_Colliders[0]->SetCollisionCallback(
    [this](auto ptr) { this->HandleCollisionWithActor(ptr); }
  );
}


RPGActor::~RPGActor()
{
}

//Getters/Setters
std::string RPGActor::getName() const
{
	return m_name;
}

std::string RPGActor::getFilePath() const
{
  return m_filePath;
}

void RPGActor::setName(std::string name)
{
	m_name = name;
}

void RPGActor::setFilePath(std::string filePath)
{
  m_filePath = filePath;
}

void RPGActor::TickUpdate(const double & delta)
{
  Engine::LevelObject::TickUpdate(delta);

}

void RPGActor::Render(std::shared_ptr<sf::RenderTarget> Target)
{
  Engine::LevelObject::Render(Target);



}

void RPGActor::HandleCollisionWithActor(std::weak_ptr<Engine::Collider2D> Collided)
{
}
