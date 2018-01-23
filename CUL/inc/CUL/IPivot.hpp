#pragma once
#include "CUL/Math/Vector3D.hpp"
#include "CUL/CUL.hpp"
namespace CUL
{
    class CULLib_API IPivot
    {
    public:
        enum class PivotType : short
        {
            ABSOLUTE,
            NORMALIZED
        };

        IPivot();
        virtual ~IPivot();

        void setPivot( const PivotType type, const double px, const double py, const double pz );
        void setPivotX( const PivotType type, const double val );
        void setPivotY( const PivotType type, const double val );
        void setPivotZ( const PivotType type, const double val );

        const CUL::Math::Vector3Dd& getPivot( const PivotType type )const;

        void setRealSize( const CUL::Math::Vector3Dd& val );
        void setRealSize( const double width, const double height, const double depth );
        void setWidth( const double val );
        void setHeight( const double val );
        void setDepth( const double val );

    protected:

    private:
        void recalculatePivotAbs();
        void recalculatePivotNorm();

#ifdef _MSC_VER
    __pragma(warning( push )) \
    __pragma(warning( disable:4251 ))
#endif
        CUL::Math::Vector3Dd m_pNorm = CUL::Math::Vector3Dd( 0.5, 0.5, 0.5 );
        CUL::Math::Vector3Dd m_pAbs = CUL::Math::Vector3Dd( 0.5, 0.5, 0.5 );
        CUL::Math::Vector3Dd m_sizeAbs;
#ifdef _MSC_VER
        __pragma(warning( pop ))
#endif
    };
}