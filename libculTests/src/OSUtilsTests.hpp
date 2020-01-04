#pragma once

#include "Gtest.hpp"

class OSUtilsTests:
    public testing::Test
{
protected:
    OSUtilsTests();
    virtual ~OSUtilsTests();

    static void SetUpTestCase();
    static void TearDownTestCase();
private:
    OSUtilsTests( const OSUtilsTests& val ) = delete;
    OSUtilsTests& operator=( const OSUtilsTests& rhv ) = delete;
};