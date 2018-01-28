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
            Degree( const double angle );
            Degree( const int angle );
            Degree( const IAngle& degree );
            virtual ~Degree();

            const double getValueD()const override;
            const int getValueI()const override;

            const IAngle::Type getType()const override;

            Degree& operator=( const double val );
            Degree& operator=( const int val );

            IAngle& operator+=( const double val ) override;
            IAngle& operator+=( const int val ) override;

        protected:
        private:
            double m_val = 0.0;
        };
    }
}