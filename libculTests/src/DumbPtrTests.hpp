#pragma once
#include "Gtest.hpp"
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4625 )
#pragma warning( disable: 4626 )
#endif
class DumbPtrTests:
    public ::testing::Test
{
protected:
    DumbPtrTests( void );
    virtual ~DumbPtrTests( void );

    static void SetUpTestCase();
    static void TearDownTestCase();
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif