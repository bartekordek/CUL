#pragma once

#include "Gtest.hpp"
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4625 )
#pragma warning( disable: 4626 )
#endif
class Benchmark: public ::testing::Test
{
protected:
    Benchmark();

    virtual ~Benchmark()
    {
    }

    virtual void SetUp();
    static void SetUpTestCase();
    static void TearDownTestCase();

    virtual void TearDown()
    {
    }
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif