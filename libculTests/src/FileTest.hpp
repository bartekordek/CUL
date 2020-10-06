#pragma once

#include "Gtest.hpp"
#include "CUL/String.hpp"
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4625 )
#pragma warning( disable: 4626 )
#endif
class FileTest: public ::testing::Test
{
public:
protected:
    FileTest()
    {
    }

    ~FileTest()
    {
    }

    void SetUp() override;

    void TearDown() override
    {
    }

    CUL::String dummyFilePath = "../media/Dummy.txt";
    CUL::String dummyImage = "../media/pikaczu.png";
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif