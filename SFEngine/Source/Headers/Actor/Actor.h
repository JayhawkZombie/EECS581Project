#ifndef SFENGINE_ACTOR_H
#define SFENGINE_ACTOR_H

#include "Level\LevelObject.h"

namespace Engine
{

  class GenericActor : public LevelObject
  {
  public:
    friend class Level;
    TYPEDEF_PARENT_CLASS(Engine::LevelObject);

    static void BuildAnimations(const std::string &filename, const std::string &texturefile, GenericActor *Actor);

    static void BindScriptMethods(chaiscript::ModulePtr module);

    GenericActor();
    GenericActor(const GenericActor &Copy);
    GenericActor(const std::string &texfile, const std::string &texID);
    virtual ~GenericActor();

    //Forbid implicit copy assignment definitions
    //We [MUST] use a clone method
    GenericActor& operator=(const GenericActor &) = delete;
    virtual std::shared_ptr<BaseEngineInterface> Clone() const override;

    virtual void TickUpdate(const double &delta) override;
    virtual void Render(std::shared_ptr<sf::RenderTarget> Target) override;
    virtual void OnShutDown() override;
    virtual void SerializeOut(std::ofstream &out) override;
    virtual void SerializeIn(std::ifstream &in) override;

    virtual void SetCollisionHandleCallback(std::function<void(LevelObject *)> Callback) override;
    virtual void HandleCollisionWithCollider(SPtrShared<Collider2D> Collider) override;
    virtual void HandleCollisionWithObject(LevelObject *Object) override;
    virtual void HandleInputEvent(const UserEvent &evnt) override;
    virtual bool WantsInputEvent(const Events &evnt) const;

    virtual void SetActorPosition(const sf::Vector2f &pos);
    virtual void SetActorPosition(float x, float y);
    virtual void SetActorSize(const sf::Vector2f &size);
    virtual void CenterAroundCollider(std::shared_ptr<Collider2D> Collider);
    virtual void SetActorVelocity(const sf::Vector2f &vel);
    virtual void SetActorAcceleration(const sf::Vector2f &acc);
    virtual void GenerateActorMesh(const std::string &meshtype, const sf::Vector2f &pos, float mass, float coeffOfRest, unsigned int num_sides = 4, float init_rot = 0.f);
    void MoveObject(const sf::Vector2f &delta);

    virtual const sf::Vector2f& GetActorPosition() const;
    virtual const sf::Vector2f& GetActorSize() const;
    virtual const sf::Vector2f& GetActorVelocity() const;
    virtual const sf::Vector2f& GetActorAcceleration() const;

  //  virtual void SetTexture(const std::string &texfile, const std::string &texID);
    virtual void AddAnimation(const std::string &ID, std::shared_ptr<Animation> info);
    virtual void SetAnimation(const std::string &ID);

    //Internal methods, each has a corresponding script that will be called
    void Spawn(const sf::Vector2f &Position);
    void Respawn(const sf::Vector2f &Position);
    void Kill();

    virtual std::string GetClass() const override {
      return "GenericActor";
    }

  protected:
    void __HandleKeyPress(const sf::Keyboard::Key &key);
    bool DrawCollisionMesh = true;

    Animation *CurrentAnimation = nullptr;
    float WindowWidth;
    float WindowHeight;

    sf::RectangleShape ActorRectangle;
    
    void ReceiveSprite(const std::string &ID, std::shared_ptr<sf::Texture> tex);
  };

}

#endif