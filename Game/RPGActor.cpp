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

void RPGActor::HandleInputEvent(const Engine::UserEvent & evnt)
{
	if (evnt.EventType == Engine::UserEventType::KeyboardPress)
	{
		if (evnt.Key == sf::Keyboard::A)
			Velocity.x = -1;
		else if (evnt.Key == sf::Keyboard::S)
			Velocity.y = 1;
		else if (evnt.Key == sf::Keyboard::D)
			Velocity.x = 1;
		else if (evnt.Key == sf::Keyboard::W)
			Velocity.y = -1;
	}
	if (evnt.EventType == Engine::UserEventType::KeyboardRelease)
	{
		if (evnt.Key == sf::Keyboard::A || evnt.Key == sf::Keyboard::D)
			Velocity.x = 0;
		else if (evnt.Key == sf::Keyboard::S || evnt.Key == sf::Keyboard::W)
			Velocity.y = 0;
	}
}

void RPGActor::TickUpdate(const double & delta)
{
  Engine::LevelObject::TickUpdate(delta);
  /*
  //Right
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
  {
	  Velocity.x = 1;
  }
  else 
  {
	  Velocity.x = 0;
  }
  //Left
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
  {
	  Velocity.x = -1;
  }
  else
  {
	  Velocity.x = 0;
  }
  //Up
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
  {
	  Velocity.y = -1;
  }/*
  else
  {
	  Velocity.y = 0;
  }
  //Down
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
  {
	  Velocity.y = 1;
  }
  else/*
  {
	  Velocity.y = 0;
  }*/
  this->MoveObject({ Velocity.x*(float)delta*(float).1, Velocity.y*(float)delta*(float).1 });

}

void RPGActor::Render(std::shared_ptr<sf::RenderTarget> Target)
{
  Engine::LevelObject::Render(Target);



}

void RPGActor::HandleCollisionWithActor(std::weak_ptr<Engine::Collider2D> Collided)
{
}
