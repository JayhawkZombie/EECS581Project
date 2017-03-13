#include "lineSeg.h"
#include "mvHit.h"

lineSeg::lineSeg(std::istream& fin) : segHit() {
  init(fin);
}

lineSeg::~lineSeg() {}

void lineSeg::init(std::istream& fin)
{
  //    unsigned int r,g,b;
  //    fin >> pos.x >> pos.y;
  segHit::init(fin);
  fin >> L.x >> L.y;
  siz = { std::abs(L.x - pos.x), std::abs(L.y - pos.y) };
  L -= pos;// new
           //    fin >> r >> g >> b;
           //    vtx[0].color.r = r; vtx[0].color.g = g; vtx[0].color.b = b;
  vtx[0].color.r = 0; vtx[0].color.g = 255; vtx[0].color.b = 0;
  //    std::cout << pos.x << ' ' << pos.y << ' ' << L.x << ' ' << L.y << ' ' << r << ' ' << g << ' ' << b << '\n';
  vtx[1].color = vtx[0].color;
  vtx[0].position.x = pos.x; vtx[0].position.y = pos.y;
  vtx[1].position.x = pos.x + L.x; vtx[1].position.y = pos.y + L.y;
  N = L.get_LH_norm();
}

void lineSeg::to_file(std::ofstream& fout)
{
  fout << "L\n";
  segHit::to_file(fout);
  fout << ' ' << pos.x + L.x << ' ' << pos.y + L.y << '\n';
  unsigned int rd = vtx[0].color.r, gn = vtx[0].color.g, bu = vtx[0].color.b;
  fout << rd << ' ' << gn << ' ' << bu;
}

lineSeg::lineSeg(float x1, float y1, float x2, float y2, sf::Color clr) {
  init(x1, y1, x2, y2, clr);
}

void lineSeg::init(float x1, float y1, float x2, float y2, sf::Color clr)
{
  pos.x = x1; pos.y = y1;
  L.x = x2 - x1;  L.y = y2 - y1;
  vtx[0].color = vtx[1].color = clr;
  vtx[0].position.x = x1; vtx[0].position.y = y1;
  vtx[1].position.x = x2; vtx[1].position.y = y2;
  N = L.get_LH_norm();
}

void lineSeg::init(vec2d pt1, vec2d pt2, sf::Color clr)
{
  pos = pt1;
  L = pt2 - pt1;
  vtx[0].color = vtx[1].color = clr;
  vtx[0].position.x = pt1.x; vtx[0].position.y = pt1.y;
  vtx[1].position.x = pt2.x; vtx[1].position.y = pt2.y;
  N = L.get_LH_norm();
}

void lineSeg::setPosition(vec2d Pos)
{
  pos = Pos;
  vtx[0].position.x = pos.x; vtx[0].position.y = pos.y;
  vtx[1].position.x = pos.x + L.x; vtx[1].position.y = pos.y + L.y;
}

/*
// ball works perfect. undercut flaw returns for poly
bool lineSeg::is_onMe( const mvHit& mh, vec2d& Pimp, vec2d& Nh, float& pen )const
{
bool Hit = mh.is_inMe( pos, Pimp, Nh, pen );
if( !Hit ) Hit = mh.is_inMe( pos+L, Pimp, Nh, pen );
// face test even if end is hit. mvHit can roll over end point across face.
if( mh.is_inMe( *static_cast<const lineSeg*>(this), Pimp, Nh, pen ) ) Hit = true;

return Hit;
}   */

/*
// poly works perfect. ball can roll off end across face so, "pothole" issue exists for ball
bool lineSeg::is_onMe( const mvHit& mh, vec2d& Pimp, vec2d& Nh, float& pen )const
{
if( mh.is_inMe( pos, Pimp, Nh, pen ) ) return true;
if( mh.is_inMe( pos+L, Pimp, Nh, pen ) ) return true;
if( mh.is_inMe( *static_cast<const lineSeg*>(this), Pimp, Nh, pen ) ) return true;
return false;
}   */

bool lineSeg::is_onMe(const mvHit& mh, vec2d& Pimp, vec2d& Nh, float& pen)const
{
  return mh.is_inMe(*static_cast<const lineSeg*>(this), Pimp, Nh, pen);
}

/*
bool lineSeg::hit( mvHit& mh )
{
vec2d Pimp, Nh;
float dSep;

if( is_onMe( mh, Pimp, Nh, dSep ) )
{
mh.bounce( Cf, Nh, friction_on );// velocity response
mh.setPosition( mh.pos + Nh*dSep );// position change response
return true;
}

return false;
}   */
