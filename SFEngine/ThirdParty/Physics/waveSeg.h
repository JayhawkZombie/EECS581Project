#ifndef WAVESEG_H_INCLUDED
#define WAVESEG_H_INCLUDED

#include<vector>
#include "lineSeg.h"

class waveSeg : public lineSeg
{
public:
  static float PIx2;

  // traveling wave - right
  float Amp_wvRt, K_wvRt;// K_wvRt = 2*PI/wavelength
  float rotFreqRt;// Note wave speed = v = rotFreq/K_wvRt = rotFreq*wavelength/2pi
                  //   float tm = 0.0f;// += 1.0f each frame per our x += v time scale?
  float phsRt = 0.0f;
  // traveling wave - left
  float Amp_wvLt, K_wvLt;// K_wvRt = 2*PI/wavelength
  float rotFreqLt;// but make > 0 too. See '+' vs '-' sign use in y(x) funcs
  float phsLt = 0.0f;

  float magL;// cached length of lineSeg (since lineSeg can't be bothered)
             //    bool viewLt = true, viewRt = true, viewSeg = true;
  bool viewLt = false, viewRt = false, viewSeg = false;

  // zones above and below too
  float grav_N;
  float Elev, airDensity;
  float Depth, fluidDensity;

  // draw the waves
  int Npts_wv = 100;
  std::vector<sf::Vertex> wvVec;
  std::vector<sf::Vertex> wvVecLt;
  std::vector<sf::Vertex> wvVecRt;

  // funcs
  waveSeg() {}// defs here
  virtual ~waveSeg() {}
  // defs in cpp
  waveSeg(std::istream& is);
  virtual void init(std::istream& is);
  virtual void to_file(std::ofstream& fout);
  virtual void draw(sf::RenderTarget&)const;
  virtual void update();
  virtual bool hit(mvHit&);

  // back to defs here
  virtual vec2d getSurfaceNormal(const mvHit& mh)const {
    return L.get_LH_norm();
  }// BASE VERSION. Modify

   //    float y_wvRt( float x ){ return Amp_wvRt*sinf( K_wvRt*x - rotFreqRt*tm ); }// rotFreq > 0  <--> wave traveling to right
   //    float y_wvLt( float x ){ return Amp_wvLt*sinf( K_wvLt*x + rotFreqLt*tm ); }// rotFreq > 0  <--> wave traveling to right
  float y_wvRt(float x) {
    return Amp_wvRt*sinf(K_wvRt*x - phsRt);
  }// rotFreq > 0  <--> wave traveling to right
  float y_wvLt(float x) {
    return Amp_wvLt*sinf(K_wvLt*x + phsLt);
  }// rotFreq > 0  <--> wave traveling to right
  float y_res(float x) {
    return y_wvRt(x) + y_wvLt(x);
  }

  //   float y_vel( float x ) { return Amp_wvLt*rotFreqLt*cosf( K_wvLt*x + rotFreqLt*tm ) - Amp_wvRt*rotFreqRt*cosf( K_wvRt*x - rotFreqRt*tm ); }// partial deriv wrt t
  //   float wv_slope( float x ) { return Amp_wvLt*K_wvLt*cosf( K_wvLt*x + rotFreqLt*tm ) + Amp_wvRt*K_wvRt*cosf( K_wvRt*x - rotFreqRt*tm ); }// partial deriv wrt x
  float y_vel(float x) {
    return Amp_wvLt*rotFreqLt*cosf(K_wvLt*x + phsLt) - Amp_wvRt*rotFreqRt*cosf(K_wvRt*x - phsRt);
  }// partial deriv wrt t
  float wv_slope(float x) {
    return Amp_wvLt*K_wvLt*cosf(K_wvLt*x + phsLt) + Amp_wvRt*K_wvRt*cosf(K_wvRt*x - phsRt);
  }// partial deriv wrt x
};

#endif // WAVESEG_H_INCLUDED
