#include "CUL/MyString.hpp"
#include "StringTest.hpp"

TEST_F( StringTests, lower )
{
    CUL::MyString string( "someString" );
    string.toLower();
    ASSERT_EQ( string, "somestring" );
}

TEST_F( StringTests, upper )
{
    CUL::MyString string( "someString" );
    string.toUpper();
    ASSERT_EQ( string, "SOMESTRING" );
}

TEST_F( StringTests, containsTrue )
{
    CUL::MyString string( "someString" );
    ASSERT_EQ( true, string.contains( "some" ) );
}

TEST_F( StringTests, containsFalse )
{
    CUL::MyString string( "someString" );
    ASSERT_EQ( false, string.contains( "xD" ) );
}

TEST_F( StringTests, replace )
{
    CUL::MyString string( "someString" );
    string.replace( "some", "WAT" );
    ASSERT_EQ( "WATString", string );
}

TEST_F( StringTests, clear )
{
    CUL::MyString string( "someString" );
    string.clear();
    ASSERT_EQ( "", string );
}

TEST_F( StringTests, assigmentOperator )
{
    CUL::MyString string = true;
    ASSERT_EQ( "1", string );

    string = 10;
    ASSERT_EQ( "10", string );

    string = -1;
    ASSERT_EQ( "-1", string );
}