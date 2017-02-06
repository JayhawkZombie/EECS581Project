#ifndef MVHIT_H_INCLUDED
#define MVHIT_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include "vec2d.h"

class ball;// fwd declare
class regPolygon;

class lineSeg;
class arcSeg;

class mvHit
{
public:
  static float wdwW, wdwH;
  static float wdwCf;// friction coeff
  static vec2d* pGravity;
  vec2d pos, v;// position, velocity
  float m, Cr;// mass and coefficient of restitution
  bool is_free = true;// new functionality: mvHits as fixed obstacles to other mvHits

                      // funcs
  mvHit(std::istream& fin) {
    init(fin);
  }
  mvHit() {}
  virtual ~mvHit() {}
  virtual void init(std::istream& fin);

  virtual void update() = 0;
  virtual void draw(sf::RenderTarget& rRW)const = 0;
  virtual void setPosition(vec2d Pos) = 0;

  virtual void respond(float dV, bool isFric) = 0;
  virtual bool hit(const vec2d& pt) = 0;
  // new funcs
  virtual bool hit(mvHit&) = 0;
  virtual bool hit(ball&) = 0;
  virtual bool hit(regPolygon&) = 0;

  virtual bool is_inMe(const lineSeg& LS, vec2d& Pimp, vec2d& Nh, float& dSep)const = 0;// detailed collision detection
  virtual bool is_inMe(const arcSeg& AS, vec2d& Pimp, vec2d& Nh, float& dSep)const = 0;// code goes here. Impact point is written.
  virtual bool is_inMe(vec2d pt, vec2d& sep, vec2d& N, float& dSep)const = 0;// writes qtys needed for collision response

  bool bounce(float Cf, vec2d N, bool isFric);// rigid bounce. N is line of action
};

#endif // MVHIT_H_INCLUDED
