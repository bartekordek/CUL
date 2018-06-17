#pragma once

#include "Math.hpp"
#include "CUL/STD_type_traits.hpp"

namespace CUL
{
    namespace Math
    {
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4820 )
#endif
        template <typename Type>
        class Epsilon
        {
        public:
            Epsilon()
            {
                const bool isFloatPoint = std::is_same<Type, float>::value || std::is_same<Type, double>::value;
                if(isFloatPoint)
                {
                    this->epsilon = static_cast<Type>( 0.0000000001 );
                }
            }

            virtual ~Epsilon() = default;

            void setEpsilon( const double epislon )
            {
                this->epsilon = epislon;
            }

            const double getEpsilon()const
            {
                return this->epsilon;
            }
        protected:
            const bool equals( const Type val1, const Type val2 )const
            {
                const Type epsilonAsType = static_cast<Type>( epsilon );
                return Util::abs( val1 - val2 ) <= epsilonAsType;
            }
        private:
            Type epsilon = static_cast<Type>( 0 );
        };
#ifdef _MSC_VER
#pragma warning( pop )
#endif
    }
}