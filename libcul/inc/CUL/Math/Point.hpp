#pragma once

#include "CUL/Math/Axis.hpp"
#include "CUL/Math/Math.hpp"

#include "CUL/IMPORT_GLM.hpp"
#include "CUL/STL_IMPORTS/STD_array.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable : 5045 )
#endif

class CULLib_API Point final
{
public:
    using Type = float;
    using PointData = std::array<Type, 3>;

    PointData values = { { static_cast<Type>( 0 ), static_cast<Type>( 0 ), static_cast<Type>( 0 ) } };

    Type diagonal = 0.f;

    Point() noexcept;
    Point( const glm::vec3& vec ) noexcept;
    Point( Type val1, Type val2, Type val3 ) noexcept;
    Point( const PointData& data ) noexcept;

    Point& operator=( const PointData& data );
    Point& operator=( const glm::vec3& vec );

    operator glm::vec3();

    inline Point operator+( const Point& rhv ) const
    {
        Point result = *this;

        for( size_t i = 0; i < values.size(); ++i )
        {
            result.values[i] += rhv.values[i];
        }

        result.calculateDiagonal();

        return result;
    }

    inline Point operator-( const Point& rhv ) const
    {
        Point result = *this;

        for( size_t i = 0; i < values.size(); ++i )
        {
            result.values[i] -= rhv.values[i];
        }

        result.calculateDiagonal();

        return result;
    }

    inline Type x() const
    {
        return values[0];
    }

    inline Type& x()
    {
        return values[0];
    }

    inline Type y() const
    {
        return values[1];
    }

    inline Type& y()
    {
        return values[1];
    }

    inline Type z() const
    {
        return values[2];
    }

    inline Type& z()
    {
        return values[2];
    }

    glm::vec3 toGlmVec() const;

    Point( const Point& arg ) noexcept;
    Point( Point&& arg ) noexcept;
    Point& operator=( const Point& rhv );
    Point& operator=( Point&& rhv ) noexcept;
    Point& operator+=( const Point& rhv );
    Point operator+( const Point& rhv );
    Point& operator-=( const Point& rhv );
    Point operator-( const Point& rhv );
    bool operator<( const Point& rhv ) const;

    Type& getValue( const AxisCarthesian axis );
    void setAxisValue( AxisCarthesian axis, Type value );

    Type operator[]( size_t index ) const;
    Type& operator[]( size_t index );

    ~Point();

protected:
private:
    void calculateDiagonal();
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( MATH )
NAMESPACE_END( CUL )