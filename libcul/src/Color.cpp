#include "CUL/Graphics/Color.hpp"

using namespace CUL::Graphics;

ColorS::ColorS()
{
}

ColorS::ColorS( const ColorS& arg ) : m_colorValues(arg.m_colorValues)
{

}

ColorS::ColorS( ColorS&& arg ) : m_colorValues( arg.m_colorValues )
{
    arg.m_colorValues.r = 0.f;
    arg.m_colorValues.g = 0.f;
    arg.m_colorValues.b = 0.f;
}

ColorS& ColorS::operator=( const ColorS& arg )
{
    if( this != &arg )
    {
        this->m_colorValues = arg.m_colorValues;
    }
    return *this;
}

ColorS& ColorS::operator=( ColorS&& arg )
{
    if( this != &arg )
    {
        this->m_colorValues = arg.m_colorValues;
        arg.m_colorValues.r = 0.f;
        arg.m_colorValues.g = 0.f;
        arg.m_colorValues.b = 0.f;
    }
    return *this;
}

ColorS::ColorS( const ColorE colorE )
{
    setFromEnum( colorE );
}

ColorS::ColorS(
    float rr,
    float gg,
    float bb,
    float aalpha )
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
    switch (color)
    {
        case ColorE::BLUE:
            setFloat( 0.0f, 0.0f, 1.0f, 0.0f );
            break;
        case ColorE::GREEN:
            setFloat( 0.0f, 1.0f, 0.0f, 0.0f );
            break;
        case ColorE::RED:
            setFloat( 1.0f, 0.0f, 0.0f, 0.0f );
            break;
        case ColorE::WHITE:
            setFloat( 1.0f, 1.0f, 1.0f, 0.0f );
            break;
        case ColorE::YELLOW:
            setFloat( 1.0f, 1.0f, 0.0f, 0.0f );
            break;
        case ColorE::BLACK:
            setFloat( 0.0f, 0.0f, 0.0f, 1.0f );
            break;
    }
}

float ColorS::getRF() const
{
    return m_colorValues[0];
}

float ColorS::getGF() const
{
    return m_colorValues[1];
}

float ColorS::getBF() const
{
    return m_colorValues[2];
}

float ColorS::getAF() const
{
    return m_colorValues[3];
}

unsigned ColorS::getRUI() const
{
    return static_cast<unsigned>( m_colorValues[0] * 255.f );
}
unsigned ColorS::getGUI() const
{
    return static_cast<unsigned>( m_colorValues[1] * 255.f );
}
unsigned ColorS::getBUI() const
{
    return static_cast<unsigned>( m_colorValues[2] * 255.f );
}
unsigned ColorS::getAUI() const
{
    return static_cast<unsigned>( m_colorValues[3] * 255.f );
}

void ColorS::setRF( float v )
{
    setRed( v );
}

void ColorS::setGF( float v )
{
    setGreen( v );
}

void ColorS::setBF( float v )
{
    setBlue( v );
}

void ColorS::setAlphaF( float v )
{
    setAlpha( v );
}

void ColorS::setFloat( float red, float green, float blue, float alpha )
{
    setRed( red );
    setBlue( blue );
    setGreen( green );
    setAlpha( alpha );
}

void ColorS::setRed( float val )
{
    m_colorValues[0] = val;
}

void ColorS::setGreen( float val )
{
    m_colorValues[1] = val;
}

void ColorS::setBlue( float val )
{
    m_colorValues[2] = val;
}

void ColorS::setAlpha( float val )
{
    m_colorValues[3] = val;
}

const glm::vec4& ColorS::getVec4() const
{
    return m_colorValues;
}

ColorS::~ColorS()
{
}