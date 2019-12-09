#pragma once

#include "CUL/Math/Axis.hpp"

#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"
#include "CUL/STL_IMPORTS/STD_algorithm.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Math )
template <typename Type>
class MultiPoint
{
public:

    explicit MultiPoint( const unsigned int axisRows = 0 )
    {
        if( 0 != axisRows )
        {
            setAxisCount( axisRows );
        }
    }

    MultiPoint( const MultiPoint<Type>& mp ) = default;

    virtual ~MultiPoint()
    {
    }

    const Type distance( const std::shared_ptr<MultiPoint<Type>>& p )const
    {
        return distance( *p );
    }

    const Type distance( const MultiPoint<Type>& p )const
    {
        const unsigned AxisCount = std::min( axisValue.size(), p.axisValue.size() );
        Type distanceSquare = static_cast<Type>( 0.0 );
        for( unsigned int i = 0; i < AxisCount; ++i )
        {
            Type leftAxisValue = ( axisValue.at( i ) );
            Type rightAxisValue = ( p.axisValue.at( i ) );
            Type differencePerDimension = abs( leftAxisValue - rightAxisValue );
            Type squareOfCurrentDimension = ( differencePerDimension * differencePerDimension );
            distanceSquare += squareOfCurrentDimension;
        }
        return static_cast<Type>( sqrt( distanceSquare ) );
    }

    const MultiPoint<Type> operator+( const MultiPoint<Type>& p )const
    {
        const unsigned AxisCount = std::max( axisValue.size(), p.axisValue.size() );
        const unsigned lowerAxisCount = std::min( axisValue.size(), p.axisValue.size() );
        MultiPoint<Type> result( AxisCount );
        for( unsigned int i = 0; i < lowerAxisCount; ++i )
        {
            result.axisValue[i] = axisValue[i] + p.axisValue[i];
        }
        return result;
    }

    MultiPoint<Type> operator-( const MultiPoint<Type>& p )const
    {
        const unsigned AxisCount = std::max( axisValue.size(), p.axisValue.size() );
        const unsigned lowerAxisCount = std::min( axisValue.size(), p.axisValue.size() );
        MultiPoint<Type> result( AxisCount );
        for( unsigned int i = 0; i < lowerAxisCount; ++i )
        {
            result.axisValue[i] = axisValue[i] - p.axisValue[i];
        }
        return result;
    }

    MultiPoint<Type> relativeDistance( const MultiPoint<Type>& right )const
    {
        const unsigned int axisCount = axisValue.size();
        const unsigned int pAxisCount = right.axisValue.size();
        const unsigned int targetAxisCount = std::max( axisCount, pAxisCount );
        MultiPoint<Type> result( targetAxisCount );
        for( unsigned int axisIndex = 0; axisIndex < targetAxisCount; ++axisIndex )
        {
            result.setValue( axisIndex, std::abs( getValue( axisIndex ) - right.getValue( axisIndex ) ) );
        }
        return result;
    }

    MultiPoint<Type>& operator=( const MultiPoint<Type>& right )
    {
        if( this != &right )
        {
            const auto pAxisCount = static_cast<unsigned int>( right.axisValue.size() );
            setAxisCount( pAxisCount );

            for( unsigned int axisIndex = 0; axisIndex < pAxisCount; ++axisIndex )
            {
                setValue( axisIndex, right.getValue( axisIndex ) );
            }
        }
        return *this;
    }

    MultiPoint<Type> operator*( const MultiPoint<Type>& p )const
    {
        const unsigned AxisCount = std::max( axisValue.size(), p.axisValue.size() );
        const unsigned lowerAxisCount = std::min( axisValue.size(), p.axisValue.size() );
        MultiPoint<Type> result( AxisCount );
        for( unsigned int i = 0; i < lowerAxisCount; ++i )
        {
            Type& leftAxisValue = *( axisValue[i] );
            Type& rightAxisValue = *( p.axisValue[i] );
            result.setValue( leftAxisValue * rightAxisValue );
        }
        return result;
    }

    const bool operator==( const MultiPoint<Type>& p )const
    {
        if( this == &p )
        {
            return true;
        }

        const unsigned int axisCount = axisValue.size();
        if( axisCount == p.axisValue.size() )
        {
            for( unsigned int i = 0; i < axisCount; ++i )
            {
                if( axisValue[i] != p.axisValue[i] )
                {
                    return false;
                }
            }
            return true;
        }

        return false;
    }

    void setAxisCount( const unsigned int count )
    {
        axisValue.resize( count );
    }

    const unsigned int getAxisCount()const
    {
        return axisValue.size();
    }

    const Type getValue( const Axis axisIndex )const
    {
        return axisValue.at( static_cast<unsigned int>( axisIndex ) );
    }

    const Type getValue( const unsigned int axisIndex )const
    {
        return axisValue.at( static_cast<unsigned int>( axisIndex ) );
    }

    void setValue( const Axis axisIndex, const Type value )
    {
        axisValue.at( static_cast<unsigned int>( axisIndex ) ) = value;
    }

    void setValue( const unsigned int axisIndex, const Type value )
    {
        axisValue.at( static_cast<unsigned int>( axisIndex ) ) = value;
    }

    const Type distanceToZeroZero()const
    {
        Type distanceToZeroZero = static_cast<Type>( 0.0 );
        for( auto& axisValue : axisValue )
        {
            distanceToZeroZero += axisValue*axisValue;
        }
        return sqrt( distanceToZeroZero );
    }

private:
    std::vector<Type> axisValue;
};
NAMESPACE_END( Math )
NAMESPACE_END( CUL )