#ifndef SFENGINE_LEVEL_OBJECT_H
#define SFENGINE_LEVEL_OBJECT_H

#include "../BasicIncludes.h"
#include "../Engine/BaseEngineInterface.h"
#include "../Animation/Animation.h"
#include "../../../ThirdParty/PhysicsEngine.h"
#include <Thor\Animations.hpp>
#include <Thor\Time.hpp>

namespace Engine
{
  class GenericActor;
  class Player;
  class Level;

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

  protected:
    std::shared_ptr<
      thor::AnimationMap<sf::Sprite, std::string>> Animations;
    std::shared_ptr<
      thor::Animator<sf::Sprite, std::string>> Animator;
    std::map<std::string, thor::FrameAnimation> FrameAnimations;

    std::shared_ptr<PhysicsEngineBaseMeshType> ObjectMesh;
    std::shared_ptr<PhysicsEngineSegmentType> ObjectSegments;
	std::shared_ptr<sf::Texture> SpriteTexture;
	sf::Sprite Sprite;
    std::shared_ptr<sf::Texture> Texture;
    sf::IntRect TextureRect;
    sf::RectangleShape ObjectRect;
    //Objects can be animated
    //std::map<std::string, std::shared_ptr<Animation>> Animations;
	float MeshRadius = 0.f;
    bool AllowsActorOverlap; //if false, then actors will never be allowed to cross over this object
    bool RenderOutlined;
    bool TestingCollisions;
  };
}



#endif