#pragma once
#include "gtest/gtest.h"
class TimeTests: public ::testing::Test
{
protected:
    TimeTests( void );
    virtual ~TimeTests();

    static void SetUpTestCase();
    static void TearDownTestCase();
};