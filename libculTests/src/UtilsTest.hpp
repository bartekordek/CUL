#pragma once

#include "Gtest.hpp"

class UtilsTest:
    public testing::Test
{
protected:
    UtilsTest( void );
    virtual ~UtilsTest( void );

    static void SetUpTestCase();
    static void TearDownTestCase();
private:
    UtilsTest( const UtilsTest& val ) = delete;
    UtilsTest& operator=( const UtilsTest& rhv ) = delete;
};