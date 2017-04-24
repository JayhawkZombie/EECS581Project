#include "Level\LevelObject.h"
#include "Actor\Actor.h"
#include "Physics\Collider.h"
#include "Physics\Occluder.h"

#include "chaiscript\chaiscript.hpp"

namespace Engine
{
  LevelObject::LevelObject()
    :
    m_Animator(m_AnimationMap)
  {
    
  }

  LevelObject::~LevelObject()
  {

  }
  


  LevelObject::LevelObject(const LevelObject & obj)
    : 
    m_Animator(m_AnimationMap),
    Position(obj.Position), 
    Size(obj.Size), 
    SpriteTexture(obj.SpriteTexture),
    Acceleration(obj.Acceleration), 
    AllowsActorOverlap(obj.AllowsActorOverlap),
    ObjectRect(obj.ObjectRect), 
    TextureRect(obj.TextureRect),
    RenderOutlined(obj.RenderOutlined), 
    Velocity(obj.Velocity),
    BaseEngineInterface()
  {
    
    for (auto & collider : obj.m_Colliders) {
      m_Colliders.push_back(collider->Clone());
    }

  }

  std::shared_ptr<BaseEngineInterface> LevelObject::Clone() const
  {
    auto Object = std::make_shared<LevelObject>(*this);

    for (auto & collider : m_Colliders) {
      Object->m_Colliders.push_back(collider->Clone());
    }

    return Object;
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

  }

  void LevelObject::TickUpdate(const double &delta)
  {
    
  }

  void LevelObject::PhysicsUpdate()
  {
    for (auto & collider : m_Colliders)
      collider->PhysicsUpdate();

	if (!(m_Colliders.size() > 0))
		return;

	  auto v = m_Colliders[0]->GetMesh().lock();
	  if (v) {
      Position = sf::Vector2f(v->pos.x, v->pos.y);
		  Sprite.setPosition({ v->pos.x - Size.x / 2.f, v->pos.y - Size.y / 2.f });
	  }
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

  sf::Vector2i LevelObject::getTopRight() const
  {
	  return{ (int)Position.x + Sprite.getTextureRect().width, (int)Position.y };
  }

  sf::Vector2i LevelObject::getTopLeft() const
  {
	  return{(int)Position.x,(int)Position.y};
  }

  sf::Vector2i LevelObject::getBottomLeft() const
  {
	  return{ (int)Position.x,(int)Position.y + Sprite.getTextureRect().height };
  }

  sf::Vector2i LevelObject::getBottomRight() const
  {
	  return{ (int)Position.x + Sprite.getTextureRect().width,(int)Position.y + Sprite.getTextureRect().height };
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

  void LevelObject::HandleCollisionWithObject(LevelObject * Object)
  {
    if (m_HandleCollisionWithObject)
      m_HandleCollisionWithObject(Object);
  }

  void LevelObject::SetCollisionHandleCallback(std::function<void(LevelObject*)> Callback)
  {
    m_HandleCollisionWithObject = Callback;
  }

  void LevelObject::HandleCollisionWithCollider(SPtrShared<Collider2D> Collider)
  {
  }

  void LevelObject::HandleCollisionWithSegment(PhysicsEngineSegmentType *Segment)
  {
    auto pos = Segment->pos;
    auto diff = Position - sf::Vector2f(pos.x, pos.y);

    sf::Vector2f move = { 0, 0 };
    
    auto right = Position.x + Size.x;
    auto top = Position.y + Size.y;
    
    //If the distance from our right to the segment is less than our size
    // we need to be pushed back a bit
    // 
    //Case for when we aproach from the left
    if (Position.x <= pos.x && right > pos.x)
      move.x = 1.2f * (pos.x - Position.x);
    else if (pos.x <= right && Position.x < pos.x)
      move.x = 1.2f * (right - pos.x);

    if (pos.y >= Position.y && top > pos.y)
      move.y = 1.2f * (pos.y - Position.y);
    else if (top >= pos.y && Position.y <= pos.y)
      move.y = 1.2f * (top - pos.y);

    MoveObject(move);
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

  void LevelObject::OnSpawn()
  {
  }

  void LevelObject::Reset()
  {
  }

  sf::FloatRect LevelObject::GetGlobalBounds() const
  {
	  return sf::FloatRect(
		  Position,
		  Size
	  );
  }

  void LevelObject::Move(const sf::Vector2f & delta)
  {
    for (auto & collider : m_Colliders)
      collider->Move(delta);
    for (auto & occluder : m_Occluders)
      occluder->Move(delta);
	  Position += delta;
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

  std::vector<std::shared_ptr<Collider2D>> LevelObject::GetColliders() const
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
    m_Colliders.back()->SetObjectPtr(this);
  }

  std::vector<std::shared_ptr<Collider2D>> LevelObject::GetOccluders() const
  {
    static std::vector<std::shared_ptr<Collider2D>> _Occluders;
    _Occluders.clear();

    for (auto & collider : m_Colliders) {
      if (collider->DoesCastShadows())
        _Occluders.push_back(collider);
    }

    return _Occluders;
  }

  void LevelObject::AddOccluder(std::shared_ptr<Collider2D> Collider)
  {
    AddCollider(Collider);
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
