#include "CUL/StringUtil.hpp"
#include "CUL/STL_IMPORTS/STD_clocale.hpp"
#include "CUL/STL_IMPORTS/STD_codecvt.hpp"
#include "CUL/STL_IMPORTS/STD_cstdlib.hpp"
#include "CUL/STL_IMPORTS/STD_cstdlib.hpp"
#include "CUL/STL_IMPORTS/STD_string.hpp"
#include "CUL/STL_IMPORTS/STD_codecvt.hpp"

#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/IMPORT_stringapiset.hpp"


NAMESPACE_BEGIN( CUL )

CharResult StringUtil::wcharToChar( const wchar_t* input, unsigned int codePageIn )
{
    CharResult result;
    result.Length = getLength( input );

    if( result.Length == 0 )
    {
        return result;
    }

#if defined(_MSC_VER)
    unsigned int codePage = CP_ACP;
    DWORD dwFlags = WC_COMPOSITECHECK;
    result.Length = WideCharToMultiByte( codePage, dwFlags, input, result.Length, NULL, 0, NULL, NULL );
    result.Ptr = new char[result.Length];
    WideCharToMultiByte( codePage, dwFlags, input, result.Length, result.Ptr, result.Length, NULL, NULL );
#else
    std::string s( wstr.begin(), wstr.end() );
    return s;
    // std::wstring str = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(wstr);
#endif
    return result;
}

WcharResult StringUtil::charToWchar( const char* input, unsigned int codePageIn )
{
    WcharResult result;
    result.Length = getLength( input );

    if( result.Length == 0 )
    {
        return result;
    }

#if defined( _MSC_VER )
    UINT codePage = codePageIn;
    DWORD dwFlags = 0;
    int cbMultiByte = -1;
    result.Length = MultiByteToWideChar( codePage, dwFlags, input, cbMultiByte, NULL, 0 );
    result.Ptr = new wchar_t[result.Length];
    MultiByteToWideChar( codePage, dwFlags, input, cbMultiByte, result.Ptr, result.Length );
#else
    std::string inCurLocale = setlocale( LC_ALL, "" );
    const char* _Source = str.c_str();
    size_t _Dsize = mbstowcs( NULL, _Source, 0 ) + 1;
    wchar_t* _Dest = new wchar_t[_Dsize];
    wmemset( _Dest, 0, _Dsize );
    mbstowcs( _Dest, _Source, _Dsize );
    std::wstring result = _Dest;
    delete[] _Dest;
    setlocale( LC_ALL, inCurLocale.c_str() );
    return result;
#endif

    return result;
}

std::string StringUtil::wcharToChar( const std::wstring& input, unsigned int codePageIn )
{
    std::string result;

    if( input.empty() )
    {
        return result;
    }

#if defined( _MSC_VER )
    unsigned int codePage = CP_ACP;
    DWORD dwFlags = WC_COMPOSITECHECK;
    int targetSize = WideCharToMultiByte( codePage, dwFlags, input.c_str(), input.size(), NULL, 0, NULL, NULL );
    result.resize( targetSize );
    WideCharToMultiByte( codePage, dwFlags, input.c_str(), targetSize, result.data(), targetSize, NULL, NULL );
#else
    std::string s( wstr.begin(), wstr.end() );
    return s;
    // std::wstring str = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(wstr);
#endif
    return result;
}

std::int32_t StringUtil::wcharToChar( char* target, std::int32_t targetSize, const wchar_t* source, unsigned int codePage,
                        std::function<char* (std::int32_t)> tooSmallTargetCallback)
{
    // codePage CP_ACP
    std::int32_t resultSize = StringUtil::getLength( source );

    if( resultSize == 0u )
    {
        return resultSize;
    }

    if( targetSize < resultSize )
    {
        target = tooSmallTargetCallback( resultSize );
    }

#if defined( _MSC_VER )
    DWORD dwFlags = WC_COMPOSITECHECK;
    const std::int32_t newSize = WideCharToMultiByte( codePage, dwFlags, source, resultSize, nullptr, 0, nullptr, nullptr );

    if( newSize > resultSize )
    {
        target = tooSmallTargetCallback( resultSize );
        resultSize = newSize;
    }

    WideCharToMultiByte( codePage, dwFlags, source, newSize, target, newSize, nullptr, nullptr );
#else
    throw std::logic_error( "Method not implemented" );
#endif
}

