#include "ball.h"

#include "lineSeg.h"
#include "arcSeg.h"

bool ball::hit(regPolygon& py) {
  return py.hit(*static_cast<ball*>(this));
}
bool ball::hit(mvHit& mh) {
  return mh.hit(*static_cast<ball*>(this));
}

ball::ball() {}// default

ball::ball(std::istream& fin) {
  init(fin);
}// from file data

void ball::init(std::istream& fin)// from file data
{
  fin >> pos.x >> pos.y >> v.x >> v.y >> r;
  fin >> m >> Cr;// new
  unsigned int red, g, b;
  fin >> red >> g >> b;
  img.setRadius(r);
  img.setPosition(pos.x, pos.y);
  img.setFillColor(sf::Color(red, g, b));
  img.setOrigin(r, r);
  //    std::cout << "ball.v = " << v.mag() << '\n';
}

void ball::respond(float dV, bool isFric)// assumes velocity components are T(x) and N(y) to obstacle
{

  if (!isFric) return;// no change in x component can occur
  if (v.y == 0.0f) return;// target speed acheived
                          // speed needs adjustment
  if (dV < 0.0f) dV *= -1.0f;// assure dV is positive
  if (v.y > 0.0f) {
    v.y -= dV; if (v.y < 0.0f) v.y = 0.0f;
  }
  else {
    v.y += dV; if (v.y > 0.0f) v.y = 0.0f;
  }

  return;
}

void ball::update()// virtual
{
  if (!is_free) return;// new

  vec2d N(1.0f, 0.0f);
  bool Hit = false;

  if (pGravity) v += *pGravity;
  pos += v;

  if (pos.x < r)
  {
    pos.x = r;
    Hit = true;
    N.x = 1.0f; N.y = 0.0f;
  }
  else if (pos.x > ball::wdwW - r)
  {
    pos.x = ball::wdwW - r;
    Hit = true;
    N.x = -1.0f; N.y = 0.0f;
  }

  if (!Hit)
  {
    if (pos.y < r)
    {
      pos.y = r;
      Hit = true;
      N.x = 0.0f; N.y = 1.0f;
    }
    else if (pos.y > ball::wdwH - r)
    {
      pos.y = ball::wdwH - r;
      Hit = true;
      N.x = 0.0f; N.y = -1.0f;
    }
  }

  if (Hit) bounce(ball::wdwCf, N, true);
  img.setPosition(pos.x, pos.y);
}

void ball::draw(sf::RenderTarget& rRW)const {
  rRW.draw(img);
}

bool ball::hit(ball& rB)
{
  float Cf = 0.3f;

  // check for collision. Check distance between centers.
  float sepSq = (pos - rB.pos).dot(pos - rB.pos);
  if (sepSq > (r + rB.r)*(r + rB.r)) return false;// not touching


                                                  // xform to base set through ball centers
  vec2d sep = rB.pos - pos;// from this center to rB center
  float sepMag = sep.mag();// take the sqrt 1 time
  vec2d N = sep / sepMag;// unit length. First of local base set. 2nd is LH normal

                         // is either ball fixed?
  if (is_free && rB.is_free)// both are free to move
  {
    float Mtot = m + rB.m;
    vec2d Vcm = (v*m + rB.v*rB.m) / Mtot;
    v -= Vcm;
    rB.v -= Vcm;

    v = v.to_base(-1.0f*N);
    rB.v = rB.v.to_base(N);
    // collision response is along line through centers
    if (v.x < 0.0f) {
      respond(Cf*v.x*(1.0f + Cr), true); v.x *= -Cr;
    }
    if (rB.v.x < 0.0f) {
      rB.respond(Cf*rB.v.x*(1.0f + Cr), true); rB.v.x *= -Cr;
    }
    // transform back
    v = v.from_base(-1.0f*N);// rotate
    rB.v = rB.v.from_base(N);
    v += Vcm;// translate
    rB.v += Vcm;

    // correct over penetration. Move apart
    float dSep = r + rB.r - sepMag;// amount of penetration
    rB.pos += (dSep*m / Mtot)*N;// preserves position of center of mass
    pos -= (dSep*rB.m / Mtot)*N;// no wrecking energy conservation!

    return true;
  }

  // one ball is not free
  ball& ballFree = is_free ? *this : rB;
  ball& ballFixed = is_free ? rB : *this;// must be other ball
                                         // N must point from fixed to free
  N = ballFree.pos - ballFixed.pos; N /= N.mag();// unit length needed

  ballFree.v = ballFree.v.to_base(N);
  if (ballFree.v.x < 0.0f) {
    ballFree.respond(Cf*ballFree.v.x*(1.0f + Cr), true); ballFree.v.x *= -Cr;
  }
  ballFree.v = ballFree.v.from_base(N);
  // correct over penetration. Move apart
  float dSep = r + rB.r - sepMag;// amount of penetration
  ballFree.pos += dSep*N;// preserves position of center of mass

  return true;
}

