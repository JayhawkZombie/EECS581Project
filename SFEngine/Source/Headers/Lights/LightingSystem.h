#ifndef SFENGINE_LIGHTING_SYSTEM_H
#define SFENGINE_LIGHTING_SYSTEM_H

#include "Physics\Occluder.h"
#include "Utils\RayCast.h"

#include "Level\LevelObject.h"

#define COSPIBY4 0.25

namespace Engine
{
  void _normalize(sf::Vector2f &v);

  float Dot(const sf::Vector2f &v1, const sf::Vector2f &v2);

  float DistanceBetween(const sf::Vector2f &a, const sf::Vector2f &b);
  
  class Light
  {
  public:
    Light() = default;

    Light(const Light &light)
      : m_Position(light.m_Position), m_Attenuation(light.m_Attenuation),
      m_Hue(light.m_Hue), m_Name(light.m_Name) {}

    ~Light() = default;

    SVector2F m_Position;
    SFLOAT m_Attenuation;
    SFLOAT m_Intensity;
    sf::Color m_Hue;
    std::string m_Name;
    sf::CircleShape m_OutlinedCircleArea;
    sf::Sprite m_LightSprite;
  };

  class LightSystem
  {
  public:
    LightSystem();
    ~LightSystem();

    void Update(std::map<std::string, SPtrShared<LevelObject>>& Objects);
    void RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture, sf::View View);

    void AddLight(sf::Vector2f Pos, float Atten, sf::Color Color, std::string Name);

  protected:
    void CreateLightTexture(const Light &light);

    bool m_DrawTriangles = true;
    bool m_DrawLines = false;

    /* We can have one shadow map per light source */
    std::map<std::string, sf::VertexArray> m_LightRegions;
    std::map<std::string, sf::VertexArray> m_DarkRegions;
    
    //std::vector<::vec2d> m_LightRegions;
    //std::vector<::vec2d> m_DarkRegions;
    sf::RenderStates RenderState;
    sf::Texture m_RadialLightTexture;

    std::vector<SPtrShared<Collider2D>> m_MapDrawn;

    std::shared_ptr<sf::RenderTexture> m_MapTexture;

    std::map<std::string, SPtrShared<Light>> m_Lights;
    std::map<std::string, SPtrShared<sf::RenderTexture>> m_LightTextures;
    sf::Shader m_BlendingShader;
    
    sf::Shader m_LightShader;
    sf::Shader m_BlendVertexShader;
    sf::Shader m_BlendFragmentShader;
  };


}
#endif
