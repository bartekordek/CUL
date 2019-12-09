#include "CUL/String.hpp"
#include "StringTest.hpp"

void StringTests::SetUpTestCase()
{
}

void StringTests::TearDownTestCase()
{
}

TEST_F( StringTests, lower )
{
    CUL::String string( "someString" );
    string.toLower();
    ASSERT_EQ( string, "somestring" );
}

TEST_F( StringTests, upper )
{
    CUL::String string( "someString" );
    string.toUpper();
    ASSERT_EQ( string, "SOMESTRING" );
}

TEST_F( StringTests, containsTrue )
{
    CUL::String string( "someString" );
    ASSERT_EQ( true, string.contains( "some" ) );
}

TEST_F( StringTests, containsFalse )
{
    CUL::String string( "someString" );
    ASSERT_EQ( false, string.contains( "xD" ) );
}

TEST_F( StringTests, replace )
{
    CUL::String string( "someString" );
    string.replace( "some", "WAT" );
    ASSERT_EQ( "WATString", string );
}

TEST_F( StringTests, clear )
{
    CUL::String string( "someString" );
    string.clear();
    ASSERT_EQ( "", string );
}

TEST_F( StringTests, assigmentOperator )
{
    CUL::String string = true;
    ASSERT_EQ( "1", string );

    string = 10;
    ASSERT_EQ( "10", string );

    string = -1;
    ASSERT_EQ( "-1", string );
}
