#include "CUL/Math/VariableWithAverageValue.hpp"

using namespace CUL;
using namespace MATH;

VariableWithAverageValue::VariableWithAverageValue():
    m_buffer_src( &m_bufferBlocks, sizeof( m_bufferBlocks ) ), 
    m_samples( &m_buffer_src )
{
}

void VariableWithAverageValue::add( float value )
{
    m_samples.push_back( value );
    m_lastVal = value;
    if( m_samples.size() > m_sampleCapacity )
    {
        m_samples.erase(m_samples.begin());
    }
    calculateAverage();
}

float VariableWithAverageValue::getAverage() const
{
    return m_average;
}

size_t VariableWithAverageValue::size() const
{
    return m_sampleCapacity;
}

void VariableWithAverageValue::setCapacity( size_t newCapacity )
{
    m_sampleCapacity = newCapacity;
}

void VariableWithAverageValue::calculateAverage()
{
    m_average = 0.f;
    size_t currentSize = m_samples.size();
    for( size_t i = 0; i < currentSize; ++i )
    {
        m_average += m_samples[i];
    }

    m_average /= (float)currentSize;
}

VariableWithAverageValue::~VariableWithAverageValue()
{
}