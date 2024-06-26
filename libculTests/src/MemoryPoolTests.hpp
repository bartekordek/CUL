#pragma once

#include "Gtest.hpp"

#include "CUL/STL_IMPORTS/STD_array.hpp"
#include "CUL/STL_IMPORTS/STD_bitset.hpp"

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4625 )
#pragma warning( disable: 4626 )
#endif

template <int Size>
class TestClass
{
public:
    TestClass()
    {
        for( auto& value : m_values )
        {
            value = std::byte{ 1 };
        }
    }

    ~TestClass()
    {
        for( auto& value : m_values )
        {
            value = std::byte{ 0 };
        }
    }

protected:
private:
    std::array<std::byte, Size> m_values;
};

class MemoryPoolTests: public ::testing::Test
{
protected:
    MemoryPoolTests();

    virtual ~MemoryPoolTests()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif