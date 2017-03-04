#ifndef SFENGINE_LIGHTING_SYSTEM_H
#define SFENGINE_LIGHTING_SYSTEM_H

#include "LightObject.h"
#include "../Utils/RayCast.h"

#define ____PI 3.141592653
#define COSPIBY4 0.25

namespace Engine
{

  void Normalize(sf::Vector2f &v);

  float Cross2D(const sf::Vector2f &v1, const sf::Vector2f &v2);

  float DistanceBetween(const sf::Vector2f &v1, const sf::Vector2f &v2);



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
    std::uint32_t ID;
    sf::CircleShape Circle;
  };

  class LightSystem {
  public:


    LightSystem();
    ~LightSystem();
    void SetBoundaries(const sf::Vector2f &TopLeft, const sf::Vector2f &TopRight, const sf::Vector2f &BottomRight, const sf::Vector2f &BottomLeft);
    void AddLightObject(std::shared_ptr<LightObject> Object);
    void AddComplexObject(const std::vector<sf::Vector2f> &positions);
    void RenderLightToTexture(std::shared_ptr<Light> light, std::shared_ptr<sf::RenderTexture> Target);
    void BlurLightTexture(std::shared_ptr<Light> light);
    void BlendLightMapWithScene(std::shared_ptr<Light> light, std::shared_ptr<sf::RenderTexture> SceneTexture, std::shared_ptr<sf::RenderTexture> OutputTexture);
    void AddLight(std::shared_ptr<Light> light);
    void UpdateLight(std::shared_ptr<Light> light);
    void SweepLight(std::shared_ptr<Light>);
    void DrawLightMap(std::shared_ptr<Light> light);
    void RefreshFrame()
    {
      LightTriangles.clear();
    }
    //start = starting end of the segment, end = the ending part of it, vector = the vector that *might* be between the two endpoints
    bool CanIntersectSegment(sf::Vector2f start, sf::Vector2f end, sf::Vector2f light_source, sf::Vector2f vector, float rad);
    bool FindClosestEdge(sf::Vector2f LightSource, sf::Vector2f Point, float Attenuation, sf::Vector2f &Intersection, int &edge_index);
    void DrawLightTexture(std::size_t which);

  protected:
    //Store the edges that cast shadows
    std::vector<Edge> Edges;
    //Data to store the lights and objects
    std::unordered_map<std::uint32_t, std::shared_ptr<LightObject>> LightObjects;
    std::unordered_map<std::uint32_t, std::shared_ptr<Light>> Lights;
    std::unordered_map<std::uint32_t, std::shared_ptr<sf::RenderTexture>> LightTextures;
    std::unordered_map<std::uint32_t, std::shared_ptr<sf::RenderTexture>> LightMaps;

    //Data for processing the sweeping ray
    float THETA;
    float dTheta = 2 * ____PI / 1024.f;
    int breaks_around_circle = 1024;

    //Store the casted light areas
    sf::RenderStates state;
    sf::VertexArray LightTriangles;
    std::unique_ptr<sf::Shader> LightShader;
    std::unique_ptr<sf::Shader> BlendShader;
    std::unique_ptr<sf::Shader> BlurShader;
  };
}
#endif
