#include "../../Headers/Actor/Actor.h"

namespace Engine
{


  GenericActor::GenericActor()
  {

  }

  GenericActor::GenericActor(const GenericActor &actor)
  {

  }

  void GenericActor::ReceiveSprite(const std::string &ID, std::shared_ptr<sf::Texture> tex)
  {
    SpriteTexture = tex;
    Sprite.setTexture(*SpriteTexture);
  }

  GenericActor::~GenericActor()
  {

  }

  void GenericActor::OnShutDown()
  {

  }

  void GenericActor::Render()
  {

  }

  void GenericActor::TickUpdate(const double &delta)
  {

  }

  bool GenericActor::WantsInputEvent(const Events &evnt) const
  {
    return false;
  }


}
