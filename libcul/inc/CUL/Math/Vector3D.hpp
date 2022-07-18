#pragma once

#include "CUL/ISerializable.hpp"
#include "CUL/Math/Epsilon.hpp"
#include "CUL/Math/Angle.hpp"
#include "CUL/Math/Axis.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/GenericUtils/IOnChange.hpp"
#include "CUL/Math/TriangleRectangularSimple2D.hpp"
#include "CUL/Math/RotationType.hpp"

#include "CUL/STL_IMPORTS/STD_cmath.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_array.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )

using ST = TriangleRectangularSimple2D;
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4514 )
#pragma warning( disable: 4625 )
#pragma warning( disable: 4820 )
#endif
template <typename Type>
class Vector3D: public Epsilon<Type>, public ISerializable, public GUTILS::IOnChange
{
public:
    using ValueType = std::array<Type, 3>;

    Vector3D()
    {
        m_values[0] = { static_cast<Type>( 0 ) };
        m_values[1] = { static_cast<Type>( 0 ) };
        m_values[2] = { static_cast<Type>( 0 ) };

        m_width[0] = 0.0;
        m_width[1] = 0.0;
        m_width[2] = 0.0;
    }

    Vector3D( const Type xVal, const Type yVal, const Type zVal )
    {
        setAxisValue( AxisCarthesian::X, xVal );
        setAxisValue( AxisCarthesian::Y, yVal );
        setAxisValue( AxisCarthesian::Z, zVal );
    }

    Vector3D( const Vector3D<Type>& v2 ):
        ISerializable(),
        GUTILS::IOnChange()
    {
        copyFromOtherVector( v2 );
    }

    void copyFromOtherVector( const Vector3D<Type>& arg )
    {
        if( this != &arg )
        {
            m_values = arg.m_values;
            m_rotationTraingles = arg.m_rotationTraingles;
            m_width = arg.m_width;
        }
    }

    template <class someOtherClass>
    Vector3D( const Vector3D<someOtherClass>& right )
    {
        auto index = static_cast<AxisCarthesian>( 0 );
        auto indexR = static_cast<RotationType>( 0 );
        for(
            unsigned i = static_cast<unsigned>( AxisCarthesian::X );
            i < static_cast<unsigned>( AxisCarthesian::ERROR );
            ++i )
        {
            index = static_cast<AxisCarthesian>( i );
            indexR = static_cast<RotationType>( i );
            m_values[(size_t)index] = static_cast<Type>( right[index] );
            m_rotationTraingles[(size_t)indexR] = right.getTriangle( indexR );
        }
    }

    ValueType getValues() const
    {
        return m_values;
    }

    String getSerializationContent( CounterType tabsSize, const bool = false ) const override
    {
        String tabs = getTab( tabsSize );
        static CUL::MATH::Angle::Type angleType = CUL::MATH::Angle::Type::RADIAN;
        String result;
        result = result + tabs + "\"pos\":\n";
        result = result + tabs + "{\n";
        result = result + tabs + "    \"x\": " + String( m_values[0] ) + ",\n";
        result = result + tabs + "    \"y\": " + String( m_values[1] ) + ",\n";
        result = result + tabs + "    \"z\": " + String( m_values[2] ) + "\n";
        result = result + tabs + "},\n";
        result = result + tabs + "\"rotation\":\n";
        result = result + tabs + "{\n";
        result = result + tabs +
        "    \"yaw\": " + String( m_rotationTraingles[(size_t)RotationType::YAW].getAngle().getValueF( angleType ) ) + ",\n";
        result = result + tabs +
        "    \"pitch\": " + String( m_rotationTraingles[(size_t)RotationType::PITCH].getAngle().getValueF( angleType ) ) + ",\n";
        result = result + tabs +
        "    \"roll\": " + String( m_rotationTraingles[(size_t)RotationType::ROLL].getAngle().getValueF( angleType ) ) + "\n";
        result = result + tabs + "}\n";
        return result;
    }

    virtual ~Vector3D() = default;

    const Type& operator[]( const AxisCarthesian axis ) const
    {
        return m_values.at( (size_t)axis );
    }

    Type& operator[]( const AxisCarthesian axis )
    {
        return m_values[ac2Size( axis )];
    }

    const Type operator[]( size_t index ) const
    {
        return m_values[index];
    }

    const Type getX() const
    {
        return operator[]( AxisCarthesian::X );
    }

    const Type getY() const
    {
        return operator[]( AxisCarthesian::Y );
    }

    const Type getZ() const
    {
        return operator[]( AxisCarthesian::Z );
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
        m_values = object.m_values;
        m_rotationTraingles = object.m_rotationTraingles;
        m_width = object.m_width;
    }

    const Angle& getAngle( const RotationType rt ) const
    {
        return m_rotationTraingles[(size_t)rt].getAngle();
    }

