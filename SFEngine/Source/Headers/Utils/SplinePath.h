#ifndef SFENGINE_UTILS_SPLINE_PATH_H
#define SFENGINE_UTILS_SPLINE_PATH_H

#include "SFEngine\ThirdParty\SelbaWard.hpp"
#include "BasicIncludes.h"
#include <SFML\Graphics.hpp>

namespace Engine
{

  class SplinePath
  {
  public:
    SplinePath(UINT32 PathStyle = SplinePath::Default);
    ~SplinePath() = default;

    static enum Style : UINT32
    {
      Default      = 1,
      Connected    = 2,
      Unconnected  = 3,
      Linear       = 4,
      Cubic        = 5,
      Smooth       = 6,
      Jagged       = 7
    };

    void MakeCirclularPath(const sf::Vector2f &Center, SFLOAT Radius, UINT32 NumPts = 100);
    void SetThickness(SFLOAT Thickness);
    UINT32 GetNumInterpolantPoints() const;
    void AddVertexAtEnd(const sf::Vector2f &Position);
    void AddVertices(const std::vector<sf::Vector2f> &Vertices);
    void MoveVertex(UINT32 Index, const sf::Vector2f &NewPosition);
    void MakeSmooth();
    void SetInterpolationSteps(UINT32 NumSteps);
    void RemoveVertex(UINT32 Index);
    void SetPrimitiveType(sf::PrimitiveType PType);
    void SetColor(sf::Color Color);
    sf::Vector2f operator[](const UINT32 &Index);
    void Update();
    void Render(std::shared_ptr<sf::RenderTarget> Target);

    sf::Vector2f GetNextPathPoint();

  protected:
    int m_CurrentPathPoint = 0;
    ::sw::Spline m_Spline;
    sf::PrimitiveType m_SplinePrimitiveType;
    UINT32 m_Style;

  };

}

#endif
