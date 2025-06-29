#pragma once
#include "CUL/String.hpp"
#include "Gtest.hpp"
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4625 )
#pragma warning( disable: 4626 )
#endif
class StringTests:
    public ::testing::Test
{
protected:
    StringTests()
    {
    }

    virtual ~StringTests()
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

public:
    CUL::String dummyFilePath = "../media/Dummy.txt";
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif