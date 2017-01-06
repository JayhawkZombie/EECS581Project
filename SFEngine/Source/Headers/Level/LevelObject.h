#ifndef SFENGINE_LEVEL_OBJECT_H
#define SFENGINE_LEVEL_OBJECT_H

#include "../BasicIncludes.h"
#include "../Engine/BaseEngineInterface.h"

#include "../Physics/Collision.h"
#include "../Physics/PhysicsState.h"

#define REQUIRED_LEVEL_OBJ_CLASS_CODE(CLASSNAME) \
  public: \
  friend class SFEngine; \
  friend class Level; \
  friend class LevelEnvironment; \
  friend struct GridCell; \
  PhysicsState CurrentPhysicsState; \
  PhysicsState PreviousPhysicsState; \
  private: \
    bool DidUpdate; \
    bool DidPhysicsUpdate; \
  public: \
  void PhysicsUpdate(const PhysicsState &state) \
  { \
    if (!DidPhysicsUpdate) { \
      PreviousPhysicsState = CurrentPhysicsState; \
      CurrentPhysicsState = state; \
      DidPhysicsUpdate = true; \
    } \
  } \
  bool DidUpdateThisFrame() const \
  { \
    return DidUpdate; \
  } \
  bool DidPhysicsUpdateThisFrame() const \
  { \
    return DidPhysicsUpdate; \
  } \
  void LevelGridCellUpdate(const double &delta) \
  { \
    if (!DidUpdate) { \
        DidUpdate = true; \
        TickUpdate(delta); \
      } \
  } \
  void CollisionUpdate(const sf::Vector2f &delta); \
  void EndOfFrame() \
  { \
    DidUpdate = false; \
    DidPhysicsUpdate = false; \
  } \
  virtual std::string ClassName() \
  { \
    return std::string(#CLASSNAME); \
  } \
  friend std::ostream& operator<<(std::ostream &out, const CLASSNAME &obj) \
    { \
       out << #CLASSNAME << "\n"; \
    }

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
    TYPEDEF_PARENT_CLASS(Engine::BaseEngineInterface);
    REQUIRED_LEVEL_OBJ_CLASS_CODE(LevelObject);

    LevelObject();
    LevelObject(const LevelObject &obj);
    virtual ~LevelObject();

    virtual void TickUpdate(const double &delta) override;
    virtual void Render() override;
    virtual void OnShutDown() override;
    virtual void SerializeOut(std::ofstream &out) override;
    virtual void SerializeIn(std::ifstream &in) override;
    void SetPosition(const sf::Vector2f &pos);

    virtual OverlapAction OnActorOverlap(GenericActor *actor);
    virtual bool DoTestCollisions() const;
    virtual bool DoesAllowActorOverlap() const;

  protected:
    CollisionBox Collsion;

    CollisionBox GlobalCollisionBox;

    bool AllowsActorOverlap; //if false, then actors will never be allowed to cross over this object
    bool RenderOutlined;
    bool TestingCollisions;
  };
}



#endif
