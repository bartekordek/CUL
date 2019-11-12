#include "AngleTests.hpp"

#include "CUL/Math/Angle.hpp"

using namespace CUL;
using namespace Math;


AngleTests::AngleTests()
{
}

TEST_F( AngleTests, halfShouldBe180Deg )
{
    Angle angle( 360, Angle::Type::DEGREE );
    angle /= 2;
    GTEST_ASSERT_EQ( 180, angle.getValueI( Angle::Type::DEGREE ) );
}

TEST_F( AngleTests, halfShouldBe180DegCopyOperator )
{
    Angle angle( 360, Angle::Type::DEGREE );
    Angle result = angle / 2;
    GTEST_ASSERT_EQ( 180, result.getValueI( Angle::Type::DEGREE ) );
}