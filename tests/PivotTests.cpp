#include "PivotTests.hpp"
#include "CUL/Math/IPivot.hpp"

using IPivot = CUL::Math::IPivot;
using Vec3Dd = CUL::Math::Vector3Dd;

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
/* I am not sure anymore if we can test Interface itself.
class TestClas final:
    public IPivot
{
public:
    TestClas( const double width, const double height, const double depth )
    {
    }

    ~TestClas()
    {

    }
#if _MSC_VER
    __pragma( warning( push ) )
    __pragma( warning( disable:4100 ) )
#endif


#if _MSC_VER
    __pragma( warning( pop ) )
#endif

protected:
private:
    Vec3Dd m_realSize;

};

TEST_F( PivotTests, dimensionSetting )
{
    const double w = 1.0;
    const double h = 2.0;
    const double d = 3.0;
    TestClas pivot( w, h, d );

    auto pivotType = IPivot::PivotType::ABSOLUTE;

    GTEST_ASSERT_EQ( pivot.getPivot( pivotType ).getX() < ( w / 2.0 + 0.1 ), true );
    GTEST_ASSERT_EQ( pivot.getPivot( pivotType ).getX() > ( w / 2.0 - 0.1), true );

    GTEST_ASSERT_EQ( pivot.getPivot( pivotType ).getY() < ( h / 2.0 + 0.1 ), true );
    GTEST_ASSERT_EQ( pivot.getPivot( pivotType ).getY() > ( h / 2.0 - 0.1 ), true );

    GTEST_ASSERT_EQ( pivot.getPivot( pivotType ).getZ() < ( d / 2.0 + 0.1 ), true );
    GTEST_ASSERT_EQ( pivot.getPivot( pivotType ).getZ() > ( d / 2.0 - 0.1 ), true );
}
*/