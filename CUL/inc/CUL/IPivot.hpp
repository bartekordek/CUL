#pragma once

/*

*/

namespace CUL
{
    class IPivot
    {
    public:
        IPivot();
        virtual ~IPivot();

        virtual void setPivotNorm( const double px, const double py, const double pz ) = 0;
        virtual void setPivotNormX( const double val ) = 0;
        virtual void setPivotNormY( const double val ) = 0;
        virtual void setPivotNormZ( const double val ) = 0;

        virtual const double getNormPivotX()const = 0;
        virtual const double getNormPivotY()const = 0;
        virtual const double getNormPivotZ()const = 0;

        virtual void setPivotAbs( const double px, const double py, const double pz ) = 0;
        virtual void setPivotAbsX( const double val ) = 0;
        virtual void setPivotAbsY( const double val ) = 0;
        virtual void setPivotAbsZ( const double val ) = 0;

        virtual const double getAbsPivotX()const = 0;
        virtual const double getAbsPivotY()const = 0;
        virtual const double getAbsPivotZ()const = 0;

    protected:

    private:

    };
}