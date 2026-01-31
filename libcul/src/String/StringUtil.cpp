#include "CUL/String/StringUtil.hpp"

#include "CUL/GenericUtils/SimpleAssert.hpp"

#include "CUL/STL_IMPORTS/STD_charconv.hpp"
#include "CUL/STL_IMPORTS/STD_cmath.hpp"
#include "CUL/STL_IMPORTS/STD_codecvt.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"
#include "CUL/STL_IMPORTS/STD_cwchar.hpp"
#include "CUL/STL_IMPORTS/STD_exception.hpp"
#include "CUL/STL_IMPORTS/STD_string.hpp"
#include "CUL/STL_IMPORTS/STD_wctype.hpp"

namespace CUL
{
void StringUtil::toLower( char* inOut )
{
    toLower( inOut, StringUtil::strLen( inOut ) );
}

void StringUtil::toLower( char* inOut, std::int32_t size )
{
    if( !inOut || size <= 0 )
    {
        return;
    }

    for( std::int32_t i = 0; i < size && inOut[i] != '\0'; ++i )
    {
        char c = inOut[i];

        if( c >= 'A' && c <= 'Z' )
        {
            inOut[i] = static_cast<char>( c + ( 'a' - 'A' ) );
        }
    }
}

void StringUtil::toLower( wchar_t* inOut )
{
    toLower( inOut, StringUtil::strLen( inOut ) );
}

void StringUtil::toLower( wchar_t* inOut, std::int32_t size )
{
    for( std::int32_t i = 0; i < size; ++i )
    {
        inOut[i] = towlower( inOut[i] );
    }
}

std::string CUL::StringUtil::toSTDstring( const std::wstring& inArg )
{
    std::string result;
    wideStringToChar( result, inArg );
    return result;
}

std::wstring CUL::StringUtil::toWideString( const std::string& inArg )
{
    std::wstring result;
    charToWideString( result, inArg );
    return result;
}

void StringUtil::removeFromStart( char* inOutSource, const char* inStr )
{
    if( !inOutSource || !inStr )
    {
        return;
    }

    const std::size_t lenStr = strLen( inStr );

    if( lenStr == 0 )
    {
        return;
    }

    // Check if inOutSource starts with inStr
    if( std::strncmp( inOutSource, inStr, lenStr ) != 0 )
    {
        return;
    }

    // Shift string left (overlap-safe)
    std::memmove( inOutSource, inOutSource + lenStr,
                  strLen( inOutSource + lenStr ) + 1  // include '\0'
    );
}

char* StringUtil::strdup( const char* source )
{
    if( !source )
    {
        return nullptr;
    }

    const std::size_t len = strlen( source ) + 1;
    char* copy = (char*)malloc( len );
    if( !copy )
    {
        return nullptr;
    }

    std::strcpy( copy, source );
    return copy;
}

void StringUtil::removeFromStart( wchar_t* inOutSource, const wchar_t* inStr )
{
    if( !inOutSource || !inStr )
    {
        return;
    }

    const std::size_t lenStr = std::wcslen( inStr );

    if( lenStr == 0 )
    {
        return;
    }

    // Check if inOutSource starts with inStr
    if( std::wcsncmp( inOutSource, inStr, lenStr ) != 0 )
    {
        return;
    }

    // Shift string left (overlap-safe)
    std::wmemmove( inOutSource, inOutSource + lenStr,
                   std::wcslen( inOutSource + lenStr ) + 1  // include L'\0'
    );
}

std::vector<std::string> StringUtil::split( const std::string& input, char delimiter )
{
    std::vector<std::string> result;
    std::size_t start = 0;

    for( std::size_t i = 0; i <= input.size(); ++i )
    {
        if( i == input.size() || input[i] == delimiter )
        {
            result.emplace_back( input.substr( start, i - start ) );
            start = i + 1;
        }
    }

    return result;
}

std::vector<std::string> StringUtil::split( const std::string& input, wchar_t delimiter )
{
    std::wstring delim;
    delim.push_back( delimiter );
    std::string delimStr;
    StringUtil::wideStringToChar( delimStr, delim );
    return split( input, delimStr );
}

std::int32_t StringUtil::wideStringToChar( char* out, std::int32_t outSize, const wchar_t* in )
{
    return wideStringToChar( out, outSize, in, StringUtil::strLen( in ) );
}
std::vector<std::string> StringUtil::split( const std::string& input, const std::string& delimiter )
{
    std::vector<std::string> result;

    // Edge case: empty delimiter
    if( delimiter.empty() )
    {
        result.push_back( input );
        return result;
    }

    std::size_t pos = 0;
    std::size_t found;

    while( ( found = input.find( delimiter, pos ) ) != std::string::npos )
    {
        result.emplace_back( input.substr( pos, found - pos ) );
        pos = found + delimiter.size();
    }

    // Add the remaining part
    result.emplace_back( input.substr( pos ) );

    return result;
}

std::vector<std::string> StringUtil::split( const std::string& input, const std::wstring& delimiter )
{
    std::vector<std::string> result;

    std::string delim;
    StringUtil::wideStringToChar( delim, delimiter );

    std::size_t pos = 0, found;
    while( ( found = input.find( delim, pos ) ) != std::string::npos )
    {
        result.emplace_back( input.substr( pos, found - pos ) );
        pos = found + delim.size();
    }

    result.emplace_back( input.substr( pos ) );
    return result;
}

std::vector<std::wstring> StringUtil::split( const std::wstring& input, char delimiter )
{
    std::string delim;
    delim.push_back( delimiter );
    std::wstring delimW;
    StringUtil::charToWideString( delimW, delim );
    return split( input, delimW );
}

std::vector<std::wstring> StringUtil::split( const std::wstring& input, wchar_t delimiter )
{
    std::vector<std::wstring> result;
    std::size_t start = 0;

    for( std::size_t i = 0; i <= input.size(); ++i )
    {
        if( i == input.size() || input[i] == delimiter )
        {
            result.emplace_back( input.substr( start, i - start ) );
            start = i + 1;
        }
    }

    return result;
}

std::vector<std::wstring> StringUtil::split( const std::wstring& input, const std::string& delimiter )
{
    std::vector<std::wstring> result;

    std::wstring delim;
    StringUtil::charToWideString( delim, delimiter );

    std::size_t pos = 0, found;
    while( ( found = input.find( delim, pos ) ) != std::wstring::npos )
    {
        result.emplace_back( input.substr( pos, found - pos ) );
        pos = found + delim.size();
    }

    result.emplace_back( input.substr( pos ) );
    return result;
}

std::vector<std::wstring> StringUtil::split( const std::wstring& input, const std::wstring& delimiter )
{
    std::vector<std::wstring> result;

    if( delimiter.empty() )
    {
        result.push_back( input );
        return result;
    }

    std::size_t pos = 0, found;
    while( ( found = input.find( delimiter, pos ) ) != std::wstring::npos )
    {
        result.emplace_back( input.substr( pos, found - pos ) );
        pos = found + delimiter.size();
    }

    result.emplace_back( input.substr( pos ) );
    return result;
}

std::int32_t StringUtil::find( const wchar_t* source, const char* word )
{
    if( !source || !word )
    {
        return -1;
    }

    std::mbstate_t state{};
    const char* src = word;
    std::wstring wword;

    wchar_t wc;
    while( std::mbrtowc( &wc, src, MB_CUR_MAX, &state ) > 0 )
    {
        wword.push_back( wc );
        src += std::mbrlen( src, MB_CUR_MAX, &state );
    }

    const wchar_t* pos = std::wcsstr( source, wword.c_str() );
    if( !pos )
    {
        return -1;
    }

    return static_cast<std::int32_t>( pos - source );
}

std::int32_t StringUtil::find( const wchar_t* source, const wchar_t* word )
{
    if( !source || !word )
    {
        return -1;
    }

    if( *word == L'\0' )
    {
        return 0;  // empty word matches at start
    }

    const wchar_t* pos = std::wcsstr( source, word );
    if( !pos )
    {
        return -1;
    }

    return static_cast<std::int32_t>( pos - source );
}

std::int32_t StringUtil::find( const char* source, const wchar_t* word )
{
    if( !source || !word )
    {
        return -1;
    }

    std::mbstate_t state{};
    const char* s = source;
    std::wstring wsource;

    wchar_t wc;
    std::size_t len;

    while( ( len = std::mbrtowc( &wc, s, MB_CUR_MAX, &state ) ) > 0 )
    {
        wsource.push_back( wc );
        s += len;
    }

    const wchar_t* pos = std::wcsstr( wsource.c_str(), word );
    if( !pos )
    {
        return -1;
    }

    return static_cast<std::int32_t>( pos - wsource.c_str() );
}

std::int32_t StringUtil::find( const char* source, const char* word )
{
    if( !source || !word )
    {
        return -1;
    }

    if( *word == '\0' )
    {
        return 0;  // empty word matches at start
    }

    const char* pos = std::strstr( source, word );
    if( !pos )
    {
        return -1;
    }

    return static_cast<std::int32_t>( pos - source );
}

std::int32_t StringUtil::find( const std::wstring& source, const std::wstring word )
{
    if( word.empty() )
    {
        return 0;
    }

    const std::size_t pos = source.find( word );
    if( pos == std::wstring::npos )
    {
        return -1;
    }

    return static_cast<std::int32_t>( pos );
}

std::int32_t StringUtil::find( const std::string& source, const std::string& word )
{
    if( word.empty() )
    {
        return 0;
    }

    const std::size_t pos = source.find( word );
    if( pos == std::string::npos )
    {
        return -1;
    }

    return static_cast<std::int32_t>( pos );
}

void StringUtil::toUpper( char* inOut )
{
    toUpper( inOut, StringUtil::strLen( inOut ) );
}

void StringUtil::toUpper( char* inOut, std::int32_t size )
{
    if( !inOut || size <= 0 )
    {
        return;
    }

    for( std::int32_t i = 0; i < size && inOut[i] != '\0'; ++i )
    {
        // cast to unsigned char is REQUIRED to avoid UB
        inOut[i] = static_cast<char>( std::toupper( static_cast<unsigned char>( inOut[i] ) ) );
    }
}

void StringUtil::toUpper( wchar_t* inOut )
{
    toUpper( inOut, StringUtil::strLen( inOut ) );
}

void StringUtil::toUpper( wchar_t* inOut, std::int32_t size )
{
    if( !inOut || size <= 0 )
    {
        return;
    }

    for( std::int32_t i = 0; i < size && inOut[i] != L'\0'; ++i )
    {
        inOut[i] = std::towupper( inOut[i] );
    }
}
std::optional<float> StringUtil::toFloat( const char* inArg )
{
    if( !isFloat( inArg ) )
    {
        return std::nullopt;
    }

#if defined( __GNUC__ ) && !defined( __clang__ )

    char* end = nullptr;
    double v = std::strtod( inArg, &end );
    return static_cast<float>( v );

#else

    size_t len = std::strlen( inArg );

    float value{};
    auto [ptr, ec] = std::from_chars( inArg, inArg + len, value );

    if( ec != std::errc{} )
    {
        return std::nullopt;
    }

    return value;

#endif
}

bool StringUtil::equals( const char* s1, const char* s2, std::size_t length )
{
    for( std::size_t i = 0u; i < length; ++i )
    {
        if( s1[i] != s2[i] )
        {
            return false;
        }
    }

    return true;
}

bool StringUtil::equals( const wchar_t* s1, const wchar_t* s2, std::size_t length )
{
    for( std::size_t i = 0u; i < length; ++i )
    {
        if( s1[i] != s2[i] )
        {
            return false;
        }
    }

    return true;
}
std::optional<float> StringUtil::toFloat( const std::string& inArg )
{
    return toFloat( inArg.c_str() );
}

std::optional<float> StringUtil::toFloat( const std::wstring& inArg )
{
    return toFloat( inArg.c_str() );
}

std::optional<float> StringUtil::toFloat( const wchar_t* inArg )
{
    if( !isFloat( inArg ) )
    {
        return std::nullopt;
    }

    wchar_t* end = nullptr;
    double value = std::wcstod( inArg, &end );

    return static_cast<float>( value );
}

bool StringUtil::isFloat( const char* s )
{
    if( s == nullptr )
    {
        return false;
    }

    if( *s == '\0' )
    {
        return false;
    }

#if defined( __GNUC__ ) && !defined( __clang__ )

    char* end = nullptr;
    std::strtod( s, &end );

    if( end == s )
    {
        return false;
    }

    if( *end != '\0' )
    {
        return false;
    }

    return true;

#else

    size_t len = std::strlen( s );

    double value;
    auto [ptr, ec] = std::from_chars( s, s + len, value );

    if( ec != std::errc{} )
    {
        return false;
    }

    if( ptr != s + len )
    {
        return false;
    }

    return true;

#endif
}

bool StringUtil::isFloat( const wchar_t* s )
{
    if( s == nullptr )
    {
        return false;
    }

    wchar_t* end = nullptr;
    std::wcstod( s, &end );

    if( end == s )
    {
        return false;
    }

    if( *end != L'\0' )
    {
        return false;
    }

    return true;
}

bool StringUtil::isFloat( const std::string& s )
{
    return isFloat( s.c_str() );
}

bool StringUtil::isFloat( const std::wstring& s )
{
    return isFloat( s.c_str() );
}

void StringUtil::fromFloat( std::string& inOutStr, float inValue )
{
    // Handle special values explicitly
    if( std::isnan( inValue ) )
    {
        inOutStr = "nan";
        return;
    }

    if( std::isinf( inValue ) )
    {
        if( inValue > 0.0f )
        {
            inOutStr = "inf";
        }
        else
        {
            inOutStr = "-inf";
        }
        return;
    }

#if defined( __GNUC__ ) && !defined( __clang__ )
    // GCC has no float to_chars � use snprintf (locale independent for C locale)
    char buffer[64];
    int len = std::snprintf( buffer, sizeof( buffer ), "%.9g", inValue );

    if( len < 0 )
    {
        inOutStr.clear();
        return;
    }

    inOutStr.assign( buffer, static_cast<std::size_t>( len ) );

#else
    // MSVC + Clang: fast, exact, no allocations
    char buffer[64];
    auto [ptr, ec] = std::to_chars( buffer, buffer + sizeof( buffer ), inValue, std::chars_format::general );

    if( ec != std::errc{} )
    {
        inOutStr.clear();
        return;
    }

    inOutStr.assign( buffer, ptr );

#endif
}

void StringUtil::fromFloat( std::wstring& inOutStr, float v )
{
    std::string utf8;
    fromFloat( utf8, v );
    charToWideString( inOutStr, utf8 );
}

bool StringUtil::startsWith( const char* inSource, const char* inArg )
{
    if( !inSource || !inArg )
    {
        return false;
    }

    const std::size_t lenArg = std::strlen( inArg );

    if( lenArg == 0 )
    {
        return true;  // empty string is always a prefix
    }

    return std::strncmp( inSource, inArg, lenArg ) == 0;
}

void StringUtil::copyString( char* target, const char* source )
{
    copyString( target, StringUtil::strLen( target ), source, StringUtil::strLen( source ) );
}

void StringUtil::copyString( char* target, std::int32_t targetSize, const char* source, std::int32_t sourceSize )
{
    Assert::simple( targetSize >= sourceSize, "TARGET TOO SMALL!" );
    std::strncpy( target, source, static_cast<std::size_t>( sourceSize + 1 ) );
}

void StringUtil::copyString( wchar_t* target, const wchar_t* source )
{
    copyString( target, StringUtil::strLen( target ), source, StringUtil::strLen( source ) );
}

void StringUtil::copyString( wchar_t* target, std::int32_t targetSize, const wchar_t* source, std::int32_t sourceSizeS )
{
    if( !(targetSize >= sourceSizeS) )
    {
        auto x = 0;
    }

    Assert::simple( targetSize >= sourceSizeS, "TARGET TOO SMALL!" );
    const std::size_t sourceSize = static_cast<std::size_t>( sourceSizeS );
    for( std::size_t i = 0; i < sourceSize; ++i )
    {
        const IString::UnderlyingChar sourceChar = source[i];
        target[i] = sourceChar;
    }
}

bool StringUtil::startsWith( const wchar_t* inSource, const wchar_t* inArg )
{
    if( !inSource || !inArg )
    {
        return false;
    }

    const std::size_t lenArg = std::wcslen( inArg );

    if( lenArg == 0 )
    {
        return true;  // empty string is always a prefix
    }

    return std::wcsncmp( inSource, inArg, lenArg ) == 0;
}

std::int32_t StringUtil::cmp( const char* s1, const char* s2 )
{
    return std::strcmp( s1, s2 );
}

bool StringUtil::equals( const char* s1, const char* s2 )
{
    return cmp( s1, s2 ) == 0;
}

std::int32_t StringUtil::cmp( const wchar_t* s1, const wchar_t* s2 )
{
    return std::wcscmp( s1, s2 );
}

bool StringUtil::equals( const wchar_t* s1, const wchar_t* s2 )
{
    return cmp( s1, s2 ) == 0;
}
}  // namespace CUL