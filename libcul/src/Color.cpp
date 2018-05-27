#include "CUL/Color.hpp"

using namespace CUL;

ColorS::ColorS()
{

}

ColorS::ColorS( cfloat rr, cfloat gg, cfloat bb, cfloat aalpha ):
    r( rr ),
    g( gg ),
    b( bb ),
    alpha( aalpha )
{
}

ColorS::ColorS( const ColorE& color )
{
    if( ColorE::BLUE == color )
    {
        this->b = 1.0f;
    }
    else if( ColorE::GREEN == color )
    {
        this->g = 1.0f;
    }
    else if( ColorE::RED == color )
    {
        this->r = 1.0f;
    }
    else if( ColorE::WHITE == color )
    {
        this->r = 1.0f;
        this->g = 1.0f;
        this->b = 1.0f;
    }
}

ColorS::~ColorS()
{

}

ColorS& ColorS::operator=( const ColorE color )
{
    if( ColorE::BLUE == color )
    {
        this->b = 1.0f;
    }
    else if( ColorE::GREEN == color )
    {
        this->g = 1.0f;
    }
    else if( ColorE::RED == color )
    {
        this->r = 1.0f;
    }
    else if( ColorE::WHITE == color )
    {
        this->r = 1.0f;
        this->g = 1.0f;
        this->b = 1.0f;
    }
    return *this;
}