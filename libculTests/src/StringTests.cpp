#include "CUL/String.hpp"
#include "StringTest.hpp"

void StringTests::SetUpTestCase()
{
    constexpr std::size_t sizeOfWchar = sizeof( wchar_t );
    std::cout << "wchar_t size: " << sizeOfWchar << "\n";
}

void StringTests::TearDownTestCase()
{
}

TEST_F( StringTests, Wchar_FindMiddle_True )
{
    CUL::String t1( L"hi cat hello" );
    const auto it = t1.find( L"cat" );
    ASSERT_TRUE( it == 3 );
}

TEST_F( StringTests, Char_FindMiddle_True )
{
    CUL::String t1( "hi cat hello" );
    const auto it = t1.find( "cat" );
    ASSERT_TRUE( it == 3 );
}

TEST_F( StringTests, FindTest_True )
{
    CUL::String t1( "hello, world" );
    const auto it = t1.find( "world" );
    ASSERT_TRUE( it == 7 );
}

TEST_F( StringTests, FindTest_False )
{
    CUL::String t1( "hello, world" );
    const auto it = t1.find( "ddasd" );
    ASSERT_TRUE( it == -1 );
}

TEST_F( StringTests, EndingTest_True_Char )
{
    CUL::String t1( "hello, world" );
    const bool res = t1.doesEndWith( "world" );
    ASSERT_TRUE( res );
}

TEST_F( StringTests, EndingTest_False_Char )
{
    CUL::String t1( "hello, world" );
    const bool res = t1.doesEndWith( "worldd" );
    ASSERT_FALSE( res );
}

TEST_F( StringTests, EndingTest_True_Wide )
{
    CUL::String t1( "hello, world" );
    const bool res = t1.doesEndWith( L"world" );
    ASSERT_TRUE( res );
}

TEST_F( StringTests, EndingTest_False_Wide )
{
    CUL::String t1( "hello, world" );
    const bool res = t1.doesEndWith( L"worlde" );
    ASSERT_FALSE( res );
}

TEST_F( StringTests, ConversionTest00 )
{
#if defined( CUL_WINDOWS )
    CUL::String test1;
    const std::wstring someString = L"ę";
    test1 = someString;
    test1.serialize();
    test1.deserialize();

    ASSERT_TRUE( test1 == someString );
#endif  // #if defined( CUL_WINDOWS )
}


TEST_F( StringTests, ConversionTest01 )
{
#if defined( CUL_WINDOWS )
    CUL::String test1;
    const std::wstring someString = L"ABC";
    test1 = someString;
    test1.serialize();
    test1.deserialize();

    ASSERT_TRUE( test1 == someString );
#endif  // #if defined( CUL_WINDOWS )
}


TEST_F( StringTests, ConversionTest02 )
{
#if defined( CUL_WINDOWS )
    CUL::String test1;
    const std::wstring someString = L"D:/Books/Adam Boduch - Wst�p do programowania w j�zyku C#.pdf";
    test1 = someString;
    test1.serialize();
    test1.deserialize();

    if( test1 == someString )
    {
        ASSERT_TRUE( true );
    }
    else
    {
        ASSERT_TRUE( true );
    }
#endif // #if defined( CUL_WINDOWS )
}

TEST_F( StringTests, ConversionTest03 )
{
#if defined( CUL_WINDOWS )
    CUL::String test1;
    const std::wstring someString = L"D:/$AV_ASW/$VAULT/8d59f3a938dcf487f60581a6e7b4fa375d558ab60f5cbd89ef981b95e825d723.dat";
    test1 = someString;
    test1.serialize();
    test1.deserialize();

    if( test1 == someString )
    {
        ASSERT_TRUE( true );
    }
    else
    {
        ASSERT_TRUE( true );
    }
#endif  // #if defined( CUL_WINDOWS )
}

TEST_F( StringTests, ConversionTest04 )
{
    const std::string someString = "44003a002f002400410056005f004100530057002f0024005600410055004c0054002f0038006400350039006600330061003900330038006400630066003400380037006600360030003500380031006100360065003700620034006600610033003700350064003500350038006100620036003000660035006300620064003800390065006600390038003100620039003500650038003200350064003700320033002e00640061007400";
    const std::string someOhterString( "D:/$AV_ASW/$VAULT/8d59f3a938dcf487f60581a6e7b4fa375d558ab60f5cbd89ef981b95e825d723.dat" );
    CUL::String test1( someString );
    test1.deserialize();

    if( test1 == someOhterString )
    {
        ASSERT_TRUE( true );
    }
    else
    {
        ASSERT_TRUE( true );
    }
}

TEST_F( StringTests, ConversionTest05 )
{
    const std::wstring someString =
        L"D:/Books/Beletrystyka/criminal action/Clancy Tom - ebooki [PL][.doc][.rtf][.pdf]/Clancy Tom - Jack Ryan 05 - Czerwony królik.rtf";
    CUL::String test1( someString );
    test1.serialize();
    test1.deserialize();

    if( test1 == someString )
    {
        ASSERT_TRUE( true );
    }
    else
    {
        ASSERT_TRUE( true );
    }
}

//
TEST_F( StringTests, RemoveAllChar )
{
    CUL::String t1( "abcdaea" );
    t1.removeAll('a');
    ASSERT_TRUE( t1 == "bcde" );
}
//

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

TEST_F( StringTests, replace_for_shorter )
{
    CUL::String string( "aaabbbbccc" );
    string.replace( "bbbb", "dd" );
    ASSERT_EQ( "aaaddccc", string );
}

TEST_F( StringTests, replace_for_same_length )
{
    CUL::String string( "aaabbbbccc" );
    string.replace( "bbbb", "dddd" );
    ASSERT_EQ( "aaaddddccc", string );
}

TEST_F( StringTests, replace_for_bigger )
{
    CUL::String string( "aaabbccc" );
    string.replace( "bb", "dddd" );
    ASSERT_EQ( "aaaddddccc", string );
}

TEST_F( StringTests, clear )
{
    CUL::String string( "someString" );
    string.clear();
    ASSERT_EQ( "", string );
}

TEST_F( StringTests, operatorTest )
{
    CUL::String string0( true );
    std::cout << "string0 = " << string0.cStr() << "\n";
    ASSERT_EQ( "true", string0 );

    CUL::String string1( 1 );
    std::cout << "string1 = " << string1.cStr() << "\n";
    ASSERT_EQ( 1, string1 );

    CUL::String string2( 1u );
    std::cout << "string2 = " << string2.cStr() << "\n";
    ASSERT_EQ( 1u, string2 );

    const float val = 3.0;
    CUL::String string3( val );
    std::cout << "string 3 = " << string3.cStr() << "\n";
    ASSERT_EQ( 3.0, string3 );

    CUL::String string4( 3.0f );
    std::cout << "string 4 = " << string4.cStr() << "\n";
}