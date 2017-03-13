#ifndef MVHIT_H_INCLUDED
#define MVHIT_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
//#include <string>
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
  static bool windowTopOpen;// allow passage above top of window

                            //    static float pressure;// temporary experimental use
  static float drag;
  //    static vec2d* pGravity;
  vec2d pos, v;// position, velocity
  vec2d siz;
  float m, Cr;// mass and coefficient of restitution
  bool is_free = true;// new functionality: mvHits as fixed obstacles to other mvHits

                      // funcs
  mvHit(std::istream& fin) {
    init(fin);
  }
  mvHit() {}
  virtual mvHit* clone() const = 0;
  virtual const char* myName() const = 0;
  //   const mvHit& operator=( const mvHit& rMH );

  virtual ~mvHit() {}
  virtual void init(std::istream& fin);

  virtual void update() = 0;
  void update(vec2d g);
  virtual void draw(sf::RenderTarget& rRW)const = 0;
  virtual void setPosition(vec2d Pos) = 0;

  virtual void respond(float dV, bool isFric);
  virtual bool hit(const vec2d& pt) = 0;
  // new funcs
  virtual bool hit(mvHit&) = 0;
  virtual bool hit(ball&) = 0;
  virtual bool hit(regPolygon&) = 0;

  virtual bool is_inMe(const lineSeg& LS, vec2d& Pimp, vec2d& Nh, float& dSep)const = 0;// detailed collision detection
  virtual bool is_inMe(const arcSeg& AS, vec2d& Pimp, vec2d& Nh, float& dSep)const = 0;// code goes here. Impact point is written.
  virtual bool is_inMe(vec2d pt, vec2d& sep, vec2d& N, float& dSep)const = 0;// writes qtys needed for collision response

                                                                             //    virtual float vShift() { return 0.0f; }

  virtual bool bounce(float Cf, vec2d N, bool isFric);// base: rigid bounce. N is line of action
  void handleImpact(mvHit& mh, vec2d sep, vec2d N, float dSep);

  virtual bool Float(vec2d Nsurf, vec2d Npen, float penAmt, float grav_N, float airDensity, float fluidDensity) = 0;
  virtual bool Float(vec2d Nsurf, float grav_N, float Density) = 0;
  virtual float project(vec2d vUnit)const = 0;
};

// utility
vec2d velCm(const mvHit& A, const mvHit& B);
float Ek(const mvHit& A, const mvHit& B);
float Ek_Cm(const mvHit& A, const mvHit& B);

#endif // MVHIT_H_INCLUDED
