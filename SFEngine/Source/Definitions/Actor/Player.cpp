#include "../../Headers/Actor/Player.h"

namespace Engine
{

  Player::Player(const std::string &texfile, const std::string &texID)
    : GenericActor(texfile, texID)
  {

    TestShape.setFillColor(sf::Color::Black);

    Position = sf::Vector2f(250, 250);
    ActorBox.Position = Position;
    ActorBox.Size = sf::Vector2f(50, 75);

    TestShape.setPosition(Position);
    TestShape.setSize(sf::Vector2f(50, 75));
    Velocity = sf::Vector2f(0, 0);
    Handler.BindCallback(Events::KeyPressed,
                         [this](const sf::Keyboard::Key &key)
    {
      this->KeyWasPressed(key);
    });
  }

  Player::Player(const Player &p)
  {

  }

  Player::Player()
  {
    TestShape.setFillColor(sf::Color::Black);

    Position = sf::Vector2f(250.f, 250.f);
    ActorBox.Position = Position;
    ActorBox.Size = sf::Vector2f(50.f, 75.f);

    TestShape.setPosition(Position);
    TestShape.setSize(sf::Vector2f(50.f, 75.f));
    Velocity = sf::Vector2f(0, 0);
    Handler.BindCallback(Events::KeyPressed,
                         [this](const sf::Keyboard::Key &key)
    {
      this->KeyWasPressed(key);
    });
  }

  Player::~Player()
  {

  }

  void Player::TickUpdate(const double &delta)
  {
    TryToMove(Velocity);
    TestShape.setPosition(Position);
    TestShape.setSize(sf::Vector2f(50.f, 75.f));
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
    //std::cerr << "Player: KeyWasPressed" << std::endl;
    switch (k)
    {
      case sf::Keyboard::Right:
        Velocity = sf::Vector2f(0.3f, 0);
        break;
      case sf::Keyboard::Left:
        Velocity = sf::Vector2f(-0.3f, 0);
        break;
      case sf::Keyboard::Up:
        Velocity = sf::Vector2f(0, -0.3f);
        break;
      case sf::Keyboard::Down:
        Velocity = sf::Vector2f(0, 0.3f);
        break;
    }
  }

  void Player::KeyWasReleased(const sf::Keyboard::Key &k)
  {
    //std::cerr << "Player: KeyWasReleased" << std::endl;
    switch (k)
    {
      case sf::Keyboard::Right:
        Velocity = sf::Vector2f(0, 0);
        break;
      case sf::Keyboard::Left:
        Velocity = sf::Vector2f(0, 0);
        break;
      case sf::Keyboard::Up:
        Velocity = sf::Vector2f(0, 0);
        break;
      case sf::Keyboard::Down:
        Velocity = sf::Vector2f(0, 0);
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