/*
bool ball::hit( ball& rB )
{
// check for collision. Check distance between centers.
float sepSq = ( pos - rB.pos ).dot( pos - rB.pos );
if( sepSq > (r + rB.r)*(r + rB.r) ) return false;// not touching

// xform velocities to center of mass
float Mtot = m + rB.m;
vec2d Vcm = ( v*m + rB.v*rB.m )/Mtot;
v -= Vcm;
rB.v -= Vcm;
// xform to base set through ball centers
vec2d sep = rB.pos - pos;// from this center to rB center
float sepMag = sep.mag();// take the sqrt 1 time
vec2d N = sep/sepMag;// unit length. First of local base set. 2nd is LH normal
v = v.to_base( N );
rB.v = rB.v.to_base( N );
// collision response is along line through centers
if( v.x > 0.0f ) v.x *= -Cr;
if( rB.v.x < 0.0f ) rB.v.x *= -Cr;
// transform back
v = v.from_base( N );// rotate
rB.v = rB.v.from_base( N );
v += Vcm;// translate
rB.v += Vcm;

// correct over penetration. Move apart
float dSep = r + rB.r - sepMag;// amount of penetration
rB.pos += (dSep*m/Mtot)*N;// preserves position of center of mass
pos -= (dSep*rB.m/Mtot)*N;// no wrecking energy conservation!

return true;
}
*/


bool ball::hit(const vec2d& pt)
{
  vec2d sep, N;
  float dSep;
  if (is_inMe(pt, sep, N, dSep))
  {
    v = v.to_base(N);
    if (v.x < 0.0f) v.x *= -Cr;// reverse component along sep
    v = v.from_base(N);
    pos += N*dSep;
    return true;
  }

  return false;
}

/*
bool ball::hit( const vec2d& pt )
{
vec2d sep = pt - pos;
float sepMag = sep.mag();
if( sepMag > r ) return false;
sep /= sepMag;// now unit length and suitable as transform base

v = v.to_base(sep);
if( v.x > 0.0f ) v.x *= -Cr;// reverse component along sep
v = v.from_base(sep);

// making position correction w/o regard to v.x
pos -= sep*( r - sepMag );// If it's in, get it out!

return true;
}   */


void ball::setPosition(vec2d Pos)
{
  pos = Pos;
  img.setPosition(pos.x, pos.y);
}

bool ball::is_inMe(vec2d pt, vec2d& sep, vec2d& N, float& dSep)const// sep is relative to ball center
{
  sep = pt - pos;
  float sepMag = sep.mag();
  if (sepMag > r) return false;

  N = -1.0f*sep / sepMag;
  sep = pt;// new
  dSep = r - sepMag;
  return true;
}

// these replace lineInMe(), arcInMe()s
bool ball::is_inMe(const lineSeg& LS, vec2d& Pimp, vec2d& Nh, float& dSep)const// detailed collision detection
{
  float magL = LS.L.mag();// length of line
  vec2d T = LS.L / magL;// unit in direction of line
  vec2d N = T.get_LH_norm();// unit normal
  vec2d s = pos - LS.pos;// relative position
  float d = s.dot(T);// position along line

  float h = s.dot(N);// height above line.  s.dot(N) should work also
  if (h > r || h < -r) return false;// too far away

  if ((d > 0.0f) && (d < magL))// center is between ends
  {
    if (h > 0) Pimp = pos - r*N;// on Nside
    else Pimp = pos + r*N;// on back side
    Nh = LS.L.get_LH_norm();// unit normal
    dSep = -1.0f*Nh.dot(Pimp - LS.pos);// amount of penetration
    if (dSep < 0.0f) {
      Nh *= -1.0f; dSep *= -1.0f;
    }
    return true;
  }
  // test for end hits
  if (is_inMe(LS.pos, Pimp, Nh, dSep)) return true;
  return is_inMe(LS.pos + LS.L, Pimp, Nh, dSep);
}

bool ball::is_inMe(const arcSeg& AS, vec2d& Pimp, vec2d& Nh, float& dSep)const// code goes here. Impact point is written.
{
  // crude check for collision. Check distance between centers.
  float sepSq = (pos - AS.pos).dot(pos - AS.pos);
  //   float R = ( AS.s[0] ).mag();

  if (sepSq > (r + AS.R)*(r + AS.R)) return false;// too far outside
  if (sepSq < (AS.R - r)*(AS.R - r)) return false;// too far inside

  bool Hit = is_inMe(AS.pos + AS.s[0], Pimp, Nh, dSep);
  if (!Hit) Hit = is_inMe(AS.pos + AS.s[1], Pimp, Nh, dSep);
  // face test even if end is hit. mvHit can roll over end point across face.

  vec2d sep = pos - AS.pos;
  if (sep.cross(AS.s[0]) < 0.0f || sep.cross(AS.s[1]) > 0.0f) return Hit;// ends missed

  sep /= sep.mag();// now a unit vector
  if (sepSq > AS.R*AS.R) Pimp = pos - sep*r;// outside hit
  else Pimp = pos + sep*r;// inside hit

  Nh = Pimp - AS.pos; Nh /= Nh.mag();// unit normal
  dSep = AS.R - (Pimp - AS.pos).mag();// amount of penetration
  if (dSep < 0.0f) {
    Nh *= -1.0f; dSep *= -1.0f;
  }

  return true;
}
