#pragma once
#include "CUL/String.hpp"
#include "Gtest.hpp"
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4625 )
#pragma warning( disable: 4626 )
#endif
class StringUTFTests:
    public ::testing::Test
{
protected:
    StringUTFTests()
    {
    }

    virtual ~StringUTFTests()
    {
    }

    static void SetUpTestCase();
    static void TearDownTestCase();

    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

    void TestBody() override
    {
    }
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif