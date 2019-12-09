#include "CUL/Graphics/Color.hpp"

using namespace CUL::Graphics;

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
        m_b = 1.0f;
    }
    else if( ColorE::GREEN == color )
    {
        m_g = 1.0f;
    }
    else if( ColorE::RED == color )
    {
        m_r = 1.0f;
    }
    else if( ColorE::WHITE == color )
    {
        m_r = 1.0f;
        m_g = 1.0f;
        m_b = 1.0f;
    }
}

ColorS& ColorS::operator=( const ColorE color )
{
    if( ColorE::BLUE == color )
    {
        m_b = 1.0f;
    }
    else if( ColorE::GREEN == color )
    {
        m_g = 1.0f;
    }
    else if( ColorE::RED == color )
    {
        m_r = 1.0f;
    }
    else if( ColorE::WHITE == color )
    {
        m_r = 1.0f;
        m_g = 1.0f;
        m_b = 1.0f;
    }
    return *this;
}

cfloat ColorS::getRF()const
{
    return m_r;
}

cfloat ColorS::getGF()const
{
    return m_g;
}

cfloat ColorS::getBF()const
{
    return m_b;
}

cfloat ColorS::getAF()const
{
    return m_alpha;
}

cuint8_t ColorS::getRUI()const
{
    return static_cast<cuint8_t>( m_r * 255.0f );
}

cuint8_t ColorS::getGUI()const
{
    return static_cast<cuint8_t>( m_g * 255.0f );
}

cuint8_t ColorS::getBUI()const
{
    return static_cast<cuint8_t>( m_b * 255.0f );
}

cuint8_t ColorS::getAUI()const
{
    return static_cast<cuint8_t>( m_alpha * 255.0f );
}

void ColorS::setRF( cfloat r )
{
    m_r = r;
}

void ColorS::setGF( cfloat g )
{
    m_g = g;
}

void ColorS::setBF( cfloat b )
{
    m_b = b;
}

void ColorS::setAlphaF( cfloat alpha )
{
    m_alpha = alpha;
}

void ColorS::setRCU( cuint8_t r )
{
    m_r = r / 255.0f;
}

void ColorS::setGCU( cuint8_t g )
{
    m_g = g / 255.0f;
}

void ColorS::setBCU( cuint8_t b )
{
    m_b = b / 255.0f;
}

void ColorS::setAlphaCU( cuint8_t alpha )
{
    m_alpha = alpha / 255.0f;
}