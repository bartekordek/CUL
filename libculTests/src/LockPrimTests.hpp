#pragma once

#include "CUL/String/String.hpp"
#include "Gtest.hpp"

class LockPrimTests:
    public ::testing::Test
{
protected:
    LockPrimTests()
    {
    }

    LockPrimTests( const LockPrimTests& rhv ) = delete;
    LockPrimTests& operator=( const LockPrimTests& rhv ) = delete;

    virtual ~LockPrimTests()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};