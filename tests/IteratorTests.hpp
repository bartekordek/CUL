#pragma once
#if _MSC_VER
__pragma(warning( push ))
__pragma(warning( disable:4389 ))
#endif
#include "gtest/gtest.h"
#if _MSC_VER
__pragma(warning( pop ))
#endif
class IteratorTests: public ::testing::Test
{
public:
protected:
    IteratorTests()
    {
    }

    virtual ~IteratorTests()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

