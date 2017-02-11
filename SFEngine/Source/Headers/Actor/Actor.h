#ifndef SFENGINE_ACTOR_H
#define SFENGINE_ACTOR_H

#include "../Engine/BaseEngineInterface.h"
#include "../Level/LevelObject.h"
#include "../Physics/PhysicsState.h"
#include "../Animation/Animation.h"

namespace Engine
{

  struct ActorInfo
  {
    std::map<std::string, std::string> Scripts;
    PhysicsState ActorState;
    std::string ID;
    std::string TextureID, TexturePath;
    AnimationInfo AnimInfo;
  };

  class GenericActor : public LevelObject
  {
  public:
    friend class Level;
    TYPEDEF_PARENT_CLASS(Engine::LevelObject);

    static void BuildAnimations(const std::string &filename, const std::string &texturefile, GenericActor *Actor);

    static void BindScriptMethods(chaiscript::ModulePtr module);

    GenericActor();
    GenericActor(const std::string &texfile, const std::string &texID);
    GenericActor(const GenericActor &actor);
    virtual ~GenericActor();

    virtual void TickUpdate(const double &delta) override;
    virtual void Render(std::shared_ptr<sf::RenderTarget> Target) override;
    virtual void OnShutDown() override;
    virtual void SerializeOut(std::ofstream &out) override;
    virtual void SerializeIn(std::ifstream &in) override;

    virtual bool WantsInputEvent(const Events &evnt) const;

    virtual void SetActorPosition(const sf::Vector2f &pos);
    virtual void SetActorPosition(float x, float y);
    virtual void SetActorSize(const sf::Vector2f &size);
    virtual void SetActorVelocity(const sf::Vector2f &vel);
    virtual void SetActorAcceleration(const sf::Vector2f &acc);
    virtual void GenerateActorMesh();

    virtual const sf::Vector2f& GetActorPosition() const;
    virtual const sf::Vector2f& GetActorSize() const;
    virtual const sf::Vector2f& GetActorVelocity() const;
    virtual const sf::Vector2f& GetActorAcceleration() const;

    virtual void SetTexture(const std::string &texfile, const std::string &texID);
    virtual void AddAnimation(const std::string &ID, std::shared_ptr<Animation> info);
    virtual void SetAnimation(const std::string &ID);
    virtual void UseTemporaryAnimation(const std::string &ID);
    virtual void UsePreviousAnimation();

  protected:
    void __HandleKeyPress(const sf::Keyboard::Key &key);
    Animation *PreviousAnimation = nullptr;
    sf::Vector2f Velocity;
    sf::Vector2f Acceleration;
    sf::Vector2f Position;
    sf::Vector2f Size;
    sf::Sprite Sprite;
    std::shared_ptr<PhysicsEngineBaseMeshType> CollisionMesh;
    bool DrawCollisionMesh = true;

    Animation *CurrentAnimation = nullptr;
    float WindowWidth;
    float WindowHeight;

    sf::RectangleShape ActorRectangle;

    std::shared_ptr<sf::Texture> SpriteTexture;
    
    void ReceiveSprite(const std::string &ID, std::shared_ptr<sf::Texture> tex);
  };

}

#endif