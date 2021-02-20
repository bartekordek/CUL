#include "TriangleTests.hpp"
#include "CUL/Math/Primitives/Triangle3D.hpp"
#include "CUL/Math/TriangleRectangularSimple2D.hpp"

using TriangleRectangularSimple2D = CUL::MATH::TriangleRectangularSimple2D;
using AngleTypes = CUL::MATH::Angle::Type;
using AxisTypes = CUL::MATH::AxisCarthesian;

TriangleTests::TriangleTests()
{
}

TriangleTests::~TriangleTests()
{
}

void TriangleTests::SetUpTestCase()
{
}

void TriangleTests::TearDownTestCase()
{
}

TEST_F( TriangleTests, degressTest0nothingHasValue )
{
    TriangleRectangularSimple2D triangle;
    const auto angle = triangle.getAngle().getValueI( AngleTypes::DEGREE );
    GTEST_ASSERT_EQ( 0, angle );
}

TEST_F( TriangleTests, degressTest0AdjacentHasValue )
{
    TriangleRectangularSimple2D triangle;
    triangle.setAdjacent( 4.3 );
    const auto angle = triangle.getAngle().getValueI( AngleTypes::DEGREE );
    GTEST_ASSERT_EQ( 0, angle );
}

TEST_F( TriangleTests, degressTest45 )
{
    TriangleRectangularSimple2D triangle;
    triangle.setOpposite( 1.0 );
    triangle.setAdjacent( 1.0 );
    const auto angle = triangle.getAngle().getValueI( AngleTypes::DEGREE );
    GTEST_ASSERT_EQ( 45, angle );
}

TEST_F( TriangleTests, degressTest90 )
{
    TriangleRectangularSimple2D triangle;
    triangle.setOpposite( 10.0 );
    const auto angle = triangle.getAngle().getValueI( AngleTypes::DEGREE );
    GTEST_ASSERT_EQ( 90, angle );
}

TEST_F( TriangleTests, degressTest120 )
{
    TriangleRectangularSimple2D triangle;
    triangle.setAdjacent( -1.0 );
    triangle.setOpposite( 1.0 );
    const auto angle = triangle.getAngle().getValueI( AngleTypes::DEGREE );
    GTEST_ASSERT_EQ( 135, angle );
}

TEST_F( TriangleTests, degressTest135 )
{
    TriangleRectangularSimple2D triangle;
    triangle.setAdjacent( -1.0 );
    triangle.setOpposite( 1.7 );
    const auto angle = triangle.getAngle().getValueI( AngleTypes::DEGREE );
    GTEST_ASSERT_LT( 118, angle );
    GTEST_ASSERT_GT( 122, angle );
}

TEST_F( TriangleTests, degressTest180 )
{
    TriangleRectangularSimple2D triangle;
    triangle.setAdjacent( -10.0 );
    const auto angle = triangle.getAngle().getValueI( AngleTypes::DEGREE );
    GTEST_ASSERT_EQ( 180, angle );
}

TEST_F( TriangleTests, degressTest240 )
{
    TriangleRectangularSimple2D triangle;
    triangle.setAdjacent( -1.0 );
    triangle.setOpposite( -1.75 );
    const auto angle = triangle.getAngle().getValueI( AngleTypes::DEGREE );
    GTEST_ASSERT_EQ( 240, angle );
}

TEST_F( TriangleTests, degressTest270 )
{
    TriangleRectangularSimple2D triangle;
    triangle.setOpposite( -10.0 );
    const auto angle = triangle.getAngle().getValueI( AngleTypes::DEGREE );
    GTEST_ASSERT_EQ( 270, angle );
}

TEST_F( TriangleTests, initializationTest )
{
    auto p1xyz = 1.f;
    auto p2xyz = 2.f;
    auto p3xyz = 3.f;

    CUL::MATH::Point p1( p1xyz, p1xyz, p1xyz );
    CUL::MATH::Point p2( p2xyz, p2xyz, p2xyz );
    CUL::MATH::Point p3( p3xyz, p3xyz, p3xyz );

    CUL::MATH::Primitives::Triangle3D triangle3D( p1, p2, p3 );

    GTEST_ASSERT_EQ( triangle3D.getP1().x(), p1xyz );
    GTEST_ASSERT_EQ( triangle3D.getP1().y(), p1xyz );
    GTEST_ASSERT_EQ( triangle3D.getP1().z(), p1xyz );

    GTEST_ASSERT_EQ( triangle3D.getP2().x(), p2xyz );
    GTEST_ASSERT_EQ( triangle3D.getP2().y(), p2xyz );
    GTEST_ASSERT_EQ( triangle3D.getP2().z(), p2xyz );

    GTEST_ASSERT_EQ( triangle3D.getP3().x(), p3xyz );
    GTEST_ASSERT_EQ( triangle3D.getP3().y(), p3xyz );
    GTEST_ASSERT_EQ( triangle3D.getP3().z(), p3xyz );
}

// TODO:
//TEST_F( TriangleTests, translationTest )
//{
//    CUL::MATH::Triangle3DI triangle3D;
//
//    int x = 1, y = 2, z = 3;
//
//    CUL::MATH::Vector3Di translationVector( x, y, z );
//    triangle3D += translationVector;
//
//    GTEST_ASSERT_EQ( triangle3D.getDimension( AxisTypes::X ), x );
//    GTEST_ASSERT_EQ( triangle3D.getDimension( AxisTypes::Y ), y );
//    GTEST_ASSERT_EQ( triangle3D.getDimension( AxisTypes::Z ), z );
//
//    const int coef = 4;
//    translationVector *= coef;
//    triangle3D += translationVector;
//
//    GTEST_ASSERT_EQ( triangle3D.getDimension( AxisTypes::X ), x + x * coef );
//    GTEST_ASSERT_EQ( triangle3D.getDimension( AxisTypes::Y ), y + y * coef );
//    GTEST_ASSERT_EQ( triangle3D.getDimension( AxisTypes::Z ), z + z * coef );
//}