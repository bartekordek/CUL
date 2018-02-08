#include "CUL/Color.hpp"

using namespace CUL;

ColorS::ColorS()
{

}

ColorS::ColorS( uint8_t rr, uint8_t gg, uint8_t bb ):
    r( rr ),
    g( gg ),
    b( bb )
{
}

ColorS::ColorS( const ColorE& color )
{
    if( ColorE::BLUE == color )
    {
        this->b = 255;
    }
    else if( ColorE::GREEN == color )
    {
        this->g = 255;
    }
    else if( ColorE::RED == color )
    {
        this->r = 255;
    }
    else if( ColorE::WHITE == color )
    {
        this->r = 255;
        this->g = 255;
        this->b = 255;
    }
}

ColorS::~ColorS()
{

}

ColorS& ColorS::operator=( const ColorE color )
{
    if( ColorE::BLUE == color )
    {
        this->b = 255;
    }
    else if( ColorE::GREEN == color )
    {
        this->g = 255;
    }
    else if( ColorE::RED == color )
    {
        this->r = 255;
    }
    else if( ColorE::WHITE == color )
    {
        this->r = 255;
        this->g = 255;
        this->b = 255;
    }
    return *this;
}