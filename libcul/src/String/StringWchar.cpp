#include "CUL/String/String.hpp"
#if CUL_USE_WCHAR
    #include "CUL/GenericUtils/SimpleAssert.hpp"
    #include "CUL/String/StringUtil.hpp"
    #include "CUL/STL_IMPORTS/STD_cwchar.hpp"
    #include "CUL/STL_IMPORTS/STD_wctype.hpp"
    #include "CUL/STL_IMPORTS/STD_codecvt.hpp"
    #include "CUL/IMPORT_windows.hpp"

namespace CUL
{
void String::append( char inChar )
{
    std::string str;
    str.push_back( inChar );
    std::wstring toAppend;
    StringUtil::charToWideString( toAppend, str );
    append( toAppend );
    verify();
    deleteTemp();
}

void String::append( const char* inChar )
{
    std::string str( inChar );
    std::wstring toAppend;
    StringUtil::charToWideString( toAppend, str );
    append( toAppend );
    verify();
    deleteTemp();
}

void String::append( const std::string& inStr )
{
    std::wstring toAppend;
    StringUtil::charToWideString( toAppend, inStr );
    append( toAppend );
    verify();
    deleteTemp();
}

void String::append( const std::wstring& inArg )
{
    append( inArg.c_str() );
}

void String::append( const wchar_t* inChar )
{
    const auto otherSize = StringUtil::strLen( inChar );
    const auto otherSizeWithTerminator = static_cast<std::size_t>( otherSize + 1 );
    const std::int32_t newSize = m_size + static_cast<std::int32_t>( otherSizeWithTerminator );
    grow( newSize, true );

    for( std::size_t i = 0; i < otherSizeWithTerminator; ++i )
    {
        m_value[m_size + i] = inChar[i];
    }
    setSize( newSize - 1 );
    verify();
    deleteTemp();
}

void String::append( wchar_t inChar )
{
    grow( m_size + 2, true );
    m_value[m_size] = inChar;
    m_value[m_size + 1] = NullTerminator;
    ++m_size;
    verify();
    deleteTemp();
}

bool String::startsWith( const char* inStr, std::size_t* /*outInStrLen*/ ) const
{
    std::wstring inStrWchar;
    StringUtil::charToWideString( inStrWchar, inStr );
    return StringUtil::startsWith( m_value, inStrWchar.c_str() );
}

bool String::startsWith( const wchar_t* inStr, std::size_t* /*outInStrLen*/ ) const
{
    return StringUtil::startsWith( m_value, inStr );
}

bool String::contains( const char inArg ) const
{
    const wchar_t targetChar = StringUtil::toWideChar( inArg );
    return contains( targetChar );
}

bool String::contains( const std::string& inArg ) const
{
    const std::wstring argStr = StringUtil::toWideString( inArg );
    return contains( argStr );
}

bool String::contains( const wchar_t inArg ) const
{
    const std::wstring word( 1, inArg );
    return StringUtil::find( m_value, word ) != -1;
}

bool String::contains( const wchar_t* inArg ) const
{
    return StringUtil::find( m_value, inArg ) != -1;
}

bool String::contains( const std::wstring& inArg ) const
{
    return StringUtil::find( m_value, inArg ) != -1;
}

std::int32_t String::find( const char* inArg ) const
{
    const std::wstring word = StringUtil::toWideString( inArg );
    return StringUtil::find( m_value, word );
}

std::int32_t String::find( const std::string& inArg ) const
{
    const std::wstring word = StringUtil::toWideString( inArg );
    return StringUtil::find( m_value, word );
}

std::int32_t String::find( const std::wstring& inArg ) const
{
    return StringUtil::find( m_value, inArg );
}

std::int32_t String::find( const wchar_t inArg ) const
{
    std::wstring word( 1, inArg );
    return StringUtil::find( m_value, word );
}

std::int32_t String::find( const wchar_t* inArg ) const
{
    return StringUtil::find( m_value, inArg );
}

std::int32_t String::find( const char inChar ) const
{
    std::string str;
    str.push_back( inChar );
    std::wstring toBeFound;
    StringUtil::charToWideString( toBeFound, str );

    return StringUtil::find( m_value, toBeFound.c_str() );
}

void String::removeFromStart( const char* inStr )
{
    std::wstring inStrWchar;
    StringUtil::charToWideString( inStrWchar, inStr );
    StringUtil::removeFromStart( m_value, inStrWchar.c_str() );
    m_size = StringUtil::strLen( m_value );
}

void String::removeFromStart( const wchar_t* inStr )
{
    StringUtil::removeFromStart( m_value, inStr );
    m_size = StringUtil::strLen( m_value );
}

bool String::equals( const char* arg ) const
{
    std::wstring argStr;
    StringUtil::charToWideString( argStr, arg );
    return StringUtil::cmp( m_value, argStr.c_str() ) == 0;
}

bool String::equals( const std::string& arg ) const
{
    std::wstring argStr;
    StringUtil::charToWideString( argStr, arg );
    return StringUtil::cmp( m_value, argStr.c_str() ) == 0;
}

bool String::equals( const wchar_t* arg ) const
{
    return StringUtil::cmp( m_value, arg ) == 0;
}

bool String::equals( const std::wstring& arg ) const
{
    return StringUtil::cmp( m_value, arg.c_str() ) == 0;
}

}  // namespace CUL
#endif  // #if CUL_USE_WCHAR