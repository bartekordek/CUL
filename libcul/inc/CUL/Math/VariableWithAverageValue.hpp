#pragma once

#include "CUL/GenericUtils/DumbPtr.hpp"

#include "CUL/STL_IMPORTS/STD_array.hpp"
#include "CUL/STL_IMPORTS/STD_memory_resource.hpp"


NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )

constexpr size_t G_arraySize = 4096;

class CULLib_API VariableWithAverageValue final
{
public:
    VariableWithAverageValue();

    void add( float value );
    float getAverage() const;

    size_t size() const;
    void setCapacity( size_t newCapacity );

    ~VariableWithAverageValue();
protected:
private:
    void calculateAverage();
    size_t m_sampleCapacity = 4;

    std::array<std::byte, G_arraySize> m_bufferBlocks;
    std::pmr::monotonic_buffer_resource m_buffer_src;
    std::pmr::vector<float> m_samples;

    float m_lastVal = 0.f;
    float m_average = 0.f;

    VariableWithAverageValue( const VariableWithAverageValue& arg ) = delete;
    VariableWithAverageValue( VariableWithAverageValue&& arg ) = delete;
    VariableWithAverageValue& operator=( const VariableWithAverageValue& arg ) = delete;
    VariableWithAverageValue& operator=( VariableWithAverageValue&& arg ) = delete;
};


NAMESPACE_END( MATH )
NAMESPACE_END( CUL )