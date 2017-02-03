#include "mvHit.h"

float mvHit::wdwW, mvHit::wdwH;
float mvHit::wdwCf = 0.0f;// friction coeff
vec2d* mvHit::pGravity = nullptr;

void mvHit::init(std::istream& fin)
{
  fin >> pos.x >> pos.y >> v.x >> v.y;
  fin >> m >> Cr;
}

bool mvHit::bounce(float Cf, vec2d N, bool isFric)// rigid bounce. N is line of action
{
  if (v.dot(N) < 0.0f)// pre-collision
  {
    v = v.to_base(N);// velocity change response
    float  dV = Cf*v.x*(1.0f + Cr);
    respond(dV, isFric);
    v.x *= -Cr;
    v = v.from_base(N);
    return true;
  }

  return false;
}
