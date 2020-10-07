#include "CUL/Graphics/Color.hpp"

using namespace CUL::Graphics;

ColorS::ColorS()
{
}

ColorS::ColorS( const ColorE colorE )
{
    setFromEnum( colorE );
}

ColorS::ColorS(
    cfloat rr,
    cfloat gg,
    cfloat bb,
    cfloat aalpha )
{
    setFloat( rr, gg, bb, aalpha );
}

ColorS& ColorS::operator=( const ColorE color )
{
    setFromEnum( color );
    return *this;
}

void ColorS::setFromEnum( const ColorE& color )
{
    if( ColorE::BLUE == color )
    {
        setFloat( 0.0f, 0.0f, 1.0f, 0.0f );
    }
    else if( ColorE::GREEN == color )
    {
        setFloat( 0.0f, 1.0f, 0.0f, 0.0f );
    }
    else if( ColorE::RED == color )
    {
        setFloat( 1.0f, 0.0f, 0.0f, 0.0f );
    }
    else if( ColorE::WHITE == color )
    {
        setFloat( 1.0f, 1.0f, 1.0f, 0.0f );
    }
}

float ColorS::getRF() const
{
    return m_redF;
}

float ColorS::getGF() const
{
    return m_greenF;
}

float ColorS::getBF() const
{
    return m_blueF;
}

float ColorS::getAF() const
{
    return m_alphaF;
}

uint8_t ColorS::getRUI() const
{
    return m_redUC;
}

uint8_t ColorS::getGUI() const
{
    return m_greenUC;
}

uint8_t ColorS::getBUI() const
{
    return m_blueUC;
}

uint8_t ColorS::getAUI() const
{
    return m_alphaUC;
}

void ColorS::setRF( cfloat v )
{
    setRed( v );
}

void ColorS::setGF( cfloat v )
{
    setGreen( v );
}

void ColorS::setBF( cfloat v )
{
    setBlue( v );
}

void ColorS::setAlphaF( cfloat v )
{
    setAlpha( v );
}

void ColorS::setRCU( CDataType r )
{
    m_redF = static_cast<float>( r ) / 255.0f;
    m_redUC = static_cast<CDataType>( r );
}

void ColorS::setGCU( CDataType g )
{
    m_greenF = static_cast<float>(g) / 255.0f;
    m_greenUC = static_cast<CDataType>(g);
}

void ColorS::setBCU( CDataType b )
{
    m_blueF = static_cast<float>(b) / 255.0f;
    m_blueUC = static_cast<CDataType>(b);
}

void ColorS::setAlphaCU( CDataType a )
{
    m_alphaF = static_cast<float>(a) / 255.0f;
    m_alphaUC = static_cast<CDataType>(a);
}

void ColorS::setFloat( cfloat red, cfloat green, cfloat blue, cfloat alpha )
{
    setRed( red );
    setBlue( blue );
    setGreen( green );
    setAlpha( alpha );
}

void ColorS::setRed( cfloat val )
{
    m_redF = val;
    m_redUC = static_cast<CDataType>( val * 255 );
}

void ColorS::setGreen( cfloat val )
{
    m_greenF = val;
    m_greenUC = static_cast<CDataType>(val * 255);
}

void ColorS::setBlue( cfloat val )
{
    m_blueF = val;
    m_blueUC = static_cast<CDataType>(val * 255);
}

void ColorS::setAlpha( cfloat val )
{
    m_alphaF = val;
    m_alphaUC = static_cast<CDataType>(val * 255);
}

ColorS::~ColorS()
{
}