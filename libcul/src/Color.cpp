#include "CUL/Graphics/Color.hpp"

using namespace CUL::Graphics;

ColorS::ColorS()
{
}

ColorS::ColorS(
    cfloat rr,
    cfloat gg,
    cfloat bb,
    cfloat aalpha )
{
    setFloat( rr, gg, bb, aalpha );
}

ColorS::ColorS( const ColorE& color )
{
    setFromEnum( color );
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
    return m_colorF[static_cast<size_t>( ColorComponent::RED )];
}

float ColorS::getGF() const
{
    return m_colorF[static_cast<size_t>( ColorComponent::GREEN )];
}

float ColorS::getBF() const
{
    return m_colorF[static_cast<size_t>( ColorComponent::BLUE )];
}

float ColorS::getAF() const
{
    return m_colorF[static_cast<size_t>( ColorComponent::ALPHA )];
}

uint8_t ColorS::getRUI() const
{
    return m_colorUC[static_cast<size_t>( ColorComponent::RED )];
}

uint8_t ColorS::getGUI() const
{
    return m_colorUC[static_cast<size_t>( ColorComponent::GREEN )];
}

uint8_t ColorS::getBUI() const
{
    return m_colorUC[static_cast<size_t>( ColorComponent::BLUE )];
}

uint8_t ColorS::getAUI() const
{
    return m_colorUC[static_cast<size_t>( ColorComponent::ALPHA )];
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

void ColorS::setRCU( cuint8_t r )
{
    m_colorF[static_cast<size_t>( ColorComponent::RED )] = r / 255.0f;
    m_colorUC[static_cast<size_t>( ColorComponent::RED )] = r;
}

void ColorS::setGCU( cuint8_t g )
{
    m_colorF[static_cast<size_t>( ColorComponent::GREEN )] = g / 255.0f;
    m_colorUC[static_cast<size_t>( ColorComponent::GREEN )] = g;
}

void ColorS::setBCU( cuint8_t b )
{
    m_colorF[static_cast<size_t>( ColorComponent::BLUE )] = b / 255.0f;
    m_colorUC[static_cast<size_t>( ColorComponent::BLUE )] = b;
}

void ColorS::setAlphaCU( cuint8_t a )
{
    m_colorF[static_cast<size_t>( ColorComponent::ALPHA )] = a / 255.0f;
    m_colorUC[static_cast<size_t>( ColorComponent::ALPHA )] = a;
}

void ColorS::setFloat( const float red, const float green, const float blue, const float alpha )
{
    setRed( red );
    setBlue( blue );
    setGreen( green );
    setAlpha( alpha );
}

void ColorS::setRed( const float val )
{
    m_colorF[static_cast<size_t>( ColorComponent::RED )] = val;
    m_colorUC[static_cast<size_t>( ColorComponent::RED )] = val * 255;
}

void ColorS::setGreen( const float val )
{
    m_colorF[static_cast<size_t>( ColorComponent::GREEN )] = val;
    m_colorUC[static_cast<size_t>( ColorComponent::GREEN )] = val * 255;
}

void ColorS::setBlue( const float val )
{
    m_colorF[static_cast<size_t>( ColorComponent::BLUE )] = val;
    m_colorUC[static_cast<size_t>( ColorComponent::BLUE )] = val * 255;
}

void ColorS::setAlpha( const float val )
{
    m_colorF[static_cast<size_t>( ColorComponent::ALPHA )] = val;
    m_colorUC[static_cast<size_t>( ColorComponent::ALPHA )] = val * 255;
}

ColorS::~ColorS()
{
}
