#ifndef SFENGINE_LEVEL_OBJECT_H
#define SFENGINE_LEVEL_OBJECT_H

#include "../Engine/BaseEngineInterface.h"
#include "../Animation/Animation.h"
#include "../../../ThirdParty/PhysicsEngine.h"
#include "../Components/ComponentManager.h"

namespace Engine
{
  class GenericActor;
  class Player;
  class Level;
  class Collider2DComponent;
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
    LevelObject();
    LevelObject(const LevelObject &obj);
    virtual ~LevelObject();

    static void BindScriptMethods(chaiscript::ModulePtr module);

    virtual void TickUpdate(const double &delta) override;
    virtual void PhysicsUpdate();
    virtual void Render(std::shared_ptr<sf::RenderTarget> Target) override;
    virtual void OnShutDown() override;
    virtual void SerializeOut(std::ofstream &out) override;
    virtual void SerializeIn(std::ifstream &in) override;
    virtual void SetPosition(const sf::Vector2f &pos);

    virtual std::shared_ptr<PhysicsEngineBaseMeshType> GetMesh() const {
      return ObjectMesh;
    }

    virtual std::shared_ptr<PhysicsEngineSegmentType> GetSegments() const {
      return ObjectSegments;
    }

    virtual void UpdateMesh();
    virtual void UpdateSegments();
    virtual void SetID(const std::string &ID) override;

    virtual void OnGameStart();
    virtual void OnGameEnd();
    virtual void OnKilled();

    static void AddItemAnimation(std::shared_ptr<LevelObject> Item, const std::string &animName);
    sf::FloatRect GetGlobalBounds() const;

    virtual void AttachComponent(std::shared_ptr<CollisionComponent> Component);
    virtual void AttachComponent(std::shared_ptr<ScriptComponent> Component);
    virtual void AttachComponent(std::shared_ptr<InteractionComponent> Component);

    virtual void Move(const sf::Vector2f &delta);
    virtual void Move(float x, float y);
    virtual void Move(int x, int y);

    void MoveObject(const sf::Vector2f &delta);

  protected:
    std::shared_ptr<
      thor::AnimationMap<sf::Sprite, std::string>> Animations;
    std::shared_ptr<
      thor::Animator<sf::Sprite, std::string>> Animator;
    std::map<std::string, thor::FrameAnimation> FrameAnimations;
    ComponentManager Components;

    std::shared_ptr<PhysicsEngineBaseMeshType> ObjectMesh;
    std::shared_ptr<PhysicsEngineSegmentType> ObjectSegments;
  	std::shared_ptr<sf::Texture> SpriteTexture;
	  sf::Sprite Sprite;
    std::shared_ptr<sf::Texture> Texture;
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