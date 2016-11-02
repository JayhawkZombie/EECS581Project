#include "../../Headers/Actor/Actor.h"

namespace Engine
{


  GenericActor::GenericActor(const std::string &texfile, const std::string &texID)
  {
    ResourceManager->RequestTexture(texfile, texID,
                                    [this](const std::shared_ptr<sf::Texture> t, const std::string &s)->void
                                          {this->ReceiveSprite(s, t); }
                                   );
  }

  GenericActor::GenericActor()
  {

  }

  GenericActor::GenericActor(const GenericActor &actor)
  {

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

  void GenericActor::OnShutDown()
  {

  }

  void GenericActor::Render()
  {
    Render::RenderShape(&ActorRectangle);
  }

  void GenericActor::TickUpdate(const double &delta)
  {

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
