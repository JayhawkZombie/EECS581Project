#include "waveSeg.h"
#include "mvHit.h"

float waveSeg::PIx2 = 6.283185f;

waveSeg::waveSeg(std::istream& is) {
  init(is);
}

void waveSeg::init(std::istream& is)
{
  lineSeg::init(is);
  magL = L.mag();// cached! Yeah!

  is >> Npts_wv;// 1st, not last
  if (Npts_wv < 2) Npts_wv = 2;

  float L_wv = 100.0f;
  is >> Amp_wvRt >> L_wv;
  if (L_wv < magL / 100.0f) L_wv = magL / 100.0f;
  K_wvRt = PIx2 / L_wv;
  is >> rotFreqRt; if (rotFreqRt < 0.0f) rotFreqRt *= 0.0f;

  is >> Amp_wvLt >> L_wv;
  if (L_wv < magL / 100.0f) L_wv = magL / 100.0f;
  K_wvLt = PIx2 / L_wv;
  is >> rotFreqLt; if (rotFreqLt < 0.0f) rotFreqLt *= 0.0f;

  is >> Elev >> airDensity;
  is >> Depth >> fluidDensity;
  std::cerr << "airD: " << airDensity << "  fluD: " << fluidDensity;

  // fill the vector<vertex>
  wvVec.reserve(Npts_wv);
  wvVecLt.reserve(Npts_wv);
  wvVecRt.reserve(Npts_wv);
  float dx = magL / (float)(Npts_wv - 1);
  sf::Vertex vtx;
  // right wave
  vtx.color = sf::Color::Red;// right wave red
  for (int i = 0; i<Npts_wv; ++i)
  {
    float x_rel = dx*(float)i;
    vtx.position.x = pos.x + x_rel;
    vtx.position.y = pos.y + y_wvRt(x_rel);
    wvVecRt.push_back(vtx);
  }
  // left wave
  vtx.color = sf::Color::Green;// left wave green
  for (int i = 0; i<Npts_wv; ++i)
  {
    float x_rel = dx*(float)i;
    vtx.position.x = pos.x + x_rel;
    vtx.position.y = pos.y + y_wvLt(x_rel);
    wvVecLt.push_back(vtx);
  }
  // resultant wave
  vtx.color = sf::Color::Blue;// result is blue
  for (int i = 0; i<Npts_wv; ++i)
  {
    float x_rel = dx*(float)i;
    vtx.position.x = pos.x + x_rel;
    vtx.position.y = wvVecRt[i].position.y + wvVecLt[i].position.y - pos.y;
    wvVec.push_back(vtx);
  }
}

void waveSeg::to_file(std::ofstream& fout)
{
  return;
}

void waveSeg::draw(sf::RenderTarget& rRW)const
{
  if (viewSeg) lineSeg::draw(rRW);
  rRW.draw(&wvVec[0], wvVec.size(), sf::LinesStrip);
  if (viewLt)  rRW.draw(&wvVecLt[0], wvVecLt.size(), sf::LinesStrip);
  if (viewRt)  rRW.draw(&wvVecRt[0], wvVecRt.size(), sf::LinesStrip);
}

void waveSeg::update()
{
  phsLt += rotFreqLt; if (phsLt > PIx2) phsLt -= PIx2;
  phsRt += rotFreqRt; if (phsRt > PIx2) phsRt -= PIx2;
  float dx = magL / (float)(Npts_wv - 1);
  float x_rel = 0.0f;

  // don't assign all if only resultant being drawn require if( viewLt || viewRt )
  for (int i = 0; i<Npts_wv; ++i)
  {
    x_rel = dx*(float)i;
    wvVecRt[i].position.y = pos.y + y_wvRt(x_rel);
    wvVecLt[i].position.y = pos.y + y_wvLt(x_rel);
    wvVec[i].position.y = wvVecRt[i].position.y + wvVecLt[i].position.y - pos.y;
  }

  return;
}

bool waveSeg::hit(mvHit& mh)
{
  // above the top?
  vec2d sepAtTop = mh.pos - (pos + N*Elev);// sep is rel position
  float h = sepAtTop.dot(N);// > 0 if above
  if (h > 0.0f) return false;
  float d = N.cross(sepAtTop);
  if (d < 0.0f || d > L.mag()) return false;// not above seg

                                            // below the bottom?
  vec2d sepAtBot = mh.pos - (pos - N*Depth);// sep is rel position
  h = sepAtBot.dot(N);// > 0 if above
  if (h < 0.0f) return false;

  // will be treating hit
  vec2d sep = mh.pos - pos;// sep is rel position
  float yPm = wv_slope(sep.x);// new pos
  float ampRes = y_res(sep.x) - mh.project(-N)*(sqrtf(1.0f + yPm*yPm) - 1.0f);// wave amplitude + set above
  sep.y -= ampRes;
  h = sep.dot(N);// height above wave to mh.pos
                 //position shift
  mh.pos.y -= ampRes;
  // velocity shift relative to rising wave
  float vShift_y = y_vel(sep.x);
  mh.v.y -= vShift_y;
  // Get normal to surface
  vec2d Nsurf(1.0f, yPm);
  Nsurf = Nsurf.get_LH_norm();

  bool Hit = false;
  vec2d Pimp, Nh;
  float dSep;
  if (is_onMe(mh, Pimp, Nh, dSep))
  {
    if (is_hard)
    {
      mh.bounce(Cf, Nsurf, friction_on);// velocity response
      mh.pos.y += ampRes;
      mh.v.y += vShift_y;
      mh.setPosition(mh.pos + Nh*dSep);// position change response
      return true;
    }
    else
      mh.Float(Nsurf, Nh, dSep, grav_N, airDensity, fluidDensity);

    Hit = true;
  }

  mh.v.y += vShift_y;// old pos
  mh.pos.y += ampRes;// new pos

  if (!is_hard && !Hit)
  {
    if (sep.dot(N) > 0.0f)// in air
      mh.Float(N, grav_N, airDensity);
    else
      mh.Float(N, grav_N, fluidDensity);
  }

  return Hit;
}


/*
bool waveSeg::hit( mvHit& mh )
{
vec2d sep = mh.pos - pos;// sep is rel position
float ampRes = y_res( sep.x );// wave amplitude here
float h = sep.dot(N);// > 0 if above

if( h > Amp_wv + Amp_wvLt + mh.project( vec2d(0.0f,1.0f) ) ) return false;// mh above wave
if( h < -1.0f*( Amp_wv + Amp_wvLt + mh.project( vec2d(0.0f,-1.0f) ) ) ) return false;// mh above wave

//position shift
mh.pos.y -= ampRes;
// velocity shift relative to rising wave
float vShift_y = y_vel(sep.x);
mh.v.y -= vShift_y;
// finally, rotate velocity to face. Will need to vShift_x also.

bool Hit = false;
vec2d Pimp, Nh;
float dSep;
if( is_onMe( mh, Pimp, Nh, dSep ) )
{
if( is_hard )
{
mh.bounce( Cf, Nh, friction_on );// velocity response
mh.pos.y += ampRes;
mh.v.y += vShift_y;
mh.setPosition( mh.pos + Nh*dSep );// position change response
return true;
}
else
mh.Float( getSurfaceNormal(mh), Nh, dSep );

Hit = true;
}

mh.pos.y += ampRes;
mh.v.y += vShift_y;

return Hit;
}
*/
