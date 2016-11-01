#ifndef SFENGINE_LEVEL_OBJECT_H
#define SFENGINE_LEVEL_OBJECT_H

#include "../BasicIncludes.h"
#include "../Engine/BaseEngineInterface.h"

#include "../Physics/Collision.h"

#define REQUIRED_OBJ_CLASS_CODE(CLASSNAME) \
  friend class SFEngine; \
  friend class Level; \
  friend class LevelEnvironment; \
  void CollisionUpdate(const sf::Vector2f &delta) 

namespace Engine
{
 

  class LevelObject : public BaseEngineInterface
  {
  public:

    REQUIRED_OBJ_CLASS_CODE(LevelObject);

    LevelObject();
    LevelObject(const LevelObject &obj);
    ~LevelObject();

    void TickUpdate(const double &delta);
    void Render();
    void OnShutDown();

  protected:
    CollisionBox Collsion;

    std::map<std::string, CollisionBox> CollisionBoxes;
    std::map<std::string, CollisionBox> PreviousPhysicsState;

    //TODO: Implement animations
    //std::map<STRING, Animation> Animations;

  };
}



#endif
