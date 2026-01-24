#include "CUL/String/String.hpp"

#if !CUL_USE_WCHAR
    #include "CUL/String/StringUtil.hpp"
    #include "CUL/GenericUtils/SimpleAssert.hpp"
    #include "CUL/STL_IMPORTS/STD_codecvt.hpp"
    #include "CUL/STL_IMPORTS/STD_cwchar.hpp"
    #include "CUL/STL_IMPORTS/STD_locale.hpp"
    #include "CUL/STL_IMPORTS/STD_wctype.hpp"
namespace CUL
{
bool String::contains( const char inArg ) const
{
    return contains( inArg );
}

bool String::contains( const std::string& inArg ) const
{
    return false;
}

bool String::contains( const wchar_t inArg ) const
{
    return false;
}

bool String::contains( const wchar_t* inArg ) const
{
    return false;
}

bool String::contains( const std::wstring& inArg ) const
{
    return false;
}

bool String::equals( const char* arg ) const
{
    return StringUtil::cmp( m_value, arg ) == 0;
}

bool String::equals( const std::string& arg ) const
{
    return StringUtil::cmp( m_value, arg.c_str() ) == 0;
}

bool String::equals( const wchar_t* arg ) const
{
    std::string argStr;
    StringUtil::wideStringToChar( argStr, arg );
    return StringUtil::cmp( m_value, argStr.c_str() ) == 0;
}

bool String::equals( const std::wstring& arg ) const
{
    std::string argStr;
    StringUtil::wideStringToChar( argStr, arg );
    return StringUtil::cmp( m_value, argStr.c_str() ) == 0;
}

std::int32_t String::find( const char* arg ) const
{
    if( arg == nullptr )
    {
        return -1;
    }
    return StringUtil::find( m_value, arg );
}

std::int32_t String::find( char arg ) const
{
    const char word[2] = { arg, '\0' };
    return StringUtil::find( m_value, word );
}

bool String::startsWith( const char* inStr, std::size_t* outInStrLen ) const
{
    return StringUtil::startsWith( m_value, inStr );
}

bool String::startsWith( const wchar_t* inStr, std::size_t* outInStrLen ) const
{
    std::string word;
    StringUtil::wideStringToChar( word, std::wstring( inStr ) );
    return StringUtil::startsWith( m_value, word.c_str() );
}

void String::append( const std::string& inStr )
{
}

void String::append( const wchar_t* inChar )
{
    const auto otherSize = StringUtil::strLen( inChar );

    #if CUL_USE_WCHAR
    const auto otherSizeWithTerminator = static_cast<std::size_t>( otherSize + 1 );
    const std::int32_t newSize = m_size + static_cast<std::int32_t>( otherSizeWithTerminator );
    grow( newSize, true );

    for( std::size_t i = 0; i < otherSizeWithTerminator; ++i )
    {
        m_value[m_size + i] = inChar[i];
    }
    setSize( newSize - 1 );
    #else   // #if CUL_USE_WCHAR
    throw std::logic_error( "Method not implemented" );
    #endif  // #if CUL_USE_WCHAR
    verify();
    deleteTemp();
}

void String::append( wchar_t inChar )
{
    #if CUL_USE_WCHAR
    grow( m_size + 2, true );

    m_value[m_size] = inChar;
    m_value[m_size + 1] = NullTerminator;
    ++m_size;
    #else   // #if CUL_USE_WCHAR
    throw std::logic_error( "Method not implemented" );
    #endif  // #if CUL_USE_WCHAR
    verify();
    deleteTemp();
}

void String::append( char inChar )
{
    const std::int32_t newSize = m_size + 2;
    grow( newSize, true );

    m_value[static_cast<std::size_t>( m_size )] = inChar;
    m_value[static_cast<std::size_t>( m_size + 1 )] = NullTerminator;
    ++m_size;

    verify();
    deleteTemp();
}

void String::append( const char* inChar )
{
    const auto charLength = StringUtil::strLen( inChar );

    const std::int32_t targetSize = m_size + charLength + 1;
    grow( targetSize, true );
    const std::size_t length = static_cast<std::size_t>( charLength );
    for( std::size_t i = 0; i < length; ++i )
    {
        m_value[m_size + i] = inChar[i];
    }
    m_value[m_size + length] = NullTerminator;

    m_size += charLength;
    verify();
    deleteTemp();
}

void String::removeFromStart( const char* inStr )
{
    if( empty() )
    {
        return;
    }

    StringUtil::removeFromStart( m_value, inStr );
    m_size = StringUtil::strLen( m_value );
}

void String::removeFromStart( const wchar_t* inStr )
{
    if( empty() )
    {
        return;
    }
    std::string word;
    StringUtil::wideStringToChar( word, std::wstring( inStr ) );
    StringUtil::removeFromStart( m_value, word.c_str() );
    m_size = StringUtil::strLen( m_value );
}

}  // namespace CUL
#endif  // !CUL_USE_WCHAR