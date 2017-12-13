#pragma once
#include "gtest/gtest.h"
class ListTests: public ::testing::Test
{
protected:
    ListTests( void );
    virtual ~ListTests();

    static void SetUpTestCase();
    static void TearDownTestCase();
};