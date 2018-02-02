#pragma once
#include "CUL/MyString.hpp"
#if _MSC_VER
__pragma(warning( push ))
__pragma(warning( disable:4389 ))
#endif
#include "gtest/gtest.h"
#if _MSC_VER
__pragma(warning( pop ))
#endif
class StringTests: public ::testing::Test
{
protected:
    StringTests()
    {
    }

    virtual ~StringTests()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

};
