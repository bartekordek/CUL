#pragma once

#include "CUL/GenericUtils/DumbPtr.hpp"

#include "CUL/STL_IMPORTS/STD_array.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"


NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )

constexpr size_t G_arraySize = 4096;

class CULLib_API VariableWithAverageValue final
{
public:
    VariableWithAverageValue();

    VariableWithAverageValue( const VariableWithAverageValue& arg );
    VariableWithAverageValue( VariableWithAverageValue&& arg );
    VariableWithAverageValue& operator=( const VariableWithAverageValue& arg );
    VariableWithAverageValue& operator=( VariableWithAverageValue&& arg ) noexcept;

    void add( float value );
    float getAverage() const;
    float getMax() const;
    float getMin() const;

    std::size_t size() const;
    void setCapacity( size_t newCapacity );

    ~VariableWithAverageValue();
protected:
private:
    void calculateAverage();
    size_t m_sampleCapacity = 4;

    std::vector<float> m_samples;

    float m_lastVal = 0.f;
    float m_average = 0.f;
    float m_maxValue{ std::numeric_limits<float>::min() };
    float m_minValue{ std::numeric_limits<float>::max() };
};
using VWAV = VariableWithAverageValue;

NAMESPACE_END( MATH )
NAMESPACE_END( CUL )