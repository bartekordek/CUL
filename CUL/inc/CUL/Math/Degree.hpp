#pragma once
#include "CUL/Math/IAngle.hpp"
namespace CUL
{
    namespace Math
    {
        class CULLib_API Degree: public IAngle
        {
        public:
            Degree();
            virtual ~Degree();

            const double getValueD()const override;
            const int getValueI()const override;


            Degree& operator=( const double val );
            Degree& operator=( const int val );

        protected:
        private:
            double m_val = 0.0;
        };
    }
}