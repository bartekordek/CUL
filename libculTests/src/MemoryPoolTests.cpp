#include "MemoryPoolTests.hpp"

#include "CUL/Memory/MemoryPool.hpp"
#include "CUL/GenericUtils/DumbPtr.hpp"

#include "CUL/Math//VariableWithAverageValue.hpp"

#include "CUL/STL_IMPORTS/STD_iostream.hpp"

using namespace CUL;
using namespace Memory;

MemoryPoolTests::MemoryPoolTests()
{
}

TEST_F( MemoryPoolTests, TEST_SINGLE_ALLOCATION )
{
    //TODO:
}

TEST_F( MemoryPoolTests, TEST_MULTIPLE_ALLOCATION )
{
    //TODO:
}

TEST_F( MemoryPoolTests, TESTING_0 )
{
    MATH::VariableWithAverageValue average;
    average.add( 1.0 );
    average.add( 2.0 );
    average.add( 3.0 );

    float averageVal = average.getAverage();
    int averageInt = (int)averageVal;
    ASSERT_EQ( 2, averageInt );
}

TEST_F( MemoryPoolTests, TESTING_1 )
{
    MATH::VariableWithAverageValue average;
    average.add( 1.0 );
    average.add( 4.0 );
    average.add( 4.0 );
    average.add( 4.0 );
    average.add( 4.0 );

    float averageVal = average.getAverage();
    int averageInt = (int)averageVal;
    ASSERT_EQ( 4, averageInt );
}

TEST_F( MemoryPoolTests, MaxMin )
{
    MATH::VariableWithAverageValue average;
    average.add( 1.f );
    average.add( 2.f );
    average.add( 3.f );

    const std::int32_t minValue = static_cast<std::int32_t>( average.getMin() );
    const std::int32_t maxValue = static_cast<std::int32_t>( average.getMax() );
    ASSERT_EQ( 1, minValue );
    ASSERT_EQ( 3, maxValue );
}