#ifndef SFENGINE_LIGHTING_SYSTEM_H
#define SFENGINE_LIGHTING_SYSTEM_H

#include "../Lights/LightObject.h"
#include "../Utils/RayCast.h"

#include <algorithm>
#include <cmath>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <chrono>

#define ____PI 3.141592653
#define COSPIBY4 0.25

const long double PI = 3.141592653589793238L;

namespace Engine
{

  void Normalize(sf::Vector2f &v);

  float Cross2D(const sf::Vector2f &v1, const sf::Vector2f &v2);

  float DistanceBetween(const sf::Vector2f &v1, const sf::Vector2f &v2);

  struct Edge {
    sf::Vector2f Start;
    sf::Vector2f End;

    sf::Vector2f FakeStart;
    sf::Vector2f FakeEnd;
  };

  class Light {
  public:
    Light() = default;
    Light(const Light &other)
      :
      Position(other.Position),
      Radius(other.Radius),
      Color(other.Color),
      Expand(other.Expand)
    {}

    float Attenuation = 0.f;
    sf::Vector2f Position;
    float Radius = 0.f;
    sf::Color Color;
    float Expand = 0.f;

    sf::CircleShape Circle;
  };

  class LightSystem {
  public:


    LightSystem();
    ~LightSystem() = default;


    void AddLightObject(const LightObject &obj) {
      Objects.push_back(obj);
    }

    void AddLightObject(const sf::Vector2f &pos, const sf::Vector2f &size, sf::Color color);

    void AddComplexObject(const std::vector<sf::Vector2f> &positions);

    void Render();

    void Render(sf::RenderTarget &tgt, sf::RenderStates &state);

    void MoveObject(int which, float x_delta, float y_delta)
    {
      Objects[which].BlockingShape.move({ x_delta, y_delta });

      //corner segments start at 4
      int start = (which + 1) * 4;

      Edges[start].End.x += x_delta; Edges[start].Start.x += x_delta;
      Edges[start].End.y += y_delta; Edges[start].Start.y += y_delta;

      Edges[start + 1].End.x += x_delta; Edges[start + 1].Start.x += x_delta;
      Edges[start + 1].End.y += y_delta; Edges[start + 1].Start.y += y_delta;

      Edges[start + 2].End.x += x_delta; Edges[start + 2].Start.x += x_delta;
      Edges[start + 2].End.y += y_delta; Edges[start + 2].Start.y += y_delta;

      Edges[start + 3].End.x += x_delta; Edges[start + 3].Start.x += x_delta;
      Edges[start + 3].End.y += y_delta; Edges[start + 3].Start.y += y_delta;

      LitTriangles.clear();
      AdvanceSweep({ 400.f, 400.f }, 400.f);
    }

    void AddLight(const sf::Vector2f &pt, float atten, sf::Color c);

    void AdvanceSweep(sf::Vector2f LightSource, float attenuation);

    void RefreshFrame()
    {
      LitTriangles.clear();
    }


    //start = starting end of the segment, end = the ending part of it, vector = the vector that *might* be between the two endpoints
    bool CanIntersectSegment(sf::Vector2f start, sf::Vector2f end, sf::Vector2f light_source, sf::Vector2f vector, float rad);

    bool FindClosestEdge(sf::Vector2f LightSource, sf::Vector2f Point, float Attenuation, sf::Vector2f &Intersection, int &edge_index);

    void DrawLightTexture(std::size_t which);


    //data used for visualizing sweeping
    int EdgeToShow = -1;
    sf::Vector2f PointHitByRay;
    sf::VertexArray DrawSegment = sf::VertexArray(sf::Lines, 2);
    sf::VertexArray DrawLine = sf::VertexArray(sf::Lines, 2);
    bool draw_hit_segment = false;
    float theta = 0;
    float dtheta = 2 * PI / 500;
    int frame_delta = 0;
    int breaks_around_circle = 1000;
    bool DoRefreshFrame = true;

    sf::Vector2f LastEdgeEnd;
    sf::Vector2f LastEdgePoint;

    //sf::Text FrameDelta;
    //sf::Text IterationsAroundCircle;
    //sf::Text SegmentHit;
    //sf::Text LastHitSegment;
    //sf::Text StatusText;
    //sf::Text SecondLightText;
    //sf::Text ThirdLightText;
    //sf::Text AttenuationRadius;

    //sf::Text InstructionsText;
    //sf::Sprite InstructionsSprite;
    sf::RenderTexture InstructionsTexture;
    sf::RenderTexture LitTrianglesTexture;
    sf::Sprite TrianglesSprite;

    sf::Font DrawFont;

    bool advancing = false;

    std::vector<Edge> Edges;
    std::vector<sf::VertexArray> LitTriangles;

    sf::RenderTexture *LightTexture = nullptr;

    bool DrawWhiteRays = false;
    std::vector<sf::VertexArray> Segments;

    std::vector<LightObject> Objects;

    std::vector<Light> Lights;
    sf::Shader LightShader;

    sf::RectangleShape OverallBounds;

    unsigned int window_size_y;
    unsigned int window_size_x;
  };
}
#endif
