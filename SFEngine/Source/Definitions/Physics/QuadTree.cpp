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
    float CenterX = Center.x - (Width / 2.f);
    float CenterY = Center.y - (Height / 2.f);

    Bounds = sf::FloatRect({ { CenterX, CenterY },{ Width, Height } });
  }

  QuadTree::~QuadTree()
  {
    if (NW)
      NW.reset();
    if (NE)
      NE.reset();
    if (SW)
      SW.reset();
    if (SE)
      SE.reset();

    for (auto & obj : ContainedObjects) {
      obj->OnShutDown();
      obj.reset();
    }

  }


  bool QuadTree::ShapeFitsInside(const sf::FloatRect &shape)
  {
    return
      (
        RectContainsRect(Bounds, shape)
        );
  }

  void QuadTree::PlaceInsideChild(const sf::FloatRect & rect)
  {
    //See if it would fit inside the children. If so, then we should subdivide
    float HalfHeight = Height / 2.f;
    float HalfWidth = Width / 2.f;

    sf::Vector2f CenterNW(Center.x - (HalfWidth / 2.f), Center.y - (HalfHeight / 2.f));
    sf::Vector2f CenterNE(Center.x + (HalfWidth / 2.f), Center.y - (HalfHeight / 2.f));
    sf::Vector2f CenterSW(Center.x - (HalfWidth / 2.f), Center.y + (HalfHeight / 2.f));
    sf::Vector2f CenterSE(Center.x + (HalfWidth / 2.f), Center.y + (HalfHeight / 2.f));

    sf::FloatRect NWBounds(CenterNW, { HalfWidth, HalfHeight });
    sf::FloatRect NEBounds(CenterNE, { HalfWidth, HalfHeight });
    sf::FloatRect SWBounds(CenterSW, { HalfWidth, HalfHeight });
    sf::FloatRect SEBounds(CenterSE, { HalfWidth, HalfHeight });

    //If the rect can fit inside a child, subdivide and return the child that we
    //should place the item into

  }

  void QuadTree::PlaceInSelf(std::shared_ptr<Engine::LevelObject> shape)
  {
    ContainedObjects.push_back(shape);
  }

  void QuadTree::Insert(std::shared_ptr<Engine::LevelObject> object)
  {
    //If we have already subdivided, see if we can add it to the children
    if (Divided) {
      if (NW && NW->ShapeFitsInside(object->CurrentPhysicsState.GetBoundingBox())) {
        NW->Insert(object);
      }
      else if (NE && NE->ShapeFitsInside(object->CurrentPhysicsState.GetBoundingBox())) {
        NE->Insert(object);
      }
      else if (SW && SW->ShapeFitsInside(object->CurrentPhysicsState.GetBoundingBox())) {
        SW->Insert(object);
      }
      else if (SE && SE->ShapeFitsInside(object->CurrentPhysicsState.GetBoundingBox())) {
        SE->Insert(object);
      }
      else {
        PlaceInSelf(object);
      }
    }
    else { //OK, so we either don't have any children or it cannot fit inside any of the children
      if (ShapeFitsInside(object->CurrentPhysicsState.GetBoundingBox())) {
        sf::FloatRect Rect = object->CurrentPhysicsState.GetBoundingBox();

        //If we can't divide anymore, just add it and stop
        if (Depth >= MaxDepth) {
          PlaceInSelf(object);
        }

        //Do we need to subdivide?
        //Quick test to see if we should even bother computing this
        //If the object's width is <= half our width, it could potentially fit inside a child
        else if ((Rect.width <= (0.5 * Bounds.width)) &&
          (Rect.height <= (0.5 * Bounds.height))) {
          //Subsivide and try to add to children
          //Calling Insert() again should work since we just created the children
          //so the test at the top of the method should pass
          Subdivide();
          Insert(object);
        }
        else {
          //We need not subdivide, there's no possible way it could fit inside one of our children
          PlaceInSelf(object);
        }
      } //if (ShapeFitsInside(shape))
      else {
        //This shouldn't happen
        std::cerr << "Shape does not fit inside bounds" << std::endl;
      }
    } //else (no children or it doesn't fit inside any of the children)
  }

  void QuadTree::Clear()
  {
    for (auto & obj : ContainedObjects) {
      obj->OnShutDown();
      obj.reset();
    }

    ContainedObjects.erase(ContainedObjects.begin(), ContainedObjects.end());

    if (NW) {
      NW->Clear();
    }
    if (NE) {
      NE->Clear();
    }
    if (SW) {
      SW->Clear();
    }
    if (SE) {
      SE->Clear();
    }
  }

  void QuadTree::Render(sf::RenderWindow & window)
  {
    //If children, render them
    if (NW)
      NW->Render(window);
    if (NE)
      NE->Render(window);
    if (SW)
      SW->Render(window);
    if (SE)
      SE->Render(window);

    //Render any objects we have
    for (auto & obj : ContainedObjects)
      obj->Render();
  }

  void QuadTree::Subdivide()
  {
    if (Depth >= MaxDepth)
      return;
    //Subdivide the children instead
    if (Divided) {
      NW->Subdivide();
      NE->Subdivide();
      SW->Subdivide();
      SE->Subdivide();
    }
    else {
      Divided = true;
      float HalfHeight = Height / 2.f;
      float HalfWidth = Width / 2.f;

      sf::Vector2f CenterNW(Center.x - (HalfWidth / 2.f), Center.y - (HalfHeight / 2.f));
      sf::Vector2f CenterNE(Center.x + (HalfWidth / 2.f), Center.y - (HalfHeight / 2.f));
      sf::Vector2f CenterSW(Center.x - (HalfWidth / 2.f), Center.y + (HalfHeight / 2.f));
      sf::Vector2f CenterSE(Center.x + (HalfWidth / 2.f), Center.y + (HalfHeight / 2.f));

      NW = std::shared_ptr<QuadTree>(new QuadTree(CenterNW, HalfWidth, HalfHeight, this, Depth + 1));
      NE = std::shared_ptr<QuadTree>(new QuadTree(CenterNE, HalfWidth, HalfHeight, this, Depth + 1));
      SW = std::shared_ptr<QuadTree>(new QuadTree(CenterSW, HalfWidth, HalfHeight, this, Depth + 1));
      SE = std::shared_ptr<QuadTree>(new QuadTree(CenterSE, HalfWidth, HalfHeight, this, Depth + 1));
    }
  }
}
