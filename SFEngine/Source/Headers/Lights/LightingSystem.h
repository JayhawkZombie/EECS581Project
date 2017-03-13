#ifndef SFENGINE_LIGHTING_SYSTEM_H
#define SFENGINE_LIGHTING_SYSTEM_H

#include "LightObject.h"
#include "../Utils/RayCast.h"

#define ____PI 3.141592653f
#define COSPIBY4 0.25

namespace Engine
{

  void Normalize(sf::Vector2f &v);

  float Cross2D(const sf::Vector2f &v1, const sf::Vector2f &v2);

  float DistanceBetween(const sf::Vector2f &v1, const sf::Vector2f &v2);

  class QuadTree;

  class LightSystem
  {
  public:
    LightSystem();
    ~LightSystem();

    void SetWindowHeight(float f);
    void SetDrawRegionSize(sf::Vector2f RegionSize);
    void Update(std::shared_ptr<QuadTree> Tree);
    void Render(std::shared_ptr<sf::RenderTexture> TargetTexture);
    void AddLight(const Light &light);
  protected:
    void DrawLights();
    void UpdateShadowVolumeForLight(std::uint32_t ID, const std::vector<std::shared_ptr<Engine::LightObject>> &Meshes);
    void ComputePenumbraRegion(std::uint32_t ID);
    sf::VertexArray ShadowVolume;
    sf::RenderTexture LightMap;
    std::map<std::uint32_t, Light> Lights;
    sf::Shader LightShader;
    sf::Shader BlendShader;
    sf::Shader ShadowingShader;
    float WindowHeight;
  };
  
}
#endif
