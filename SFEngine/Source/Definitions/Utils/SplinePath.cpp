#include "Utils\SplinePath.h"

namespace Engine
{



  SplinePath::SplinePath(UINT32 PathStyle)
  {
    m_Style = PathStyle;
    //m_Spline.setHandlesVisible(true);
    //m_Spline.setPrimitiveType(sf::Points);
  }

  void SplinePath::MakeCirclularPath(const sf::Vector2f & Center, SFLOAT Radius, UINT32 NumPts)
  {
    assert(NumPts != 0);

    SFLOAT Theta = 0.f;
    SFLOAT dTheta = 2 * ____PI / NumPts;

    SVector2F Point;
    SFLOAT s = 0.f; SFLOAT c = 0.f;
    for (UINT32 i = 0; i < NumPts; ++i) {
      s = std::sin(Theta);
      c = std::cos(Theta);
      Theta += dTheta;

      Point = Center + Radius * SVector2F(c, s);
      m_Spline.addVertex(Point);
    }

    //Connect the last/first point
    Point = Center + Radius * SVector2F(1, 0);
    m_Spline.addVertex(Point);

    if (m_Style & SplinePath::Cubic)
      m_Spline.setBezierInterpolation(true);

    if (m_Style & SplinePath::Smooth)
      m_Spline.smoothHandles();

    m_Spline.update();
  }

  void SplinePath::SetThickness(SFLOAT Thickness)
  {
    m_Spline.setThickness(Thickness);
  }

  UINT32 SplinePath::GetNumInterpolantPoints() const
  {
    return m_Spline.getInterpolationSteps();
  }

  void SplinePath::AddVertexAtEnd(const sf::Vector2f & Position)
  {
    m_Spline.addVertex(Position);
  }

  void SplinePath::AddVertices(const std::vector<sf::Vector2f>& Vertices)
  {
    m_Spline.addVertices(Vertices);
  }

  void SplinePath::MoveVertex(UINT32 Index, const sf::Vector2f & NewPosition)
  {
    if (Index < m_Spline.getVertexCount()) {
      m_Spline[Index].position = NewPosition;
      m_Spline.update();
    }
  }

  void SplinePath::MakeSmooth()
  {
    m_Spline.smoothHandles();
  }

  void SplinePath::SetInterpolationSteps(UINT32 NumSteps)
  {
    m_Spline.setBezierInterpolation(true);
    m_Spline.setInterpolationSteps(NumSteps);
    m_Spline.update();
  }

  void SplinePath::RemoveVertex(UINT32 Index)
  {
    if (Index < m_Spline.getVertexCount()) {
      m_Spline.removeVertex(Index);
    }
  }

  void SplinePath::SetPrimitiveType(sf::PrimitiveType PType)
  {
    m_SplinePrimitiveType = PType;
    m_Spline.setPrimitiveType(PType);
  }

  void SplinePath::SetColor(sf::Color Color)
  {
    m_Spline.setColor(Color);
  }

  sf::Vector2f SplinePath::operator[](const UINT32 & Index)
  {
    if (Index < m_Spline.getVertexCount()) {
      return m_Spline[Index].position;
    }

    return sf::Vector2f();
  }

  void SplinePath::Update()
  {
    m_Spline.update();
  }

  void SplinePath::Render(std::shared_ptr<sf::RenderTarget> Target)
  {
    Target->draw(m_Spline);
  }

  sf::Vector2f SplinePath::GetNextPathPoint()
  {
    sf::Vector2f pos;

    if (m_CurrentPathPoint < m_Spline.getInterpolatedVertexCount()) {
      pos = m_Spline.getInterpolatedVertex(m_CurrentPathPoint);
      m_CurrentPathPoint++;
    }
    else if (m_Spline.getInterpolatedVertexCount() > 0) {
      pos = m_Spline.getInterpolatedVertex(0);
      m_CurrentPathPoint = 0;
      m_CurrentPathPoint++;
    }
   
    return pos;

  }

}
