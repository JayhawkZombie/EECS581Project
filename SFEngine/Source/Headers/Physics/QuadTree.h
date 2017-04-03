#ifndef __QUAD_TREE_H
#define __QUAD_TREE_H

#include "../Level/LevelObject.h"
#include "../Lights/LightObject.h"

#include <SFML/Graphics.hpp>

#include <memory>

namespace Engine
{
  const std::size_t MaxDepth = 6;

  class Collider2D;

  class QuadTree
  {
  public:
    QuadTree();
    QuadTree(const sf::Vector2f &cen, float wid, float hei, QuadTree *prnt, std::size_t level = 0);
    ~QuadTree();

    void InsertObject(std::shared_ptr<Engine::LevelObject> Object);
    //void InsertShadowCaster(std::shared_ptr<Engine::LightObject> Caster);
    void InsertCollidingMesh(std::shared_ptr<PhysicsEngineBaseMeshType> Mesh);

    void Render(sf::RenderWindow &window);
    void Subdivide();
    void Clear();
    bool ShapeFitsInside(const sf::FloatRect &shape);
    void PlaceInsideChild(const sf::FloatRect &rect);

    std::vector<std::shared_ptr<Engine::LevelObject>> GetContainedObjectsInRange(const sf::FloatRect &Region);
    void GetColliderObjectsInRange(const sf::FloatRect &Region, std::vector<std::shared_ptr<Collider2D>> &Colliders);
    //std::vector<std::shared_ptr<Engine::LightObject>> GetContainedShadowCastingObjectsInRange(const sf::FloatRect &Region);
    std::vector<std::shared_ptr<Collider2D>> GetContainedCollidingMeshesInRange(const sf::FloatRect &Region);

  private:
    void PlaceInSelf(std::shared_ptr<Engine::Collider2D> shape);
    void GetCollidersInRangeSelf(std::vector<std::shared_ptr<Engine::Collider2D>> &Colliders);
    void GetCollidersInRangeChild(std::vector<std::shared_ptr<Engine::Collider2D>> &Colliders, QuadTree *Child);
    inline bool IntersectsChild(const sf::FloatRect &Region, QuadTree *Child);
    int FitsInsideAnyChild(std::shared_ptr<Engine::LevelObject> LObject);
    //int FitsInsideAnyChild(std::shared_ptr<Engine::LightObject> LightObject);
    int FitsInsideAnyChild(std::shared_ptr<PhysicsEngineBaseMeshType> Mesh);
    int PlaceInChild(std::shared_ptr<QuadTree> Tree);
  public:

    sf::Vector2f Center;
    std::size_t Depth = 0;
    sf::FloatRect Bounds;
    float Width = 0;
    float Height = 0;
    bool Divided = false;

    std::shared_ptr<QuadTree> NW;
    std::shared_ptr<QuadTree> NE;
    std::shared_ptr<QuadTree> SW;
    std::shared_ptr<QuadTree> SE;
    QuadTree *Parent;
    
    std::vector<std::shared_ptr<Collider2D>> ContainedColliders;

    std::vector<std::shared_ptr<Engine::LevelObject>> ContainedObjects;
    //std::vector<std::shared_ptr<Engine::LightObject>> ShadowCastingObjects;
    std::vector<std::shared_ptr<PhysicsEngineBaseMeshType>> CollidingMeshes;
  };
}

#endif
