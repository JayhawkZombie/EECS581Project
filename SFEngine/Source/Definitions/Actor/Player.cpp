#include "../../Headers/Actor/Player.h"

namespace Engine
{

  Player::Player()
  {
    Handler.BindCallback(Events::KeyPressed,
    [this](const sf::Keyboard::Key &key)
    {
      this->KeyWasPressed(key);
    });

    TestShape.setFillColor(sf::Color::Black);

    Position = sf::Vector2f(250, 250);
    ActorBox.Position = Position;
    ActorBox.Size = sf::Vector2f(50, 75);

    TestShape.setPosition(Position);
    TestShape.setSize(sf::Vector2f(50, 75));
  }

  Player::~Player()
  {

  }

  void Player::TickUpdate(const double &delta)
  {

  }

  void Player::Render()
  {
    Render::RenderShape(&TestShape);
  }

  void Player::OnShutDown()
  {

  }

  bool Player::WantsInputEvent(const Events &evnt) const
  {
    switch (evnt)
    {
      case Events::KeyPressed:
      case Events::KeyReleased:
      case Events::MouseDown:
      case Events::MouseReleased:
        return true;
      default:
        return false;
    }
  }

  void Player::KeyWasPressed(const sf::Keyboard::Key &k)
  {
    switch (k)
    {
      case sf::Keyboard::Right:
        TryToMove(sf::Vector2f(16, 0));
        break;
      case sf::Keyboard::Left:
        TryToMove(sf::Vector2f(-16, 0));
        break;
      case sf::Keyboard::Up:
        TryToMove(sf::Vector2f(0, -16));
        break;
      case sf::Keyboard::Down:
        TryToMove(sf::Vector2f(0, 16));
        break;
    }
  }

  void Player::MoveTo(const sf::Vector2f &pos)
  {
    Position = pos;
    TestShape.setPosition(Position);
    ActorBox.Position = pos;
    Collsion.Position = pos;
  }

  void Player::TryToMove(const sf::Vector2f &amount)
  {
    Position += amount;
    TestShape.setPosition(Position);
    ActorBox.Position = Position;
    Collsion.Position += amount;
  }

}
