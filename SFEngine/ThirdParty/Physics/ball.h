#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include "vec2d.h"
//#include "mvHit.h"
#include "regPolygon.h"

class ball : public mvHit
{
    public:
    float r;// radius
    sf::CircleShape img;// image

    ball( std::ifstream& fin );
    ball();
    virtual ~ball() {}
    virtual void init( std::ifstream& fin );

    virtual void update();
    virtual void draw( sf::RenderWindow& rRW )const;
    virtual void setPosition( vec2d Pos );
    virtual void respond( float dV, bool isFric );
    virtual bool hit( const vec2d& pt );
    virtual bool hit( ball& rB );
    virtual bool hit( regPolygon& py );// { return py.hit( *static_cast<ball*>(this) ); }
    virtual bool hit( mvHit& mh );// { return mh.hit( *static_cast<ball*>(this) ); }

    virtual bool is_inMe( const lineSeg& LS, vec2d& Pimp, vec2d& Nh, float& dSep )const;// detailed collision detection
    virtual bool is_inMe( const arcSeg& AS, vec2d& Pimp, vec2d& Nh, float& dSep )const;// code goes here. Impact point is written.
    virtual bool is_inMe( vec2d pt, vec2d& sep, vec2d& N, float& dSep )const;// writes qtys needed for collision response
};


#endif // BALL_H_INCLUDED
