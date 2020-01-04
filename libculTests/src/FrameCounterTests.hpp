#pragma once
#include "Gtest.hpp"
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4625 )
#pragma warning( disable: 4626 )
#pragma warning( disable: 4820 )
#endif
class FrameCounterTests: public ::testing::Test
{
protected:
    FrameCounterTests();
    virtual ~FrameCounterTests();

    static void SetUpTestCase();
    static void TearDownTestCase();

    const unsigned int measurePeriod = 50;
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif