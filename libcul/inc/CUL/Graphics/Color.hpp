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
    BLUE
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

class CULLib_API ColorS final
{
public:
    ColorS();

    ColorS(
        cfloat rr,
        cfloat gg,
        cfloat bb,
        cfloat aalpha = 0.0f );

    ColorS( const ColorE& color );

    ColorS& operator=( const ColorE color );

    float getRF() const;
    float getGF() const;
    float getBF() const;
    float getAF() const;

    uint8_t getRUI() const;
    uint8_t getGUI() const;
    uint8_t getBUI() const;
    uint8_t getAUI() const;

    void setRF( cfloat r );
    void setGF( cfloat g );
    void setBF( cfloat b );
    void setAlphaF( cfloat alpha );

    void setRCU( cuint8_t r );
    void setGCU( cuint8_t g );
    void setBCU( cuint8_t b );
    void setAlphaCU( cuint8_t alpha );

    ~ColorS();

protected:
private:
    void setFromEnum( const ColorE& color );
    void setFloat( const float red, const float green, const float blue, const float alpha );
    void setRed( const float val );
    void setGreen( const float val );
    void setBlue( const float val );
    void setAlpha( const float val );

    std::array<float, 4 > m_colorF = { 0.0f, 0.0f, 0.0f, 0.0f };
    std::array<unsigned char, 4 > m_colorUC = { 0, 0, 0, 0 };

};
NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )
