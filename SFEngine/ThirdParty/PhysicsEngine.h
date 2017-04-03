#ifndef SFENGINE_PHYSICS_INCLUDE_ALL_H
#define SFENGINE_PHYSICS_INCLUDE_ALL_H

#include <memory>
#include <vector>
#include <string>
#include <sstream>

#include "Physics/arcSeg.h"
#include "Physics/ball.h"
#include "Physics/ball_go.h"
#include "Physics/lineBumper.h"
#include "Physics/lineSeg.h"
#include "Physics/lineSegElevator.h"
#include "Physics/lineSegFlip.h"
#include "Physics/lineSegRotate.h"
#include "Physics/lineSegSwing.h"
#include "Physics/mvHit.h"
#include "Physics/regPolygon.h"
#include "Physics/segHit.h"
#include "Physics/vec2d.h"
#include "Physics/waveSeg.h"

namespace Engine
{
  typedef mvHit PhysicsEngineBaseMeshType;
  typedef segHit PhysicsEngineSegmentType;
  typedef waveSeg PhysicsEngineWaveSegment;

  class Collider2D;

  typedef std::shared_ptr<PhysicsEngineBaseMeshType> BaseMeshPtr;
  typedef std::shared_ptr<PhysicsEngineSegmentType> SegmentPtr;
  typedef std::shared_ptr<PhysicsEngineWaveSegment> WaveSegmentPtr;

  BaseMeshPtr BuildBallMesh(char BallType, const sf::Vector2f &InitialPosition, const sf::Vector2f &InitialVelocity, unsigned int Radius, float Mass, float CoeffecientOfRest, const sf::Color &Color);
  BaseMeshPtr BuildPolygonMesh(unsigned int num_sides, float radius, float init_rotation, const sf::Vector2f &InitialPosition, const sf::Vector2f &InitialVelocity, float mass, float CoeffOfRest, const sf::Color &Color);
  SegmentPtr BuildSegmentMesh(char type, const sf::Vector2i &TopLeftCorner, const sf::Vector2i &BottomRightCorner, float radius = -1);
  WaveSegmentPtr BuildWaveSegment(char type, const sf::Vector2i &TopLeftCorner, const sf::Vector2i &BottomRightCorner, float radius, bool IsHard,
                                  unsigned int NumWavePts, float ampRight, float waveLenRight, float rFreqRight,
                                  float ampLeft, float waveLenLeft, float rFreqLeft,
                                  float elev, float airDen, float depth, float fluidDen);

  std::stringstream GetFormattedBallConstructionData(char BallType, const sf::Vector2f &InitialPosition, const sf::Vector2f &InitialVelocity, unsigned int Radius, float Mass, float CoeffecientOfRest, const sf::Color &Color);
  std::stringstream GetFormattedPolyConstructionData(unsigned int num_sides, float radius, float init_rotation, const sf::Vector2f &InitialPosition, const sf::Vector2f &InitialVelocity, float mass, float CoeffOfRest, const sf::Color &Color);
  std::stringstream GetFormattedSegmentConstructionData(char type, const sf::Vector2i &TopLeftCorner, const sf::Vector2i &BottomRightCorner, float radius);
  std::stringstream GetFormattedWaveSegmentConstructionData(char type, const sf::Vector2i &TopLeftCorner, const sf::Vector2i &BottomRightCorner, float radius, bool IsHard, 
                                                            unsigned int NumWavePts, float ampRight, float waveLenRight, float rFreqRight,
                                                            float ampLeft, float waveLenLeft, float rFreqLeft,
                                                            float elev, float airDen, float depth, float fluidDen);

  void UpdatePhysics(std::vector<PhysicsEngineBaseMeshType *> &Meshes, std::vector<PhysicsEngineSegmentType *> Segments, std::size_t Steps = 1);
  void UpdatePhysics(std::vector<std::shared_ptr<Engine::Collider2D>> Colliders, std::vector<PhysicsEngineSegmentType *> Segments, std::size_t steps = 1);
  void AssignBoundaries(float WindowHeight, float WindowWidth);
  void SetGravity(::vec2d *Gravity);
}

#endif
