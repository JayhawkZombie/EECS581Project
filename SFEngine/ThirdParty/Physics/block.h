#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED
#include <sstream>
#include "regPolygon.h"

class block : public regPolygon
{
public:
  float W, H;// dimensions
             //    float r;// length of rays
             //   size_t nSides;// = ptVec.size()
             //   std::vector<vec2d> ptVec;// official
             //   std::vector<sf::Vertex> vtxVec;// visual

  block(std::stringstream& fin);
  block() {}
  virtual ~block() {}
  virtual void init(std::stringstream& fin);
  virtual void setRotation(float angle);
  virtual float getRotation()const;
  virtual bool inCircle(vec2d ctr, float R, vec2d& Pimp)const;
  // all other inherited functions should do
};

#endif // BLOCK_H_INCLUDED
