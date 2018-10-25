#pragma once

#include "CUL/UselessMacros.hpp"
#include "CUL/Math/Epsilon.hpp"
#include "CUL/CUL.hpp"
#include "CUL/Math/Axis.hpp"
#include "CUL/SimpleAssert.hpp"

#include "CUL/STD_array.hpp"
#include "CUL/STD_vector.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Math )

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4514 )
#pragma warning( disable: 4820 )
#endif
template <typename Type>
class Vector3D:
    public Epsilon<Type>
{
public:
    Vector3D()
    {
    }

    Vector3D( 
        const Type xVal,
        const Type yVal,
        const Type zVal )
    {
        this->setAxisValue( AxisCarthesian::X, xVal );
        this->setAxisValue( AxisCarthesian::Y, yVal );
        this->setAxisValue( AxisCarthesian::Z, zVal );
    }

    Vector3D( const Vector3D<Type>& v2 ):
        m_vals( v2.m_vals )
    {

    }

    template <class someOtherClass>
    Vector3D( const Vector3D<someOtherClass>& right )
    {
        for( size_t i = 0; i < 3; ++i )
        {
            this->m_vals[i] = static_cast<Type>( right.m_vals[i] );
        }
    }

    virtual ~Vector3D() = default;

    const Type getX()const
    {
        return this->m_vals[ ac2size_t( AxisCarthesian::X ) ];
    }

    const Type getY()const
    {
        return this->m_vals[ ac2size_t( AxisCarthesian::Y ) ];
    }

    const Type getZ()const
    {
        return this->m_vals[ ac2size_t( AxisCarthesian::Z ) ];
    }

    void setX( const Type xValue )
    {
        this->m_vals[ ac2size_t( AxisCarthesian::X ) ] = xValue;
    }

    void setY( const Type yValue )
    {
        this->m_vals[ ac2size_t( AxisCarthesian::Y ) ] = yValue;
    }

    void setZ( const Type zValue )
    {
        this->m_vals[ ac2size_t( AxisCarthesian::Z ) ] = zValue;
    }

    void setXYZ(
        const Type xVal,
        const Type yVal,
        const Type zVal )
    {
        setAxisValue( AxisCarthesian::X, xVal );
        setAxisValue( AxisCarthesian::Y, yVal );
        setAxisValue( AxisCarthesian::Z, zVal );
    }

    void setXYZ( const Vector3D& object )
    {
        setAxisValue( AxisCarthesian::X, object.getX() );
        setAxisValue( AxisCarthesian::Y, object.getY() );
        setAxisValue( AxisCarthesian::Z, object.getZ() );
    }

    const bool operator!=( Vector3D& r ) const
    {
        return !this->operator==( r );
    }

    const bool operator==( const Vector3D& ivector )const
    {
        if( 
            Epsilon<Type>::equals( this->getX(), ivector.getX() ) &&
            Epsilon<Type>::equals( this->getY(), ivector.getY() ) &&
            Epsilon<Type>::equals( this->getZ(), ivector.getZ() ) )
        {
            return true;
        }
        return false;
    }

    Vector3D<Type> operator*( const Vector3D<Type>& t )const
    {
        Vector3D<Type> result;
        result.getX() = this->getX() * t.getX();
        result.getY() = this->getY() * t.getY();
        result.getZ() = this->getZ() * t.getZ();
        return result;
    }

    Vector3D<Type> operator-( const Vector3D<Type>& t )const
    {
        Vector3D<Type> result;
        result.getX() = this->getX() - t.getX();
        result.getY() = this->getY() - t.getY();
        result.getZ() = this->getZ() - t.getZ();
        return result;
    }

    Vector3D<Type>& operator*=( const Vector3D<Type>& t )
    {
        this->m_vals[ ac2size_t( AxisCarthesian::X ) ] *= t.getX();
        this->m_vals[ ac2size_t( AxisCarthesian::Y ) ] *= t.getY();
        this->m_vals[ ac2size_t( AxisCarthesian::Z ) ] *= t.getZ();
        return *this;
    }

    Vector3D<Type> operator*( const Type& t )const
    {
        Vector3D<Type> result;
        result.getX() = this->getX() * t;
        result.getY() = this->getY() * t;
        result.getZ() = this->getZ() * t;
        return result;
    }

    Vector3D<Type>& operator*=( const Type& t )
    {
        this->m_vals[ ac2size_t( AxisCarthesian::X ) ] *= t;
        this->m_vals[ ac2size_t( AxisCarthesian::Y ) ] *= t;
        this->m_vals[ ac2size_t( AxisCarthesian::Z ) ] *= t;
        return *this;
    }

    Vector3D<Type> operator+( const Vector3D<Type>& right )
    {
        Vector3D<Type> result( *this );
        result += right;
        return result;
    }

    Vector3D<Type>& operator+=( const Vector3D<Type>& right )
    {
        this->m_vals[ ac2size_t( AxisCarthesian::X ) ] += right.getX();
        this->m_vals[ ac2size_t( AxisCarthesian::Y ) ] += right.getY();
        this->m_vals[ ac2size_t( AxisCarthesian::Z ) ] += right.getZ();
        return *this;
    }

    Vector3D<Type> operator-( const Vector3D<Type>& right )
    {
        Vector3D<Type> result( *this );
        result -= right;
        return result;
    }

    Vector3D<Type>& operator-=( const Vector3D<Type>& right )
    {
        this->getX() -= right.getX();
        this->getY() -= right.getY();
        this->getZ() -= right.getZ();
        return *this;
    }

    Vector3D<Type>& operator=( const Vector3D<Type>& right )
    {
        if( this != &right )
        {
            this->setX( right.getX() );
            this->setY( right.getY() );
            this->setZ( right.getZ() );
        }
        return *this;
    }

    Vector3D<Type> operator/( const Vector3D<Type>& t )const
    {
        Vector3D<Type> result;
        result.getX() = this->getX() / t.getX();
        result.getY() = this->getY() / t.getY();
        result.getZ() = this->getZ() / t.getZ();
        return result;
    }

    Vector3D<Type>& operator/=( const Vector3D<Type>& t )
    {
        this->getX() = this->getX() / t.getX();
        this->getY() = this->getY() / t.getY();
        this->getZ() = this->getZ() / t.getZ();
        return *this;
    }

    Vector3D<Type> operator/( const Type& t )const
    {
        Vector3D<Type> result;
        result.getX() = this->getX() / t;
        result.getY() = this->getY() / t;
        result.getZ() = this->getZ() / t;
        return result;
    }

    Vector3D<Type>& operator/=( const Type& t )
    {
        this->getX() = this->getX() / t;
        this->getY() = this->getY() / t;
        this->getZ() = this->getZ() / t;
        return *this;
    }

    const Type dotProdcut( const Vector3D<Type>& right )const
    {
        const Type xx = this->getX() * right.getX();
        const Type yy = this->getY() * right.getY();
        const Type zz = this->getZ() * right.getZ();
        return xx * yy * zz;
    }

    const Vector3D<Type> crossProducti( const Vector3D<Type>& right )const
    {
        const auto& v1 = *this;
        const auto& v2 = right;

        const Type cx = v1.getY() * v2.getZ() - v1.getZ() * v2.getY();
        const Type cy = v1.getZ() * v2.getX() - v1.getX() * v2.getZ();
        const Type cz = v1.getX() * v2.getY() - v1.getY() * v2.getX();
        return Vector3D<Type>( cx, cy, cz );
    }

    void setAxisValue( const AxisCarthesian axis, const Type value )
    {
        this->m_vals[ ac2size_t( axis ) ] = value;
    }

    void setAxisValue( const Axis axis, const Type value )
    {
        this->m_vals[ ax2size_t( axis ) ] = value;
    }

    const Type getAxis( const AxisCarthesian axis )const
    {
        if( AxisCarthesian::X == axis )
        {
            return this->getX();
        }
        else if( AxisCarthesian::Y == axis )
        {
            return this->getY();
        }
        else if( AxisCarthesian::Z == axis )
        {
            return this->getZ();
        }
        return static_cast< Type >( 0 );
    }

    const Type getAxis( const Axis axis )const
    {
        if( Axis::WIDTH == axis )
        {
            return this->getX();
        }
        else if( Axis::HEIGHT == axis )
        {
            return this->getY();
        }
        else if( Axis::DEPTH == axis )
        {
            return this->getZ();
        }
        return static_cast<Type>(0);
    }

    template <class someOtherClass>
    Vector3D<Type>& operator=( const Vector3D<someOtherClass>& right )
    {
        this->getX() = static_cast<Type>( right.getX() );
        this->getY() = static_cast<Type>( right.getY() );
        this->getZ() = static_cast<Type>( right.getZ() );
        return *this;
    }

    const Type min( const Vector3D<Type>& p2, const Axis axis )const
    {
        return Util::min( this->getAxis( axis ), p2.getAxis( axis ) );
    }

    const Type max( const Vector3D<Type>& p2, const Axis axis )const
    {
        return Util::max( this->getAxis( axis ), p2.getAxis( axis ) );
    }

protected:
private:
    std::array<Type, 3> m_vals = {
        static_cast< Type >( 0 ),
        static_cast< Type >( 0 ),
        static_cast< Type >( 0 ) };
 
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif
using Vector3Dd = Vector3D<double> ;
using Vector3Di = Vector3D<int>;
using Vector3Du = Vector3D<unsigned>;

template <typename Type>
const Type max( const std::vector<Vector3D<Type>>& values, const Axis axis )
{
    CUL::Assert::simple( values.size() != 0, "VECTOR IS EMPTY." );
    Type result = values.at( 0 ).getAxis( axis );
    for( const auto value : values )
    {
        if( value.getAxis( axis ) > result )
        {
            result = value.getAxis( axis );
        }
    }
    return result;
}

template <typename Type>
const Type min( const std::vector<Vector3D<Type>>& values, const Axis axis )
{
    CUL::Assert::simple( values.size() != 0, "VECTOR IS EMPTY." );
    Type result = values.at( 0 ).getAxis( axis );
    for( const auto value : values )
    {
        if( value.getAxis( axis ) < result )
        {
            result = value.getAxis( axis );
        }
    }
    return result;
}

template <typename Type>
const Type max( const Vector3D<Type>& p1, const Vector3D<Type>& p2, const Axis axis )
{
    return Util::max( p1.getAxis( axis ), p2.getAxis( axis ) );
}

template <typename Type>
const Type min( const Vector3D<Type>& p1, const Vector3D<Type>& p2, const Axis axis )
{
    return Util::min( p1.getAxis( axis ), p2.getAxis( axis ) );
}

template <typename Type>
const Type max(
    const Vector3D<Type>& p1,
    const Vector3D<Type>& p2,
    const Vector3D<Type>& p3,
    const Axis axis )
{
    return Util::max(
        p1.getAxis( axis ),
        p2.getAxis( axis ),
        p3.getAxis( axis ) );
}

template <typename Type>
const Type min(
    const Vector3D<Type>& p1,
    const Vector3D<Type>& p2,
    const Vector3D<Type>& p3,
    const Axis axis )
{
    return Util::min(
        p1.getAxis( axis ),
        p2.getAxis( axis ),
        p3.getAxis( axis ) );
}

NAMESPACE_END( Math )
NAMESPACE_END( CUL )
