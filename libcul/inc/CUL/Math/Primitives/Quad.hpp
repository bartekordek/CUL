#pragma once

#include "CUL/ISerializable.hpp"
#include "CUL/Math/Vector3D.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )
NAMESPACE_BEGIN( Primitives )

class CULLib_API Quad final:
    public ISerializable
{
public:
    using PointType = std::array<float, 3>;
    using QuadData = std::array<PointType, 4>;

    Quad();
    Quad( const Quad& arg );

    Quad& operator=( const Quad& arg );

    void* dataVoid();

    void setData( const QuadData& dataIn );

    PointType& operator[](size_t index);
    const PointType& operator[](size_t index) const;

    QuadData data;
    void* dataAsVoid = nullptr;

    ~Quad();
protected:
private:
    void updateData();
    String getSerializationContent( CounterType tabsSize, const bool = false ) const override;


// Deleted:
    Quad( Quad&& arg ) = delete;
    Quad& operator=( Quad&& arg ) = delete;
};

NAMESPACE_END( Primitives )
NAMESPACE_END( MATH )
NAMESPACE_END( CUL )