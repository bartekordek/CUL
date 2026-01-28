#include "CUL/String/StringUtil.hpp"

#if CUL_USE_WCHAR
    #include "CUL/STL_IMPORTS/STD_codecvt.hpp"
    #include "CUL/STL_IMPORTS/STD_cwchar.hpp"
    #include "CUL/STL_IMPORTS/STD_wctype.hpp"
    #include "CUL/IMPORT_windows.hpp"
    #include "CUL/GenericUtils/SimpleAssert.hpp"

namespace CUL
{
std::int32_t StringUtil::wideStringToChar( std::string& out, const std::wstring& inChar )
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converterX;
    out = converterX.to_bytes( inChar );
    return static_cast<std::int32_t>( out.size() );
}

std::int32_t StringUtil::charToWideString( std::int32_t codePage, wchar_t* out, std::int32_t outSize, const char* in )
{
    return charToWideString( codePage, out, outSize, in, static_cast<std::int32_t>( std::strlen( in ) ) );
}

std::int32_t StringUtil::charToWideString( std::int32_t codePage, wchar_t& out, char in )
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;
    const std::wstring stringCpy = converterX.from_bytes( in );
    const std::int32_t result = (std::int32_t)stringCpy.size();
    if( result == 1 )
    {
        out = stringCpy[0];
        return 1;
    }

    CUL::Assert::simple( false, "Conversion failed!" );
    return -1;
}

std::int32_t StringUtil::charToWideString( std::wstring& out, const std::string& in )
{
    const std::size_t bufferSize = in.size() * 2u;
    std::vector<wchar_t> buffer;
    buffer.resize( bufferSize );

    const auto resultSize = charToWideString( CP_ACP, buffer.data(), bufferSize, in.c_str(), in.size() );
    out = buffer.data();
    return static_cast<std::int32_t>( resultSize );
}

const char* StringUtil::strStr( const char* left, const char* right )
{
    return std::strstr( left, right );
}

const wchar_t* StringUtil::strStr( const wchar_t* left, const wchar_t* right )
{
    return std::wcsstr( left, right );
}


void StringUtil::removeAll( wchar_t* inOut, wchar_t toRemove )
{
    if( !inOut )
    {
        return;
    }

    wchar_t word[2] = { toRemove, L'\0' };

    std::int32_t pos = find( inOut, word );
    while( pos != -1 )
    {
        erase( inOut, pos, 1 );
        pos = find( inOut, word );
    }
}

void StringUtil::erase( wchar_t* inOut, std::int32_t index, std::int32_t length )
{
    if( inOut == nullptr )
    {
        return;
    }

    const std::int32_t wordLen = strLen( inOut );
    const std::int32_t newEnd = wordLen - length;
    const std::int32_t stop = index + length;
    for( std::int32_t i = index; i < wordLen; ++i )
    {
        if( ( i >= index ) && ( i < newEnd ) )
        {
            inOut[i] = inOut[i + length];
        }
        else
        {
            inOut[i] = NullTerminator;
        }
    }
}

// TODO: make this function template
void StringUtil::erase( char* inOut, std::int32_t index, std::int32_t length )
{
    if( inOut == nullptr )
    {
        return;
    }

    const std::int32_t wordLen = strLen( inOut );
    const std::int32_t newEnd = wordLen - length;
    const std::int32_t stop = index + length;
    for( std::int32_t i = index; i < wordLen; ++i )
    {
        if( ( i >= index ) && ( i < newEnd ) )
        {
            inOut[i] = inOut[i + index];
        }
        else
        {
            inOut[i] = NullTerminator;
        }
    }
}

char StringUtil::toChar( wchar_t inChar )
{
    std::wstring inputChar;
    inputChar.push_back( inChar );

    std::string resultStr( 4, '\0' );
    wideStringToChar( resultStr, inputChar );

    return resultStr[0];
}

wchar_t StringUtil::toWideChar( char inChar )
{
    std::string inputChar;
    inputChar.push_back( inChar );

    std::wstring resultStr( 4, L'\0' );
    charToWideString( resultStr, inputChar );

    return resultStr[0];
}

std::int32_t StringUtil::wideStringToChar( char* out, std::int32_t /*outSize*/, const wchar_t* inChar, std::int32_t inSize )
{
    UINT codePage = CP_ACP;
    DWORD dwFlags = WC_COMPOSITECHECK;
    const int sizeNeeded = WideCharToMultiByte( codePage, dwFlags, inChar, inSize + 1, NULL, 0, NULL, NULL );

    const auto convertedLength = WideCharToMultiByte( codePage, dwFlags, inChar, inSize + 1, out, sizeNeeded, NULL, NULL );

    return convertedLength;
}

std::int32_t StringUtil::wideStringToChar( char& inOut, wchar_t inChar )
{
    UINT codePage = CP_ACP;
    DWORD dwFlags = WC_COMPOSITECHECK;
    const int sizeNeeded = WideCharToMultiByte( codePage, dwFlags, &inChar, 1, NULL, 0, NULL, NULL );

    char result[4];
    const auto convertedLength = WideCharToMultiByte( codePage, dwFlags, &inChar, 1, &result[0], sizeNeeded, NULL, NULL );

    inOut = result[0];

    return convertedLength;
}

std::int32_t StringUtil::charToWideString( std::int32_t codePage, wchar_t* out, std::int32_t outSize, const char* in, std::int32_t inSize )
{
    Assert::simple( outSize >= inSize, "NOT ENOUGH PLACE FOR STRING" );

    const int size_needed = MultiByteToWideChar( static_cast<UINT>( codePage ),
                                                 0,       // flags
                                                 in,      // from
                                                 inSize,  // from byte count
                                                 NULL,    // to
                                                 0 );     // to char count
    std::wstring result( static_cast<std::size_t>( size_needed ), 0 );
    const std::int32_t resultSize = MultiByteToWideChar( static_cast<UINT>( codePage ),
                                                         0,                                    // flags
                                                         in,                                   // from
                                                         inSize,                               // from byte count
                                                         result.data(),                        // to
                                                         static_cast<int>( result.size() ) );  // to char count

    copyString( out, outSize, result.data(), resultSize + 1 );
    return resultSize;
}
}  // namespace CUL
#endif  // #if CUL_USE_WCHAR