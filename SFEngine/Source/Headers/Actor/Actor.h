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
    TYPEDEF_PARENT_CLASS(Engine::LevelObject);

    GenericActor();
    GenericActor(const std::string &texfile, const std::string &texID);
    GenericActor(const GenericActor &actor);
    virtual ~GenericActor();

    virtual void TickUpdate(const double &delta) override;
    virtual void Render() override;
    virtual void OnShutDown() override;
    virtual void SerializeOut(std::ostream &out) override;

    virtual bool WantsInputEvent(const Events &evnt) const;

    virtual void SetActorPosition(const sf::Vector2f &pos);
    virtual void SetActorSize(const sf::Vector2f &size);
    virtual void SetActorVelocity(const sf::Vector2f &vel);
    virtual void SetActorAcceleration(const sf::Vector2f &acc);

    virtual const sf::Vector2f& GetActorPosition() const;
    virtual const sf::Vector2f& GetActorSize() const;
    virtual const sf::Vector2f& GetActorVelocity() const;
    virtual const sf::Vector2f& GetActorAcceleration() const;

    virtual void SetTexture(const std::string &texfile, const std::string &texID);
    
  protected:
    void __HandleKeyPress(const sf::Keyboard::Key &key);

    sf::Vector2f Velocity;
    sf::Vector2f Acceleration;
    sf::Vector2f Position;
    sf::Vector2f Size;
    sf::Sprite Sprite;

    sf::RectangleShape ActorRectangle;

    std::shared_ptr<sf::Texture> SpriteTexture;
    CollisionBox ActorBox;
    void ReceiveSprite(const std::string &ID, std::shared_ptr<sf::Texture> tex);
  };

}

#endif
