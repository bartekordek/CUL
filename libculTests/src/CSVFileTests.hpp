#pragma once
#include "Gtest.hpp"
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4625 )
#pragma warning( disable: 4626 )
#endif
class CSVFileTests: public ::testing::Test
{
protected:
    CSVFileTests();
    virtual ~CSVFileTests();

    static void SetUpTestCase();
    static void TearDownTestCase();
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif