#pragma once

#include "CUL/ISerializable.hpp"
#include "CUL/Math/Vector3D.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )
NAMESPACE_BEGIN( Primitives )

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4514 )
#endif

class CULLib_API Triangle final:
    public ISerializable
{
public:
    using Type = float;
    using PointType = Vector3D<Type>;
    using ValuesType = std::array< PointType, 3 >;

    ValuesType vals;

    Triangle();
    Triangle( const Triangle& arg );

    Triangle& operator=( const Triangle& arg );
    PointType& operator[]( size_t index );

    const PointType& operator[]( size_t index ) const;

    std::vector<float> toVectorOfFloat() const;

    ~Triangle();

protected:
private:
    String getSerializationContent( CounterType tabsSize, const bool = false ) const override;

    // Deleted:
    Triangle( Triangle&& arg ) = delete;
    Triangle& operator=( Triangle&& arg ) = delete;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( Primitives )
NAMESPACE_END( MATH )
NAMESPACE_END( CUL )