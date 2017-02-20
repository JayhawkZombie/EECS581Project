#ifndef SFENGINE_LEVEL_OBJECT_H
#define SFENGINE_LEVEL_OBJECT_H

#include "../BasicIncludes.h"
#include "../Engine/BaseEngineInterface.h"
#include "../Animation/Animation.h"
#include "../../../ThirdParty/PhysicsEngine.h"

namespace Engine
{
  class GenericActor;
  class Player;

  enum class OverlapAction
  {
    KILL_ACTOR = 0,
    DISALLOW_ACTOR_OVERLAP = 1,
    CUSTOM_ACTION
  };

  class LevelObject : public BaseEngineInterface
  {
  public:

    LevelObject();
    LevelObject(const LevelObject &obj);
    virtual ~LevelObject();

    virtual void TickUpdate(const double &delta) override;
    virtual void Render(std::shared_ptr<sf::RenderTarget> Target) override;
    virtual void OnShutDown() override;
    virtual void SerializeOut(std::ofstream &out) override;
    virtual void SerializeIn(std::ifstream &in) override;
    virtual void SetPosition(const sf::Vector2f &pos);

    virtual PhysicsEngineBaseMeshType* GetMesh() const {
      return ObjectMesh.get();
    }

    virtual PhysicsEngineSegmentType* GetSegments() const {
      return ObjectSegments.get();
    }

    virtual void UpdateMesh();
    virtual void UpdateSegments();
    virtual void SetID(const std::string &ID) override;

    virtual void OnGameStart();
    virtual void OnGameEnd();
    virtual void OnKilled();

  protected:

    std::string GameStartEvalString;
    std::string GameEndEvalString;
    std::string KilledEvalString;
    std::string UpdateEvalString;

    //Strings for invoking methods
    static std::string GAME_START_STRING;
    static std::string GAME_END_STRING;
    static std::string KILLED_STRING;
    static std::string UPDATE_STRING;

    std::shared_ptr<PhysicsEngineBaseMeshType> ObjectMesh;
    std::shared_ptr<PhysicsEngineSegmentType> ObjectSegments;

    std::shared_ptr<sf::Texture> Texture;
    sf::IntRect TextureRect;
    sf::RectangleShape ObjectRect;
    //Objects can be animated
    std::map<std::string, std::shared_ptr<Animation>> Animations;

    bool AllowsActorOverlap; //if false, then actors will never be allowed to cross over this object
    bool RenderOutlined;
    bool TestingCollisions;
  };
}



#endif