std::wstring StringUtil::charToWchar( const std::string& input, unsigned int codePageIn )
{
    std::wstring result;

    if( input.empty() )
    {
        return result;
    }

#if defined( _MSC_VER )
    UINT codePage = codePageIn;
    DWORD dwFlags = 0;
    int cbMultiByte = -1;
    int targetSize = MultiByteToWideChar( codePage, dwFlags, input.c_str(), cbMultiByte, NULL, 0 );
    result.resize( targetSize );
    MultiByteToWideChar( codePage, dwFlags, input.c_str(), cbMultiByte, result.data(), targetSize );
#else
    std::string inCurLocale = setlocale( LC_ALL, "" );
    const char* _Source = str.c_str();
    size_t _Dsize = mbstowcs( NULL, _Source, 0 ) + 1;
    wchar_t* _Dest = new wchar_t[_Dsize];
    wmemset( _Dest, 0, _Dsize );
    mbstowcs( _Dest, _Source, _Dsize );
    std::wstring result = _Dest;
    delete[] _Dest;
    setlocale( LC_ALL, inCurLocale.c_str() );
#endif

    return result;
}

std::int32_t StringUtil::charToWchar( wchar_t* output, std::int32_t targetSize, const char* input, unsigned int codePage,
                                    std::function<wchar_t* (std::int32_t)> tooSmallTargetCallback)
{
    std::int32_t resultSize = StringUtil::getLength( input );
    if( resultSize == 0u )
    {
        return resultSize;
    }

    if( resultSize > targetSize )
    {
        output = tooSmallTargetCallback( resultSize );
    }

#if defined( _MSC_VER )
    DWORD dwFlags = 0;
    int cbMultiByte = -1;
    resultSize = MultiByteToWideChar( codePage, dwFlags, input, cbMultiByte, nullptr, 0 );

    if( resultSize > targetSize )
    {
        output = tooSmallTargetCallback( resultSize );
    }

    MultiByteToWideChar( codePage, dwFlags, input, cbMultiByte, output, resultSize );
#else
    std::string inCurLocale = setlocale( LC_ALL, "" );
    size_t _Dsize = mbstowcs( NULL, input, 0 ) + 1;
    result.first = new wchar_t[result.second];
    wmemset( result.first, 0, result.second );
    mbstowcs( result.first, input, result.second );
    setlocale( LC_ALL, inCurLocale.c_str() );
#endif
    return resultSize;
}

std::int32_t StringUtil::getLength( const wchar_t* input )
{
    return std::wcslen( input );
}

std::int32_t StringUtil::getLength( const char* input )
{
    return std::strlen( input );
}

std::pair<wchar_t*, std::int32_t> StringUtil::duplicate( const wchar_t* input )
{
    const std::int32_t strLen = std::wcslen( input );
    return duplicate( input, strLen );
}

std::pair<wchar_t*, std::int32_t> StringUtil::duplicate( const wchar_t* input, std::int32_t strLen )
{
    std::pair<wchar_t*, std::int32_t> result;

    if( input )
    {
        result.second = std::wcslen( input );
        std::wcscpy( result.first, input );
    }

    return result;
}

std::pair<char*, std::int32_t> StringUtil::duplicate( const char* input )
{
    if( input == nullptr )
    {
        return std::pair<char*, std::int32_t>();
    }

    const std::int32_t strLen = std::strlen( input );
    return duplicate( input, strLen );
}

std::pair<char*, std::int32_t> StringUtil::duplicate( const char* input, std::int32_t strLen )
{
    std::pair<char*, std::int32_t> result;

    if( input == nullptr )
    {
        return result;
    }

    result.second = std::strlen( input );

    if( result.second > 0 )
    {
        result.first = new char[result.second + 1];
        std::strcpy( result.first, input );
    }

    return result;
}


void StringUtil::copy( wchar_t* output, const wchar_t* input )
{
    std::wcscpy( output, input );
}

void StringUtil::copy( char* output, const char* input )
{
    std::strcpy( output, input );
}

void StringUtil::copy( wchar_t* output, const wchar_t* input, std::int32_t len )
{
    for( std::int32_t i = 0u; i < len; ++i )
    {
        output[i] = input[i];
    }
}

void StringUtil::copy( char* output, const char* input, std::int32_t len )
{
    for( std::int32_t i = 0u; i < len; ++i )
    {
        output[i] = input[i];
    }
}

float StringUtil::toFloat( const char* input )
{
    return std::stof( input );
}

double StringUtil::toDouble( const char* input )
{
    return std::stod( input );
}

std::uint32_t StringUtil::toUint32( const char* input )
{
    const auto so32 = sizeof( std::uint32_t );
    const auto soul = sizeof( unsigned long );
    return std::stoul( input );
}

std::int32_t StringUtil::toInt32( const char* input )
{
    return std::stoi( input );
}

std::uint64_t StringUtil::toUint64( const char* input )
{
    const auto so32 = sizeof( std::uint64_t );
    const auto soul = sizeof( unsigned long long );
    return std::stoull( input );
}

std::int64_t StringUtil::toInt64( const char* input )
{
    return std::stoi( input );
}

NAMESPACE_END( CUL )