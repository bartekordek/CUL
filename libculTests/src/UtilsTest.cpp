#include "CSVFileTests.hpp"
#include "CUL/Math/Vector3D.hpp"
#include "CUL/Math/Primitives/Triangle3D.hpp"
#include "UtilsTest.hpp"

const int someBigValue = 1000;

UtilsTest::UtilsTest()
{
}

UtilsTest::~UtilsTest()
{
}

void UtilsTest::SetUpTestCase()
{
}

void UtilsTest::TearDownTestCase()
{
}

#ifdef _MSC_VER
// Yes, I know that is a Spectre mitigation.
// But for now, I let this as TODO, since i don't know
// How to fix this.
// TODO
#pragma warning( push )
#pragma warning( disable: 5045 )
#endif
TEST_F( UtilsTest, vectHigher )
{
    std::vector<CUL::MATH::Vector3Di> values;
    for( int i = 1; i <= someBigValue; ++i )
    {
        CUL::MATH::Vector3Di value( i, 0, 0 );
        values.push_back( value );
    }
    const auto highestVal = CUL::MATH::max( values, CUL::MATH::Axis::WIDTH );
    GTEST_ASSERT_EQ( someBigValue, highestVal );
}

TEST_F( UtilsTest, vectHigherCart )
{
    std::vector<CUL::MATH::Vector3Di> values;
    for( int i = 1; i <= someBigValue; ++i )
    {
        CUL::MATH::Vector3Di value( i, 0, 0 );
        values.push_back( value );
    }
    const auto highestVal = CUL::MATH::max( values, CUL::MATH::Axis::WIDTH );
    GTEST_ASSERT_EQ( someBigValue, highestVal );
}

TEST_F( UtilsTest, vectLower )
{
    std::vector<CUL::MATH::Vector3Di> values;
    for( int i = 0; i < someBigValue; ++i )
    {
        CUL::MATH::Vector3Di value( i, 0, 0 );
        values.push_back( value );
    }
    const auto lowestVal = CUL::MATH::min( values, CUL::MATH::Axis::WIDTH );
    GTEST_ASSERT_EQ( 0, lowestVal );
}

TEST_F( UtilsTest, vectLowerCart )
{
    std::vector<CUL::MATH::Vector3Di> values;
    for( int i = 0; i < someBigValue; ++i )
    {
        CUL::MATH::Vector3Di value( i, 0, 0 );
        values.push_back( value );
    }
    const auto lowestVal = CUL::MATH::min( values, CUL::MATH::Axis::WIDTH );
    GTEST_ASSERT_EQ( 0, lowestVal );
}

TEST_F( UtilsTest, minOf2Points )
{
    CUL::MATH::Vector3Di v1( 0, 0, 0 );
    CUL::MATH::Vector3Di v2( 1, 1, 1 );
    const auto minValue = CUL::MATH::min( v1, v2, CUL::MATH::Axis::WIDTH );
    GTEST_ASSERT_EQ( 0, minValue );
}

TEST_F( UtilsTest, maxOf2Points )
{
    CUL::MATH::Vector3Di v1( 0, 0, 0 );
    CUL::MATH::Vector3Di v2( 1, 1, 1 );
    const auto maxValue = CUL::MATH::max( v1, v2, CUL::MATH::Axis::WIDTH );
    GTEST_ASSERT_EQ( 1, maxValue );
}

TEST_F( UtilsTest, minOf3Points )
{
    const auto minValue = -190;
    CUL::MATH::Vector3Di v1( 0, 0, 0 );
    CUL::MATH::Vector3Di v2( minValue, 1, 1 );
    CUL::MATH::Vector3Di v3( 90, 89, 88 );
    const auto minValueTest = CUL::MATH::min( v1, v2, v3, CUL::MATH::Axis::WIDTH );
    GTEST_ASSERT_EQ( minValue, minValueTest );
}

TEST_F( UtilsTest, maxOf3Points )
{
    const auto max = 50;
    CUL::MATH::Vector3Di v1( 0, 0, 0 );
    CUL::MATH::Vector3Di v2( 1, 1, 1 );
    CUL::MATH::Vector3Di v3( max, 3, 3 );
    const auto maxValue = CUL::MATH::max( v1, v2, v3, CUL::MATH::Axis::WIDTH );
    GTEST_ASSERT_EQ( max, maxValue );
}

TEST_F( UtilsTest, triangleWidth )
{
    CUL::MATH::Vector3Di value;
    value.setXYZ( 1, 1, 0 );
    GTEST_ASSERT_EQ( 1, value.getX() );
    GTEST_ASSERT_EQ( 1, value.getY() );
    GTEST_ASSERT_EQ( 0, value.getZ() );
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif