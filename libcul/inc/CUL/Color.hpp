#pragma once
#include "CUL.hpp"
#include <cstdint>
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

        ColorS( uint8_t rr, uint8_t gg, uint8_t bb );

        ColorS( const ColorE& color );

        ColorS& operator=( const ColorE colore );

        uint8_t r = 0;
        uint8_t g = 0;
        uint8_t b = 0;
        uint8_t alpha = 255;
    };
}