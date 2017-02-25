#ifndef SFENGINE_PHYSICS_INCLUDE_ALL_H
#define SFENGINE_PHYSICS_INCLUDE_ALL_H

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

#include <memory>
#include <vector>
#include <string>
#include <sstream>

namespace Engine
{
  typedef mvHit PhysicsEngineBaseMeshType;
  typedef segHit PhysicsEngineSegmentType;

  typedef std::shared_ptr<PhysicsEngineBaseMeshType> BaseMeshPtr;
  typedef std::shared_ptr<PhysicsEngineSegmentType> SegmentPtr;

  //std::shared_ptr<PhysicsEngineBaseMeshType> BuildMesh(std::stringstream &data_stream);
  //std::shared_ptr<PhysicsEngineSegmentType> BuildSegment(std::stringstream &data_stream);

  BaseMeshPtr BuildBallMesh(char BallType, const sf::Vector2f &InitialPosition, const sf::Vector2f &InitialVelocity, unsigned int Radius, float Mass, float CoeffecientOfRest, const sf::Color &Color);
  BaseMeshPtr BuildPolygonMesh(unsigned int num_sides, float radius, float init_rotation, const sf::Vector2f &InitialPosition, const sf::Vector2f &InitialVelocity, float mass, float CoeffOfRest, const sf::Color &Color);
  SegmentPtr BuildSegmentMesh(char type, const sf::Vector2i &TopLeftCorner, const sf::Vector2i &BottomRightCorner, float radius = -1);

  std::stringstream GetFormattedBallConstructionData(char BallType, const sf::Vector2f &InitialPosition, const sf::Vector2f &InitialVelocity, unsigned int Radius, float Mass, float CoeffecientOfRest, const sf::Color &Color);
  std::stringstream GetFormattedPolyConstructionData(unsigned int num_sides, float radius, float init_rotation, const sf::Vector2f &InitialPosition, const sf::Vector2f &InitialVelocity, float mass, float CoeffOfRest, const sf::Color &Color);
  std::stringstream GetFormattedSegmentConstructionData(char type, const sf::Vector2i &TopLeftCorner, const sf::Vector2i &BottomRightCorner, float radius = -1);

  void UpdatePhysics(std::vector<BaseMeshPtr> &Meshes, std::vector<SegmentPtr> Segments, std::size_t Steps = 1);
  void AssignBoundaries(float WindowHeight, float WindowWidth);
  void SetGravity(vec2d *Gravity);
}

#endif
