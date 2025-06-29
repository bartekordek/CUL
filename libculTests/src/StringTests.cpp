#include "CUL/String.hpp"
#include "StringTest.hpp"
#include "CUL/Filesystem/Path.hpp"
#include "CUL/Filesystem/FS.hpp"
#include "CUL/Filesystem/IFile.hpp"
#include "CUL/Filesystem/FSApi.hpp"
#include "CUL/Filesystem/FileFactory.hpp"
#include "CUL/CULInterface.hpp"

void StringTests::SetUpTestCase()
{
    constexpr std::size_t sizeOfWchar = sizeof( wchar_t );
    std::cout << "wchar_t size: " << sizeOfWchar << "\n";
}

void StringTests::TearDownTestCase()
{
}

#define TEST_UTF 0

TEST_F( StringTests, WcharRestore )
{
#if TEST_UTF
    CUL::CULInterface::getInstance()->createInstance();
    CUL::FS::IFile* file = CUL::CULInterface::getInstance()->getFF()->createFileFromPath( dummyFilePath );
    file->load( false, false );
    const char* utfLine = file->getContent()[2];

    CUL::String t1( "Krążek" );

    CUL::String t2 = utfLine;

    ASSERT_TRUE( t1 == t2 );
#endif // TEST_UTF
}

TEST_F( StringTests, SanitizeDeSanitize )
{
    CUL::CULInterface::getInstance()->createInstance();
    CUL::FS::IFile* file = CUL::CULInterface::getInstance()->getFF()->createFileFromPath( dummyFilePath );
    file->load( false, false );
    const char* utfLine = file->getContent()[4];

    CUL::String loadedString = utfLine;
    loadedString.singleQuoteEscape();
    loadedString.singleQuoteRestore();

    const bool quoteSame = loadedString.equals( utfLine );

    ASSERT_TRUE( quoteSame );
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

TEST_F( StringTests, ConversionTest00a )
{
    CUL::String test0( "ę" );
    test0.serialize();

    CUL::String test1;
    const std::wstring someString = L"ę";
    test1 = someString;
    test1.serialize();
    test1.deserialize();

    ASSERT_TRUE( test1 == someString );
}

TEST_F( StringTests, ConversionTest00b )
{
    CUL::String test0( "ę" );
    test0.serialize();

#if CUL_USE_WCHAR
    CUL::String test1( "0c40022210000" );
#else
    CUL::String test1( "1c49900" );
#endif

    ASSERT_TRUE( test1 == test0 );
}

TEST_F( StringTests, ConversionTest01 )
{
    CUL::String test1;
    const std::wstring someString = L"ABC";
    test1 = someString;
    test1.serialize();
    test1.deserialize();

    ASSERT_TRUE( test1 == someString );
}

TEST_F( StringTests, ConversionTest02 )
{
    CUL::String test1;
    const std::wstring someString = L"D:/Books/Adam Boduch - Wst�p do programowania w j�zyku C#.pdf";
    test1 = someString;
    test1.serialize();
    test1.deserialize();

    ASSERT_TRUE( test1 == someString );
}

TEST_F( StringTests, ConversionTest03 )
{
    CUL::String test1;
    const std::wstring someString = L"D:/$AV_ASW/$VAULT/8d59f3a938dcf487f60581a6e7b4fa375d558ab60f5cbd89ef981b95e825d723.dat";
    test1 = someString;
    test1.serialize();
    test1.deserialize();

    ASSERT_TRUE( test1 == someString );
}

TEST_F( StringTests, ConversionTest04 )
{
    const std::string someString =
        "044003a002f002400410056005f004100530057002f0024005600410055004c0054002f0038006400350039006600330061003900330038006400630066003"
        "4003"
        "800370066003600300035003800310061003600650037006200340066006100330037003500640035003500380061006200360030006600350063006200640"
        "0380"
        "0390065006600390038003100620039003500650038003200350064003700320033002e0064006100740000";
    const std::string someOhterString( "D:/$AV_ASW/$VAULT/8d59f3a938dcf487f60581a6e7b4fa375d558ab60f5cbd89ef981b95e825d723.dat" );
    CUL::String test1( someString );
    test1.deserialize();

    ASSERT_TRUE( test1 == someOhterString );
}

TEST_F( StringTests, ConversionTest05 )
{
    const std::wstring someString =
        L"D:/Books/Beletrystyka/criminal action/Clancy Tom - ebooki [PL][.doc][.rtf][.pdf]/Clancy Tom - Jack Ryan 05 - Czerwony "
        L"królik.rtf";
    CUL::String test1( someString );
    test1.serialize();
    test1.deserialize();

    ASSERT_TRUE( test1 == someString );
}

//
TEST_F( StringTests, RemoveAllChar )
{
    CUL::String t1( "abcdaea" );
    t1.removeAll( 'a' );
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

TEST_F( StringTests, deserializationTest00 )
{
    CUL::String string0(
        "044003a002f0042006f006f006b0073004c006900620072006100720079002f004d006100670061007a0069006e00650073002f00430044002d00410063007"
        "4006"
        "9006f006e002f0031003900390039002f004300440041002000310030002d00390039002e007000640066000000" );
    string0.deserialize();
    ASSERT_TRUE( string0 == "D:/BooksLibrary/Magazines/CD-Action/1999/CDA 10-99.pdf" );
}

TEST_F( StringTests, pathToFile00 )
{
    CUL::FS::Path current( "D:/BooksLibrary/Magazines/CD-Action/1999/CDA 02-99.pdf" );
    CUL::String pathAsString = current;
    pathAsString.serialize();
#if CUL_USE_WCHAR
    ASSERT_TRUE( pathAsString ==
                 "044003a002f0042006f006f006b0073004c006900620072006100720079002f004d006100670061007a0069006e00650073002f00430044002d004100"
                 "6300740069006f006e002f0031003900390039002f004300440041002000300032002d00390039002e007000640066000000" );
#else
    ASSERT_TRUE( pathAsString ==
                 "1443a2f426f6f6b734c6962726172792f4d6167617a696e65732f43442d416374696f6e2f313939392f4344412030322d39392e70646600" );
#endif
}