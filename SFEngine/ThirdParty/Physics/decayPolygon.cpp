#include "decayPolygon.h"
#include "ball.h"

std::vector<mvHit*> *decayPolygon::p_mvHitVec = nullptr;

bool decayPolygon::hit(mvHit& mh)
{
  regPolygon* pRP = dynamic_cast<regPolygon*>(&mh);
  if (pRP) return hit(*pRP);
  return mh.hit(*static_cast<regPolygon*>(this));
}

/*
bool decayPolygon::hit( mvHit& mh )
{
bool Hit = mh.hit( *static_cast<regPolygon*>(this) );

if( Hit )
{
regPolygon* pRP = dynamic_cast<regPolygon*>(&mh);
if( pRP )
{
float pgEnergy = 0.5f*pRP->m*pRP->v.dot(pRP->v);
//std::cerr << "\n decayPolygon::impact(rpg). E = " << pgEnergy << " rpg.nSides = " << pRP->nSides;

if( pRP->nSides < 6 && pgEnergy > 3.0f*3.0f*3.0f )
absorb_reg(*pRP);
}
}

return Hit;
}
*/

bool decayPolygon::hit(ball& rB)
{
  float ballEnergy = 0.5f*rB.m*rB.v.dot(rB.v);
  bool Hit = regPolygon::hit(rB);

  if (Hit)// bust a triangle off
  {
    regPolygon* pRP = nullptr;
    if (ballEnergy > 2.0f*3.0f*3.0f && nSides > 7) pRP = split_reg(4);
    else if (ballEnergy > 2.0f*2.0f*2.0f && nSides > 5) pRP = split_reg(3);

    if (pRP) p_mvHitVec->push_back(pRP);
  }

  return Hit;
}

regPolygon* decayPolygon::split_reg(size_t n)// returns pointer to new 3 sided regPolygon and modifies *this to N-3
{
  if (n > 5) return nullptr;// that would be a decayPolygon instead
  if (nSides < n + 3) return nullptr;

  sf::Color vtxClr = vtxVec[0].color;

  // construct the N-3 poly
  nSides -= n;
  ptVec.clear();
  ptVec.reserve(nSides);
  vtxVec.clear();
  vtxVec.reserve(nSides + 1);
  vec2d pt0(r, 0.0f);// starter side
                     //    pt0 = pt0.Rotate(  );
  float dAngle = 6.283185f / nSides;
  for (size_t i = 0; i<nSides; ++i)
  {
    ptVec.push_back(pt0);
    vtxVec.push_back(sf::Vertex(sf::Vector2f(pos.x + pt0.x, pos.y + pt0.y), vtxClr));
    pt0 = pt0.Rotate(dAngle);
  }
  vtxVec.push_back(sf::Vertex(sf::Vector2f(pos.x + ptVec[0].x, pos.y + ptVec[0].y), vtxClr));

  //    return nullptr;

  // construct the new triangle
  regPolygon* pRP = new regPolygon;
  pRP->nSides = n;
  pRP->ptVec.reserve(pRP->nSides);
  pRP->vtxVec.reserve(pRP->nSides + 1);
  pRP->r = r;
  //    pRP->pos = pos - (r+pRP->r);// create just right of hit one
  v = v.mag()*v.get_LH_norm();
  pRP->v = -1.0f*v;
  pRP->pos = pos - v*((r + pRP->r) / v.mag());// create just right of hit one
  pRP->m = m;
  pRP->Cr = Cr;
  pt0.x = r; pt0.y = 0.0f;
  dAngle = 6.283185f / (float)n;
  //   vec2d pt0( r, 0.0f );// starter side
  //    pt0 = pt0.Rotate( iAngle );
  //   float dAngle = 6.283185f/nSides;
  for (size_t i = 0; i<pRP->nSides; ++i)
  {
    pRP->ptVec.push_back(pt0);
    //   //std::cerr << "\n pt0.mag() = " << pt0.mag();
    pRP->vtxVec.push_back(sf::Vertex(sf::Vector2f(pRP->pos.x + pt0.x, pRP->pos.y + pt0.y), vtxClr));
    pt0 = pt0.Rotate(dAngle);
  }
  pRP->vtxVec.push_back(sf::Vertex(sf::Vector2f(pRP->pos.x + pRP->ptVec[0].x, pRP->pos.y + pRP->ptVec[0].y), sf::Color::White));
  return pRP;
}


bool decayPolygon::hit(regPolygon& rpg)
{
  //    float pgEnergy = 0.5f*rpg.m*rpg.v.dot(rpg.v);
  float pgEnergy = 0.5f*(m*v.dot(v) + rpg.m*rpg.v.dot(rpg.v));
  bool Hit = regPolygon::hit(rpg);

  if (Hit) //std::cerr << "\n decayPolygon::impact(rpg). E = " << pgEnergy << " rpg.nSides = " << rpg.nSides;

  if (Hit && rpg.nSides < 6)
  {
    //        if( pgEnergy > 3.0f*3.0f*3.0f )
    if (pgEnergy > 2.0f*2.0f*3.0f)
    {
      absorb_reg(rpg);
    }
  }
  return Hit;
}

void decayPolygon::absorb_reg(regPolygon& rpg)
{
  //   mvHit* pMH = nullptr;
  std::vector<mvHit*>& rMHvec = *p_mvHitVec;
  std::vector<mvHit*>::iterator it = rMHvec.begin();
  for (std::vector<mvHit*>::iterator it = rMHvec.begin(); it != rMHvec.end(); ++it)
  {
    if (*it == &rpg)// found it!
    {
      rMHvec.erase(it);
      break;
    }
  }

  size_t dN = rpg.nSides;
  delete &rpg;// now we've done it!

  sf::Color vtxClr = vtxVec[0].color;

  // construct the nSides + dN sided poly
  nSides += dN;
  ptVec.clear();
  ptVec.reserve(nSides);
  vtxVec.clear();
  vtxVec.reserve(nSides + 1);
  vec2d pt0(r, 0.0f);// starter side
                     //    pt0 = pt0.Rotate(  );
  float dAngle = 6.283185f / nSides;
  for (size_t i = 0; i<nSides; ++i)
  {
    ptVec.push_back(pt0);
    vtxVec.push_back(sf::Vertex(sf::Vector2f(pos.x + pt0.x, pos.y + pt0.y), vtxClr));
    pt0 = pt0.Rotate(dAngle);
  }
  vtxVec.push_back(sf::Vertex(sf::Vector2f(pos.x + ptVec[0].x, pos.y + ptVec[0].y), vtxClr));
}
