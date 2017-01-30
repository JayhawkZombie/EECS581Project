#ifndef DECAYPOLYGON_H_INCLUDED
#define DECAYPOLYGON_H_INCLUDED
#include <sstream>
#include<vector>
#include "regPolygon.h"

class decayPolygon : public regPolygon
{
public:
  static std::vector<mvHit*> *p_mvHitVec;

  decayPolygon(std::stringstream& fin) : regPolygon(fin) {}
  decayPolygon() {}
  virtual ~decayPolygon() {}
  //    virtual void init( std::stringstream& fin );
  virtual bool hit(ball& rB);// split
  virtual bool hit(mvHit&);
  virtual bool hit(regPolygon& rpg);// absorb
                                    //   virtual void impact( regPolygon& rpg );// absorb

  regPolygon* split_reg(size_t n);// returns pointer to new n sided regPolygon and modifies *this to N-n
  void absorb_reg(regPolygon& rpg);
  // all other inherited functions should do
};

#endif // DECAYPOLYGON_H_INCLUDED
