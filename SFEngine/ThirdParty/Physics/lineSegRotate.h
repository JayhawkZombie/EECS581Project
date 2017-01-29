#ifndef LINESEGROTATE_H_INCLUDED
#define LINESEGROTATE_H_INCLUDED

#include "lineSeg.h"

class lineSegRotate: public lineSeg
{
    public:
    float rotVel;

    lineSegRotate(): lineSeg(){}// don't use a default constructed lineSeg
    lineSegRotate( std::ifstream& fin );
    virtual void init( std::ifstream& fin );
    virtual ~lineSegRotate() {}
    virtual void to_file( std::ofstream& fout );

    virtual void update();
    virtual bool hit( mvHit& mh );
};

#endif // LINESEGROTATE_H_INCLUDED
