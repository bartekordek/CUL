#include "Vector3DTests.hpp"
#include "CUL/Math/Vector3D.hpp"

using namespace CUL;
using namespace MATH;

TEST_F( Vector3DTests, initialization )
{
    Vector3Di v( 1, 2, 3 );
    GTEST_ASSERT_EQ( v.getX(), 1 );
    GTEST_ASSERT_EQ( v.getY(), 2 );
    GTEST_ASSERT_EQ( v.getZ(), 3 );
}

TEST_F( Vector3DTests, multiplicationVecTimesVec )
{
    Vector3Di v1( 2, 2, 2 );
    Vector3Di v2( 3, 3, 3 );
    v1 *= v2;

    GTEST_ASSERT_EQ( v1, Vector3Di( 6, 6, 6 ) );
}

TEST_F( Vector3DTests, addVec2Vec )
{
    Vector3Di v1( 2, 2, 2 );
    Vector3Di v2( 3, 3, 3 );
    v1 += v2;
    GTEST_ASSERT_EQ( v1, Vector3Di( 5, 5, 5 ) );
}

TEST_F( Vector3DTests, multiplicationVecTimesScalar )
{
    Vector3Di v( 3, 3, 3 );
    v *= 10;
    GTEST_ASSERT_EQ( v, Vector3Di( 30, 30, 30 ) );
}

TEST_F( Vector3DTests, assigmentOperator )
{
    Vector3Di v1( 1, 2, 3 );
    Vector3Di v2( 3, 2, 1 );
    v1 = v2;
    GTEST_ASSERT_EQ( v1, v2 );
}

TEST_F( Vector3DTests, angleXYRoll )
{
    Vector3Di v1( 1, 1, 0 );
    GTEST_ASSERT_EQ( 45, v1.getAngle( RotationType::ROLL ).getValueI( Angle::Type::DEGREE ) );
    GTEST_ASSERT_EQ( 90, v1.getAngle( RotationType::PITCH ).getValueI( Angle::Type::DEGREE ) );
    GTEST_ASSERT_EQ( 90, v1.getAngle( RotationType::YAW ).getValueI( Angle::Type::DEGREE ) );
}

TEST_F( Vector3DTests, angleXYPitchRoll180 )
{
    Vector3Di v1( 0, 0, -1 );
    //TODO 270?!
    GTEST_ASSERT_EQ( 0, v1.getAngle( RotationType::ROLL ).getValueI( Angle::Type::DEGREE ) );
    GTEST_ASSERT_EQ( 180, v1.getAngle( RotationType::PITCH ).getValueI( Angle::Type::DEGREE ) );
    GTEST_ASSERT_EQ( 180, v1.getAngle( RotationType::YAW ).getValueI( Angle::Type::DEGREE ) );
}