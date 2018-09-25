#pragma once

#include "CUL.hpp"
#include "CUL/STD_cstdint.hpp"

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

    using cfloat = const float;
    using cuint8_t = const uint8_t;

    class CULLib_API ColorS
    {
    public:
        ColorS();
      
        ColorS(
            cfloat rr,
            cfloat gg,
            cfloat bb,
            cfloat aalpha );

        ColorS( const ColorE& color );

        virtual ~ColorS();
        
        ColorS& operator=( const ColorE color );

        cfloat getRF()const;
        cfloat getGF()const;
        cfloat getBF()const;
        cfloat getAF()const;

        cuint8_t getRUI()const;
        cuint8_t getGUI()const;
        cuint8_t getBUI()const;
        cuint8_t getAUI()const;

        void setRF( cfloat r );
        void setGF( cfloat g );
        void setBF( cfloat b );
        void setAlphaF( cfloat alpha );

        void setRCU( cuint8_t r );
        void setGCU( cuint8_t g );
        void setBCU( cuint8_t b );
        void setAlphaCU( cuint8_t alpha );


    protected:
    private:
        float m_r = 0.0f;
        float m_g = 0.0f;
        float m_b = 0.0f;
        float m_alpha = 0.0f;

    };
}