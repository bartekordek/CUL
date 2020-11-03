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
using CDataType = unsigned char;

class CULLib_API ColorS final
{
public:
    ColorS();

    ColorS( const ColorE colorE );

    ColorS(
        cfloat rr,
        cfloat gg,
        cfloat bb,
        cfloat aalpha = 0.0f );

    ColorS& operator=( const ColorE color );


    float getRF() const;
    float getGF() const;
    float getBF() const;
    float getAF() const;

    CDataType getRUI() const;
    CDataType getGUI() const;
    CDataType getBUI() const;
    CDataType getAUI() const;

    void setRF( cfloat r );
    void setGF( cfloat g );
    void setBF( cfloat b );
    void setAlphaF( cfloat alpha );

    void setRCU( CDataType r );
    void setGCU( CDataType g );
    void setBCU( CDataType b );
    void setAlphaCU( CDataType alpha );

    ~ColorS();

protected:
private:
    void setFromEnum( const ColorE& color );
    void setFloat(
        cfloat red,
        cfloat green,
        cfloat blue,
        cfloat alpha );
    void setRed( cfloat val );
    void setGreen( cfloat val );
    void setBlue( cfloat val );
    void setAlpha( cfloat val );

    float m_redF = 0.0f;
    float m_greenF = 0.0f;
    float m_blueF = 0.0f;
    float m_alphaF = 0.0f;

    CDataType m_redUC = 0;
    CDataType m_greenUC = 0;
    CDataType m_blueUC = 0;
    CDataType m_alphaUC = 0;

};
NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )