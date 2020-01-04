#pragma once
#include "Gtest.hpp"
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4625 )
#pragma warning( disable: 4626 )
#endif
class SimpleStandardOutputLoggerTests:
    public ::testing::Test
{
protected:
    SimpleStandardOutputLoggerTests();
    virtual ~SimpleStandardOutputLoggerTests();

    static void SetUpTestCase();
    static void TearDownTestCase();

};
#ifdef _MSC_VER
#pragma warning( pop )
#endif