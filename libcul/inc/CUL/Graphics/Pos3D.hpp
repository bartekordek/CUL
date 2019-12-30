#pragma once

#include "CUL/CUL.hpp"
#include "CUL/STL_IMPORTS/STD_utility.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

template <typename Type>
class CULLib_API Pos3D
{
public:
    Type x = static_cast<Type>( 0 );
    Type y = static_cast<Type>( 0 );
    Type z = static_cast<Type>( 0 );

    Pos3D()
    {

    }

    Pos3D( const Type inX, const Type inY, const Type inZ ):
        x( inX ),
        y( inY ),
        z( inZ )
    {

    }

    Pos3D( const Pos3D& arg ):
        x( arg.x ),
        y( arg.y ),
        z( arg.z )
    {

    }

    Pos3D( Pos3D&& arg ):
        x( std::move( arg.x ) ),
        y( std::move( arg.y ) ),
        z( std::move( arg.z ) )
    {

    }

    Pos3D& operator=( const Pos3D& rhv )
    {
        if( this != &rhv )
        {
            x = rhv.x;
            y = rhv.y;
            z = rhv.z;
        }
        return *this;
    }

    Pos3D& operator=( Pos3D&& rhv )
    {
        if( this != &rhv )
        {
            x = std::move( rhv.x );
            y = std::move( rhv.y );
            z = std::move( rhv.z );
        }
        return *this;
    }

    virtual ~Pos3D()
    {

    }

protected:
private:
};

using Pos3Df = Pos3D<float>;
using Pos3Dd = Pos3D<double>;
using Pos3Di = Pos3D<int>;

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )