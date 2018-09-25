#pragma once
#include "Gtest.hpp"
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4625 )
#pragma warning( disable: 4626 )
#endif
class PivotTests final:
    public ::testing::Test
{
protected:
    PivotTests( void );
    virtual ~PivotTests();

    static void SetUpTestCase();
    static void TearDownTestCase();
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif