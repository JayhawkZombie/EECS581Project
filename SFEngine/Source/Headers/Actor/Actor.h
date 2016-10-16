#ifndef SFENGINE_ACTOR_H
#define SFENGINE_ACTOR_H

#include "../Engine/BaseEngineInterface.h"
#include "../Level/LevelObject.h"

namespace Engine
{

  class GenericActor : public LevelObject
  {
  public:
    GenericActor();
    GenericActor(const GenericActor &actor);
    ~GenericActor();

    void TickUpdate(const double &delta);
    void Render();
    void OnShutDown();
    
  protected:
    sf::Vector2f Velocity;
    sf::Vector2f Acceleration;
    sf::Vector2f Position;
    sf::Sprite Sprite;
    std::shared_ptr<sf::Texture> SpriteTexture;

    void ReceiveSprite(const std::string &ID, std::shared_ptr<sf::Texture> tex);
  };

}

#endif
