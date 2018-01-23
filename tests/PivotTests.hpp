#pragma once
#include "gtest/gtest.h"
class PivotTests : public ::testing::Test
{
protected:
    PivotTests( void );
    virtual ~PivotTests();

    static void SetUpTestCase();
    static void TearDownTestCase();
};