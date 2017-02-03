#include "../../Headers/Actor/Player.h"

namespace Engine
{

  Player::Player(const std::string &texfile, const std::string &texID)
    : GenericActor(texfile, texID)
  {

    
  }

  Player::Player(const Player &p)
  {

  }

  Player::Player()
  {
    
  }

  Player::~Player()
  {

  }

  void Player::KeyRightPressed()
  {

  }

  void Player::KeyUpPressed()
  {

  }

  void Player::KeyDownPressed()
  {

  }

  void Player::KeyLeftPressed()
  {

  }

  void Player::ForcePosition(float x, float y)
  {
    
  }

  void Player::SerializeOut(std::ofstream &out)
  {

  }

  void Player::SerializeIn(std::ifstream & in)
  {
  }

  void Player::TickUpdate(const double &delta)
  {
    //TryToMove(Velocity);
    //TestShape.setPosition(Position);
    //TestShape.setSize(sf::Vector2f(50.f, 75.f));
  }

  void Player::Render(std::shared_ptr<sf::RenderTarget> Target)
  {

    
  }

  void Player::OnShutDown()
  {

  }

  bool Player::WantsInputEvent(const Events &evnt) const
  {
    return false;
  }

  void Player::KeyWasPressed(const sf::Keyboard::Key &k)
  {
    
  }

  void Player::KeyWasReleased(const sf::Keyboard::Key &k)
  {
    
  }

  void Player::MoveTo(const sf::Vector2f &pos)
  {
    
  }

  void Player::TryToMove(const sf::Vector2f &amount)
  {
    
  }

}