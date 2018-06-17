#pragma once
#include "Gtest.hpp"
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4625 )
#pragma warning( disable: 4626 )
#endif
class TimeTests: public ::testing::Test
{
protected:
    TimeTests( void );
    virtual ~TimeTests();

    static void SetUpTestCase();
    static void TearDownTestCase();
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif