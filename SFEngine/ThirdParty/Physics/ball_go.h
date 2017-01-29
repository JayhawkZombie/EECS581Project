#ifndef BALL_GO_H_INCLUDED
#define BALL_GO_H_INCLUDED

#include "ball.h"

class ball_go : public ball
{
    public:
    float maxVel;// magnitude, so > 0

    // functions
    ball_go( std::ifstream& fin );
    ball_go() {}
    virtual ~ball_go() {}

    virtual void init( std::ifstream& fin );
    virtual void respond( float dV, bool isFric );
};

#endif // BALL_GO_H_INCLUDED
