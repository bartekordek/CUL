#pragma once

#include "CUL/CUL.hpp"
#include "CUL/STL_IMPORTS/STD_inttypes.hpp"
#include "CUL/STL_IMPORTS/STD_array.hpp"
#include "CUL/STL_IMPORTS/STD_optional.hpp"
#include "CUL/STL_IMPORTS/STD_string.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"

namespace CUL
{
 #if CUL_USE_WCHAR
 constexpr decltype( std::wstring::npos ) StringUtilNpos{ std::wstring::npos };
 #else   // #if CUL_USE_WCHAR
 constexpr decltype( std::string::npos ) StringUtilNpos{ std::string::npos };
 #endif  // #if CUL_USE_WCHAR

class CULLib_API StringUtil
{
public:
    static void valueToHex( std::uint16_t inValue, std::array<std::uint8_t, 2>& outValue );
    static void valueToHex( std::uint8_t inValue, std::uint8_t& outValue );
    static std::uint16_t hexToValue( std::uint16_t inValue );
    static void valueToHex( char in, std::array<char, 2>& outValue );
    static void valueToHex( std::uint8_t in, std::array<uint8_t, 2>& outValue );
    static std::uint8_t hexToValue( const std::array<uint8_t, 2>& in );
    static std::uint8_t hexToValue( std::uint8_t in );
    static std::uint8_t charToValue( std::uint8_t in );

    static bool isNumber( const char* inNumber );
    static bool isNumber( const char* inNumber, std::size_t inSize );

    static bool isNumber( const wchar_t* inNumber );
    static bool isNumber( const wchar_t* inNumber, std::size_t inSize );

    static std::int32_t strLen( const char* inString );
    static std::int32_t strLen( const wchar_t* inString );

    static std::uint64_t strToUint64( const std::wstring& inString );
    static std::uint64_t strToUint64( const std::string& inString );

    static std::size_t replaceCalculateRequiredSize( const char* source, const char* inWhat, const char* inFor, bool allOccurences );
    static std::size_t replaceCalculateRequiredSize( const wchar_t* source, const wchar_t* inWhat, const wchar_t* inFor,
                                                     bool allOccurences );
    static bool replace( char* inSource, const char inWhat, const char inFor, bool allOccurences );
    static bool replace( wchar_t* inSource, const wchar_t inWhat, const wchar_t inFor, bool allOccurences );
    static bool replace( char* inSource, std::size_t inSourceSize, const char* inWhat, const char* inFor, bool allOccurences );
    static bool replace( wchar_t* inSource, std::size_t inSourceSize, const wchar_t* inWhat, const wchar_t* inFor, bool allOccurences );

    static std::int32_t wideStringToChar( char* out, std::int32_t outSize, const wchar_t* in );
    static std::int32_t wideStringToChar( char* out, std::int32_t outSize, const wchar_t* in, std::int32_t inSize );
    static std::int32_t wideStringToChar( char& out, wchar_t in );
    static std::int32_t wideStringToChar( std::string& out, const std::wstring& in );

    static std::int32_t charToWideString( std::int32_t codePage, wchar_t* out, std::int32_t outSize, const char* in );
    static std::int32_t charToWideString( std::int32_t codePage, wchar_t* out, std::int32_t outSize, const char* in, std::int32_t inSize );
    static std::int32_t charToWideString( std::int32_t codePage, wchar_t& out, char in );
    static std::int32_t charToWideString( std::wstring& out, const std::string& in );

    static char toChar( wchar_t inChar);
    static std::string toSTDstring( const std::wstring& inArg );
    static wchar_t toWideChar( char inChar );
    static std::wstring toWideString( const std::string& inArg );

    static void copyString( char* target, const char* source );
    static void copyString( char* target, std::int32_t targetSize, const char* source, std::int32_t sourceSize );
    static void copyString( wchar_t* target, const wchar_t* source );
    static void copyString( wchar_t* target, std::int32_t targetSize, const wchar_t* source, std::int32_t sourceSize );

    static std::int32_t cmp( const char* s1, const char* s2 );
    static bool equals( const char* s1, const char* s2, std::size_t length );
    static std::int32_t cmp( const wchar_t* s1, const wchar_t* s2 );
    static bool equals( const wchar_t* s1, const wchar_t* s2, std::size_t length );

    static const char* strStr( const char* left, const char* right );
    static const wchar_t* strStr( const wchar_t* left, const wchar_t* right );

    static void removeFromStart( wchar_t* inOutSource, const wchar_t* inStr );
    static void removeFromStart( char* inOutSource, const char* inStr );

    static bool startsWith( const char* inSource, const char* inArg );
    static bool startsWith( const wchar_t* inSource, const wchar_t* inArg );

    static void toLower( char* inOut );
    static void toLower( char* inOut, std::int32_t size );

    static void toLower( wchar_t* inOut );
    static void toLower( wchar_t* inOut, std::int32_t size );

    static void toUpper( char* inOut );
    static void toUpper( char* inOut, std::int32_t size );

    static void toUpper( wchar_t* inOut );
    static void toUpper( wchar_t* inOut, std::int32_t size );

    static std::optional<float> toFloat( const char* inArg );
    static std::optional<float> toFloat( const wchar_t* inArg );
    static std::optional<float> toFloat( const std::string& inArg );
    static std::optional<float> toFloat( const std::wstring& inArg );

    static void removeAll( char* inOut, char toRemove );
    static void removeAll( char* inOut, wchar_t toRemove );
    static void removeAll( wchar_t* inOut, wchar_t toRemove );
    static void removeAll( wchar_t* inOut, char toRemove );

    static void erase( wchar_t* inOut, std::int32_t index, std::int32_t length );
    static void erase( char* inOut, std::int32_t index, std::int32_t length );

    static std::int32_t find( const wchar_t* source, const char* word );
    static std::int32_t find( const wchar_t* source, const wchar_t* word );
    static std::int32_t find( const char* source, const wchar_t* word );
    static std::int32_t find( const char* source, const char* word );
    static std::int32_t find( const std::wstring& source, const std::wstring word );
    static std::int32_t find( const std::string& source, const std::string& word );

    static std::vector<std::string> split( const std::string& input, const std::string& delimiter );
    static std::vector<std::string> split( const std::string& input, const std::wstring& delimiter );

    static std::vector<std::string> split( const std::string& input, char delimiter );
    static std::vector<std::string> split( const std::string& input, wchar_t delimiter );

    static std::vector<std::wstring> split( const std::wstring& input, const std::string& delimiter );
    static std::vector<std::wstring> split( const std::wstring& input, const std::wstring& delimiter );

    static std::vector<std::wstring> split( const std::wstring& input, char delimiter );
    static std::vector<std::wstring> split( const std::wstring& input, wchar_t delimiter );

    static char* strdup( const char* source );

protected:
private:
};
}