#pragma once

#include "Gtest.hpp"
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4625 )
#pragma warning( disable: 4626 )
#endif
class AngleTests: public ::testing::Test
{
protected:
    AngleTests();

    virtual ~AngleTests()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif