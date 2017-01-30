#include "../../Headers/Physics/QuadTree.h"

#include <iostream>

namespace Engine
{

  bool RectContainsRect(const sf::FloatRect &Outer, const sf::FloatRect &Inner)
  {
    //It must contain all 4 corners if it is inside the rectangle
    sf::Vector2f TopLeft(Inner.left, Inner.top);
    sf::Vector2f TopRight(Inner.left + Inner.width, Inner.top);
    sf::Vector2f BottomLeft(Inner.left, Inner.top + Inner.height);
    sf::Vector2f BottomRight(Inner.left + Inner.width, Inner.top + Inner.height);

    return
      (
        Outer.contains(TopLeft) &&
        Outer.contains(TopRight) &&
        Outer.contains(BottomLeft) &&
        Outer.contains(BottomRight)
        );
  }

  QuadTree::QuadTree()
    : NW(nullptr), NE(nullptr), SW(nullptr), SE(nullptr), Divided(false)
  {

  }

  QuadTree::QuadTree(const sf::Vector2f &cen, float wid, float hei, QuadTree *prnt, std::size_t level)
    : NW(nullptr), NE(nullptr), SW(nullptr), SE(nullptr), Parent(prnt), Center(cen), Height(hei), Width(wid), Depth(level), Divided(false)
  {
    
  }

  QuadTree::~QuadTree()
  {
    

  }


  bool QuadTree::ShapeFitsInside(const sf::FloatRect &shape)
  {
    return false;
  }

  void QuadTree::PlaceInsideChild(const sf::FloatRect & rect)
  {
    

  }

  void QuadTree::PlaceInSelf(std::shared_ptr<Engine::LevelObject> shape)
  {
    
  }

  void QuadTree::Insert(std::shared_ptr<Engine::LevelObject> object)
  {
    
  }

  void QuadTree::Clear()
  {
    
  }

  void QuadTree::Render(sf::RenderWindow & window)
  {
    
  }

  void QuadTree::Subdivide()
  {
    
  }
}
