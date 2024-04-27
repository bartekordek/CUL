#include "CUL/StrintUTF.hpp"
#include "StringUTFTests.hpp"
#include "CUL/StringUtil.hpp"

void StringUTFTests::SetUpTestCase()
{
}

void StringUTFTests::TearDownTestCase()
{
}

TEST_F( StringUTFTests, ConversionTest )
{
#if defined( CUL_WINDOWS )
    CUL::StringUTF test1;
    const std::wstring someString = L"D:/Books/Adam Boduch - Wstêp do programowania w jêzyku C#.pdf";
    const std::string simpleConversion = CUL::StringUtil::wcharToChar( someString, 0 );
    test1 = someString.c_str();
    test1.convertToHexData();
    test1.convertFromHexToString();

    //ASSERT_EQ( someString, test1.getString() );
#endif // #if defined( CUL_WINDOWS )
}

TEST_F( StringUTFTests, lower )
{
    CUL::StringUTF string( "someString" );
    string.toLower();
    //ASSERT_EQ( string, "somestring" );
}

TEST_F( StringUTFTests, upper )
{
    CUL::StringUTF string( "someString" );
    string.toUpper();
    //ASSERT_EQ( string, "SOMESTRING" );
}

TEST_F( StringUTFTests, containsTrue )
{
    CUL::StringUTF string( "someString" );
    //ASSERT_EQ( true, string.contains( "some" ) );
}

TEST_F( StringUTFTests, containsFalse )
{
    CUL::String string( "someString" );
    //ASSERT_EQ( false, string.contains( "xD" ) );
}

TEST_F( StringUTFTests, replace )
{
    CUL::String string( "someString" );
    string.replace( "some", "WAT" );
    //ASSERT_EQ( "WATString", string );
}

TEST_F( StringUTFTests, clear )
{
    CUL::String string( "someString" );
    string.clear();
    //ASSERT_EQ( "", string );
}

TEST_F( StringUTFTests, operatorTest )
{
    CUL::StringUTF string0;//= true;
    std::cout << "string0 = " << string0.cStr() << "\n";
    //ASSERT_EQ( "true", string0 );

    CUL::StringUTF string1 /*= 1*/;
    std::cout << "string1 = " << string1.cStr() << "\n";
    //ASSERT_EQ( 1, string1 );

    CUL::StringUTF string2 /*= 1u*/;
    std::cout << "string2 = " << string2.cStr() << "\n";
    //ASSERT_EQ( 1u, string2 );

    const float val = 3.0;
    CUL::StringUTF string3 /*= val*/;
    std::cout << "string 3 = " << string3.cStr() << "\n";
    //ASSERT_EQ( 3.0, string3 );

    CUL::StringUTF string4 /*= 3.0f*/;
    std::cout << "string 4 = " << string4.cStr() << "\n";

}