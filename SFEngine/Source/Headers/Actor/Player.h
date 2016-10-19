#ifndef SFENGINE_PLAYER_H
#define SFENGINE_PLAYER_H

#include "Actor.h"

namespace Engine
{
  class Player : public GenericActor
  {
  public:
    Player();
    Player(const std::string &texfile, const std::string &texID);
    ~Player();


    virtual void TickUpdate(const double &delta);
    virtual void Render();
    virtual void OnShutDown();
    virtual bool WantsInputEvent(const Events &evnt) const override;

    virtual void MoveTo(const sf::Vector2f &pos);

  protected:
    void KeyWasPressed(const sf::Keyboard::Key &k);
    void KeyWasReleased(const sf::Keyboard::Key &k);
    
    void TryToMove(const sf::Vector2f &amount);

    sf::RectangleShape TestShape;
  };
}


#endif
