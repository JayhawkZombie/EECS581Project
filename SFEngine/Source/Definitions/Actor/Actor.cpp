#include "../../Headers/Actor/Actor.h"

namespace Engine
{


  GenericActor::GenericActor(const std::string &texfile, const std::string &texID)
  {
    ResourceManager->RequestTexture(texfile, texID,
                                    [this](const std::shared_ptr<sf::Texture> t, const std::string &s)->void
                                          {this->ReceiveSprite(s, t); }
                                   );

    Handler.BindCallback(Events::KeyPressed,
                         [this](const sf::Keyboard::Key &k) {this->__HandleKeyPress(k); }
    );
  }

  void GenericActor::BindScriptMethods(chaiscript::ModulePtr mptr)
  {
    //UGHSDJLGHSD LJHFSDLFHS DLFH SDF
    //It's SO UGLY!
    chaiscript::utility::add_class<Engine::GenericActor>(*mptr, "GenericActor",
    { chaiscript::constructor<Engine::GenericActor()>() },
    { {
      chaiscript::fun(static_cast<void(GenericActor::*)(const std::string &)>(&GenericActor::SetID)), "SetID"},
      {chaiscript::fun(static_cast<std::string(GenericActor::*)(void) const>(&GenericActor::GetID)), "GetID" },
      {chaiscript::fun(static_cast<const sf::Vector2f &(GenericActor::*)(void) const>(&GenericActor::GetActorPosition)), "GetPosition"},
      {chaiscript::fun(static_cast<void(GenericActor::*)(const sf::Vector2f &)>(&GenericActor::SetActorPosition)), "SetPosition"}
      }
    );
  }

  GenericActor::GenericActor()
  {

  }

  GenericActor::GenericActor(const GenericActor &actor)
  {

  }

  void GenericActor::AddAnimation(const std::string &ID, AnimationInfo info)
  {
    Animations[ID] = {};
    
  }

  void GenericActor::__HandleKeyPress(const sf::Keyboard::Key &key)
  {
    switch (key)
    {
      case sf::Keyboard::Up:
        CurrentPhysicsState.Velocity = sf::Vector2f(0, -1);
        break;
      case sf::Keyboard::Left:
        CurrentPhysicsState.Velocity = sf::Vector2f(-1, 0);
        break;
      case sf::Keyboard::Down:
        CurrentPhysicsState.Velocity = sf::Vector2f(0, 1);
        break;
      case sf::Keyboard::Right:
        CurrentPhysicsState.Velocity = sf::Vector2f(1, 0);
        break;
    }
  }

  void GenericActor::SetTexture(const std::string &texfile, const std::string &texID)
  {
    ResourceManager->RequestTexture(texfile, texID,
                                    [this](const std::shared_ptr<sf::Texture> t, const std::string &s)->void
                                          {this->ReceiveSprite(s, t); }
                                    );
  }

  void GenericActor::ReceiveSprite(const std::string &ID, std::shared_ptr<sf::Texture> tex)
  {
    SpriteTexture = tex;
    Sprite.setTexture(*SpriteTexture);
    ActorRectangle.setTexture(SpriteTexture.get());
  }

  GenericActor::~GenericActor()
  {

  }

  void GenericActor::SerializeOut(std::ostream &out)
  {

  }

  void GenericActor::OnShutDown()
  {

  }

  void GenericActor::Render()
  {
    ActorRectangle.setPosition(CurrentPhysicsState.ScreenPosition);
    Render::RenderShape(&ActorRectangle);
  }

  void GenericActor::TickUpdate(const double &delta)
  {
    CurrentPhysicsState.LevelPosition += CurrentPhysicsState.Velocity * static_cast<float>(delta);
  }

  bool GenericActor::WantsInputEvent(const Events &evnt) const
  {
    return false;
  }

  void GenericActor::SetActorPosition(const sf::Vector2f &pos)
  {
    Position = pos;
  }

  void GenericActor::SetActorSize(const sf::Vector2f &size)
  {
    Size = size;
  }

  void GenericActor::SetActorVelocity(const sf::Vector2f &vel)
  {
    Velocity = vel;
  }

  void GenericActor::SetActorAcceleration(const sf::Vector2f &acc)
  {
    Acceleration = acc;
  }

  const sf::Vector2f& GenericActor::GetActorPosition() const
  {
    return Position;
  }

  const sf::Vector2f& GenericActor::GetActorSize() const
  {
    return Size;
  }

  const sf::Vector2f& GenericActor::GetActorVelocity() const
  {
    return Velocity;
  }

  const sf::Vector2f& GenericActor::GetActorAcceleration() const
  {
    return Acceleration;
  }

}
