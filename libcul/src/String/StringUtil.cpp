#include "CUL/String/StringUtil.hpp"
#include "CUL/STL_IMPORTS/STD_codecvt.hpp"
#include "CUL/STL_IMPORTS/STD_cwchar.hpp"
#include "CUL/STL_IMPORTS/STD_wctype.hpp"
#include "CUL/STL_IMPORTS/STD_string.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"

namespace CUL
{
void StringUtil::toLower( char* inOut )
{
    toLower( inOut, StringUtil::strLen( inOut ) );
}

void StringUtil::toLower( char* inOut, std::int32_t size )
{
    for( std::int32_t i = 0; i < size; ++i )
    {
        inOut[i] = static_cast<char>( std::tolower( inOut[i] ) );
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

        std::optional<float> StringUtil::toFloat( const char* inArg )
        {
            return std::optional<float>();
        }
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

}
std::optional<float> StringUtil::toFloat( const wchar_t* inArg )
{
}
std::optional<float> StringUtil::toFloat( const std::string& inArg )
{
}
std::optional<float> StringUtil::toFloat( const std::wstring& inArg )
{
}
}