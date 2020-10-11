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

TEST_F( StringTests, operatorTest )
{
    CUL::String string0 = true;
    std::cout << "string0 = " << string0.cStr() << "\n";
    ASSERT_EQ( "true", string0 );

    CUL::String string1 = 1;
    std::cout << "string1 = " << string1.cStr() << "\n";
    ASSERT_EQ( 1, string1 );

    CUL::String string2 = 1u;
    std::cout << "string2 = " << string2.cStr() << "\n";
    ASSERT_EQ( 1u, string2 );

    CUL::String string3 = 3.0;
    std::cout << "string 3 = " << string3.cStr() << "\n";

    CUL::String string4 = 3.0f;
    std::cout << "string 4 = " << string4.cStr() << "\n";

}