#include "CUL/MyString.hpp"
#include "StringTest.hpp"

void function( CUL::CnstMyStr& val )
{
    std::cout << val << "\n";
}

TEST_F( StringTests, shouldStringBeLowerWhenLowered )
{
    CUL::MyString string( "someString" );
    ASSERT_EQ( string.toLower(), "somestring" );
}

TEST_F( StringTests, shouldStringBeLowerWhenLoweredByStatic )
{
    CUL::MyString string( "someString" );
    ASSERT_EQ( string.toLower(), "somestring" );
}

TEST_F( StringTests, implicitConversionTest )
{
    function( "Hi!" );
    ASSERT_EQ( true, true );
}