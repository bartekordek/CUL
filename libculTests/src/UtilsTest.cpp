#include "CSVFileTests.hpp"
#include "CUL/Math/Vector3D.hpp"
#include "CUL/Math/Triangle.hpp"
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
    std::vector<CUL::Math::Vector3Di> values;
    for( int i = 1; i <= someBigValue; ++i )
    {
        CUL::Math::Vector3Di value( i, 0, 0 );
        values.push_back( value );
    }
    const auto highestVal = CUL::Math::max( values, CUL::Math::Axis::WIDTH );
    GTEST_ASSERT_EQ( someBigValue, highestVal );
}

TEST_F( UtilsTest, vectHigherCart )
{
    std::vector<CUL::Math::Vector3Di> values;
    for( int i = 1; i <= someBigValue; ++i )
    {
        CUL::Math::Vector3Di value( i, 0, 0 );
        values.push_back( value );
    }
    const auto highestVal = CUL::Math::max( values, CUL::Math::Axis::WIDTH );
    GTEST_ASSERT_EQ( someBigValue, highestVal );
}

TEST_F( UtilsTest, vectLower )
{
    std::vector<CUL::Math::Vector3Di> values;
    for( int i = 0; i < someBigValue; ++i )
    {
        CUL::Math::Vector3Di value( i, 0, 0 );
        values.push_back( value );
    }
    const auto lowestVal = CUL::Math::min( values, CUL::Math::Axis::WIDTH );
    GTEST_ASSERT_EQ( 0, lowestVal );
}

TEST_F( UtilsTest, vectLowerCart )
{
    std::vector<CUL::Math::Vector3Di> values;
    for( int i = 0; i < someBigValue; ++i )
    {
        CUL::Math::Vector3Di value( i, 0, 0 );
        values.push_back( value );
    }
    const auto lowestVal = CUL::Math::min( values, CUL::Math::Axis::WIDTH );
    GTEST_ASSERT_EQ( 0, lowestVal );
}

TEST_F( UtilsTest, minOf2Points )
{
    CUL::Math::Vector3Di v1( 0, 0, 0 );
    CUL::Math::Vector3Di v2( 1, 1, 1 );
    const auto minValue = CUL::Math::min( v1, v2, CUL::Math::Axis::WIDTH );
    GTEST_ASSERT_EQ( 0, minValue );
}

TEST_F( UtilsTest, maxOf2Points )
{
    CUL::Math::Vector3Di v1( 0, 0, 0 );
    CUL::Math::Vector3Di v2( 1, 1, 1 );
    const auto maxValue = CUL::Math::max( v1, v2, CUL::Math::Axis::WIDTH );
    GTEST_ASSERT_EQ( 1, maxValue );
}

TEST_F( UtilsTest, minOf3Points )
{
    const auto minValue = -190;
    CUL::Math::Vector3Di v1( 0, 0, 0 );
    CUL::Math::Vector3Di v2( minValue, 1, 1 );
    CUL::Math::Vector3Di v3( 90, 89, 88 );
    const auto minValueTest = CUL::Math::min( v1, v2, v3, CUL::Math::Axis::WIDTH );
    GTEST_ASSERT_EQ( minValue, minValueTest );
}

TEST_F( UtilsTest, maxOf3Points )
{
    const auto max = 50;
    CUL::Math::Vector3Di v1( 0, 0, 0 );
    CUL::Math::Vector3Di v2( 1, 1, 1 );
    CUL::Math::Vector3Di v3( max, 3, 3 );
    const auto maxValue = CUL::Math::max( v1, v2, v3, CUL::Math::Axis::WIDTH );
    GTEST_ASSERT_EQ( max, maxValue );
}

TEST_F( UtilsTest, triangleWidth )
{
    CUL::Math::Vector3Di value;
    value.setXYZ( 1, 1, 0 );
    GTEST_ASSERT_EQ( 1, value.getX() );
    GTEST_ASSERT_EQ( 1, value.getY() );
    GTEST_ASSERT_EQ( 0, value.getZ() );
}

TEST_F( UtilsTest, rad )
{
    CUL::Math::Angle rad;
    rad.setCurrentType( CUL::Math::Angle::Type::RADIAN );
    rad += 0.3;
    rad -= -0.1;
    const auto val = rad.getValueD();
    CUL::Math::Angle rad2( val );
}
#ifdef _MSC_VER
#pragma warning( pop )
#endif