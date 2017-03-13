#ifndef SEGHIT_H_INCLUDED
#define SEGHIT_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include "vec2d.h"

class mvHit;

class segHit
{
public:
  vec2d pos;
  vec2d siz;
  bool testEnd1 = false, testEnd2 = false;

  float Cf = 0.5f;// friction coeff
  bool friction_on = false;
  bool is_hard = true;

  segHit() {}
  segHit(std::istream& fin);
  virtual ~segHit() {}
  virtual void init(std::istream& fin);
  virtual void to_file(std::ofstream& fout);
  virtual void setPosition(vec2d) = 0;
  virtual vec2d getPosition()const {
    return pos;
  }

  virtual void draw(sf::RenderTarget&)const = 0;
  virtual void update();// added so lineRotateSeg has in interface

  virtual bool hit(mvHit&);//
  virtual bool is_onMe(const mvHit& mh, vec2d& Pimp, vec2d& Nh, float& pen)const = 0;
  virtual vec2d getSurfaceNormal(const mvHit& mh)const = 0;
};

#endif // SEGHIT_H_INCLUDED
