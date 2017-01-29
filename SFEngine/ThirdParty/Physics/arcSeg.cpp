#include "arcSeg.h"
#include "mvHit.h"

arcSeg::arcSeg( std::ifstream& fin ) { init(fin); }

void arcSeg::init( std::ifstream& fin )
{
 //   fin >> testEnd1 >> testEnd2;
    fin >> s[0].x >> s[0].y;
    fin >> s[1].x >> s[1].y;
    fin >> R;
 //   unsigned int rd,gn,bu;
 //   fin >> rd >> gn >> bu;
 //   sf::Color lnClr( rd, gn, bu );
    sf::Color lnClr( 255, 0, 0 );
    for( unsigned int i=0; i<20 ; ++i )Q[i].color = lnClr;

    vec2d arc = s[1] - s[0];
    arc *= 0.5f;
    float hfArcMag = arc.mag();
    pos = s[0] + arc + arc.get_LH_norm()*sqrtf( R*R - hfArcMag*hfArcMag );
    std::cout << "pos at: " << pos.x << ", " << pos.y << '\n';
 //   vec2d R0 = s[0] - pos;
    s[0] -= pos;
    s[1] -= pos;
 //   float angle = acosf( R0.dot(s[1]-pos)/(R*R) );
    float angle = acosf( s[0].dot(s[1])/(R*R) );
    std::cout << "angle = " << angle << '\n';
    float dA = angle/19.0f;
    for( unsigned int i=0; i<20 ; ++i )
    {
        vec2d vtxPos = pos + s[0].Rotate( -1.0f*(float)i*dA );
        Q[i].position.x = vtxPos.x;
        Q[i].position.y = vtxPos.y;
    }
}

void arcSeg::to_file( std::ofstream& fout )
{
    fout << "A\n";
    fout << ( testEnd1 ? '1' : '0' ) << ' ' << ( testEnd2 ? '1' : '0' ) << '\n';
    vec2d S = s[0] + pos;
    fout << S.x << ' ' << S.y;
    S = s[1] + pos;
    fout << ' ' << S.x << ' ' << S.y;
    fout << ' ' << R << '\n';
    unsigned int rd = Q[0].color.r, gn = Q[0].color.g, bu = Q[0].color.b;
    fout << rd << ' ' << gn << ' ' << bu;
}

arcSeg::~arcSeg(){}

void arcSeg::setPosition( vec2d Pos )
{
    vec2d dPos = Pos - pos;
    pos = Pos;
    for( size_t i=0; i<20; ++i )
    {
        Q[i].position.x += dPos.x;
        Q[i].position.y += dPos.y;
    }
}

bool arcSeg::is_onMe( const mvHit& mh, vec2d& Pimp, vec2d& N, float& pen )const
{
    if( mh.is_inMe( pos+s[0], Pimp, N, pen ) ) return true;
    if( mh.is_inMe( pos+s[1], Pimp, N, pen ) ) return true;
    if( mh.is_inMe( *static_cast<const arcSeg*>(this), Pimp, N, pen ) ) return true;
    return false;
}

/*
bool arcSeg::hit( mvHit& mh )
{
    vec2d Pimp, N;
    float dSep;

    if( is_onMe( mh, Pimp, N, dSep ) )
    {
        mh.bounce( Cf, N, friction_on );// velocity response
        mh.setPosition( mh.pos + N*dSep );// position change response
        return true;
    }

    return false;
}   */
