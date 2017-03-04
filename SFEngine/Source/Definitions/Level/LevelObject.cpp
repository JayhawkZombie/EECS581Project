#include "../../Headers/Level/LevelObject.h"

#include "../../Headers/Actor/Actor.h"

namespace Engine
{
  LevelObject::LevelObject()
    :
    Animations(std::make_shared<thor::AnimationMap<sf::Sprite, std::string>>()),
    Animator(std::make_shared<thor::Animator<sf::Sprite, std::string>>(*Animations))
  {

  }

  LevelObject::LevelObject(const LevelObject &copy)
  {

  }

  LevelObject::~LevelObject()
  {

  }

  void LevelObject::TickUpdate(const double &delta)
  {

  }

  void LevelObject::Render(std::shared_ptr<sf::RenderTarget> Target)
  {
    
  }

  void LevelObject::OnShutDown()
  {

  }

  void LevelObject::SerializeOut(std::ofstream &out)
  {

  }

  void LevelObject::SerializeIn(std::ifstream &in)
  {

  }

  void LevelObject::SetPosition(const sf::Vector2f &pos)
  {
    
  }

  void LevelObject::UpdateMesh()
  {
  }

  void LevelObject::UpdateSegments()
  {
  }

  void LevelObject::SetID(const std::string & ID)
  {
    BaseEngineInterface::SetID(ID);
  }

  void LevelObject::OnGameStart()
  {
  }

  void LevelObject::OnGameEnd()
  {
  }

  void LevelObject::OnKilled()
  {
  }

}