#include "Lights\LightingSystem.h"
#include "Physics\QuadTree.h"
#include "Physics\Collider.h"

#include <math.h>

namespace Engine
{
#ifndef ____PI
#define ____PI 3.141592653
#endif

  void SortByAngleFrom(::vec2d OriginPt, const std::vector<::vec2d> &Points, ::vec2d &lowExtremePt, ::vec2d &highExtremePt) {
    float low_angle = 0.f;
    float high_angle = 0.f;

    float _angle = 0.f;
    ::vec2d _moved_pt;

    for (auto & point : Points) {
      _moved_pt = point - OriginPt;
      if (_moved_pt.x != 0 && _moved_pt.y != 0)
        _angle = atan2f(_moved_pt.y, _moved_pt.x);
      else
        _angle = 0.f;

      if (_angle <= low_angle) {
        low_angle = _angle;
        lowExtremePt = point;
      }
      if (_angle >= high_angle) {
        high_angle = _angle;
        highExtremePt = point;
      }
    }

  }

  ::vec2d ToVec2d(const sf::Vector2f &vec) {
    return ::vec2d(vec.x, vec.y);
  }

  void _normalize(sf::Vector2f &v)
  {
    if (v.x == 0 && v.y == 0)
      return;

    float mag = (v.x * v.x) + (v.y * v.y);
    mag = std::sqrt(mag);
    v /= mag;
  }

  float Dot(const sf::Vector2f &v1, const sf::Vector2f &v2)
  {
    return ((v1.x * v2.x) + (v1.y * v2.y));
  }

  float DistanceBetween(const sf::Vector2f &a, const sf::Vector2f &b)
  {
    float x_dist = b.x - a.x;
    float y_dist = b.y - a.y;
    return (sqrt(
      (x_dist * x_dist) + (y_dist * y_dist)
    ));
  }

  LightSystem::LightSystem()
  {
  }

  LightSystem::~LightSystem()
  {
  }

  void LightSystem::Update(std::map<std::string, SPtrShared<LevelObject>>& Objects)
  {
    m_MapDrawn.clear();

    for (auto & obj : Objects) {

      for (auto & occluder : obj.second->GetOccluders()) {
        m_MapDrawn.push_back(occluder);
      }
    }

    /* Sort based on angle from light source */
    ::vec2d _v1, _v2;
    ::vec2d _o1, _o2;
    ::vec2d _v1_dir, _v2_dir;
    sf::Vector2f pt;

    sf::Vertex V1, V2, O1, O2, L;

    float d_squared = 0.f;
    float atten_squared = 0.f;

    for (auto & light : m_Lights) {
      atten_squared = light.second->m_Attenuation;
      atten_squared *= atten_squared;

      /* Create the triangles for the light and dark regions */
      for (auto & ptVec : m_MapDrawn) {
        m_LightRegions[light.first].clear();
        m_DarkRegions[light.first].clear();

        auto vec = ptVec->GetVertices();

        /* 0/1 , 1/2, 2/3, ... size - 1/0 */
        for (std::size_t i = 0; i < vec.size(); ++i) {
          _v1 = vec[i];
          _v2 = (i == vec.size() - 1 ? vec[0] : vec[i + 1]);
          _v1_dir = _v1 - ToVec2d(light.second->m_Position);
          _v2_dir = _v2 - ToVec2d(light.second->m_Position);
          _v1_dir /= _v1_dir.mag();
          _v2_dir /= _v2_dir.mag();
          _o1 = _v1 + (light.second->m_Attenuation) * _v1_dir;
          _o2 = _v2 + (light.second->m_Attenuation) * _v2_dir;

          V1.position = (sf::Vector2f)_v1; V2.position = (sf::Vector2f)_v2; L.position = light.second->m_Position;
          V1.color = light.second->m_Hue; 
          V2.color = light.second->m_Hue; 
          L.color = light.second->m_Hue;

          m_LightRegions[light.first].append(L);
          m_LightRegions[light.first].append(V1);
          m_LightRegions[light.first].append(V2);

          O1.position = (sf::Vector2f)_o1; O2.position = (sf::Vector2f)_o2;
          V1.color = sf::Color::Black;
          V2.color = sf::Color::Black;
          O1.color = sf::Color::Black;
          O2.color = sf::Color::Black;

          m_DarkRegions[light.first].append(V1);
          m_DarkRegions[light.first].append(V2);
          m_DarkRegions[light.first].append(O1);

          m_DarkRegions[light.first].append(V2);
          m_DarkRegions[light.first].append(O1);
          m_DarkRegions[light.first].append(O2);
        }

      } //for auto & ptVec : m_MapDrawn

    } // for auto & light : m_Lights

    if (m_LightRegions.size() == 0) {
      std::cerr << "NO LIGHT REGIONS" << std::endl;
    }
  }

  void LightSystem::RenderOnTexture(std::shared_ptr<sf::RenderTexture> Texture)
  {
    RenderState.blendMode = sf::BlendAdd;

    //for (auto & light_region : m_LightRegions)
    //  Texture->draw(light_region.second);
    for (auto & dark_region : m_DarkRegions)
      Texture->draw(dark_region.second);
    for (auto & light : m_Lights)
      Texture->draw(light.second->m_OutlinedCircleArea);
  }

  void LightSystem::AddLight(sf::Vector2f Pos, float Atten, sf::Color Color, std::string Name)
  {
    m_Lights[Name] = std::make_shared<Engine::Light>();
    m_Lights[Name]->m_Position = Pos;
    m_Lights[Name]->m_Attenuation = Atten;
    m_Lights[Name]->m_Hue = Color;
    m_Lights[Name]->m_Name = Name;

    m_Lights[Name]->m_OutlinedCircleArea.setPosition(Pos);
    m_Lights[Name]->m_OutlinedCircleArea.setRadius(Atten);
    m_Lights[Name]->m_OutlinedCircleArea.setOrigin({ Atten, Atten });
    m_Lights[Name]->m_OutlinedCircleArea.setFillColor(sf::Color(98, 98, 98, 115));
    m_Lights[Name]->m_OutlinedCircleArea.setOutlineThickness(2);
    m_Lights[Name]->m_OutlinedCircleArea.setOutlineColor(sf::Color::White);

    m_LightRegions[Name] = sf::VertexArray(sf::Triangles);
    m_DarkRegions[Name] = sf::VertexArray(sf::Triangles);
    
  }

}
