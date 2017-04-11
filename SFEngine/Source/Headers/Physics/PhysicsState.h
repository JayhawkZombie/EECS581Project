//#ifndef SFENGINE_PHYSICS_STATE_H
//#define SFENGINE_PHYSICS_STATE_H
//
//#include <SFML\Graphics.hpp>
//
//namespace Engine
//{
//
//  class PhysicsState
//  {
//  public:
//    friend class SFEngine;
//    friend class Level;
//    friend class GenericActor;
//    friend class LevelEnvironment;
//
//    PhysicsState();
//    PhysicsState(const PhysicsState &state);
//    ~PhysicsState();
//
//    sf::Vector2f GetLevelPosition() const;
//    sf::Vector2f GetScreenPosition() const;
//    sf::Vector2f GetVelocity() const;
//    sf::Vector2f GetAcceleration() const;
//    sf::FloatRect GetBoundingBox() const;
//
//    void SetLevelPosition(const sf::Vector2f &pos);
//    void SetScreenPosition(const sf::Vector2f &pos);
//    void SetVelocity(const sf::Vector2f &vel);
//    void SetAcceleration(const sf::Vector2f &acc);
//    void SetBoundingBox(const sf::FloatRect &box);
//
//    void RetrieveState(GenericActor *actor);
//
//  private:
//    sf::Vector2f LevelPosition;
//    sf::Vector2f Velocity;
//    sf::Vector2f Acceleration;
//
//    sf::Vector2f ScreenPosition;
//
//    sf::FloatRect BoundingBox;
//
//  };
//
//}
//
//#endif
