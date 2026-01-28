#include "CUL/String/StringUtil.hpp"

#if !CUL_USE_WCHAR
    #include "CUL/GenericUtils/SimpleAssert.hpp"
    #include "CUL/STL_IMPORTS/STD_codecvt.hpp"
    #include "CUL/STL_IMPORTS/STD_cwchar.hpp"
    #include "CUL/STL_IMPORTS/STD_iconv.hpp"
    #include "CUL/STL_IMPORTS/STD_wctype.hpp"

namespace CUL
{
char StringUtil::toChar( wchar_t inChar )
{
    char result[2];
    wchar_t inWord[2] = { inChar, L'\0' };
    wcstombs( result, inWord, 1u );
    return result[0];
}

wchar_t StringUtil::toWideChar( char inChar )
{
    char inWord[2] = { inChar, '\0' };
    wchar_t result[2];
    mbstowcs( result, inWord, 1u );
    return result[1];
}

std::int32_t StringUtil::charToWideString( std::int32_t codePage, wchar_t* out, std::int32_t outSize, const char* in, std::int32_t inSize )
{
    Assert::simple( outSize >= inSize, "NOT ENOUGH PLACE FOR STRING" );

    std::size_t length;
    wchar_t* dest = out;
    mbstate_t mbs;
    memset( &mbs, 0, sizeof( mbs ) );
    mbrlen( NULL, 0, &mbs ); /* initialize mbs */

    std::size_t max = static_cast<std::size_t>( inSize );
    const char* pt = in;

    std::int32_t writtent{ 0 };
    while( max > 0 )
    {
        length = mbrtowc( dest, pt, max, &mbs );
        if( ( length == 0 ) || ( length >= max ) )
        {
            break;
        }
        wprintf( L"[%lc]", *dest );
        pt += length;
        max -= length;
        ++dest;
        ++writtent;
        if( writtent >= outSize )
        {
            break;
        }
    }

    return static_cast<decltype( outSize )>( writtent );
}

std::int32_t StringUtil::charToWideString( std::int32_t codePage, wchar_t& out, char in )
{
    iconv_t cd = iconv_open( "WCHAR_T", "UTF-8" );
    if( cd == (iconv_t)-1 )
    {
        return 0;
    }

    char inBufRaw[1] = { in };
    char* inBuf = inBufRaw;
    size_t inBytes = 1;

    wchar_t outBufRaw[1];
    char* outBuf = reinterpret_cast<char*>( outBufRaw );
    size_t outBytes = sizeof( wchar_t );

    size_t res = iconv( cd, &inBuf, &inBytes, &outBuf, &outBytes );
    iconv_close( cd );

    if( res == (size_t)-1 )
        return 0;

    // Must consume 1 byte and produce exactly 1 wchar_t
    if( inBytes != 0 || outBytes != 0 )
        return 0;

    out = outBufRaw[0];
    return 1;
}

std::int32_t StringUtil::charToWideString( std::wstring& out, const std::string& in )
{
    out.clear();
    if( in.empty() )
        return 0;

    iconv_t cd = iconv_open( "WCHAR_T", "UTF-8" );
    if( cd == (iconv_t)-1 )
    {
        return 0;
    }

    const char* inBuf = in.data();
    size_t inBytes = in.size();

    // Worst case: 1 UTF-8 byte -> 1 wchar_t
    out.resize( in.size() );

    char* outBuf = reinterpret_cast<char*>( out.data() );
    size_t outBytes = out.size() * sizeof( wchar_t );

    size_t res = iconv( cd, const_cast<char**>( &inBuf ), &inBytes, &outBuf, &outBytes );

    iconv_close( cd );

    if( res == (size_t)-1 )
    {
        out.clear();
        return 0;
    }

    // How many wchar_t were written
    size_t written = ( out.size() * sizeof( wchar_t ) - outBytes ) / sizeof( wchar_t );
    out.resize( written );

    return static_cast<std::int32_t>( written );
}

std::int32_t StringUtil::wideStringToChar( std::string& out, const std::wstring& inChar )
{
    out.clear();
    if( inChar.empty() )
    {
        return 0;
    }

    iconv_t cd = iconv_open( "UTF-8", "WCHAR_T" );
    if( cd == (iconv_t)-1 )
    {
        return 0;
    }

    const char* inBuf = reinterpret_cast<const char*>( inChar.data() );
    size_t inBytes = inChar.size() * sizeof( wchar_t );

    // Worst case UTF-8: 4 bytes per wchar_t
    out.resize( inChar.size() * 4 );

    char* outBuf = out.data();
    size_t outBytes = out.size();

    size_t res = iconv( cd, const_cast<char**>( &inBuf ), &inBytes, &outBuf, &outBytes );

    iconv_close( cd );

    if( res == (size_t)-1 )
    {
        out.clear();
        return 0;
    }

    size_t written = out.size() - outBytes;
    out.resize( written );

    return static_cast<std::int32_t>( written );
}

std::int32_t StringUtil::wideStringToChar( char* out, std::int32_t outSize, const wchar_t* inChar, std::int32_t inSize )
{
    std::size_t result = 0u;
    if( !out || !inChar || outSize <= 0 )
    {
        return 0;
    }

    iconv_t cd = iconv_open( "UTF-8", "WCHAR_T" );
    if( cd == (iconv_t)-1 )
    {
        return 0;
    }

    // Input buffer
    char* inBuf = (char*)inChar;
    size_t inBytes = inSize * sizeof( wchar_t );

    // Output buffer
    char* outBuf = out;
    size_t outBytes = outSize;

    size_t res = iconv( cd, &inBuf, &inBytes, &outBuf, &outBytes );

    iconv_close( cd );

    if( res == (size_t)-1 )
    {
        return 0;
    }

    return (std::int32_t)( outSize - outBytes );  // bytes written
}

std::int32_t StringUtil::wideStringToChar( char& out, wchar_t inChar )
{
    iconv_t cd = iconv_open( "UTF-8", "WCHAR_T" );
    if( cd == (iconv_t)-1 )
    {
        return 0;
    }

    char* inBuf = (char*)&inChar;
    size_t inBytes = sizeof( wchar_t );

    char buffer[4];
    char* outBuf = buffer;
    size_t outBytes = sizeof( buffer );

    size_t res = iconv( cd, &inBuf, &inBytes, &outBuf, &outBytes );
    iconv_close( cd );

    size_t written = sizeof( buffer ) - outBytes;

    if( res == (size_t)-1 || written != 1 )
    {
        return 0;
    }

    out = buffer[0];
    return 1;
}
}  // namespace CUL
#endif  // #if !CUL_USE_WCHAR