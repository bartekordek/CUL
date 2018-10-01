#pragma once
#include "Gtest.hpp"
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4625 )
#pragma warning( disable: 4626 )
#endif
class FrameCounterTests: public ::testing::Test
{
protected:
    FrameCounterTests( void );
    virtual ~FrameCounterTests( void );

    static void SetUpTestCase();
    static void TearDownTestCase();
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif