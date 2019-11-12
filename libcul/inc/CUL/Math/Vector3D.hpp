#pragma once

#include "CUL/Math/Epsilon.hpp"
#include "CUL/CUL.hpp"
#include "CUL/Math/Angle.hpp"
#include "CUL/Math/Axis.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/Math/RotationType.hpp"
#include "CUL/Math/TriangleRectangularSimple2D.hpp"

#include "CUL/STL_IMPORTS/STD_cmath.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_map.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Math )

using ST = TriangleRectangularSimple2D;
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4514 )
#pragma warning( disable: 4625 )
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
        m_vals( v2.m_vals ),
        m_rotationTraingles( v2.m_rotationTraingles )
    {

    }

    template <class someOtherClass>
    Vector3D( const Vector3D<someOtherClass>& right )
    {
        auto index = static_cast< AxisCarthesian >( 0 );
        auto indexR = static_cast< RotationType >( 0 );
        for(
            unsigned i = static_cast<unsigned>( AxisCarthesian::X );
            i < static_cast<unsigned>( AxisCarthesian::ERROR );
            ++i )
        {
            index = static_cast< AxisCarthesian >( i );
            indexR = static_cast< RotationType >( i );
            this->m_vals[ index ] = static_cast<Type>( right[ index ] );
            this->m_rotationTraingles[indexR] = right.getTriangle( indexR );
        }
    }

    virtual ~Vector3D() = default;

    const Type& operator[]( const AxisCarthesian axis )const
    {
        return this->m_vals.at( axis );
    }

    Type& operator[]( const AxisCarthesian axis )
    {
        return this->m_vals[ ac2Size( axis ) ];
    }

    const Type operator[]( const unsigned axis )const = delete;

    const Type getX()const
    {
        return this->operator[]( AxisCarthesian::X );
    }

    const Type getY()const
    {
        return this->operator[]( AxisCarthesian::Y );
    }

    const Type getZ()const
    {
        return this->operator[]( AxisCarthesian::Z );
    }

    void setX( const Type val )
    {
        setAxisValue( AxisCarthesian::X, val );
    }

    void setY( const Type val )
    {
        setAxisValue( AxisCarthesian::Y, val );
    }

    void setZ( const Type val )
    {
        setAxisValue( AxisCarthesian::Z, val );
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
        this->m_vals = object.m_vals;
        this->m_rotationTraingles = object.m_rotationTraingles;
        this->m_width = object.m_width;
    }

    const Angle& getAngle( const RotationType rt )const
    {
        return this->m_rotationTraingles.at( rt ).getAngle();
    }

    const ST& getTriangle( const RotationType rt )const
    {
        return this->m_rotationTraingles.at( rt );
    }

    void rotate( const Angle& angle, const RotationType rt )
    {
        auto s = std::sin( angle.getValueD() );
        auto c = std::cos( angle.getValueD() );

        if( RotationType::ROLL == rt )
        {
            setX( getX() * c - getY() * s );
            setY( getX() * s - getY() * c );
        }
        else if( RotationType::PITCH == rt )
        {
            setX( getX() * c - getZ() * s );
            setZ( getX() * s - getZ() * c );
        }
        else
        {
            setZ( getZ() * c - getY() * s );
            setY( getZ() * s - getY() * c );
        }
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
        Vector3D<Type> result( *this );
        auto index = static_cast< AxisCarthesian >( 0 );
        for( unsigned i = static_cast<unsigned>( AxisCarthesian::X ); i < static_cast<unsigned>( AxisCarthesian::ERROR ); ++i )
        {
            index = static_cast< AxisCarthesian >( i );
            result.m_vals[ index ] *= t.m_vals.at( index );
        }
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
        this->m_vals[ AxisCarthesian::X ] *= t.getX();
        this->m_vals[ AxisCarthesian::Y ] *= t.getY();
        this->m_vals[ AxisCarthesian::Z ] *= t.getZ();
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
        for( unsigned i = static_cast<unsigned>( AxisCarthesian::X ); i < static_cast<unsigned>( AxisCarthesian::ERROR ); ++i )
        {
            this->m_vals[ static_cast<AxisCarthesian>( i ) ] *= t;
        }
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
        this->m_vals[ AxisCarthesian::X ] += right.getX();
        this->m_vals[ AxisCarthesian::Y ] += right.getY();
        this->m_vals[ AxisCarthesian::Z ] += right.getZ();
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
        auto index = static_cast< AxisCarthesian >( 0 );
        for( unsigned i = static_cast<unsigned>( AxisCarthesian::X ); i < static_cast<unsigned>( AxisCarthesian::ERROR ); ++i )
        {
            index = static_cast< AxisCarthesian >( i );
            this->m_vals[ index ] -= right.m_vals.at( index );
        }
        return *this;
    }

    Vector3D<Type>& operator=( const Vector3D<Type>& right )
    {
        if( this != &right )
        {
            this->m_vals = right.m_vals;
        }
        return *this;
    }

    Vector3D<Type> operator/( const Vector3D<Type>& t )const
    {
        Vector3D<Type> result( *this );
        result /= t;
        return result;
    }

    Vector3D<Type>& operator/=( const Vector3D<Type>& right )
    {
        auto index = static_cast< AxisCarthesian >( 0 );
        for( unsigned i = static_cast<unsigned>( AxisCarthesian::X ); i < static_cast<unsigned>( AxisCarthesian::ERROR ); ++i )
        {
            index = static_cast< AxisCarthesian >( i );
            this->m_vals[ index ] /= right.m_vals.at( index );
        }
        return *this;
    }

    Vector3D<Type> operator/( const Type& t )const
    {
        Vector3D<Type> result( *this );
        for( unsigned i = 0; i < 3; ++i )
        {
            result.m_vals[ i ] /= t;
        }
        return result;
    }

    Vector3D<Type>& operator/=( const Type& t )
    {
        for( unsigned i = 0; i < 3; ++i )
        {
            this->m_vals[ i ] /= t;
        }
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

    void setAxisValue( const Axis axis, const Type value )
    {
        setAxisValue( Util::normal2Carthesian( axis ), value );
    }

    void setAxisValue( const AxisCarthesian axis, const Type value )
    {
        this->m_vals[axis] = value;
        if( AxisCarthesian::X == axis )
        {
            this->m_rotationTraingles[RotationType::PITCH].setOpposite( static_cast< double >( value ) );
            this->m_rotationTraingles[RotationType::ROLL].setAdjacent( static_cast< double >( value ) );
        }
        else if( AxisCarthesian::Y == axis )
        {
            this->m_rotationTraingles[RotationType::ROLL].setOpposite( static_cast< double >( value ) );
            this->m_rotationTraingles[RotationType::YAW].setOpposite( static_cast< double >( value ) );
        }
        else
        {
            this->m_rotationTraingles[RotationType::YAW].setAdjacent( static_cast< double >( value ) );
            this->m_rotationTraingles[RotationType::PITCH].setAdjacent( static_cast< double >( value ) );
        }
    }

    const Type getAxis( const AxisCarthesian axis )const
    {
        return this->m_vals.at(axis);
    }

    const Type getAxis( const Axis axis )const
    {
        return this->m_vals.at( Util::normal2Carthesian( axis ) );
    }

    template <class someOtherClass>
    Vector3D<Type>& operator=( const Vector3D<someOtherClass>& right )
    {
        auto index = static_cast< AxisCarthesian >( 0 );
        for( unsigned i = static_cast<unsigned>( AxisCarthesian::X ); i < static_cast<unsigned>( AxisCarthesian::ERROR ); ++i )
        {
            index = static_cast< AxisCarthesian >( i );
            this->m_vals[ index ] = static_cast< Type >( right[index] );
        }
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
    void recalculateWidth( const RotationType rt )
    {
        if( RotationType::ROLL == rt )
        {
            const auto xW = m_vals[AxisCarthesian::X];
            const auto yW = m_vals[AxisCarthesian::Y];
            this->m_width[rt] = std::sqrt( 1.0 * xW * xW + 1.0 * yW * yW );
            this->m_rotationTraingles[rt].setOpposite( this->m_width[rt] );
        }
        else if( RotationType::PITCH == rt )
        {
            const auto xW = m_vals[AxisCarthesian::X];
            const auto zW = m_vals[AxisCarthesian::Z];
            this->m_width[rt] = std::sqrt( 1.0 * xW * xW + 1.0 * zW * zW );
        }
        else
        {
            const auto yW = m_vals[AxisCarthesian::Y];
            const auto zW = m_vals[AxisCarthesian::Z];
            this->m_width[RotationType::YAW] = std::sqrt( 1.0 * yW * yW + 1.0 * zW * zW );
        }
    }

    std::map<AxisCarthesian,Type> m_vals =
    {
        { AxisCarthesian::X, static_cast<Type>( 0 ) },
        { AxisCarthesian::Y, static_cast<Type>( 0 ) },
        { AxisCarthesian::Z, static_cast<Type>( 0 ) }
    };

    std::map<RotationType, ST> m_rotationTraingles =
    {
        { RotationType::ROLL, ST() },
        { RotationType::PITCH, ST() },
        { RotationType::YAW, ST() }
    };

    std::map<RotationType, double> m_width =
    {
        { RotationType::ROLL, 0.0 },
        { RotationType::PITCH, 0.0 },
        { RotationType::YAW, 0.0 }
    };

};
#ifdef _MSC_VER
#pragma warning( pop )
#endif
using Vector3Dd = Vector3D<double> ;
using Vector3Di = Vector3D<int>;
using Vector3Du = Vector3D<unsigned>;

#ifdef _MSC_VER
// Yes, I know that is a Spectre mitigation.
// But for now, I let this as TODO, since i don't know
// How to fix this.
// TODO
#pragma warning( push )
#pragma warning( disable: 5045 )
#endif
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
#ifdef _MSC_VER
#pragma warning( pop )
#endif

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
    const AxisCarthesian axis )
{
    const Type v1 = p1.getAxis( axis );
    const Type v2 = p2.getAxis( axis );
    const Type v3 = p3.getAxis( axis );
    return Util::max( v1, v2, v3 );
}

template <typename Type>
const Type max(
    const Vector3D<Type>& p1,
    const Vector3D<Type>& p2,
    const Vector3D<Type>& p3,
    const Axis axis )
{
    const Type v1 = p1.getAxis( axis );
    const Type v2 = p2.getAxis( axis );
    const Type v3 = p3.getAxis( axis );
    return Util::max( v1, v2, v3 );
}

template <typename Type>
const Type min(
    const Vector3D<Type>& p1,
    const Vector3D<Type>& p2,
    const Vector3D<Type>& p3,
    const AxisCarthesian axis )
{
    const Type v1 = p1.getAxis( axis );
    const Type v2 = p2.getAxis( axis );
    const Type v3 = p3.getAxis( axis );

    return Util::min( v1, v2, v3 );
}

template <typename Type>
const Type min(
    const Vector3D<Type>& p1,
    const Vector3D<Type>& p2,
    const Vector3D<Type>& p3,
    const Axis axis )
{
    const Type v1 = p1.getAxis( axis );
    const Type v2 = p2.getAxis( axis );
    const Type v3 = p3.getAxis( axis );

    return Util::min( v1, v2, v3 );
}

NAMESPACE_END( Math )
NAMESPACE_END( CUL )