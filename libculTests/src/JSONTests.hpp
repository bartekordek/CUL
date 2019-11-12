#pragma once
#include "Gtest.hpp"
#include "CUL/MyString.hpp"
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4625 )
#pragma warning( disable: 4626 )
#endif
class JSONTests: public ::testing::Test
{
protected:
    JSONTests( void );
    virtual ~JSONTests( void );

    static void SetUpTestCase();
    static void TearDownTestCase();

    CUL::MyString jsonTestFileName = { "test.json" };
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif