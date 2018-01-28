#pragma once
#include <CUL/CUL.hpp>
namespace CUL
{
    namespace Math
    {
        class CULLib_API IAngle
        {
        public:
            enum class Type: short
            {
                DEGREE,
                RADIAN
            };

            IAngle( void );
            virtual ~IAngle( void );

            virtual const double getValueD()const = 0;
            virtual const int getValueI()const = 0;
            virtual const Type getType()const = 0;

            virtual IAngle& operator+=( const double val ) = 0;
            virtual IAngle& operator+=( const int val ) = 0;

            virtual IAngle& operator-=( const double val ) = 0;
            virtual IAngle& operator-=( const int val ) = 0;


        protected:
        private:
        };
    }
}