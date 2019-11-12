#pragma once
#include "Gtest.hpp"

class TriangleTests:
    public testing::Test
{
protected:
    TriangleTests( void );
    virtual ~TriangleTests( void );

    static void SetUpTestCase();
    static void TearDownTestCase();
private:
    TriangleTests( const TriangleTests& val ) = delete;
    TriangleTests& operator=( const TriangleTests& rhv ) = delete;
};