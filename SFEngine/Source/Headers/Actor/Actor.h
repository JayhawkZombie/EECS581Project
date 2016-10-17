#ifndef SFENGINE_ACTOR_H
#define SFENGINE_ACTOR_H

#include "../Engine/BaseEngineInterface.h"
#include "../Level/LevelObject.h"

namespace Engine
{

  class GenericActor : public LevelObject
  {
  public:
    friend class Level;

    GenericActor();
    GenericActor(const GenericActor &actor);
    ~GenericActor();

    virtual void TickUpdate(const double &delta);
    virtual void Render();
    virtual void OnShutDown();

    virtual bool WantsInputEvent(const Events &evnt) const;
    
  protected:
    sf::Vector2f Velocity;
    sf::Vector2f Acceleration;
    sf::Vector2f Position;
    sf::Sprite Sprite;
    std::shared_ptr<sf::Texture> SpriteTexture;
    CollisionBox ActorBox;
    void ReceiveSprite(const std::string &ID, std::shared_ptr<sf::Texture> tex);
  };

}

#endif
