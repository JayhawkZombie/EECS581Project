#ifndef __QUAD_TREE_H
#define __QUAD_TREE_H

#include "../Level/LevelObject.h"

#include <SFML/Graphics.hpp>

#include <memory>

namespace Engine
{
  const std::size_t MaxDepth = 6;

  class QuadTree
  {
  public:
    QuadTree();
    QuadTree(const sf::Vector2f &cen, float wid, float hei, QuadTree *prnt, std::size_t level = 0);
    ~QuadTree();

    void Insert(std::shared_ptr<Engine::LevelObject> shape);
    void Render(sf::RenderWindow &window);
    void Subdivide();
    void Clear();
    bool ShapeFitsInside(const sf::FloatRect &shape);
    void PlaceInsideChild(const sf::FloatRect &rect);

  private:
    void PlaceInSelf(std::shared_ptr<Engine::LevelObject> shape);
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
    
    std::vector<std::shared_ptr<Engine::LevelObject>> ContainedObjects;
  };
}

#endif
