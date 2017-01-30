#ifndef LINESEGROTATE_H_INCLUDED
#define LINESEGROTATE_H_INCLUDED
#include <sstream>
#include "lineSeg.h"

class lineSegRotate: public lineSeg
{
    public:
    float rotVel;

    lineSegRotate(): lineSeg(){}// don't use a default constructed lineSeg
    lineSegRotate( std::stringstream& fin );
    virtual void init( std::stringstream& fin );
    virtual ~lineSegRotate() {}
    virtual void to_file( std::ofstream& fout );

    virtual void update();
    virtual bool hit( mvHit& mh );
};

#endif // LINESEGROTATE_H_INCLUDED
