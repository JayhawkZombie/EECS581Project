#ifndef BALL_GO_H_INCLUDED
#define BALL_GO_H_INCLUDED

#include "ball.h"

class ball_go : public ball
{
public:
  float maxVel;// magnitude, so > 0

               // functions
  ball_go(std::istream& fin);
  ball_go() {}
  virtual ~ball_go() {}

  virtual void init(std::istream& fin);
  virtual void respond(float dV, bool isFric);
};

#endif // BALL_GO_H_INCLUDED
