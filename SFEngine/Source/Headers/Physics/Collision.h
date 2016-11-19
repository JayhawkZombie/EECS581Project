#ifndef SFENGINE_COLLISION_H
#define SFENGINE_COLLISION_H

#include "../BasicIncludes.h"

namespace Engine
{

  class LevelObject;

  namespace Physics
  {

    bool BoxesOverlap(const sf::FloatRect &FR1, const sf::FloatRect &FR2);
    sf::Vector2f PointOfIntersection(const sf::Vector2f start, const sf::Vector2f end, const sf::Vector2f &P1, const sf::Vector2f &P2);
    
    float Dot(const sf::Vector2f &a, const sf::Vector2f &b);
    unsigned int Dot(const sf::Vector2u &a, const sf::Vector2u &b);
    int Dot(const sf::Vector2i &a, const sf::Vector2i &b);

    float Mag(const sf::Vector2f &a);
    unsigned int Mag(const sf::Vector2u &a);
    int Mag(const sf::Vector2i &a);

    bool DoObjectsOverlap(LevelObject *Obj1, LevelObject *Obj2);

  }

  enum class MeshType {
    Simple,
    Complex,
    None
  };

  class Mesh
  {
  public:
    Mesh(const MeshType &type);
    ~Mesh();

  private:
    MeshType &type;
    sf::FloatRect SimpleMesh;
    std::vector<sf::Vertex> ComplexMesh;
  };

  class CollisionBox
  {
  public:
    CollisionBox();
    CollisionBox(const CollisionBox &box);
    ~CollisionBox();

    sf::FloatRect GetBox() const;

    sf::Vector2f Position;
    sf::Vector2f Size;
  };
}

#endif
