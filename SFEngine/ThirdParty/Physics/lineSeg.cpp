#include "lineSeg.h"
#include "mvHit.h"

lineSeg::lineSeg( std::ifstream& fin ): segHit() { init(fin); }

lineSeg::~lineSeg(){}

void lineSeg::init( std::ifstream& fin )
{
//    unsigned int r,g,b;
//    fin >> pos.x >> pos.y;
    segHit::init(fin);
    fin >> L.x >> L.y;
    L -= pos;// new
//    fin >> r >> g >> b;
//    vtx[0].color.r = r; vtx[0].color.g = g; vtx[0].color.b = b;
    vtx[0].color.r = 0; vtx[0].color.g = 255; vtx[0].color.b = 0;
//    std::cout << pos.x << ' ' << pos.y << ' ' << L.x << ' ' << L.y << ' ' << r << ' ' << g << ' ' << b << '\n';
    vtx[1].color = vtx[0].color;
    vtx[0].position.x = pos.x; vtx[0].position.y = pos.y;
    vtx[1].position.x = pos.x + L.x; vtx[1].position.y = pos.y + L.y;
    N = L.get_LH_norm();
}

void lineSeg::to_file( std::ofstream& fout )
{
    fout << "L\n";
    segHit::to_file(fout);
    fout << ' ' << pos.x + L.x << ' ' << pos.y + L.y << '\n';
    unsigned int rd = vtx[0].color.r, gn = vtx[0].color.g, bu = vtx[0].color.b;
    fout << rd << ' ' << gn << ' ' << bu;
}

void lineSeg::setPosition( vec2d Pos )
{
    pos = Pos;
    vtx[0].position.x = pos.x; vtx[0].position.y = pos.y;
    vtx[1].position.x = pos.x + L.x; vtx[1].position.y = pos.y + L.y;
}

bool lineSeg::is_onMe( const mvHit& mh, vec2d& Pimp, vec2d& Nh, float& pen )const
{
    if( mh.is_inMe( pos, Pimp, Nh, pen ) ) return true;
    if( mh.is_inMe( pos+L, Pimp, Nh, pen ) ) return true;
    if( mh.is_inMe( *static_cast<const lineSeg*>(this), Pimp, Nh, pen ) ) return true;
    return false;
}

/*
bool lineSeg::hit( mvHit& mh )
{
    vec2d Pimp, Nh;
    float dSep;

    if( is_onMe( mh, Pimp, Nh, dSep ) )
    {
        mh.bounce( Cf, Nh, friction_on );// velocity response
        mh.setPosition( mh.pos + Nh*dSep );// position change response
        return true;
    }

    return false;
}   */