    const ST& getTriangle( const RotationType rt ) const
    {
        return m_rotationTraingles.at( (size_t)rt );
    }

    void rotate( const Angle& angle, const RotationType rt )
    {
        auto s = std::sin( angle.getRad() );
        auto c = std::cos( angle.getRad() );

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

    bool operator!=( Vector3D& r ) const
    {
        return !operator==( r );
    }

    bool operator==( const Vector3D& ivector ) const
    {
        if(
            Epsilon<Type>::equals( getX(), ivector.getX() ) &&
            Epsilon<Type>::equals( getY(), ivector.getY() ) &&
            Epsilon<Type>::equals( getZ(), ivector.getZ() ) )
        {
            return true;
        }
        return false;
    }

    Vector3D<Type> operator*( const Vector3D<Type>& t ) const
    {
        Vector3D<Type> result( *this );
        auto index = static_cast<AxisCarthesian>( 0 );
        for( unsigned i = static_cast<unsigned>( AxisCarthesian::X ); i < static_cast<unsigned>( AxisCarthesian::ERROR ); ++i )
        {
            index = static_cast<AxisCarthesian>( i );
            result.m_values[index] *= t.m_values.at( index );
        }
        return result;
    }

    Vector3D<Type> operator-( const Vector3D<Type>& t ) const
    {
        Vector3D<Type> result;
        result.getX() = getX() - t.getX();
        result.getY() = getY() - t.getY();
        result.getZ() = getZ() - t.getZ();
        return result;
    }

    Vector3D<Type>& operator*=( const Vector3D<Type>& t )
    {
        m_values[(size_t)AxisCarthesian::X] *= t.getX();
        m_values[(size_t)AxisCarthesian::Y] *= t.getY();
        m_values[(size_t)AxisCarthesian::Z] *= t.getZ();
        return *this;
    }

    Vector3D<Type> operator*( const Type& t ) const
    {
        Vector3D<Type> result;
        result.getX() = getX() * t;
        result.getY() = getY() * t;
        result.getZ() = getZ() * t;
        return result;
    }
#ifdef _MSC_VER
    // Yes, I know that is a Spectre mitigation.
    // But for now, I let this as TODO, since i don't know
    // How to fix this.
    // TODO
#pragma warning( push )
#pragma warning( disable: 5045 )
#endif
    Vector3D<Type>& operator*=( const Type& t )
    {
        for( size_t i = static_cast<size_t>( AxisCarthesian::X ); i < static_cast<size_t>( AxisCarthesian::ERROR ); ++i )
        {
            m_values[ i ] *= t;
        }
        return *this;
    }
#ifdef _MSC_VER
#pragma warning( pop )
#endif

    Vector3D<Type> operator+( const Vector3D<Type>& right )
    {
        Vector3D<Type> result( *this );
        result += right;
        return result;
    }

    Vector3D<Type>& operator+=( const Vector3D<Type>& right )
    {
        m_values[(size_t)AxisCarthesian::X] += right.getX();
        m_values[(size_t)AxisCarthesian::Y] += right.getY();
        m_values[(size_t)AxisCarthesian::Z] += right.getZ();
        return *this;
    }

    Vector3D<Type> operator-( const Vector3D<Type>& right )
    {
        Vector3D<Type> result( *this );
        result -= right;
        return result;
    }

    //TODO:
    Vector3D<Type>& operator-=( const Vector3D<Type>& right )
    {
        auto index = static_cast<AxisCarthesian>( 0 );
        for( unsigned i = static_cast<unsigned>( AxisCarthesian::X ); i < static_cast<unsigned>( AxisCarthesian::ERROR ); ++i )
        {
            index = static_cast<AxisCarthesian>( i );
            m_values[index] -= right.m_values.at( index );
        }
        return *this;
    }

    Vector3D<Type>& operator=( const Vector3D<Type>& right )
    {
        if( this != &right )
        {
            m_values = right.m_values;
            m_rotationTraingles = right.m_rotationTraingles;
            m_width = right.m_width;
        }
        return *this;
    }

    Vector3D<Type> operator/( const Vector3D<Type>& t ) const
    {
        Vector3D<Type> result( *this );
        result /= t;
        return result;
    }

    Vector3D<Type>& operator/=( const Vector3D<Type>& right )
    {
        auto index = static_cast<AxisCarthesian>( 0 );
        for( unsigned i = static_cast<unsigned>( AxisCarthesian::X ); i < static_cast<unsigned>( AxisCarthesian::ERROR ); ++i )
        {
            index = static_cast<AxisCarthesian>( i );
            m_values[index] /= right.m_values.at( index );
        }
        return *this;
    }

    Vector3D<Type> operator/( const Type& t ) const
    {
        Vector3D<Type> result( *this );
        for( unsigned i = 0; i < 3; ++i )
        {
            result.m_values[i] /= t;
        }
        return result;
    }

    Vector3D<Type>& operator/=( const Type& t )
    {
        for( unsigned i = 0; i < 3; ++i )
        {
            m_values[i] /= t;
        }
        return *this;
    }

    const Type dotProdcut( const Vector3D<Type>& right ) const
    {
        const Type xx = getX() * right.getX();
        const Type yy = getY() * right.getY();
        const Type zz = getZ() * right.getZ();
        return xx * yy * zz;
    }

    const Vector3D<Type> crossProducti( const Vector3D<Type>& right ) const
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
        setAxisValue( UTIL::normal2Carthesian( axis ), value );
    }

