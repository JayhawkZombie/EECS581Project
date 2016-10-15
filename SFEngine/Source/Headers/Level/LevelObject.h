#ifndef SFENGINE_LEVEL_OBJECT_H
#define SFENGINE_LEVEL_OBJECT_H

#include "../BasicIncludes.h"
#include "../Engine/BaseEngineInterface.h"

#include "../Physics/Collision.h"

namespace Engine
{
 

  class LevelObject : public BaseEngineInterface
  {
  public:
    friend class SFEngine;

    LevelObject();
    LevelObject(const LevelObject &obj);
    ~LevelObject();

    void TickUpdate(const double &delta);
    void Render();
    void OnShutDown();

  protected:
    CollisionBox Collsion;

    std::vector<std::shared_ptr<sf::Texture>> Textures;

    //TODO: Implement animations
    //std::map<STRING, Animation> Animations;

  };
}



#endif
