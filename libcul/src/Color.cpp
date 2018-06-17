#include "CUL/Color.hpp"

using namespace CUL;

ColorS::ColorS()
{

}

ColorS::ColorS(
    cfloat rr,
    cfloat gg,
    cfloat bb,
    cfloat aalpha ):
    m_r( rr ),
    m_g( gg ),
    m_b( bb ),
    m_alpha( aalpha )
{

}

ColorS::~ColorS()
{

}

ColorS::ColorS( const ColorE& color )
{
    if( ColorE::BLUE == color )
    {
        this->m_b = 1.0f;
    }
    else if( ColorE::GREEN == color )
    {
        this->m_g = 1.0f;
    }
    else if( ColorE::RED == color )
    {
        this->m_r = 1.0f;
    }
    else if( ColorE::WHITE == color )
    {
        this->m_r = 1.0f;
        this->m_g = 1.0f;
        this->m_b = 1.0f;
    }
}

ColorS& ColorS::operator=( const ColorE color )
{
    if( ColorE::BLUE == color )
    {
        this->m_b = 1.0f;
    }
    else if( ColorE::GREEN == color )
    {
        this->m_g = 1.0f;
    }
    else if( ColorE::RED == color )
    {
        this->m_r = 1.0f;
    }
    else if( ColorE::WHITE == color )
    {
        this->m_r = 1.0f;
        this->m_g = 1.0f;
        this->m_b = 1.0f;
    }
    return *this;
}

cfloat ColorS::getRF()const
{
    return this->m_r;
}

cfloat ColorS::getGF()const
{
    return this->m_g;
}

cfloat ColorS::getBF()const
{
    return this->m_b;
}

cfloat ColorS::getAF()const
{
    return this->m_alpha;
}

cuint8_t ColorS::getRUI()const
{
    return this->m_r * 255.0f;
}

cuint8_t ColorS::getGUI()const
{
    return this->m_g * 255.0f;
}

cuint8_t ColorS::getBUI()const
{
    return this->m_b * 255.0f;
}

cuint8_t ColorS::getAUI()const
{
    return this->m_alpha * 255.0f;
}

void ColorS::setRF( cfloat r )
{
    this->m_r = r;
}

void ColorS::setGF( cfloat g )
{
    this->m_g = g;
}

void ColorS::setBF( cfloat b )
{
    this->m_b = b;
}

void ColorS::setAlphaF( cfloat alpha )
{
    this->m_alpha = alpha;
}

void ColorS::setRCU( cuint8_t r )
{
    this->m_r = r / 255.0f;
}

void ColorS::setGCU( cuint8_t g )
{
    this->m_g = g / 255.0f;
}

void ColorS::setBCU( cuint8_t b )
{
    this->m_b = b / 255.0f;
}

void ColorS::setAlphaCU( cuint8_t alpha )
{
    this->m_alpha = alpha / 255.0f;
}