#pragma once
#include "Gtest.hpp"

class TriangleTests:
    public testing::Test
{
protected:
    TriangleTests();
    virtual ~TriangleTests();

    static void SetUpTestCase();
    static void TearDownTestCase();
private:
    TriangleTests( const TriangleTests& val ) = delete;
    TriangleTests& operator=( const TriangleTests& rhv ) = delete;
};