#include "../../Headers/Level/LevelObject.h"
#include "../../Headers/Actor/Actor.h"
#include "../../../ThirdParty/chaiscript/chaiscript.hpp"
#include "../../Headers/Physics/Collider.h"

namespace Engine
{
  LevelObject::LevelObject()
    :
    m_Animator(m_AnimationMap)
  {
    
  }

  LevelObject::LevelObject(const LevelObject &copy)
    : LevelObject()
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

  void LevelObject::ScriptInit()
  {
    try
    {
      ScriptEngine->eval("var " + ItemID + " = Player(\"" + ItemID + "\")");
    }
    catch (std::exception &err)
    {
      std::cerr << "Exception in LevelObject ScriptInit" << std::endl;

      throw err;
    }
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
    for (auto & collider : m_Colliders)
      collider->PhysicsUpdate();

    Sprite.setPosition(Position);
  }

  void LevelObject::Render(std::shared_ptr<sf::RenderTarget> Target)
  {
    Target->draw(Sprite);
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
    Position = pos;
    Sprite.setPosition(Position);
  }

	void LevelObject::SetSize(const sf::Vector2f & size)
	{
			Size = size;
	}

	void LevelObject::SetTexture(std::shared_ptr<sf::Texture> mytexture)
	{
			SpriteTexture = mytexture;
			Sprite.setTexture(*(SpriteTexture));
	}

  void LevelObject::SetTextureRect(sf::IntRect myRect)
  {
    Sprite.setTextureRect(myRect);
  }

  std::shared_ptr<sf::Texture> LevelObject::GetTexture() const
  {
    return SpriteTexture;
  }

  sf::Vector2f LevelObject::GetSize() const
  {
    return Size;
  }

  sf::IntRect LevelObject::GetTextureRect() const
  {
    return TextureRect;
  }

  void LevelObject::HandleInputEvent(const UserEvent & evnt)
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

  void LevelObject::Move(const sf::Vector2f & delta)
  {
    for (auto & collider : m_Colliders)
      collider->Move(delta);
    Sprite.move(delta);
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

  std::vector<std::shared_ptr<Collider2D>> LevelObject::GetColliders()
  {
    std::vector<std::shared_ptr<Collider2D>> RetColls;
    for (auto & coll : m_Colliders) {
      if (coll->IsAwake() && coll->IsEnabled())
        RetColls.push_back(coll);
    }

    return RetColls;
  }

  void LevelObject::AddCollider(std::shared_ptr<Collider2D> Collider)
  {
    m_Colliders.push_back(Collider);
  }

  void LevelObject::AddFrameAnimation(const std::string & ID, const std::vector<sf::IntRect>& Frames, sf::Time Duration)
  {
    m_FrameAnimations[ID] = {};
    for (auto & frame : Frames) {
      m_FrameAnimations[ID].addFrame(1.f, frame);
    }

    m_AnimationMap.addAnimation(ID, m_FrameAnimations[ID], Duration);
  }

}
