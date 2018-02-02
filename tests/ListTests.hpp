#pragma once
#if _MSC_VER
__pragma(warning( push )) \
__pragma(warning( disable:4389 ))
#endif
#include "gtest/gtest.h"
class ListTests: public ::testing::Test
{
protected:
    ListTests( void );
    virtual ~ListTests();

    static void SetUpTestCase();
    static void TearDownTestCase();
};
#if _MSC_VER
__pragma(warning( pop ))
#endif