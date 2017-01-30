#include "segHit.h"
#include "mvHit.h"

segHit::segHit(std::stringstream& fin) {
  init(fin);
}

void segHit::init(std::stringstream& fin)
{
  //   fin >> testEnd1 >> testEnd2;
  fin >> pos.x >> pos.y;
  testEnd1 = testEnd2 = true;
}

void segHit::to_file(std::ofstream& fout)
{
  fout << (testEnd1 ? '1' : '0') << ' ' << (testEnd2 ? '1' : '0') << '\n';
  fout << pos.x << ' ' << pos.y;
}

void segHit::update() {
  return;
}

bool segHit::hit(mvHit& mh)
{
  vec2d Pimp, Nh;
  float dSep;

  if (is_onMe(mh, Pimp, Nh, dSep))
  {
    mh.bounce(Cf, Nh, friction_on);// velocity response
    mh.setPosition(mh.pos + Nh*dSep);// position change response
    return true;
  }

  return false;
}
