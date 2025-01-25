#pragma once

#include "CUL/Math/Utils.hpp"
#include "CUL/STL_IMPORTS/STD_cmath.hpp"

NAMESPACE_BEGIN(CUL)
NAMESPACE_BEGIN(MATH)

template<class T>
class SphericalCoord final
{
public:
    static T Zero;
    static T TwoPi;

    SphericalCoord() = default;
    SphericalCoord( const SphericalCoord& arg ) : m_theta( arg.m_theta ), m_phi( arg.m_phi ), m_r( arg.m_r )
    {
    }

    SphericalCoord( SphericalCoord&& arg ) : m_theta( arg.m_theta ), m_phi( arg.m_phi ), m_r( arg.m_r )
    {
        arg.m_theta = static_cast<T>( 0 );
        arg.m_phi = static_cast<T>( 0 );
        arg.m_r = static_cast<T>( 0 );
    }

    SphericalCoord& operator=( const SphericalCoord& arg )
    {
        if( this != &arg )
        {
            m_theta = arg.m_theta;
            m_phi = arg.m_phi;
            m_r = arg.m_r;
        }

        return *this;
    }

    SphericalCoord& operator=( SphericalCoord&& arg )
    {
        if( this != &arg )
        {
            m_theta = arg.m_theta;
            m_phi = arg.m_phi;
            m_r = arg.m_r;

            arg.m_theta = static_cast<T>( 0 );
            arg.m_phi = static_cast<T>( 0 );
            arg.m_r = static_cast<T>( 0 );
        }

        return *this;
    }

    void incrementTheta( const T inTheta )
    {
        setTheta( m_theta + inTheta );
    }

    void setTheta( const T inTheta )
    {
        static const T maxValue{ TwoPi };
        if( inTheta >= maxValue )
        {
            m_theta = Utils::floatModulo( inTheta, maxValue );
        }
        else if( inTheta <= -maxValue )
        {
            m_theta = Utils::floatModulo( inTheta, maxValue );
        }
        else
        {
            m_theta = inTheta;
        }
    }

    void incrementPhi( const T inPhi )
    {
        setPhi( m_phi + inPhi );
    }

    void setPhi( const T inPhi )
    {
        static const T maxValue{ Constants<T>::Pi };
        if( m_phi >= maxValue )
        {
            m_phi = Utils::floatModulo( inPhi, maxValue );
        }
        else if( m_phi <= -maxValue )
        {
            m_phi = Utils::floatModulo( inPhi, maxValue );
        }
        else
        {
            m_phi = inPhi;
        }
    }

    void incrementR( const T inR )
    {
        setR( m_r + inR );
    }

    void setR( const T inR )
    {
        m_r = inR;
    }

    T getTheta() const
    {
        return m_theta;
    }

    T getPhi() const
    {
        return m_phi;
    }

    T getR() const
    {
        return m_r;
    }

    void toCarthezian( T& inOutX, T& inOutY, T& inOutZ )
    {
        inOutX = m_r * std::sin( m_theta ) * std::cos( m_phi );
        inOutY = m_r * std::sin( m_theta ) * std::sin( m_phi );
        inOutZ = m_r * std::cos( m_theta );
    }

    void fromCarthezian( T inX, T inY, T inZ )
    {
        m_r = std::sqrt( inX * inX + inY * inY + inZ * inZ );
        m_theta = std::acos( inZ / m_r );
        m_phi = std::atan( inY / inX );
    }

    ~SphericalCoord() = default;

protected:
private:
    T m_theta{ Zero };  // On a x-y plane, counted from 0x, 0 <= theta < 2Pi.
    T m_phi{ Zero };    // Angle from x-y plane, 0 <= phi <= Pi.
    T m_r{ Zero };      // radius
};

template <class T>
T SphericalCoord<T>::Zero = static_cast<T>( 0 );

template <class T>
T SphericalCoord<T>::TwoPi = static_cast<T>( Constants<T>::Pi ) * static_cast<T>( 2 );

NAMESPACE_END(MATH)
NAMESPACE_END(CUL)