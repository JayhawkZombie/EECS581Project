#ifndef SFENGINE_PLAYER_H
#define SFENGINE_PLAYER_H

#include "Actor\Actor.h"

namespace Engine
{
  class Player : public GenericActor
  {
  public:
    TYPEDEF_PARENT_CLASS(Engine::GenericActor);

    Player();
    Player(const std::string &texfile, const std::string &texID);
    Player(const Player &p);
    virtual ~Player();


    virtual void TickUpdate(const double &delta) override;
    virtual void Render(std::shared_ptr<sf::RenderTarget> Target) override;
    virtual void OnShutDown() override;
    virtual void SerializeOut(std::ofstream &out) override;
    virtual void SerializeIn(std::ifstream &in) override;

    virtual void KeyRightPressed();
    virtual void KeyUpPressed();
    virtual void KeyDownPressed();
    virtual void KeyLeftPressed();
    virtual void ForcePosition(float x, float y);
    virtual float GetPositionX() {
      return Sprite.getPosition().x;
    }
    virtual float GetPositionY() {
      return Sprite.getPosition().y;
    }

    virtual void HandleInputEvent(const UserEvent &evnt);
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