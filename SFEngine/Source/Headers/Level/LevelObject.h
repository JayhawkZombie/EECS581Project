#ifndef SFENGINE_LEVEL_OBJECT_H
#define SFENGINE_LEVEL_OBJECT_H

#include "../Engine/BaseEngineInterface.h"
#include "../Animation/Animation.h"
#include "../Components/ComponentBase.h"
#include "../../../ThirdParty/PhysicsEngine.h"

#include <Thor\Animations.hpp>

namespace Engine
{
  class GenericActor;
  class Player;
  class Level;
  class BasicLevel;
  class Collider2DComponent;
  class Collider2D;
  class Interact2DComponent;

  enum class OverlapAction
  {
    KILL_ACTOR = 0,
    DISALLOW_ACTOR_OVERLAP = 1,
    CUSTOM_ACTION
  };

  class LevelObject : public BaseEngineInterface
  {
  public:
	friend class Level;
  friend class BasicLevel;
    LevelObject();
    LevelObject(const LevelObject &obj);
    virtual ~LevelObject();

    static void BindScriptMethods(chaiscript::ModulePtr module);
    virtual void ScriptInit();
    virtual void TickUpdate(const double &delta) override;
    virtual void PhysicsUpdate();
    virtual void Render(std::shared_ptr<sf::RenderTarget> Target) override;
    virtual void OnShutDown() override;
    virtual void SerializeOut(std::ofstream &out) override;
    virtual void SerializeIn(std::ifstream &in) override;
    virtual void SetPosition(const sf::Vector2f &pos);
		virtual void SetSize(const sf::Vector2f &size);
		virtual void SetTexture(std::shared_ptr<sf::Texture> mytexture);
    virtual void SetTextureRect(sf::IntRect myRect);
	
	virtual sf::Vector2i getUpperLeft() const;
	virtual sf::Vector2i getLowerRight() const;
    std::shared_ptr<sf::Texture> GetTexture() const;
    sf::Vector2f GetSize() const;
    sf::IntRect GetTextureRect() const;

    virtual void HandleInputEvent(const UserEvent &evnt);
    virtual void SetID(const std::string &ID) override;

    virtual void OnGameStart();
    virtual void OnGameEnd();
    virtual void OnKilled();
    virtual void OnSpawn();

    static void AddItemAnimation(std::shared_ptr<LevelObject> Item, const std::string &animName);
    sf::FloatRect GetGlobalBounds() const;

    virtual void Move(const sf::Vector2f &delta);
    virtual void Move(float x, float y);
    virtual void Move(int x, int y);

    void MoveObject(const sf::Vector2f &delta);

    std::vector<std::shared_ptr<Collider2D>> GetColliders();
    void AddCollider(std::shared_ptr<Collider2D> Collider);

    void AddFrameAnimation(const std::string &ID, const std::vector<sf::IntRect> &Frames, sf::Time Duration);

  protected:
    thor::AnimationMap<sf::Sprite, std::string> m_AnimationMap;
    thor::Animator<sf::Sprite, std::string> m_Animator;
    std::unordered_map<std::string, thor::FrameAnimation> m_FrameAnimations;

    std::vector<std::shared_ptr<Collider2D>> m_Colliders;

  	std::shared_ptr<sf::Texture> SpriteTexture;
	  sf::Sprite Sprite;
    sf::IntRect TextureRect;
    sf::RectangleShape ObjectRect;
    sf::Vector2f Velocity;
    sf::Vector2f Acceleration;
    sf::Vector2f Position;
    sf::Vector2f Size;
    float MeshRadius = 0.f;
    bool AllowsActorOverlap; //if false, then actors will never be allowed to cross over this object
    bool RenderOutlined;
    bool TestingCollisions;
  };
}



#endif