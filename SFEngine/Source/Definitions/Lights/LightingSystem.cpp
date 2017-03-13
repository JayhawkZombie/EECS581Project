#include "../../Headers/Lights/LightingSystem.h"
#include "../../Headers/Physics/QuadTree.h"

namespace Engine
{
#ifndef ____PI
#define ____PI 3.141592653
#endif

#define COSPIBY4 0.25

#define MAX_CIRCLE_ANGLE 512
#define HALF_MAX_CIRCLE_ANGLE (MAX_CIRCLE_ANGLE >> 1)
#define QUARTER_MAX_CIRCLE_ANGLE (MAX_CIRCLE_ANGLE >> 2)
#define MASK_MAX_CIRCLE_ANGLE (MAX_CIRCLE_ANGLE - 1)
#define PI 3.141592653589793238f

#define USE_LOOKUP_TABLE

  float CosineTable[MAX_CIRCLE_ANGLE];

  inline void FtoInt(int *int_ptr, float f) {
    __asm fld f
    __asm mov edx, int_ptr
    __asm FRNDINT
    __asm fistp dword ptr[edx];
  }

  inline float fastcos(float n) {
    float f = n * HALF_MAX_CIRCLE_ANGLE / PI;
    int i;
    FtoInt(&i, f);
    return(
      i < 0 ?
      CosineTable[((-i) + QUARTER_MAX_CIRCLE_ANGLE) & MASK_MAX_CIRCLE_ANGLE] :
      CosineTable[(i + QUARTER_MAX_CIRCLE_ANGLE) & MASK_MAX_CIRCLE_ANGLE]);
  }

  inline float fastsin(float n) {
    float f = n * HALF_MAX_CIRCLE_ANGLE / PI;
    int i;
    FtoInt(&i, f);
    return(
      i < 0 ?
      CosineTable[(-((-i)&MASK_MAX_CIRCLE_ANGLE)) + MAX_CIRCLE_ANGLE] :
      CosineTable[i & MASK_MAX_CIRCLE_ANGLE]);
  }

  INLINE void Normalize(sf::Vector2f & v)
  {
    float mag = std::sqrt((v.x * v.x) + (v.y * v.y));
    v.x /= mag;
    v.y /= mag;
  }

  INLINE float Cross2D(const sf::Vector2f & v1, const sf::Vector2f & v2)
  {
    return ((v1.x * v2.y) - (v1.y * v2.x));
  }

  INLINE float DistanceBetween(const sf::Vector2f & v1, const sf::Vector2f & v2)
  {
    float x = v1.x - v2.x;
    float y = v1.y - v2.y;

    return (std::sqrt((x * x) + (y * y)));
  }

  LightSystem::LightSystem()
  {
    #ifdef USE_LOOKUP_TABLE
        //pre-compute all of our sin/cos values  
        for (int i = 0; i < MAX_CIRCLE_ANGLE; ++i) {
          CosineTable[i] = (float)(std::sin((double)i * PI / HALF_MAX_CIRCLE_ANGLE));
        }
    #endif
  }

  LightSystem::~LightSystem()
  {
  }

  void LightSystem::SetWindowHeight(float f)
  {
  }

  void LightSystem::SetDrawRegionSize(sf::Vector2f RegionSize)
  {
    sf::Vector2u Size = { __UINT_FROM_FLOAT__(std::ceil(RegionSize.x)), 
                          __UINT_FROM_FLOAT__(std::ceil(RegionSize.y)) };
    LightMap.create(Size.x, Size.y);
  }

  void LightSystem::Update(std::shared_ptr<QuadTree> Tree)
  {
    sf::FloatRect Region;
    ShadowVolume.clear();

    for (auto & light : Lights) {
      Region = { light.second.Position.x, light.second.Position.y, light.second.Attenuation, light.second.Attenuation };
      UpdateShadowVolumeForLight(light.first, Tree->GetContainedShadowCastingObjectsInRange(Region));

      if (light.second.CastSoftShadow)
        ComputePenumbraRegion(light.first);
    }
  }

  void LightSystem::Render(std::shared_ptr<sf::RenderTexture> TargetTexture)
  {
    LightMap.clear(sf::Color::Transparent);
    DrawLights();
  }

  void LightSystem::AddLight(const Light & light)
  {
  }

  void LightSystem::DrawLights()
  {
  }

  void LightSystem::UpdateShadowVolumeForLight(std::uint32_t ID, const std::vector<std::shared_ptr<Engine::LightObject>> &Meshes)
  {
  }

  void LightSystem::ComputePenumbraRegion(std::uint32_t ID)
  {
  }

}
