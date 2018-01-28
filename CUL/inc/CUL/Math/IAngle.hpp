#pragma once
#include <CUL/CUL.hpp>
namespace CUL
{
    namespace Math
    {
        class CULLib_API IAngle
        {
        public:
            IAngle( void );
            virtual ~IAngle( void );

            virtual const double getValueD()const = 0;
            virtual const int getValueI()const = 0;

        protected:
        private:
        };
    }
}