#pragma once

#include "Gtest.hpp"
#include "CUL/MyString.hpp"
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

    virtual ~FileTest()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

    CUL::MyString dummyFilePath = "../media/Dummy.txt";

};
#ifdef _MSC_VER
#pragma warning( pop )
#endif
