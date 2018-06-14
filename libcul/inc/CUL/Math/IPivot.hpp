#pragma once
#include "CUL/Math/Vector3D.hpp"
#include "CUL/CUL.hpp"
#include "CUL/Math/IPivotObserver.hpp"
namespace CUL
{
    namespace Math
    {
        class CULLib_API IPivot
        {
        public:
            enum class CULLib_API PivotType: short
            {
                ABSOLUTE,
                NORMALIZED
            };

           IPivot();
            virtual ~IPivot();

            virtual void setPivot( const double px, const double py, const double pz, const PivotType type = PivotType::NORMALIZED ) = 0;
            virtual void setPivotX( const double val, const PivotType type = PivotType::NORMALIZED ) = 0;
            virtual void setPivotY( const double val, const PivotType type = PivotType::NORMALIZED ) = 0;
            virtual void setPivotZ( const double val, const PivotType type = PivotType::NORMALIZED ) = 0;

            virtual const Vector3Dd& getPivot( const PivotType type = PivotType::NORMALIZED )const = 0;

        protected:

        private:

#ifdef _MSC_VER
            __pragma( warning( push ) ) \
            __pragma( warning( disable:4251 ) )
#endif


#ifdef _MSC_VER
            __pragma( warning( pop ) )
#endif
        };
    }
}