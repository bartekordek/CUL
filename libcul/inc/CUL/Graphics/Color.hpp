#pragma once

#include "CUL/CUL.hpp"
#include "CUL/STL_IMPORTS/STD_array.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

enum class ColorE: short
{
    BLACK = 0,
    WHITE,
    RED,
    GREEN,
    BLUE,
    YELLOW
};

enum class ColorComponent: short
{
    RED = 0,
    GREEN,
    BLUE,
    ALPHA
};

using cfloat = const float;
using cuint8_t = const uint8_t;
using CDataType = unsigned char;

class CULLib_API ColorS final
{
public:
    ColorS();

    ColorS( const ColorE colorE );

    ColorS(
        float rr,
        float gg,
        float bb,
        float aalpha = 0.0f );

    ColorS& operator=( const ColorE color );

    unsigned getRUI() const;
    unsigned getGUI() const;
    unsigned getBUI() const;
    unsigned getAUI() const;

    float getRF() const;
    float getGF() const;
    float getBF() const;
    float getAF() const;

    void setRF( float r );
    void setGF( float g );
    void setBF( float b );
    void setAlphaF( float alpha );

    std::array<float, 4>& getData();

    ~ColorS();

protected:
private:
    void setFromEnum( const ColorE& color );
    void setFloat(
        float red,
        float green,
        float blue,
        float alpha );
    void setRed( float val );
    void setGreen( float val );
    void setBlue( float val );
    void setAlpha( float val );

    std::array<float, 4> m_colorValues;

};
NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )