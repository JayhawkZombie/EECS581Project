#include "RPGActor.h"
//Constructors/Destructors

#include <Thor\Animations.hpp>

RPGActor::RPGActor()
{
	m_name = "";
  m_filePath = "";
  /*
  m_Colliders.push_back(Engine::Collider2D::CreatePolygonMesh(4, 16.f, 0.f, { Position.x, Position.y }, { 0, 0 }, 1.f, 0.4f, sf::Color::Blue));
  m_Colliders[0]->SetCollisionCallback(
    [this](auto ptr) { this->HandleCollisionWithActor(ptr); }
  );
  */


  AddAnimations();
  m_Animator.play() << "myActor_standDown";
  m_Animator.animate(Sprite);
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
		if (evnt.Key == sf::Keyboard::A||evnt.Key == sf::Keyboard::Left) {
			m_Animator.play() << "myActor_walkLeft" << thor::Playback::loop("myActor_walkLeft");
			Velocity.x = -1;

		}
		else if (evnt.Key == sf::Keyboard::S||evnt.Key == sf::Keyboard::Down) {
			m_Animator.play() << "myActor_walkDown" << thor::Playback::loop("myActor_walkDown");
			Velocity.y = 1;
		}
		else if (evnt.Key == sf::Keyboard::D||evnt.Key == sf::Keyboard::Right) {
			m_Animator.play() << "myActor_walkRight" << thor::Playback::loop("myActor_walkRight");
			Velocity.x = 1;
		}
		else if (evnt.Key == sf::Keyboard::W||evnt.Key == sf::Keyboard::Up) {
			m_Animator.play() << "myActor_walkUp" << thor::Playback::loop("myActor_walkUp");
			Velocity.y = -1;
		}
	}
	if (evnt.EventType == Engine::UserEventType::KeyboardRelease)
	{
		if (evnt.Key == sf::Keyboard::A || evnt.Key == sf::Keyboard::Left) {
			Velocity.x = 0;
			m_Animator.play() << "myActor_standLeft";
		}
		else if (evnt.Key == sf::Keyboard::D || evnt.Key == sf::Keyboard::Right) {
			Velocity.x = 0;
			m_Animator.play() << "myActor_standRight";
		}
		else if (evnt.Key == sf::Keyboard::S || evnt.Key == sf::Keyboard::Down) {
			Velocity.y = 0;
			m_Animator.play() << "myActor_standDown";
		}
		else if (evnt.Key == sf::Keyboard::W || evnt.Key == sf::Keyboard::Up) {
			Velocity.y = 0;
			m_Animator.play() << "myActor_standUp";
		}
	}
}

void RPGActor::AddAnimations()
{
	sf::IntRect myActor_standDown_frame1(0, 0, 256, 256);
	sf::IntRect myActor_standUp_frame1(256, 0, 256, 256);
	sf::IntRect myActor_standLeft_frame1(512, 0, 256, 256);
	sf::IntRect myActor_standRight_frame1(768, 0, 256, 256);
	sf::IntRect myActor_walkDown_frame1(0, 0, 256, 256);
	sf::IntRect myActor_walkDown_frame2(0, 256, 256, 256);
	sf::IntRect myActor_walkDown_frame3(0, 512, 256, 256);
	sf::IntRect myActor_walkUp_frame1(256, 0, 256, 256);
	sf::IntRect myActor_walkUp_frame2(256, 256, 256, 256);
	sf::IntRect myActor_walkUp_frame3(256, 512, 256, 256);
	sf::IntRect myActor_walkLeft_frame1(512, 0, 256, 256);
	sf::IntRect myActor_walkLeft_frame2(512, 256, 256, 256);
	sf::IntRect myActor_walkLeft_frame3(512, 512, 256, 256);
	sf::IntRect myActor_walkRight_frame1(768, 0, 256, 256);
	sf::IntRect myActor_walkRight_frame2(768, 256, 256, 256);
	sf::IntRect myActor_walkRight_frame3(768, 512, 256, 256);

	thor::FrameAnimation myActor_standDown;
	myActor_standDown.addFrame(1.f, myActor_standDown_frame1);
	thor::FrameAnimation myActor_standUp;
	myActor_standUp.addFrame(1.f, myActor_standUp_frame1);
	thor::FrameAnimation myActor_standLeft;
	myActor_standLeft.addFrame(1.f, myActor_standLeft_frame1);
	thor::FrameAnimation myActor_standRight;
	myActor_standRight.addFrame(1.f, myActor_standRight_frame1);

	thor::FrameAnimation myActor_walkDown;
	myActor_walkDown.addFrame(1.f, myActor_walkDown_frame1);
	myActor_walkDown.addFrame(1.f, myActor_walkDown_frame2);
	myActor_walkDown.addFrame(1.f, myActor_walkDown_frame3);

	thor::FrameAnimation myActor_walkUp;
	myActor_walkUp.addFrame(1.f, myActor_walkUp_frame1);
	myActor_walkUp.addFrame(1.f, myActor_walkUp_frame2);
	myActor_walkUp.addFrame(1.f, myActor_walkUp_frame3);

	thor::FrameAnimation myActor_walkLeft;
	myActor_walkLeft.addFrame(1.f, myActor_walkLeft_frame1);
	myActor_walkLeft.addFrame(1.f, myActor_walkLeft_frame2);
	myActor_walkLeft.addFrame(1.f, myActor_walkLeft_frame3);

	thor::FrameAnimation myActor_walkRight;
	myActor_walkRight.addFrame(1.f, myActor_walkRight_frame1);
	myActor_walkRight.addFrame(1.f, myActor_walkRight_frame2);
	myActor_walkRight.addFrame(1.f, myActor_walkRight_frame3);

	m_AnimationMap.addAnimation("myActor_standDown", myActor_standDown, sf::microseconds(1));
	m_AnimationMap.addAnimation("myActor_standUp", myActor_standUp, sf::microseconds(1));
	m_AnimationMap.addAnimation("myActor_standLeft", myActor_standLeft, sf::microseconds(1));
	m_AnimationMap.addAnimation("myActor_standRight", myActor_standRight, sf::microseconds(1));
	m_AnimationMap.addAnimation("myActor_walkDown", myActor_walkDown, sf::seconds(0.6f));
	m_AnimationMap.addAnimation("myActor_walkUp", myActor_walkUp, sf::seconds(0.6f));
	m_AnimationMap.addAnimation("myActor_walkLeft", myActor_walkLeft, sf::seconds(0.6f));
	m_AnimationMap.addAnimation("myActor_walkRight", myActor_walkRight, sf::seconds(0.6f));

	//myActor_texture.loadFromFile("./Projects/TestProject/Textures/Guy12FSpriteSheetBig.png");
	Sprite.scale({ 16 / 256.f, 16 / 256.f });
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
  static sf::Clock c;
  m_Animator.update(c.restart());
  m_Animator.animate(Sprite);

}

void RPGActor::Render(std::shared_ptr<sf::RenderTarget> Target)
{
  Engine::LevelObject::Render(Target);



}

void RPGActor::HandleCollisionWithActor(std::weak_ptr<Engine::Collider2D> Collided)
{
}
