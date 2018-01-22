#pragma once
#include "CUL/Math/Vector3D.hpp"
namespace CUL
{
    class IPivot
    {
    public:
        IPivot();
        virtual ~IPivot();

        void setPivotNorm( const double px, const double py, const double pz );
        void setPivotNormX( const double val );
        void setPivotNormY( const double val );
        void setPivotNormZ( const double val );

        const CUL::Math::Vector3Du& getPivotNormalized()const;

        virtual void setPivotAbs( const double px, const double py, const double pz ) = 0;
        virtual void setPivotAbsX( const double val ) = 0;
        virtual void setPivotAbsY( const double val ) = 0;
        virtual void setPivotAbsZ( const double val ) = 0;

        virtual const double getAbsPivotX()const = 0;
        virtual const double getAbsPivotY()const = 0;
        virtual const double getAbsPivotZ()const = 0;

    protected:
        virtual void calculateAbsPivot() = 0;

    private:
        CUL::Math::Vector3Du m_pNorm = CUL::Math::Vector3Dd( 0.5, 0.5, 0.5 );

    };
}