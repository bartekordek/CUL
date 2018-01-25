#include "PivotTests.hpp"
#include "CUL/IPivot.hpp"

using namespace CUL;

PivotTests::PivotTests( void )
{
}

PivotTests::~PivotTests()
{
}

void PivotTests::SetUpTestCase()
{
}

void PivotTests::TearDownTestCase()
{
}

TEST_F( PivotTests, dimensionSetting )
{
    const double w = 1.0;
    const double h = 2.0;
    const double d = 3.0;
    CUL::IPivot pivot( nullptr );
    pivot.setWidth( w );
    pivot.setHeight( h );
    pivot.setDepth( d );

    auto pivotType = CUL::IPivot::PivotType::ABSOLUTE;

    GTEST_ASSERT_EQ( pivot.getPivot( pivotType ).getX() < ( w / 2.0 + 0.1 ), true );
    GTEST_ASSERT_EQ( pivot.getPivot( pivotType ).getX() > ( w / 2.0 - 0.1), true );

    GTEST_ASSERT_EQ( pivot.getPivot( pivotType ).getY() < ( h / 2.0 + 0.1 ), true );
    GTEST_ASSERT_EQ( pivot.getPivot( pivotType ).getY() > ( h / 2.0 - 0.1 ), true );

    GTEST_ASSERT_EQ( pivot.getPivot( pivotType ).getZ() < ( d / 2.0 + 0.1 ), true );
    GTEST_ASSERT_EQ( pivot.getPivot( pivotType ).getZ() > ( d / 2.0 - 0.1 ), true );
}