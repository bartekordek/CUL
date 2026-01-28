#include "CUL/String/String.hpp"
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
    std::u32string tmp( U"ии" );
    CUL::String t0( L"ии" );

    CUL::CULInterface::getInstance()->createInstance();
    CUL::FS::IFile* file = CUL::CULInterface::getInstance()->getFF()->createFileFromPath( dummyFilePath );
    file->load( false, false );
    const char* utfLine = file->getContent()[2];

    CUL::String t1( "ии" );

    CUL::String t2 = utfLine;

    ASSERT_TRUE( t1 == t2 );
#endif  // TEST_UTF
}

TEST_F( StringTests, SanitizeDeSanitize )
{
    CUL::CULInterface::getInstance()->createInstance();
    CUL::FS::IFile* file = CUL::CULInterface::getInstance()->getFF()->createFileFromPath( dummyFilePath );
    file->load( false, false );
    const std::string utfLine = file->getLineUtf( 4 );

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

    ASSERT_TRUE( test1.equals( someString ) );
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

    ASSERT_TRUE( test1.equals( test0.getString() ) );
}

TEST_F( StringTests, ConversionTest01 )
{
    CUL::String test1;
    const std::wstring someString = L"ABC";
    test1 = someString;
    test1.serialize();
    test1.deserialize();

    ASSERT_TRUE( test1.equals( someString ) );
}

TEST_F( StringTests, ConversionTest02 )
{
    CUL::String test1;
    const std::wstring someString = L"D:/Books/Adam Boduch - Wst�p do programowania w j�zyku C#.pdf";
    test1 = someString;
    test1.serialize();
    test1.deserialize();

    ASSERT_TRUE( test1.equals( someString ) );
}

TEST_F( StringTests, ConversionTest03 )
{
    CUL::String test1;
    const std::wstring someString = L"D:/$AV_ASW/$VAULT/8d59f3a938dcf487f60581a6e7b4fa375d558ab60f5cbd89ef981b95e825d723.dat";
    test1 = someString;
    test1.serialize();
    test1.deserialize();

    ASSERT_TRUE( test1.equals( someString ) );
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

    ASSERT_TRUE( test1.equals( someOhterString ) );
}

TEST_F( StringTests, ConversionTest05 )
{
    const std::wstring someString =
        L"D:/Books/Beletrystyka/criminal action/Clancy Tom - ebooki [PL][.doc][.rtf][.pdf]/Clancy Tom - Jack Ryan 05 - Czerwony "
        L"królik.rtf";
    CUL::String test1( someString );
    test1.serialize();
    test1.deserialize();

    ASSERT_TRUE( test1.equals( someString ) );
}

TEST_F( StringTests, ConvertToi32 )
{
    CUL::String test1( "02" );

    ASSERT_TRUE( test1.toInt() == 2 );
}

TEST_F( StringTests, ConvertToi64 )
{
    CUL::String test1( "03" );

    ASSERT_TRUE( test1.toInt64() == 3 );
}

TEST_F( StringTests, ConvertToui32 )
{
    CUL::String test1( "04" );

    ASSERT_TRUE( test1.toUInt() == 4u );
}

TEST_F( StringTests, ConvertToui64 )
{
    CUL::String test1( "05" );

    ASSERT_TRUE( test1.toUInt() == 5u );
}

TEST_F( StringTests, ConvertToint2 )
{
    CUL::String test1( "06" );

    ASSERT_TRUE( test1.toInt64() == 6 );

    test1 = "08";
    ASSERT_TRUE( test1.toInt64() == 8 );
}

//
TEST_F( StringTests, RemoveAllChar )
{
    CUL::String t1( "abcdaea" );
    t1.removeAll( 'a' );
    ASSERT_TRUE( t1.equals( "bcde" ) );
}
//

TEST_F( StringTests, lower )
{
    CUL::String string( "someString" );
    string.toLower();
    GTEST_ASSERT_TRUE( string.equals( "somestring" ) );
}

TEST_F( StringTests, upper )
{
    CUL::String string( "someString" );
    string.toUpper();
    GTEST_ASSERT_TRUE( string.equals( "SOMESTRING" ) );
}

TEST_F( StringTests, containsTrue )
{
    CUL::String string( "someString" );
    GTEST_ASSERT_TRUE( string.contains( "some" ) );
}

TEST_F( StringTests, containsFalse )
{
    CUL::String string( "someString" );
    GTEST_ASSERT_TRUE( !string.contains( "xD" ) );
}

TEST_F( StringTests, replace_for_shorter )
{
    CUL::String string( "aaabbbbccc" );
    string.replace( "bbbb", "dd" );
    ASSERT_TRUE( string.equals( "aaaddccc" ) );
}

TEST_F( StringTests, replace_for_same_length )
{
    CUL::String string( "aaabbbbccc" );
    string.replace( "bbbb", "dddd" );
    ASSERT_TRUE( string.equals( "aaaddddccc" ) );
}

TEST_F( StringTests, replace_for_bigger )
{
    CUL::String string( "aaabbccc" );
    string.replace( "bb", "dddd" );
    ASSERT_TRUE( string.equals( "aaaddddccc" ) );
}

TEST_F( StringTests, clear )
{
    CUL::String string( "someString" );
    string.clear();
    ASSERT_TRUE( string.empty() );
}

TEST_F( StringTests, operatorTest )
{
}

TEST_F( StringTests, deserializationTest00 )
{
    CUL::String string0(
        "044003a002f0042006f006f006b0073004c006900620072006100720079002f004d006100670061007a0069006e00650073002f00430044002d00410063007"
        "4006"
        "9006f006e002f0031003900390039002f004300440041002000310030002d00390039002e007000640066000000" );
    string0.deserialize();
    ASSERT_TRUE( string0.equals( "D:/BooksLibrary/Magazines/CD-Action/1999/CDA 10-99.pdf" ) );
}

TEST_F( StringTests, pathToFile00 )
{
    CUL::FS::Path current( "D:/BooksLibrary/Magazines/CD-Action/1999/CDA 02-99.pdf" );
    CUL::String pathAsString = current.getPath().getValue();
    pathAsString.serialize();
#if CUL_USE_WCHAR
    ASSERT_TRUE( pathAsString.equals(
        "044003a002f0042006f006f006b0073004c006900620072006100720079002f004d006100670061007a0069006e00650073002f00430044002d004100"
        "6300740069006f006e002f0031003900390039002f004300440041002000300032002d00390039002e007000640066000000" ) );
#else
    ASSERT_TRUE( pathAsString.equals(
        "1443a2f426f6f6b734c6962726172792f4d6167617a696e65732f43442d416374696f6e2f313939392f4344412030322d39392e70646600" ) );
#endif
}