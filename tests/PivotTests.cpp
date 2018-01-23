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
    CUL::IPivot pivot;
    pivot.setWidth( w );
    pivot.setHeight( h );
    pivot.setDepth( d );

    GTEST_ASSERT_GE( w, 0.0 );
    GTEST_ASSERT_LE( w, 1.5 );

    GTEST_ASSERT_GE( h, 1.5 );
    GTEST_ASSERT_LE( h, 2.5 );

    GTEST_ASSERT_GE( d, 2.5 );
    GTEST_ASSERT_LE( d, 3.5 );
}