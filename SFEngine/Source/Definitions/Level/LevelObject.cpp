#include "../../Headers/Level/LevelObject.h"
#include "../../Headers/Actor/Actor.h"
#include "../../../ThirdParty/chaiscript/chaiscript.hpp"

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
//Starting the chaiscript bindings, need to figure out which functions need scripted
  void LevelObject::BindScriptMethods(chaiscript::ModulePtr mptr)
  {

	  chaiscript::utility::add_class<Engine::LevelObject>(
		  *mptr,
		  "LevelObject",
		  { 
			  chaiscript::constructor<Engine::LevelObject()>() },
			  { 
          { chaiscript::fun(static_cast<void(LevelObject::*)(void)>(&LevelObject::OnKilled)), "OnKilled" },
          { chaiscript::fun(static_cast<void(LevelObject::*)(const sf::Vector2f &)>(&LevelObject::MoveObject)), "MoveObject" }
        }
	  );
  }

  void LevelObject::TickUpdate(const double &delta)
  {
    try
    {
      ScriptEngine->eval(ItemID + ".Update()");
    }
    catch (std::exception &err)
    {
      std::cerr << "Script error: " << err.what() << std::endl;
    }
  }

  void LevelObject::PhysicsUpdate()
  {
    Position = { ObjectMesh->pos.x - MeshRadius, ObjectMesh->pos.y - MeshRadius };
    Velocity = { ObjectMesh->v.x, ObjectMesh->v.y };
    Sprite.setPosition(Position);
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

  sf::FloatRect LevelObject::GetGlobalBounds() const
  {
    return sf::FloatRect();
  }

  void LevelObject::AttachComponent(std::shared_ptr<CollisionComponent> Component)
  {
  }

  void LevelObject::AttachComponent(std::shared_ptr<ScriptComponent> Component)
  {

  }

  void LevelObject::AttachComponent(std::shared_ptr<InteractionComponent> Component)
  {

  }

  void LevelObject::Move(const sf::Vector2f & delta)
  {
    ObjectMesh->pos += vec2d(delta.x, delta.y);
    ObjectMesh->v = vec2d(0, 0);
  }

  void LevelObject::Move(float x, float y)
  {
    Move(sf::Vector2f(x, y));
  }

  void LevelObject::Move(int x, int y)
  {
    Move(sf::Vector2f((float)x, (float)y));
  }

  void LevelObject::MoveObject(const sf::Vector2f &delta)
  {
    Move(delta);
  }

}