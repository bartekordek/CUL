#pragma once

#include "CUL.hpp"
#include <cstdint>
#include <type_traits>

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

    template<typename Type>
    class CULLib_API ColorS
    {
    public:
        ColorS()
        {

        }
       
        virtual ~ColorS()
        {

        }
        
        ColorS(
            const Type rr,
            const Type gg,
            const Type bb,
            const Type aalpha ):
            m_r( rr ),
            m_g( gg ),
            m_b( bb ),
            m_alpha( aalpha )
        {

        }

        ColorS( const ColorE& color )
        {
            if( ColorE::BLUE == color )
            {
                this->b = this->m_max;
            }
            else if( ColorE::GREEN == color )
            {
                this->g = this->m_max;
            }
            else if( ColorE::RED == color )
            {
                this->r = this->m_max;
            }
            else if( ColorE::WHITE == color )
            {
                this->r = this->m_max;
                this->g = this->m_max;
                this->b = this->m_max;
            }
        }
        
        ColorS& operator=( const ColorE colore )
        {
            if( ColorE::BLUE == color )
            {
                this->b = this->m_max;
            }
            else if( ColorE::GREEN == color )
            {
                this->g = this->m_max;
            }
            else if( ColorE::RED == color )
            {
                this->r = this->m_max;
            }
            else if( ColorE::WHITE == color )
            {
                this->r = this->m_max;
                this->g = this->m_max;
                this->b = this->m_max;
            }
            return *this;
        }

        Type m_r = static_cast<Type>( 0 );
        Type m_g = static_cast<Type>( 0 );
        Type m_b = static_cast<Type>( 0 );
        Type m_alpha = static_cast<Type>( 0 );
        Type m_max = static_cast<Type>( 0 );

    protected:
    private:
        void checkTypeMax()
        {
            if( std::is_same<T, double> )
            {
                this->m_max = 1.0;
            }
            else if( std::is_same<T, float> )
            {
                this->m_max = 1.0f;
            }
            else if( std::is_same<T, int> || std::is_same<T, unsigned> )
            {
                this->m_max = 255;
            }
        }
    };

    using ColorSUI = ColorS<uint8_t>;
}