#pragma once

#include "CUL/CUL.hpp"

#include "CUL/STL_IMPORTS/STD_array.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"

#include "CUL/IMPORT_GLM.hpp"

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

class ColorS final
{
public:
    CULLib_API ColorS();
    CULLib_API ColorS( const ColorS& arg );
    CULLib_API ColorS( ColorS&& arg );
    CULLib_API ColorS& operator=(const ColorS& arg);
    CULLib_API ColorS& operator=(ColorS&& arg);

    CULLib_API ColorS( const ColorE colorE );

    CULLib_API ColorS(
        float rr,
        float gg,
        float bb,
        float aalpha = 0.0f );

    CULLib_API ColorS& operator=( const ColorE color );

    CULLib_API unsigned getRUI() const;
    CULLib_API unsigned getGUI() const;
    CULLib_API unsigned getBUI() const;
    CULLib_API unsigned getAUI() const;

    CULLib_API float getRF() const;
    CULLib_API float getGF() const;
    CULLib_API float getBF() const;
    CULLib_API float getAF() const;

    CULLib_API void setRF( float r );
    CULLib_API void setGF( float g );
    CULLib_API void setBF( float b );
    CULLib_API void setAlphaF( float alpha );

    CULLib_API const glm::vec4& getVec4() const;

    CULLib_API ~ColorS();

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

    glm::vec4 m_colorValues = { 0.f, 0.f, 0.f, 0.f };

};
NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )