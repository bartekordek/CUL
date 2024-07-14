#pragma once

#include "Gtest.hpp"
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4625 )
#pragma warning( disable: 4626 )
#endif
class TrackerTests: public ::testing::Test
{
protected:
    TrackerTests();

    virtual ~TrackerTests()
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