    void setAxisValue( const AxisCarthesian axis, const Type value )
    {
        m_values[(size_t)axis] = value;
        if( AxisCarthesian::X == axis )
        {
            m_rotationTraingles[(size_t)RotationType::PITCH].setOpposite( static_cast<double>( value ) );
            m_rotationTraingles[(size_t)RotationType::ROLL].setAdjacent( static_cast<double>( value ) );
        }
        else if( AxisCarthesian::Y == axis )
        {
            m_rotationTraingles[(size_t)RotationType::ROLL].setOpposite( static_cast<double>( value ) );
            m_rotationTraingles[(size_t)RotationType::YAW].setOpposite( static_cast<double>( value ) );
        }
        else
        {
            m_rotationTraingles[(size_t)RotationType::YAW].setAdjacent( static_cast<double>( value ) );
            m_rotationTraingles[(size_t)RotationType::PITCH].setAdjacent( static_cast<double>( value ) );
        }
    }

    const Type getAxis( const AxisCarthesian axis ) const
    {
        return m_values.at( axis );
    }

    const Type getAxis( const Axis axis ) const
    {
        return m_values.at( (size_t)UTIL::normal2Carthesian( axis ) );
    }

    template <class someOtherClass>
    Vector3D<Type>& operator=( const Vector3D<someOtherClass>& right )
    {
        auto index = static_cast<AxisCarthesian>( 0 );
        for( unsigned i = static_cast<unsigned>( AxisCarthesian::X ); i < static_cast<unsigned>( AxisCarthesian::ERROR ); ++i )
        {
            index = static_cast<AxisCarthesian>( i );
            m_values[(size_t)index] = static_cast<Type>( right[(size_t)index] );
        }
        return *this;
    }

    const Type min( const Vector3D<Type>& p2, const Axis axis ) const
    {
        return UTIL::min( getAxis( axis ), p2.getAxis( axis ) );
    }

    const Type max( const Vector3D<Type>& p2, const Axis axis ) const
    {
        return UTIL::max( getAxis( axis ), p2.getAxis( axis ) );
    }

protected:
private:
    void recalculateWidth( const RotationType rt )
    {
        if( RotationType::ROLL == rt )
        {
            const auto xW = m_values[(size_t)AxisCarthesian::X];
            const auto yW = m_values[(size_t)AxisCarthesian::Y];
            m_width[(size_t)rt] = std::sqrt( 1.0 * xW * xW + 1.0 * yW * yW );
            m_rotationTraingles[(size_t)rt].setOpposite( m_width[(size_t)rt] );
        }
        else if( RotationType::PITCH == rt )
        {
            const auto xW = m_values[AxisCarthesian::X];
            const auto zW = m_values[AxisCarthesian::Z];
            m_width[(size_t)rt] = std::sqrt( 1.0 * xW * xW + 1.0 * zW * zW );
        }
        else
        {
            const auto yW = m_values[(size_t)AxisCarthesian::Y];
            const auto zW = m_values[(size_t)AxisCarthesian::Z];
            m_width[(size_t)RotationType::YAW] = std::sqrt( 1.0 * yW * yW + 1.0 * zW * zW );
        }
    }

    ValueType m_values;

    std::array<ST, 3> m_rotationTraingles;

    std::array<double, 3> m_width;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

using Vector3Dd = Vector3D<double>;
using Vector3Di = Vector3D<int>;
using Vector3Du = Vector3D<unsigned>;
using Vector3Df = Vector3D<float>;

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
    return UTIL::max( p1.getAxis( axis ), p2.getAxis( axis ) );
}

template <typename Type>
const Type min( const Vector3D<Type>& p1, const Vector3D<Type>& p2, const Axis axis )
{
    return UTIL::min( p1.getAxis( axis ), p2.getAxis( axis ) );
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
    return UTIL::max( v1, v2, v3 );
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
    return UTIL::max( v1, v2, v3 );
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

    return UTIL::min( v1, v2, v3 );
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

    return UTIL::min( v1, v2, v3 );
}

NAMESPACE_END( MATH )
NAMESPACE_END( CUL )
