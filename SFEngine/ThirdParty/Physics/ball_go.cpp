#include "ball_go.h"

ball_go::ball_go( std::ifstream& fin )// from file data
{
  init(fin);
}

void ball_go::init( std::ifstream& fin )// from file data
{
    ball::init(fin);
 //   fin >> maxVel;// >> maxAcc;
    maxVel = 0.0f;
}

void ball_go::respond( float dV, bool isFric )// assumes velocity components are T(x) and N(y) to obstacle
{
    if( !isFric ) return;// no change in x component can occur
    if( v.y == maxVel ) return;// target speed acheived

    // speed needs adjustment
    if( dV < 0.0f ) dV *= -1.0f;// assure dV is positive
    if( v.y > maxVel ){ v.y -= dV; if( v.y < maxVel ) v.y = maxVel; }
    else { v.y += dV; if( v.y > maxVel ) v.y = maxVel; }

    return;
}
