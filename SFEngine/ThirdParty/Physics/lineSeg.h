#ifndef LINESEG_H_INCLUDED
#define LINESEG_H_INCLUDED

#include "segHit.h"

class lineSeg: public segHit
{
    public:
    vec2d L, N;
    sf::Vertex vtx[2];

    // funcs
    lineSeg(){}// don't use a default constructed lineSeg
    lineSeg( std::ifstream& fin );
    virtual ~lineSeg();
    virtual void init( std::ifstream& fin );
    virtual void to_file( std::ofstream& fout );
    virtual void draw( sf::RenderWindow& rRW )const { rRW.draw(vtx, 2, sf::Lines); }
    virtual void setPosition( vec2d );

 //   virtual bool hit( mvHit& mh );
    bool is_onMe( const mvHit& mh, vec2d& Pimp, vec2d& Nh, float& pen )const;
};

//sf::Vector2f& operator=( sf::Vector2f sfPos, vec2d pos ) { sfPos.x += pos.x; sfPos.y += pos.y; return sfPos; }


#endif // LINESEG_H_INCLUDED
