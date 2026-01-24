#pragma once

#include "CUL/ISerializable.hpp"

#include "CUL/STL_IMPORTS/STD_array.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )
NAMESPACE_BEGIN( Primitives )

class CULLib_API Line final:
    public ISerializable
{
public:
    using PointType = std::array<float, 3>;
    using LineData = std::array<PointType, 2>;

    Line();
    Line( const Line& arg );

    Line& operator=( const Line& arg );

    void* dataVoid();

    void setData( const LineData& dataIn );
    std::vector<float> toVectorOfFloat() const;

    PointType& operator[](size_t index);
    const PointType& operator[](size_t index) const;

    LineData data;
    void* dataAsVoid = nullptr;

    ~Line();
protected:
private:
    void updateData();
    StringWr getSerializationContent( CounterType tabsSize, const bool = false ) const override;


// Deleted:
    Line( Line&& arg ) = delete;
    Line& operator=( Line&& arg ) = delete;
};

NAMESPACE_END( Primitives )
NAMESPACE_END( MATH )
NAMESPACE_END( CUL )