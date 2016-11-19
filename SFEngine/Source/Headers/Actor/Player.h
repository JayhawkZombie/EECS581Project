#ifndef SFENGINE_PLAYER_H
#define SFENGINE_PLAYER_H

#include "Actor.h"

namespace Engine
{
  class Player : public GenericActor
  {
  public:
    TYPEDEF_PARENT_CLASS(Engine::GenericActor);

    Player();
    Player(const std::string &texfile, const std::string &texID);
    Player(const Player &p);
    ~Player();


    virtual void TickUpdate(const double &delta) override;
    virtual void Render() override;
    virtual void OnShutDown() override;
    virtual void SerializeOut(std::ostream &out) override;

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
