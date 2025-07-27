#include "CUL/Math/VariableWithAverageValue.hpp"
#include <CUL/STL_IMPORTS/STD_cmath.hpp>

using namespace CUL;
using namespace MATH;

VariableWithAverageValue::VariableWithAverageValue()
{
}

VariableWithAverageValue::VariableWithAverageValue( const VariableWithAverageValue& arg )
    : m_sampleCapacity( arg.m_sampleCapacity ),
      m_samples( arg.m_samples ),
      m_lastVal( arg.m_lastVal ),
      m_average( arg.m_average ),
      m_maxValue(arg.m_maxValue),
      m_minValue(arg.m_minValue)
{
}

VariableWithAverageValue::VariableWithAverageValue( VariableWithAverageValue&& arg )
    : m_sampleCapacity( arg.m_sampleCapacity ),
      m_samples( std::move( arg.m_samples ) ),
      m_lastVal( arg.m_lastVal ),
      m_average( arg.m_average ),
      m_maxValue( arg.m_maxValue ),
      m_minValue( arg.m_minValue )
{
    arg.m_sampleCapacity = 0;
}

VariableWithAverageValue& VariableWithAverageValue::operator=( const VariableWithAverageValue& arg )
{
    if( this != &arg )
    {
        m_sampleCapacity = arg.m_sampleCapacity;
        m_samples = arg.m_samples;
        m_lastVal = arg.m_lastVal;
        m_average = arg.m_average;
        m_maxValue = arg.m_maxValue;
        m_minValue = arg.m_minValue;
    }
    return *this;
}

VariableWithAverageValue& VariableWithAverageValue::operator=( VariableWithAverageValue&& arg ) noexcept
{
    if( this != &arg )
    {
        m_sampleCapacity = arg.m_sampleCapacity;
        m_samples = std::move( arg.m_samples );
        m_lastVal = arg.m_lastVal;
        m_average = arg.m_average;
        m_maxValue = arg.m_maxValue;
        m_minValue = arg.m_minValue;

        arg.m_sampleCapacity = 0u;
        arg.m_lastVal = 0.f;
        m_average = 0.f;
        m_maxValue = 0.f;
        arg.m_minValue = 0.f;

    }
    return *this;
}

void VariableWithAverageValue::add( float value )
{
    if( std::isnan( value ) )
    {
        auto x = 0;
    }

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

float VariableWithAverageValue::getMax() const
{
    return m_maxValue;
}

float VariableWithAverageValue::getMin() const
{
    return m_minValue;
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

    if( currentSize > 0 )
    {
        //m_minValue = std::min( m_samples[0u], m_minValue );
        //m_maxValue = std::max( m_samples[0u], m_maxValue );

        m_minValue = m_samples[0u];
        m_maxValue = m_samples[0u];
    }

    for( std::size_t i = 0; i < currentSize; ++i )
    {
        const float currentValue = m_samples[i];

        m_average += currentValue;

        if( i == 0u )
        {
            continue;
        }

        m_minValue = std::min( m_minValue, currentValue );
        m_maxValue = std::max( m_maxValue, currentValue );
    }

    m_average /= (float)currentSize;
}

VariableWithAverageValue::~VariableWithAverageValue()
{
}