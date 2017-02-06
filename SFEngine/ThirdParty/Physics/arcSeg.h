#ifndef ARCSEG_H_INCLUDED
#define ARCSEG_H_INCLUDED

#include "segHit.h"

class arcSeg : public segHit
{
public:
  vec2d s[2];// use inherited pos as Ctr
  float R;
  sf::Vertex Q[20];// draw arc as a lineStrip

  arcSeg() {}// don't use a default constructed lineSeg
  arcSeg(std::istream& fin);
  virtual void init(std::istream& fin);
  virtual void to_file(std::ofstream& fout);
  virtual ~arcSeg();
  virtual void setPosition(vec2d Pos);

  virtual void draw(sf::RenderTarget& rRW)const override {
    rRW.draw(Q, 20, sf::LinesStrip);
  }
  //   virtual bool hit( mvHit& );
  bool is_onMe(const mvHit& mh, vec2d& Pimp, vec2d& N, float& pen)const;
};


#endif // ARCSEG_H_INCLUDED
