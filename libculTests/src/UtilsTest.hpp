#pragma once

#include "Gtest.hpp"

class UtilsTest:
    public testing::Test
{
protected:
    UtilsTest();
    virtual ~UtilsTest();

    static void SetUpTestCase();
    static void TearDownTestCase();
private:
    UtilsTest( const UtilsTest& val ) = delete;
    UtilsTest& operator=( const UtilsTest& rhv ) = delete;
};