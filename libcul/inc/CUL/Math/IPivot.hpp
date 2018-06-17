#pragma once
#include "CUL/Math/Vector3D.hpp"
#include "CUL/CUL.hpp"
#include "CUL/Math/IPivotObserver.hpp"
namespace CUL
{
    namespace Math
    {
        using CDouble = const double;
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

            virtual void setPivot(
                CDouble px,
                CDouble py,
                CDouble pz,
                const PivotType type = PivotType::NORMALIZED ) = 0;
            virtual void setPivotX(
                CDouble val,
                const PivotType type = PivotType::NORMALIZED ) = 0;
            virtual void setPivotY(
                CDouble val,
                const PivotType type = PivotType::NORMALIZED ) = 0;
            virtual void setPivotZ(
                CDouble val,
                const PivotType type = PivotType::NORMALIZED ) = 0;

            virtual const Vector3Dd& getPivot(
                const PivotType type = PivotType::NORMALIZED )const = 0;

        protected:
        private:
        };
    }
}