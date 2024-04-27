#pragma once

#include "CUL/CUL.hpp"
#include "STL_IMPORTS/STD_cstdint.hpp"
#include "STL_IMPORTS/STD_string.hpp"
#include "STL_IMPORTS/STD_functional.hpp"

NAMESPACE_BEGIN( CUL )

struct WcharResult
{
    wchar_t* Ptr = nullptr;
    std::int32_t Length = 0;
};

struct CharResult
{
    char* Ptr = nullptr;
    std::int32_t Length = 0;
};

class CULLib_API StringUtil final
{
public:
    static std::int32_t wcharToChar( char* target, std::int32_t targetSize, const wchar_t* source, unsigned int codePage,
                                     std::function<char*( std::int32_t )> tooSmallTargetCallback );
    static std::int32_t charToWchar( wchar_t* target, std::int32_t targetSize, const char* source, unsigned int codePage,
                                     std::function<wchar_t*( std::int32_t )> tooSmallTargetCallback );
    static CharResult wcharToChar( const wchar_t* input, unsigned int codePageIn );
    static WcharResult charToWchar( const char* input, unsigned int codePageIn );

    static std::string wcharToChar( const std::wstring& input, unsigned int codePageIn );
    static std::wstring charToWchar( const std::string& input, unsigned int codePageIn );

    static std::int32_t getLength( const wchar_t* input );
    static std::int32_t getLength( const char* input );

    static std::pair<wchar_t*, std::int32_t> duplicate( const wchar_t* input );
    static std::pair<wchar_t*, std::int32_t> duplicate( const wchar_t* input, std::int32_t strLen );

    static std::pair<char*, std::int32_t> duplicate( const char* input );
    static std::pair<char*, std::int32_t> duplicate( const char* input, std::int32_t strLen );

    static void copy( wchar_t* output, const wchar_t* input );
    static void copy( wchar_t* output, const wchar_t* input, std::int32_t len );

    static void copy( char* output, const char* input );
    static void copy( char* output, const char* input, std::int32_t len );

    template <class T>
    static std::string toChar( T value )
    {
        const std::string valueAsString = std::to_string( value );
        return valueAsString;
    }

    template <class T>
    static std::pair<wchar_t*, std::int32_t> toWchar( T value )
    {
        std::pair<wchar_t*, std::int32_t> result;

        const std::wstring valueAsString = std::to_wstring( value );
        result.second = valueAsString.length();
        result.first = new wchar_t[result.second];
        std::wcscpy( result.first, valueAsString.c_str() );

        return result;
    }

    static float toFloat( const char* input );
    static double toDouble( const char* input );
    static std::uint32_t toUint32( const char* input );
    static std::int32_t toInt32( const char* input );
    static std::uint64_t toUint64( const char* input );
    static std::int64_t toInt64( const char* input );

protected:
private:
};


NAMESPACE_END( CUL )