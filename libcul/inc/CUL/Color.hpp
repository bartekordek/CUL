#pragma once
#include "CUL.hpp"
#include <cstdint>
using cfloat = const float;
namespace CUL
{
    enum class ColorE: short
    {
        BLACK = 0,
        WHITE,
        RED,
        GREEN,
        BLUE
    };

    struct CULLib_API ColorS
    {
        ColorS();
        virtual ~ColorS();
        ColorS( cfloat rr, cfloat gg, cfloat bb, cfloat aalpha );
        ColorS( const ColorE& color );
        ColorS& operator=( const ColorE colore );

        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
        float alpha = 1.0f;
    };
}