#ifndef REGPOLYGON_H_INCLUDED
#define REGPOLYGON_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include "vec2d.h"
//#include "ball.h"
#include "mvHit.h"

class regPolygon : public mvHit
{
    public:
    float r;// length of rays
    size_t nSides;// = ptVec.size()
    std::vector<vec2d> ptVec;// official
    std::vector<sf::Vertex> vtxVec;// visual

    regPolygon( std::ifstream& fin );
    regPolygon();
    virtual ~regPolygon() {}
    virtual void init( std::ifstream& fin );

    virtual void update();
    virtual void draw( sf::RenderWindow& rRW )const;
    virtual void setPosition( vec2d Pos );

    virtual void respond( float dV, bool isFric );
    virtual bool hit( const vec2d& pt );

    virtual bool hit( regPolygon& rpg );
    virtual bool hit( ball& rB );
    virtual bool hit( mvHit& );

    virtual bool is_inMe( const lineSeg& LS, vec2d& Pimp, vec2d& Nh, float& dSep )const;// detailed collision detection
    virtual bool is_inMe( const arcSeg& AS, vec2d& Pimp, vec2d& Nh, float& dSep )const;// code goes here. Impact point is written.
    virtual bool is_inMe( vec2d pt, vec2d& sep, vec2d& N, float& dSep )const;// writes qtys needed for collision response

    float project( vec2d vUnit )const;// max projection along vUnit

    void handleImpact( vec2d ptPos, ball& rB );
    bool inCircle( vec2d ctr, float R, vec2d& Pimp )const;
    float getRotation()const;
    void setRotation( float angle );
};

#endif // REGPOLYGON_H_INCLUDED
