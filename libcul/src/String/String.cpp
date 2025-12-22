#include "CUL/String.hpp"

#include "Filesystem/FSUtils.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/Log/ILogger.hpp"

#include "CUL/STL_IMPORTS/STD_algorithm.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"
#include "CUL/STL_IMPORTS/STD_sstream.hpp"
#include "CUL/STL_IMPORTS/STD_cmath.hpp"
#include "CUL/STL_IMPORTS/STD_wctype.hpp"
#include "CUL/STL_IMPORTS/STD_codecvt.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"
#include "CUL/STL_IMPORTS/STD_cstdarg.hpp"
#include "CUL/STL_IMPORTS/STD_cwchar.hpp"

#define CUL_DEBUG_STRING 0

using namespace CUL;

#if CUL_USE_WCHAR
const std::wstring SingleQuote{ L"'" };
#else
const std::string SingleQuote{ "'" };
#endif

String String::createFromPrintf( const char* msg... )
{
    va_list args;
    va_start( args, msg );
    constexpr std::size_t bufferSize{ 1024u };
    char buffer[bufferSize];
    snprintf( buffer, bufferSize, msg, args );
    va_end( args );

    String result( buffer );

    return result;
}

String::String() noexcept: m_capacity( SSO_Size ), m_size( 0 )
{
    init();
    resetWithMaxValue();
}

String::String( const String& arg ) noexcept
{
    init();
    resetWithMaxValue();
    createFrom( arg );
}

String::String( String&& arg ) noexcept
{
    init();
    resetWithMaxValue();
    createFromMove( arg );
}

String::String( bool arg ) noexcept
{
    init();
    resetWithMaxValue();
    createFrom( arg );
}

String::String( const char* arg ) noexcept
{
    init();
    resetWithMaxValue();
    createFrom( arg );
}

String::String( const wchar_t* arg ) noexcept
{
    init();
    resetWithMaxValue();
    createFrom( arg );
}

String::String( unsigned char* /*arg*/ ) noexcept
{
    init();
    resetWithMaxValue();
    CUL::Assert::simple( false, "Method not implemented" );
}

String::String( const std::string& arg ) noexcept
{
    init();
    resetWithMaxValue();
    createFrom( arg );
}

String::String( const std::wstring& arg ) noexcept
{
    init();
    resetWithMaxValue();
    createFrom( arg );
}

String::String( float arg ) noexcept
{
    init();
    resetWithMaxValue();
    createFrom( arg );
}

String::String( double arg ) noexcept
{
    init();
    resetWithMaxValue();
    createFrom( arg );
}

String::String( std::int32_t arg ) noexcept
{
    init();
    resetWithMaxValue();
    createFrom( arg );
}

String::String( std::uint32_t arg ) noexcept
{
    init();
    resetWithMaxValue();
    createFrom( arg );
}

String::String( std::int64_t arg ) noexcept
{
    init();
    resetWithMaxValue();
    createFrom( arg );
}

String::String( std::uint64_t arg ) noexcept
{
    init();
    resetWithMaxValue();
    createFrom( arg );
}

void String::init()
{
    m_value = &m_staticValue[0];
    m_value[0] = NullTerminator;
}

String& String::operator=( const String& arg )
{
    if( this != &arg )
    {
        clear();
        createFrom( arg );
    }
    return *this;
}

String& String::operator=( String&& arg ) noexcept
{
    if( this != &arg )
    {
        clear();
        createFromMove( arg );
    }
    return *this;
}

String& String::operator=( bool arg )
{
    clear();
    createFrom( arg );
    return *this;
}

String& String::operator=( const char* arg )
{
    clear();
    createFrom( arg );
    return *this;
}

String& String::operator=( const wchar_t* arg )
{
    clear();
    createFrom( arg );
    return *this;
}

#ifdef _MSC_VER
    // Yes, I know that is a Spectre mitigation.
    // But for now, I let this as TODO, since i don't know
    // How to fix this.
    // TODO
    #pragma warning( push )
    #pragma warning( disable : 5045 )
#endif
String& String::operator=( unsigned char* /*arg*/ )
{
    clear();
    CUL::Assert::check( false, "Method not implemented" );
    return *this;
}
#ifdef _MSC_VER
    #pragma warning( pop )
#endif

String& String::operator=( const std::string& arg )
{
    clear();
    createFrom( arg );
    return *this;
}

String& String::operator=( const std::wstring& arg )
{
    clear();
    createFrom( arg );
    return *this;
}

String& String::operator=( float arg )
{
    clear();
    createFrom( arg );
    return *this;
}

String& String::operator=( double arg )
{
    clear();
    createFrom( arg );
    return *this;
}

String& String::operator=( std::int32_t arg )
{
    clear();
    createFrom( arg );
    return *this;
}

String& String::operator=( std::uint32_t arg )
{
    clear();
    createFrom( arg );
    return *this;
}

String& String::operator=( std::int64_t arg )
{
    clear();
    createFrom( arg );
    return *this;
}

String& String::operator=( std::uint64_t arg )
{
    clear();
    createFrom( arg );
    return *this;
}

const char* String::operator*() const
{
    return cStr();
}

String String::operator+( const String& arg ) const
{
    String result;
    result.append( *this );
    result.append( arg );
    return result;
}

String& String::operator+=( const String& arg )
{
    append( arg );
    return *this;
}

String::UnderlyingChar String::operator[]( Length inPos ) const
{
    return m_value[inPos];
}

String::UnderlyingChar& String::operator[]( Length inPos )
{
    return m_value[inPos];
}

bool String::operator==( const String& arg ) const
{
    return cmp( m_value, arg.m_value ) == 0;
}

bool String::operator!=( const String& arg ) const
{
    return !operator==( arg );
}

bool String::operator==( const std::string& arg ) const
{
#if CUL_USE_WCHAR
    return m_value == FS::s2ws( arg );
#else   // #if defined( CUL_USE_WCHAR )
    return cmp( m_value, arg.c_str() ) == 0;
#endif  // #if defined( CUL_USE_WCHAR )
}

bool String::operator!=( const std::string& arg ) const
{
    return !operator==( arg );
}

bool String::operator!=( const char* arg ) const
{
    return !operator==( arg );
}

bool String::operator==( const char* arg ) const
{
#if CUL_USE_WCHAR
    fetchTemp();
    const Length argLen = StringUtil::strLen( arg );

    if( argLen == 0 && m_size == 0 )
    {
        return true;
    }

    return cmp( m_temp, arg ) == 0;
#else   // #if CUL_USE_WCHAR
    return cmp( m_value, arg ) == 0;
#endif  // #if CUL_USE_WCHAR
}

bool String::operator!=( std::int32_t arg ) const
{
    return !operator==( arg );
}

bool String::operator==( std::int32_t arg ) const
{
#if CUL_USE_WCHAR
    return operator==( std::to_wstring( arg ) );
#else   // #if CUL_USE_WCHAR
    return operator==( std::to_string( arg ) );
#endif  // #if CUL_USE_WCHAR
}

bool String::operator!=( std::uint32_t arg ) const
{
    return !operator==( arg );
}

bool String::operator==( std::uint32_t arg ) const
{
#if CUL_USE_WCHAR
    return operator==( std::to_wstring( arg ) );
#else   // #if CUL_USE_WCHAR
    return operator==( std::to_string( arg ) );
#endif  // #if CUL_USE_WCHAR
}

bool String::operator!=( float arg ) const
{
    return !operator==( arg );
}

bool String::operator==( float arg ) const
{
#if CUL_USE_WCHAR
    return operator==( std::to_wstring( arg ) );
#else   // #if CUL_USE_WCHAR
    return operator==( std::to_string( arg ) );
#endif  // #if CUL_USE_WCHAR
}

bool String::operator!=( double arg ) const
{
    return !operator==( arg );
}

bool String::operator==( double arg ) const
{
#if CUL_USE_WCHAR
    return operator==( std::to_wstring( arg ) );
#else   // #if CUL_USE_WCHAR
    return operator==( std::to_string( arg ) );
#endif  // #if CUL_USE_WCHAR
}

bool String::operator<( const String& arg ) const
{
    return cmp( m_value, arg.m_value ) < 0;
}

bool String::operator>( const String& arg ) const
{
    return cmp( m_value, arg.m_value ) > 0;
}

bool String::operator()( const String& v1, const String& v2 ) const
{
    return v1 == v2;
}

void String::append( const String& arg )
{
    if( arg.m_size == 0 )
    {
        return;
    }

    append( arg.m_value, arg.m_size );
}

void String::append( const char* inChar )
{
    append( inChar, StringUtil::strLen( inChar ) );
}

void String::append( const char* inChar, Length charLength )
{
#if CUL_USE_WCHAR
    const Length maxWcharLength = 2 * charLength;
    UnderlyingChar* out = new UnderlyingChar[static_cast<std::size_t>( maxWcharLength )];
    const Length newLength = charToWideString( CP_ACP, out, maxWcharLength, inChar, charLength );
    append( out, newLength - 1 );
#else   // #if CUL_USE_WCHAR
    const Length targetSize = m_size + charLength + 1;
    grow( targetSize, true );
    const std::size_t length = static_cast<std::size_t>( charLength );
    for( std::size_t i = 0; i < length; ++i )
    {
        m_value[m_size + i] = inChar[i];
    }
    m_value[m_size + length] = NullTerminator;

    m_size += charLength;
#endif  // #if CUL_USE_WCHAR
    verify();
    deleteTemp();
}

void String::append( char inChar )
{
#if CUL_USE_WCHAR
    wchar_t out[4];
    std::size_t result = mbstowcs( out, &inChar, 1 );
    if( result == 1u )
    {
        const Length newSizeWithTerminator = m_size + 2;
        grow( newSizeWithTerminator, true );
        m_value[m_size] = out[0];
        m_value[m_size + 1u] = NullTerminator;
    }
    else
    {
        append( &out[0], static_cast<Length>( result ) );
    }
#else   // #if CUL_USE_WCHAR
    const Length newSize = m_size + 2;
    grow( newSize, true );

    m_value[static_cast<std::size_t>( m_size )] = inChar;
    m_value[static_cast<std::size_t>( m_size + 1 )] = NullTerminator;
    ++m_size;
#endif  // #if CUL_USE_WCHAR
    verify();
    deleteTemp();
}

void String::append( const wchar_t* inWchar )
{
    append( inWchar, StringUtil::strLen( inWchar ) );
}

void String::append( const wchar_t* inChar, Length otherSize )
{
    if( otherSize == 0 )
    {
        return;
    }

#if CUL_USE_WCHAR
    const auto otherSizeWithTerminator = static_cast<std::size_t>( otherSize + 1 );
    const Length newSize = m_size + static_cast<Length>( otherSizeWithTerminator );
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

std::int32_t String::find( const String& arg ) const
{
    return find( arg, 0 );
}

std::int32_t String::find( const String& arg, Length startPos ) const
{
    return find( arg.getChar(), startPos, arg.size() );
}

std::int32_t String::find( char arg ) const
{
    return find( arg, 0 );
}

std::int32_t String::find( char arg, Length startPosIn ) const
{
    if( m_size == 0 )
    {
        return -1;
    }

    const std::size_t startPos = static_cast<std::size_t>( startPosIn );
#if CUL_USE_WCHAR
    UnderlyingChar argConverted;
    charToWideString( CP_ACP, argConverted, arg );

    const auto currentSize = static_cast<std::size_t>( m_size );
    for( std::size_t i = startPos; i < currentSize; ++i )
    {
        if( m_value[i] == argConverted )
        {
            return static_cast<std::int32_t>( i );
        }
    }
#else   // #if defined(CUL_WINDOWS)
    const std::size_t currentSize = static_cast<std::size_t>( m_size );
    for( std::size_t i = startPos; i < currentSize; ++i )
    {
        if( m_value[i] == arg )
        {
            return static_cast<Length>( i );
        }
    }
#endif  // #if defined(CUL_WINDOWS)

    return -1;
}

std::int32_t String::find( const char* arg ) const
{
    return find( arg, 0 );
}

std::int32_t String::find( const char* arg, Length startPos, Length inArgSize ) const
{
#if CUL_USE_WCHAR
    (void*)inArgSize;
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converterX;
    const std::wstring stringCpy = converterX.from_bytes( arg );
    return find( stringCpy, startPos );
#else   // #if defined(CUL_WINDOWS)
    if( arg == nullptr )
    {
        return -1;
    }

    const Length argSize = inArgSize != -1 ? inArgSize : StringUtil::strLen( arg );

    if( startPos + argSize >= m_size )
    {
        return -1;
    }

    for( Length i = startPos; i < m_size; ++i )
    {
        UnderlyingChar* current = &m_value[i];

        if( i + argSize > m_size )
        {
            break;
        }

        if( equals( current, arg, argSize ) )
        {
            return i;
        }
    }
#endif  // #if defined(CUL_WINDOWS)
    return -1;
}

std::int32_t String::find( wchar_t arg ) const
{
    return find( arg, 0 );
}

std::int32_t String::find( wchar_t arg, Length startPosIn ) const
{
    if( m_size == 0 )
    {
        return -1;
    }

    const std::size_t startPos = static_cast<std::size_t>( startPosIn );
#if CUL_USE_WCHAR
    const auto currentSize = static_cast<std::size_t>( m_size );
    for( std::size_t i = startPos; i < currentSize; ++i )
    {
        if( m_value[i] == arg )
        {
            return static_cast<std::int32_t>( i );
        }
    }
#else   // #if defined(CUL_WINDOWS)
    const std::size_t currentSize = static_cast<std::size_t>( m_size );
    UnderlyingChar argConverted;
    wideStringToChar( argConverted, arg );
    for( std::size_t i = startPos; i < currentSize; ++i )
    {
        if( m_value[i] == argConverted )
        {
            return static_cast<Length>( i );
        }
    }
#endif  // #if defined(CUL_WINDOWS)

    return -1;
}

std::int32_t String::find( const wchar_t* arg ) const
{
    return find( arg, 0 );
}

std::int32_t String::find( const wchar_t* arg, Length startPos, Length inArgSize ) const
{
    if( arg == nullptr )
    {
        return -1;
    }

    const Length argSize = inArgSize != -1 ? inArgSize : StringUtil::strLen( arg );
    const auto argSizeU = static_cast<std::size_t>( argSize );
    if( startPos + argSize >= m_size )
    {
        return -1;
    }

#if CUL_USE_WCHAR
    const wchar_t* input = arg;
#else   // #if CUL_USE_WCHAR
    std::string converted;
    wideStringToChar( converted, arg );
    const char* input = converted.c_str();
#endif  // #if CUL_USE_WCHAR

    for( std::int32_t i = startPos; i < m_size; ++i )
    {
        UnderlyingChar* current = &m_value[i];

        if( i + inArgSize > m_size )
        {
            break;
        }

        if( equals( current, input, argSizeU ) )
        {
            return i;
        }
    }
    return -1;
}

String String::substr( Length pos, Length len ) const
{
    const Length targetSize = pos + len;
    if( targetSize > m_size )
    {
        return String{};
    }

    String strResult;
    strResult.grow( len, false );
    copyString( strResult.m_value, strResult.m_capacity, m_value + pos, len );
    strResult.m_value[len] = NullTerminator;
    strResult.setSize( len );
    strResult.removePrecedingZero();
    return strResult;
}

void String::toLower()
{
    toLower( m_value, m_size );
}

String String::toLowerR() const
{
    String result = *this;

    result.toLower();

    return result;
}

void String::toUpper()
{
    toUpper( m_value, m_size );
}

bool String::contains( const String& inputString ) const
{
    return find( inputString ) != -1;
}

bool String::contains( const char* inputString ) const
{
#if CUL_USE_WCHAR
    const Length inputLen = StringUtil::strLen( inputString );
    const Length wcharLen = inputLen * 2;
    wchar_t* temp = new wchar_t[static_cast<std::size_t>( wcharLen )];
    charToWideString( CP_ACP, temp, wcharLen, inputString, inputLen );

    const bool result = find( temp ) != -1;
    delete[] temp;
    return result;
#else   // #if defined(CUL_WINDOWS)
    return find( inputString ) != -1;
#endif  // #if defined(CUL_WINDOWS)
}

void String::replace( const String& inWhat, const String& inFor )
{
    if( m_size == 0 )
    {
        return;
    }

    if( inWhat.m_size == 0 )
    {
        return;
    }

    if( inFor.m_size == 0 )
    {
        return;
    }

    std::int32_t index = find( inWhat );
    if( index == -1 )
    {
        return;
    }

    std::int32_t diff = inFor.m_size - inWhat.m_size;
    if( diff > 0 )
    {
        grow( m_size + diff, true );

        const Length newSize = m_size + diff;
        m_value[newSize] = L'\0';
        const Length copyEnd = index + inWhat.size();
        for( Length i = newSize - 1; i >= copyEnd; --i )
        {
            m_value[i] = m_value[i - diff];
        }

        const Length offset = inFor.size();
        const Length end = index + offset;
        for( Length i = index; i < end; ++i )
        {
            m_value[i] = inFor.m_value[i - index];
        }
        setSize( newSize );
    }
    else if( diff < 0 )
    {
        const Length newLength = m_size + diff;
        const Length newStart = index + inFor.size();
        const Length offset = -diff;
        for( Length i = newStart; i < m_size; ++i )
        {
            m_value[i] = i + offset < m_size ? m_value[i + offset] : L'\0';
        }

        const std::size_t forSize = static_cast<std::size_t>( inFor.m_size );
        for( std::size_t i = 0u; i < forSize; ++i )
        {
            m_value[i + index] = inFor.m_value[i];
        }

        setSize( newLength );
    }
    else
    {
        for( std::int32_t i = 0; i < inFor.m_size; ++i )
        {
            m_value[index + i] = inFor.m_value[i];
        }
    }
    deleteTemp();
}

void String::replace( const char inWhat, const char inFor, bool allOccurences )
{
    if( m_size == 0 )
    {
        return;
    }
    const std::size_t currentLength = static_cast<std::size_t>( m_size );

#if CUL_USE_WCHAR
    wchar_t inConverted;
    charToWideString( CP_ACP, inConverted, inWhat );

    wchar_t forConverted;
    charToWideString( CP_ACP, forConverted, inFor );

    for( std::size_t i = 0; i < currentLength; ++i )
    {
        if( m_value[i] == inConverted )
        {
            m_value[i] = forConverted;
            if( allOccurences == false )
            {
                return;
            }
        }
    }

#else   // #if defined(CUL_WINDOWS)
    for( std::size_t i = 0; i < currentLength; ++i )
    {
        if( m_value[i] == inWhat )
        {
            m_value[i] = inFor;
            if( allOccurences == false )
            {
                return;
            }
        }
    }
#endif  // #if defined(CUL_WINDOWS)
    deleteTemp();
}

void String::replace( const wchar_t inWhat, const wchar_t inFor, bool allOccurences )
{
    if( m_size == 0 )
    {
        return;
    }
    const std::size_t currentLength = static_cast<std::size_t>( m_size );

#if CUL_USE_WCHAR
    for( std::size_t i = 0; i < currentLength; ++i )
    {
        if( m_value[i] == inWhat )
        {
            m_value[i] = inFor;
            if( allOccurences == false )
            {
                return;
            }
        }
    }

#else   // #if defined(CUL_WINDOWS)
    char inConverted;
    wideStringToChar( inConverted, inWhat );

    char forConverted;
    wideStringToChar( forConverted, inFor );
    for( std::size_t i = 0; i < currentLength; ++i )
    {
        if( m_value[i] == inConverted )
        {
            m_value[i] = forConverted;
            if( allOccurences == false )
            {
                return;
            }
        }
    }
#endif  // #if defined(CUL_WINDOWS)
    deleteTemp();
}

void String::removeFrist()
{
    if( m_size == 0u )
    {
        return;
    }

    --m_size;
    const auto sizeCasted = static_cast<std::size_t>( m_size );
    for( std::size_t i = 0u; i < sizeCasted; ++i )
    {
        m_value[i] = m_value[i + 1];
    }
    m_value[sizeCasted] = NullTerminator;
}

void String::removeLast()
{
    if( m_size == 0u )
    {
        return;
    }

    --m_size;
    const auto sizeCasted = static_cast<std::size_t>( m_size );
    m_value[sizeCasted] = NullTerminator;
}

void String::removeAll( const char inWhat )
{
#if CUL_USE_WCHAR
    UnderlyingChar what;
    charToWideString( 0, what, inWhat );
#else   // CUL_USE_WCHAR
    UnderlyingChar what = inWhat;
#endif  // CUL_USE_WCHAR

    for( Length i = m_size - 1; i >= 0; --i )
    {
        if( m_value[i] == what )
        {
            for( Length j = i; j < m_size; ++j )
            {
                if( j == m_size - 1u )
                {
                    m_value[j] = NullTerminator;
                }
                else
                {
                    m_value[j] = m_value[j + 1];
                }
            }
            --m_size;
        }
    }
    deleteTemp();
}

bool String::equals( const char* arg ) const
{
    return *this == arg;
}

bool String::equals( const std::string& arg ) const
{
    return *this == arg;
}

bool String::equals( const String& arg ) const
{
    return m_value == arg.m_value;
}

bool String::doesBeginWith( const std::string& end ) const
{
    if( m_size == 0 )
    {
        return false;
    }

    const auto endLen_t = end.size();
    const auto endLen = static_cast<Length>( endLen_t );

    if( m_size < endLen )
    {
        return false;
    }

#if CUL_USE_WCHAR
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converterX;
    const std::wstring stringCpy = converterX.from_bytes( end );
    return equals( &m_value[0], stringCpy.c_str(), endLen_t );
#else   // #if CUL_USE_WCHAR
    return equals( &m_value[0], end.c_str(), endLen_t );
#endif  // #if CUL_USE_WCHAR
}

bool String::doesBeginWith( const std::wstring& end ) const
{
    if( m_size == 0 )
    {
        return false;
    }

    const auto endLen_t = end.size();
    const auto endLen = static_cast<Length>( endLen_t );

    if( m_size < endLen )
    {
        return false;
    }

#if CUL_USE_WCHAR
    return equals( &m_value[0], end.c_str(), endLen_t );
#else   // #if CUL_USE_WCHAR
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converterX;
    const std::string stringCpy = converterX.to_bytes( end );

    return equals( &m_value[0], stringCpy.c_str(), stringCpy.size() );
#endif  // #if CUL_USE_WCHAR
}

bool String::doesEndWith( const std::string& end ) const
{
    if( m_size == 0 )
    {
        return false;
    }

    const auto endLen_t = end.size();
    const auto endLen = static_cast<Length>( endLen_t );

    if( m_size < endLen )
    {
        return false;
    }

    const std::size_t endPos = m_size - endLen;

#if CUL_USE_WCHAR
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converterX;
    const std::wstring stringCpy = converterX.from_bytes( end );
    return equals( &m_value[endPos], stringCpy.c_str(), endLen_t );
#else   // #if CUL_USE_WCHAR
    return equals( &m_value[endPos], end.c_str(), endLen_t );
#endif  // #if CUL_USE_WCHAR
}

bool String::doesEndWith( const std::wstring& end ) const
{
    if( m_size == 0 )
    {
        return false;
    }

    const auto endLen_t = end.size();
    const auto endLen = static_cast<Length>( endLen_t );

    if( m_size < endLen )
    {
        return false;
    }

    const std::size_t endPos = m_size - endLen_t;
#if CUL_USE_WCHAR
    return equals( &m_value[endPos], end.c_str(), endLen_t );
#else   // #if CUL_USE_WCHAR
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converterX;
    const std::string stringCpy = converterX.to_bytes( end );

    return equals( &m_value[endPos], stringCpy.c_str(), stringCpy.size() );
#endif  // #if CUL_USE_WCHAR
}

std::string String::string() const
{
#if CUL_USE_WCHAR
    return FS::ws2s( m_value );
#else   /// #if defined(CUL_WINDOWS)
    return m_value;
#endif  // #if defined(CUL_WINDOWS)
}

std::wstring String::wstring() const
{
#if CUL_USE_WCHAR
    return m_value;
#else   // #if defined(CUL_WINDOWS)
    return FS::s2ws( m_value );
#endif  // #if defined(CUL_WINDOWS)
}

const String::UnderlyingType String::getString() const
{
    return String::UnderlyingType( m_value );
}

const char* String::cStr() const
{
    if( m_size == 0 )
    {
        return nullptr;
    }

    fetchTemp();
#if CUL_USE_WCHAR
    return m_temp;
#else   // #if CUL_USE_WCHAR
    return m_value;
#endif  // #if CUL_USE_WCHAR
}

const wchar_t* String::wCstr() const
{
    fetchTemp();
#if CUL_USE_WCHAR
    return m_value;
#else   // #if CUL_USE_WCHAR
    return m_temp;
#endif  // #if CUL_USE_WCHAR
}

void String::fetchTemp() const
{
    if( m_temp )
    {
        return;
    }

#if CUL_USE_WCHAR
    // TODO: check when it should be released, possible leak.
    const Length charLength = m_size != 0 ? 2 * m_size : 2;
    m_temp = new char[static_cast<std::size_t>( charLength )];
    wideStringToChar( m_temp, charLength, m_value, m_size );
#else   // #if CUL_USE_WCHAR
    const std::size_t wcharBufferSize = 2u * m_size;
    m_temp = new wchar_t[wcharBufferSize];
    charToWideString( 0, m_temp, wcharBufferSize, m_value, m_size );
#endif  // #if CUL_USE_WCHAR
}

const String::UnderlyingChar* String::getChar() const
{
    return m_value;
}

bool String::isFloat() const
{
    std::istringstream iss( cStr() );
    float tmp;
    iss >> std::noskipws >> tmp;

    return iss.eof() && !iss.fail();
}

float String::toFloat() const
{
    return std::stof( m_value );
}

double String::toDouble() const
{
    CUL::Assert::check( false, "Method not implemented" );
    return 0.0;
}

int String::toInt()
{
    return std::stoi( m_value, nullptr, 0 );
}

int64_t String::toInt64() const
{
    return std::stoll( m_value, nullptr, 0 );
}

uint64_t String::toUint64() const
{
    return std::stoull( m_value, nullptr, 0 );
}

std::uint64_t String::toUInt() const
{
    return std::stoull( m_value, nullptr, 0 );
}

ThreeState String::toBool() const
{
    if( empty() )
    {
        return ThreeState::Undetermined;
    }

    String lowerCaseValue = toLowerR();

#if CUL_USE_WCHAR
    if( lowerCaseValue == L"true" )
    {
        return ThreeState::True;
    }

    if( cmp( m_value, L"false" ) )
    {
        return ThreeState::False;
    }
#else   // #if CUL_USE_WCHAR
    if( lowerCaseValue == "true" )
    {
        return ThreeState::True;
    }

    if( cmp( m_value, "false" ) )
    {
        return ThreeState::False;
    }
#endif  // #if CUL_USE_WCHAR

    return ThreeState::Undetermined;
}

Length String::length() const
{
    return m_size;
}

Length String::size() const
{
    return m_size;
}

Length String::capacity() const
{
    return m_capacity;
}

void String::clear()
{
    if( m_size == 0 )
    {
        return;
    }

    std::memset( &m_staticValue[0], 0, SSO_Size );
    delete[] m_dynamicValue;
    m_dynamicValue = nullptr;
    m_staticValue = {};
    m_value = &m_staticValue[0];
    m_capacity = SSO_Size;

    setSize( 0 );
}

bool String::empty() const
{
    return m_size == 0;
}

void String::reserve( std::int32_t newSize, bool keepValues )
{
    grow( newSize, keepValues );
}

void String::erase( Length index )
{
    for( Length i = index; i < m_size; ++i )
    {
        m_value[i] = m_value[i + 1];
    }
    --m_size;
}

constexpr char hexmap[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

void StringUtil::valueToHex( std::uint16_t inValue, std::array<std::uint8_t, 2>& outValue )
{
    outValue[0u] = hexmap[( inValue & 0xF0 ) >> 8];
    outValue[1u] = hexmap[( inValue & 0x0F ) >> 0];
}

void StringUtil::valueToHex( std::uint8_t inValue, std::uint8_t& outValue )
{
    outValue = hexmap[( inValue & 0x0F ) >> 0];
}

std::uint8_t StringUtil::charToValue( std::uint8_t inValue )
{
    return inValue - 48u;
}

bool StringUtil::isNumber( const char* inNumber )
{
    return isNumber( inNumber, StringUtil::strLen( inNumber ) );
}

bool StringUtil::isNumber( const char* inNumber, std::size_t inSize )
{
    for( std::size_t i = 0u; i < inSize; ++i )
    {
        if( std::isdigit( inNumber[i] ) == 0 )
        {
            return false;
        }
    }

    return true;
}

bool StringUtil::isNumber( const wchar_t* inNumber )
{
    return isNumber( inNumber, StringUtil::strLen( inNumber ) );
}

bool StringUtil::isNumber( const wchar_t* inNumber, std::size_t inSize )
{
    for( std::size_t i = 0u; i < inSize; ++i )
    {
        if( inNumber[i] > 255 )
        {
            return false;
        }

        if( std::isdigit( inNumber[i] ) == false )
        {
            return false;
        }
    }

    return true;
}

std::uint8_t StringUtil::hexToValue( std::uint8_t in )
{
    if( in < 61 )
    {
        return in - 48u;
    }

    if( in < 103 )
    {
        return in - 87u;
    }

    return 0u;
}

std::uint16_t StringUtil::hexToValue( std::uint16_t inValue )
{
    std::uint16_t MSB = inValue & 0xF0 >> 4;
    std::uint16_t LSB = inValue & 0x0F >> 0;
    return 16u * MSB + LSB;
}

std::uint8_t hexToChar( std::uint8_t in )
{
    char x = 'f';
    char* xx = &x;

    if( in < 10 )
    {
        return in + 48u;
    }

    if( in <= 15 )
    {
        return in + 87u;
    }

    return in + 65u;
}

void StringUtil::valueToHex( std::uint8_t in, std::array<uint8_t, 2>& outValue )
{
    if( in == 0u )
    {
        outValue[0] = '0';
        outValue[1] = '0';
        return;
    }

    if( in < 10u )
    {
        outValue[0] = '0';
        outValue[1] = in + 48u;
        return;
    }

    std::uint8_t* inPtr = &in;

    std::uint8_t upper = ( in & 0xF0 );
    std::uint8_t lower = ( in & 0x0F );

    std::uint8_t MSB_i = lower;
    std::uint8_t LSB_i = upper >> 4;

    outValue[1] = hexToChar( MSB_i );
    outValue[0] = hexToChar( LSB_i );
}

void StringUtil::valueToHex( char in, std::array<char, 2>& outValue )
{
    char* inPtr = &in;

    std::uint8_t upper = ( in & 0xF0 );
    std::uint8_t lower = ( in & 0x0F );

    std::uint8_t MSB_i = lower;
    std::uint8_t LSB_i = upper >> 4;

    outValue[1] = hexToChar( MSB_i );
    outValue[0] = hexToChar( LSB_i );
}

std::uint8_t StringUtil::hexToValue( const std::array<uint8_t, 2>& in )
{
    if( in[0] == '0' && in[1] == '0' )
    {
        return 0u;
    }

    std::uint8_t MSB_i = hexToValue( in[1] );
    std::uint8_t LSB_i = hexToValue( in[0] );

    return MSB_i + LSB_i * 16u;
}

uint16_t hexCharToInt( char valu )
{
    uint16_t result = valu - 48u;
    if( result >= 10u )
    {
        result = result - 39u;
    }
    return result;
}

uint16_t stringHex2Data( char val[4] )
{
    uint16_t result = 0u;

    for( int i = 0; i < 4; ++i )
    {
        const auto currentValue = val[3 - i];
        const auto intVal = hexCharToInt( currentValue );
        const auto powValue = std::pow( 16, i );
        result += powValue * intVal;
    }

    return result;
}

void String::serialize()
{
    if( m_size == 0 )
    {
        return;
    }

    std::vector<std::uint8_t> result;

    std::uint8_t* valueAsBytesPtr = reinterpret_cast<std::uint8_t*>( m_value );
    std::size_t dataLength = ( m_size + 1u ) * UnderlyingCharSize;

    std::array<std::uint8_t, 2> twoBytes;

#if CUL_USE_WCHAR
    std::uint8_t charType{ 0 };
#else
    std::uint8_t charType{ 1 };
#endif

    std::uint8_t charTypeHex;
    StringUtil::valueToHex( charType, charTypeHex );
    result.push_back( charTypeHex );

    for( std::size_t i = 0u; i < dataLength; ++i )
    {
        std::uint8_t current = valueAsBytesPtr[i];
        std::uint8_t* ptrToCurrent = &valueAsBytesPtr[i];

        StringUtil::valueToHex( current, twoBytes );
        result.push_back( twoBytes[0] );
        result.push_back( twoBytes[1] );
    }

    releaseBuffer();
    const std::size_t newBufferSize = result.size();
    grow( newBufferSize + 1u, false );

    for( std::size_t i = 0u; i < newBufferSize; ++i )
    {
        m_value[i] = result[i];
    }
    m_value[newBufferSize] = NullTerminator;

    m_size = newBufferSize;
    m_serialized = true;
    deleteTemp();
}

void String::deserialize()
{
    if( m_size == 0 )
    {
        return;
    }

    const std::uint8_t charTypeIdChar = *m_value;
    const std::uint8_t charType = StringUtil::charToValue( charTypeIdChar );

    if( charType == 0 )
    {
#if CUL_USE_WCHAR
        std::wstring out;
#else
        std::string out;
#endif
        deserializeWchar( out );
        operator=( out );
    }
    else if( charType == 1 )
    {
        std::string out;
        deserializeChar( out );
        operator=( out );
    }

    m_serialized = false;
    tryFitIntoSSO();
    deleteTemp();
}

#if CUL_USE_WCHAR
void String::deserializeWchar( std::wstring& out )
{
    std::string temp;
    wideStringToChar( temp, m_value + 1u );
#else
void String::deserializeWchar( std::string& out )
{
    std::string temp( m_value + 1u );
#endif  // #if CUL_USE_WCHAR

    std::size_t dataLength = temp.size() - 1u;
    std::vector<std::uint8_t> target;
    target.reserve( dataLength );
    std::array<std::uint8_t, 2> hexValue;

#if CUL_USE_WCHAR
    for( std::size_t i = 0u; i < dataLength - 1; i += 2 )
    {
        hexValue[0u] = temp[i];
        hexValue[1u] = temp[i + 1u];
        std::uint8_t value = StringUtil::hexToValue( hexValue );

        target.push_back( value );
    }
#else
    for( std::size_t i = 0u; i < dataLength - 1; i += 4 )
    {
        hexValue[0] = temp[i];
        hexValue[1] = temp[i + 1];
        std::uint8_t value = StringUtil::hexToValue( hexValue );

        target.push_back( value );
    }
#endif

    Length zeroCount{ 0u };
    for( Length i = target.size() - 1; i >= 0; --i )
    {
        if( target[i] == NullTerminator )
        {
            ++zeroCount;
        }
        else
        {
            break;
        }
    }

    if( zeroCount < 2 )
    {
        target.push_back( 0 );
        target.push_back( 0 );
    }

    const std::size_t newSize = target.size();

    clear();

    std::uint8_t* newValuePtr = new std::uint8_t[newSize + 1u];

    for( std::size_t i = 0u; i < newSize; ++i )
    {
        newValuePtr[i] = target[i];
    }
    newValuePtr[newSize] = 0;
#if CUL_USE_WCHAR
    out = (wchar_t*)newValuePtr;
#else
    out = (char*)newValuePtr;
#endif
    delete[] newValuePtr;
    deleteTemp();
}

void String::deserializeChar( std::string& out )
{
#if CUL_USE_WCHAR
    std::string temp;
    wideStringToChar( temp, m_value + 1u );
#else   // #if CUL_USE_WCHAR
    std::string temp( m_value + 1u );
#endif  // #if CUL_USE_WCHAR

    std::size_t dataLength = temp.size() - 1u;
    std::vector<std::uint8_t> target;
    target.reserve( dataLength );
    std::array<std::uint8_t, 2> hexValue;

    for( std::size_t i = 0u; i < dataLength - 1; i += 2 )
    {
        hexValue[0] = temp[i];
        hexValue[1] = temp[i + 1];
        std::uint8_t value = StringUtil::hexToValue( hexValue );

        target.push_back( value );
    }

    Length zeroCount{ 0u };
    for( Length i = target.size() - 1; i >= 0; --i )
    {
        if( target[i] == NullTerminator )
        {
            ++zeroCount;
        }
        else
        {
            break;
        }
    }

    if( zeroCount < 2 )
    {
        target.push_back( 0 );
        target.push_back( 0 );
    }

    const std::size_t newSize = target.size();

    clear();

    std::uint8_t* newValuePtr = new std::uint8_t[newSize + 1u];

    for( std::size_t i = 0u; i < newSize; ++i )
    {
        newValuePtr[i] = target[i];
    }
    newValuePtr[newSize] = 0;
    out = (char*)newValuePtr;
    delete[] newValuePtr;
}

void String::tryFitIntoSSO()
{
    if( m_size == 0 )
    {
        return;
    }

    if( m_size + 1 > static_cast<Length>( SSO_Size ) )
    {
        return;
    }

    if( m_dynamicValue == nullptr )
    {
        return;
    }

    copyString( &m_staticValue[0], SSO_Size, m_dynamicValue, m_size );
    delete m_dynamicValue;
    m_dynamicValue = nullptr;
    m_value = &m_staticValue[0];
    m_capacity = SSO_Size;
    terminate();
}

void String::verifyTerminator()
{
    const auto terminator = m_value[m_size + 1u];
    if( terminator != NullTerminator )
    {
    }
}

const std::vector<String> String::split( const String& delimiter ) const
{
    std::vector<String> result;

    Length delimPos = find( delimiter, 0 );
    Length lastDelim = 0;
    while( delimPos != -1 )
    {
        const String sub = substr( lastDelim, delimPos - lastDelim );
        result.emplace_back( sub );
        lastDelim = delimPos + 1;
        delimPos = find( delimiter, lastDelim );
    }

    if( lastDelim != -1 && lastDelim < m_size )
    {
        const String sub = substr( lastDelim, m_size - lastDelim );
        result.emplace_back( sub );
    }

    return result;
}

const std::vector<String> String::split( const char delimiter ) const
{
    std::vector<String> result;

    Length delimPos = find( delimiter, 0 );
    Length lastDelim = 0;
    while( delimPos != -1 )
    {
        const String sub = substr( lastDelim, delimPos - lastDelim );
        result.emplace_back( sub );
        lastDelim = delimPos + 1;
        delimPos = find( delimiter, lastDelim );
    }

    if( lastDelim != -1 && lastDelim < m_size )
    {
        const String sub = substr( lastDelim, m_size - lastDelim );
        result.emplace_back( sub );
    }

    return result;
}

const std::vector<String> String::split( const wchar_t delimiter ) const
{
    std::vector<String> result;

    Length delimPos = find( delimiter, 0 );
    Length lastDelim = 0;
    while( delimPos != -1 )
    {
        const String sub = substr( lastDelim, delimPos - lastDelim );
        result.emplace_back( sub );
        lastDelim = delimPos + 1;
        delimPos = find( delimiter, lastDelim );
    }

    if( lastDelim != -1 && lastDelim < m_size )
    {
        const String sub = substr( lastDelim, m_size - lastDelim );
        result.emplace_back( sub );
    }

    return result;
}

bool String::getIsSerialized() const
{
    return m_serialized;
}

Length String::wideStringToChar( char* out, Length outSize, const wchar_t* in )
{
    return wideStringToChar( out, outSize, in, StringUtil::strLen( in ) );
}

Length String::wideStringToChar( char* out, Length outSize, const wchar_t* inChar, Length inSize )
{
#if CUL_USE_WCHAR
    UINT codePage = CP_ACP;
    DWORD dwFlags = WC_COMPOSITECHECK;
    const int sizeNeeded = WideCharToMultiByte( codePage, dwFlags, inChar, inSize + 1, NULL, 0, NULL, NULL );

    const auto convertedLength = WideCharToMultiByte( codePage, dwFlags, inChar, inSize + 1, out, sizeNeeded, NULL, NULL );

    return convertedLength;
#else   // #if CUL_USE_WCHAR
    std::size_t result = 0u;

    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;
    const std::string stringCpy = converterX.to_bytes( inChar );
    copyString( out, outSize, stringCpy.c_str(), stringCpy.size() );

    return StringUtil::strLen( out );
#endif  // #if CUL_USE_WCHAR
}

Length String::wideStringToChar( char& inOut, wchar_t inChar )
{
#if CUL_USE_WCHAR
    UINT codePage = CP_ACP;
    DWORD dwFlags = WC_COMPOSITECHECK;
    const int sizeNeeded = WideCharToMultiByte( codePage, dwFlags, &inChar, 1, NULL, 0, NULL, NULL );

    char result[4];
    const auto convertedLength = WideCharToMultiByte( codePage, dwFlags, &inChar, 1, &result[0], sizeNeeded, NULL, NULL );

    return convertedLength;
#else   // #if CUL_USE_WCHAR
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;
    const std::string stringCpy = converterX.to_bytes( inChar );
    inOut = stringCpy[0];

    return true;
#endif  // #if CUL_USE_WCHAR
}

Length String::wideStringToChar( std::string& out, const std::wstring& inChar )
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converterX;
    out = converterX.to_bytes( inChar );
    return out.size();
}

Length String::charToWideString( Length codePage, wchar_t* out, Length outSize, const char* in )
{
    return charToWideString( codePage, out, outSize, in, static_cast<Length>( std::strlen( in ) ) );
}

Length String::charToWideString( Length codePage, wchar_t* out, Length outSize, const char* in, Length inSize )
{
    CUL::Assert::simple( outSize >= inSize, "NOT ENOUGH PLACE FOR STRING" );

#if defined( CUL_WINDOWS )
    const int size_needed = MultiByteToWideChar( static_cast<UINT>( codePage ),
                                                 0,       // flags
                                                 in,      // from
                                                 inSize,  // from byte count
                                                 NULL,    // to
                                                 0 );     // to char count
    std::wstring result( static_cast<std::size_t>( size_needed ), 0 );
    const std::int32_t resultSize = MultiByteToWideChar( codePage,
                                                         0,                                    // flags
                                                         in,                                   // from
                                                         inSize,                               // from byte count
                                                         result.data(),                        // to
                                                         static_cast<int>( result.size() ) );  // to char count

    copyString( out, outSize, result.data(), resultSize + 1 );
    return resultSize;
#else   // #if defined(CUL_WINDOWS)
    std::size_t length;
    wchar_t* dest = out;
    mbstate_t mbs;
    memset( &mbs, 0, sizeof( mbs ) );
    mbrlen( NULL, 0, &mbs ); /* initialize mbs */

    std::size_t max = static_cast<std::size_t>( inSize );
    const char* pt = in;

    Length writtent{ 0 };
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
#endif  // #if defined(CUL_WINDOWS)
}

Length String::charToWideString( Length codePage, wchar_t& out, char in )
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;
    const std::wstring stringCpy = converterX.from_bytes( in );
    const Length result = stringCpy.size();
    if( result == 1 )
    {
        out = stringCpy[0];
        return 1;
    }

    CUL::Assert::simple( false, "Conversion failed!" );
    return -1;
}

Length String::charToWideString( std::wstring& out, const std::string& in )
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converterX;
    out = converterX.from_bytes( in );
    return static_cast<Length>( out.size() );
}

void String::copyString( char* target, const char* source )
{
    copyString( target, StringUtil::strLen( target ), source, StringUtil::strLen( source ) );
}

void String::copyString( char* target, Length targetSize, const char* source, Length sourceSize )
{
    CUL::Assert::simple( targetSize >= sourceSize, "TARGET TOO SMALL!" );
    std::strncpy( target, source, static_cast<std::size_t>( sourceSize + 1 ) );
}

void String::copyString( wchar_t* target, const wchar_t* source )
{
    copyString( target, StringUtil::strLen( target ), source, StringUtil::strLen( source ) );
}

void String::copyString( wchar_t* target, Length targetSize, const wchar_t* source, Length sourceSizeS )
{
    CUL::Assert::simple( targetSize >= sourceSizeS, "TARGET TOO SMALL!" );
    const std::size_t sourceSize = static_cast<std::size_t>( sourceSizeS );
    for( std::size_t i = 0; i < sourceSize; ++i )
    {
        const UnderlyingChar sourceChar = source[i];
        target[i] = sourceChar;
    }
}

std::int32_t String::cmp( const char* s1, const char* s2 )
{
    return std::strcmp( s1, s2 );
}

bool String::equals( const char* s1, const char* s2, std::size_t length )
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

std::int32_t String::cmp( const wchar_t* s1, const wchar_t* s2 )
{
    return std::wcscmp( s1, s2 );
}

bool String::equals( const wchar_t* s1, const wchar_t* s2, std::size_t length )
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

void String::toLower( char* inOut )
{
    toLower( inOut, StringUtil::strLen( inOut ) );
}

void String::toLower( char* inOut, std::int32_t size )
{
    for( std::int32_t i = 0; i < size; ++i )
    {
        inOut[i] = static_cast<char>( std::tolower( inOut[i] ) );
    }
}

void String::toLower( wchar_t* inOut )
{
    toLower( inOut, StringUtil::strLen( inOut ) );
}

void String::toLower( wchar_t* inOut, std::int32_t size )
{
    for( std::int32_t i = 0; i < size; ++i )
    {
        inOut[i] = towlower( inOut[i] );
    }
}

void String::toUpper( char* inOut )
{
    toUpper( inOut, StringUtil::strLen( inOut ) );
}

void String::toUpper( char* inOut, std::int32_t size )
{
    for( std::int32_t i = 0; i < size; ++i )
    {
        inOut[i] = static_cast<char>( std::toupper( inOut[i] ) );
    }
}

void String::toUpper( wchar_t* inOut )
{
    toUpper( inOut, StringUtil::strLen( inOut ) );
}

void String::toUpper( wchar_t* inOut, std::int32_t size )
{
    for( std::int32_t i = 0; i < size; ++i )
    {
        inOut[i] = towupper( inOut[i] );
    }
}

void String::setSize( Length newSize )
{
    m_size = newSize;
    terminate();
}

void String::verify()
{
    const std::size_t currentSize = static_cast<std::size_t>( m_size );
    for( std::size_t i = 0; i < currentSize; ++i )
    {
        CUL::Assert::check( m_value[i] != NullTerminator, "FOUND NULL TERMINATOR IN BETWEEN RANGE!" );
    }
}

void String::createFrom( const String& arg )
{
    if( arg.m_size == 0 )
    {
        m_size = 0;
        m_capacity = SSO_Size;
        delete m_dynamicValue;
        m_dynamicValue = nullptr;
        m_value = &m_staticValue[0];
    }
    else
    {
        m_capacity = arg.m_capacity;
        m_size = arg.m_size;
        const Length copySize = m_size + 1;  // +1 for nullterminator.
        if( arg.m_dynamicValue )
        {
            m_dynamicValue = new UnderlyingChar[static_cast<std::size_t>( m_capacity )];
            m_value = m_dynamicValue;
        }
        else
        {
            m_value = &m_staticValue[0];
        }
        copyString( m_value, copySize, arg.m_value, copySize );
    }
}

void String::createFromMove( String& arg )
{
    m_value = m_dynamicValue;
    m_size = arg.m_size;
    m_capacity = arg.m_capacity;

    if( arg.m_dynamicValue )
    {
        delete m_dynamicValue;
        m_dynamicValue = arg.m_dynamicValue;
        m_value = m_dynamicValue;
    }
    else
    {
        delete m_dynamicValue;
        m_dynamicValue = nullptr;
        m_value = &m_staticValue[0];
        if( m_size > 0 )
        {
            copyString( m_value, m_size, arg.m_value, m_size );
            terminate();
        }
    }

    arg.m_dynamicValue = nullptr;
    arg.m_size = 0;
    arg.m_value = nullptr;
    arg.m_capacity = 0;
}

void String::createFrom( bool arg )
{
    m_value = &m_staticValue[0];
    setSize( arg ? 4 : 5 );
#if CUL_USE_WCHAR
    copyString( m_value, m_capacity, arg ? L"true" : L"false", m_size );
#else   // #if CUL_USE_WCHAR
    std::strcpy( m_value, arg ? "true" : "false" );
#endif  // #if CUL_USE_WCHAR
    deleteTemp();
}

void String::createFrom( const char* arg )
{
    const Length newLength = StringUtil::strLen( arg );
    grow( newLength, false );

#if CUL_USE_WCHAR
    if( newLength == 0 )
    {
        m_value[0] = NullTerminator;
        setSize( 0 );
    }
    else
    {
        charToWideString( CP_ACP, m_value, m_capacity, arg );
        const std::int32_t size = StringUtil::strLen( m_value );
        setSize( size );
    }
#else   // #if CUL_USE_WCHAR
    if( newLength == 0 )
    {
        m_value[0] = NullTerminator;
        setSize( 0 );
    }
    else
    {
        copyString( m_value, m_capacity, arg, newLength );
        setSize( newLength );
    }
#endif  // #if CUL_USE_WCHAR
    deleteTemp();
    removePrecedingZero();
}

void String::createFrom( const std::string& arg )
{
#if CUL_USE_WCHAR
    const Length argLen = static_cast<Length>( arg.size() );
    const Length newLength = static_cast<Length>( static_cast<float>( argLen ) * 1.2f );
    if( newLength >= m_capacity )
    {
        m_capacity = calcualteCapacity( newLength );
        m_dynamicValue = new UnderlyingChar[static_cast<std::size_t>( m_capacity )];
        m_value = m_dynamicValue;
    }
    else
    {
        m_value = &m_staticValue[0];
    }

    if( newLength == 0 )
    {
        m_value[0] = NullTerminator;
    }
    else
    {
        charToWideString( CP_ACP, m_value, m_capacity, arg.c_str(), argLen );
    }
#else   // #if CUL_USE_WCHAR
    const Length argLen = static_cast<Length>( arg.size() );
    if( argLen == 0 )
    {
        m_value[0] = NullTerminator;
    }
    else
    {
        grow( argLen + 1, false );
        copyString( m_value, m_capacity, arg.c_str(), static_cast<Length>( arg.size() ) );
    }
#endif  // #if CUL_USE_WCHAR
    setSize( argLen );
    deleteTemp();
}

void String::createFrom( const std::wstring& arg )
{
#if CUL_USE_WCHAR
    const Length argLen = static_cast<Length>( arg.size() );
    grow( argLen, false );
    copyString( m_value, m_capacity, arg.c_str(), argLen );
    setSize( argLen );
#else
    std::string out;
    wideStringToChar( out, arg );

    operator=( out );
#endif
    deleteTemp();
}

void String::terminate()
{
    m_value[m_size] = NullTerminator;
    deleteTemp();
}

void String::createFrom( const wchar_t* arg )
{
    const Length newLength = StringUtil::strLen( arg );
    if( newLength >= m_capacity )
    {
        m_capacity = calcualteCapacity( newLength );
        m_dynamicValue = new UnderlyingChar[static_cast<std::size_t>( m_capacity )];
        m_value = m_dynamicValue;
    }
    else
    {
        m_value = &m_staticValue[0];
    }

#if CUL_USE_WCHAR
    copyString( m_value, m_capacity, arg, newLength );
#else

    wideStringToChar( m_value, m_capacity, arg, newLength );
#endif
    setSize( newLength );
    deleteTemp();
}

void String::createFrom( std::int32_t arg )
{
#if CUL_USE_WCHAR
    const std::wstring temp = std::to_wstring( arg );
#else   // #if CUL_USE_WCHAR
    const std::string temp = std::to_string( arg );
#endif  // #if CUL_USE_WCHAR
    createFrom( temp );
    deleteTemp();
}

void String::createFrom( std::uint32_t arg )
{
#if CUL_USE_WCHAR
    const std::wstring temp = std::to_wstring( arg );
#else   // #if CUL_USE_WCHAR
    const std::string temp = std::to_string( arg );
#endif  // #if CUL_USE_WCHAR
    createFrom( temp );
    deleteTemp();
}

void String::createFrom( std::int64_t arg )
{
#if CUL_USE_WCHAR
    const std::wstring temp = std::to_wstring( arg );
#else   // #if CUL_USE_WCHAR
    const std::string temp = std::to_string( arg );
#endif  // #if CUL_USE_WCHAR
    createFrom( temp );
    deleteTemp();
}

void String::createFrom( std::uint64_t arg )
{
#if CUL_USE_WCHAR
    const std::wstring temp = std::to_wstring( arg );
#else   // #if CUL_USE_WCHAR
    const std::string temp = std::to_string( arg );
#endif  // #if CUL_USE_WCHAR
    createFrom( temp );
    deleteTemp();
}

void String::createFrom( float arg )
{
#if CUL_USE_WCHAR
    const std::wstring temp = std::to_wstring( arg );
#else   // #if CUL_USE_WCHAR
    const std::string temp = std::to_string( arg );
#endif  // #if CUL_USE_WCHAR
    createFrom( temp );
    deleteTemp();
}

void String::createFrom( double arg )
{
#if CUL_USE_WCHAR
    const std::wstring temp = std::to_wstring( arg );
#else   // #if CUL_USE_WCHAR
    const std::string temp = std::to_string( arg );
#endif  // #if CUL_USE_WCHAR
    createFrom( temp );
    deleteTemp();
}

void String::grow( Length targetSize, bool keepValue )
{
    if( targetSize + 1 < m_capacity )
    {
        return;
    }

    const Length oldCapacity = m_capacity;
    m_capacity = calcualteCapacity( targetSize );

    UnderlyingChar* newArray = new UnderlyingChar[static_cast<std::size_t>( m_capacity )];

    if( keepValue && m_size > 0 )
    {
        copyString( newArray, m_capacity, m_value, m_size + 1 );
    }

    if( oldCapacity != SSO_Size )
    {
        delete[] m_value;
    }

    m_value = newArray;
    m_dynamicValue = newArray;

    if( keepValue == false && m_size == 0 )
    {
        m_value[0] = NullTerminator;
    }
}

Length String::calcualteCapacity( Length inSize ) const
{
    if( inSize < m_capacity - 1 )
    {
        return m_capacity;
    }

    return static_cast<Length>( static_cast<float>( ( inSize + 1 ) ) * CapacityCoeficient );
}

void String::resetWithMaxValue()
{
#if CUL_DEBUG_STRING
    const std::size_t capacity = static_cast<std::size_t>( m_capacity );
    for( std::size_t i = 0; i < capacity; ++i )
    {
        m_staticValue[i] = L'D';
    }
#endif  // CUL_DEBUG_STRING
}

void String::removeFromStart( const wchar_t* inStr )
{
    std::size_t inStrLen{ 0u };
    if( startsWith( inStr, &inStrLen ) == false )
    {
        return;
    }

    const std::size_t sizeAsSizeT = static_cast<std::size_t>( m_size );
    const std::size_t newSize = sizeAsSizeT - inStrLen;
    for( std::size_t i = 0u; i < sizeAsSizeT; ++i )
    {
        if( i < newSize )
        {
            m_value[i] = m_value[i + inStrLen];
        }
        else
        {
            m_value[i] = NullTerminator;
        }
    }

    m_size = static_cast<Length>( newSize );
}

bool String::startsWith( const wchar_t* inStr, std::size_t* outInStrLen ) const
{
#if CUL_USE_WCHAR
    const std::wstring sample = inStr;
#else   // #if CUL_USE_WCHAR
    std::string sample;
    wideStringToChar( sample, inStr );
#endif  // #if CUL_USE_WCHAR

    const std::size_t inStrLen = sample.size();
    if( outInStrLen )
    {
        *outInStrLen = inStrLen;
    }

    for( std::size_t i = 0u; i < inStrLen && i < static_cast<std::size_t>( m_size ); ++i )
    {
        if( sample[i] != m_value[i] )
        {
            return false;
        }
    }
    return true;
}

void String::removeFromStart( const char* inStr )
{
    std::size_t inStrLen{ 0u };
    if( startsWith( inStr, &inStrLen ) == false )
    {
        return;
    }

    const std::size_t sizeAsSizeT = static_cast<std::size_t>( m_size );
    const std::size_t newSize = sizeAsSizeT - inStrLen;
    for( std::size_t i = 0u; i < sizeAsSizeT; ++i )
    {
        if( i < newSize )
        {
            m_value[i] = m_value[i + inStrLen];
        }
        else
        {
            m_value[i] = NullTerminator;
        }
    }

    m_size = static_cast<Length>( newSize );
}

bool String::startsWith( const char* inStr, std::size_t* outInStrLen ) const
{
#if CUL_USE_WCHAR
    std::wstring sample;
    charToWideString( sample, inStr );
#else   // #if CUL_USE_WCHAR
    const std::string sample = inStr;
#endif  // #if CUL_USE_WCHAR

    const std::size_t inStrLen = sample.size();

    if( outInStrLen )
    {
        *outInStrLen = inStrLen;
    }

    for( std::size_t i = 0u; i < inStrLen && i < static_cast<std::size_t>( m_size ); ++i )
    {
        if( sample[i] != m_value[i] )
        {
            return false;
        }
    }
    return true;
}
void String::removeTrailingLineEnd()
{
    const std::int32_t stringLength = static_cast<std::int32_t>( m_size );
    for( std::int32_t i = stringLength - 1; i >= 0; --i )
    {
        UnderlyingChar& currentChar = m_value[i];
        if( ( currentChar == LineEnding ) /*|| ( currentChar == LineEndingCarriage )*/ )
        {
            currentChar = NullTerminator;
            --m_size;
        }
        else
        {
            break;
        }
    }
    deleteTemp();
}

void String::sanitize()
{
    singleQuoteEscape();
}

void String::escapeCharacter( const UnderlyingType& characterToEscape )
{
    if( m_size == 0u )
    {
        return;
    }

    const Length sizeCast = static_cast<Length>( m_size );
    for( Length i = sizeCast - 1; i >= 0; )
    {
        const std::size_t iCast = static_cast<std::size_t>( i );
        if( m_value[iCast] != characterToEscape[0] )
        {
            --i;
            continue;
        }

        if( i < 1 )
        {
            --i;
            continue;
        }

        const auto newSize = m_size + 1;
        grow( newSize, true );
        m_size = newSize;

        m_value[m_size] = NullTerminator;
        const auto sizeCast2 = static_cast<Length>( m_size );
        for( Length j = sizeCast2 - 1; j > i; --j )
        {
            std::size_t jCast = static_cast<std::size_t>( j );
            m_value[j] = m_value[j - 1];
        }

        i -= 1;
    }
}

void String::singleQuoteEscape()
{
    if( m_size == 0u )
    {
        return;
    }

    const Length sizeCast = static_cast<Length>( m_size );
    for( Length i = sizeCast - 1; i >= 0; )
    {
        const std::size_t iCast = static_cast<std::size_t>( i );
        if( m_value[iCast] != SingleQuote[0] )
        {
            --i;
            continue;
        }

        if( i < 1 )
        {
            --i;
            continue;
        }

        Length consecutiveQuotesCount{ 0 };
        Length sizeCast2 = static_cast<Length>( m_size );
        for( Length j = i; j >= 0; --j )
        {
            const std::size_t jCast = static_cast<std::size_t>( j );
            if( m_value[jCast] == SingleQuote[0] )
            {
                ++consecutiveQuotesCount;
            }
            else
            {
                break;
            }
        }

        const auto newSize = m_size + consecutiveQuotesCount;
        grow( newSize, true );
        m_size = newSize;

        m_value[m_size] = NullTerminator;
        sizeCast2 = static_cast<Length>( m_size );
        for( Length j = sizeCast2 - 1; j > i; --j )
        {
            std::size_t jCast = static_cast<std::size_t>( j );
            m_value[j] = m_value[j - consecutiveQuotesCount];
        }

        i -= consecutiveQuotesCount;
    }
}

void String::singleQuoteRestore()
{
    if( m_size == 0u )
    {
        return;
    }

    if( count( std::string( "'" )[0] ) > 1 )
    {
        auto x = 0;
    }

    for( Length i = 0; i < m_size; )
    {
        const std::size_t iCast = static_cast<std::size_t>( i );

        if( m_value[iCast] != SingleQuote[0] )
        {
            ++i;
            continue;
        }

        Length consecutiveQuotesCount{ 0 };
        for( Length j = i; j < m_size; ++j )
        {
            const std::size_t jCast = static_cast<std::size_t>( j );
            if( m_value[jCast] == SingleQuote[0] )
            {
                ++consecutiveQuotesCount;
            }
            else
            {
                break;
            }
        }

        if( consecutiveQuotesCount < 2 )
        {
            ++i;
            continue;
        }

        const Length reduceSize = consecutiveQuotesCount > 1 ? consecutiveQuotesCount / 2 : 0;
        const std::size_t reduceSizeCast = static_cast<std::size_t>( reduceSize );
        const auto newSize = m_size - reduceSize;
        const auto newSizeCast = static_cast<std::size_t>( newSize );

        for( std::size_t j = i; j < newSizeCast; ++j )
        {
            m_value[j] = m_value[j + reduceSizeCast];
        }
        m_size = newSize;
        m_value[m_size] = NullTerminator;
        i += reduceSizeCast;
    }
}

Length String::count( wchar_t inChar ) const
{
    if( m_size == 0u )
    {
        return 0;
    }

    Length result{ 0 };

#if CUL_USE_WCHAR
    wchar_t toBeFound = inChar;
#else
    char toBeFound;
    wideStringToChar( toBeFound, inChar );
#endif
    const std::size_t sizeCasted = static_cast<std::size_t>( m_size );
    for( std::size_t i = 0; i < sizeCasted; ++i )
    {
        if( m_value[i] == toBeFound )
        {
            ++result;
        }
    }

    return result;
}

void String::removePrecedingZero()
{
    if( m_size < 2u )
    {
        return;
    }

    if( StringUtil::isNumber( m_value, m_size ) == false )
    {
        return;
    }

    while( true )
    {
        if( m_value[0] != ZeroChar )
        {
            return;
        }

        if( m_size == 1u )
        {
            return;
        }

        for( CUL::Length i = 0u; i < m_size; ++i )
        {
            m_value[i] = m_value[i + 1u];
        }
        --m_size;
    }
}

Length String::count( char inChar ) const
{
    if( m_size == 0u )
    {
        return 0;
    }

    Length result{ 0 };
#if CUL_USE_WCHAR
    wchar_t toBeFound;
    charToWideString( CP_ACP, toBeFound, inChar );
#else
    char toBeFound = inChar;
#endif
    const std::size_t sizeCasted = static_cast<std::size_t>( m_size );
    for( std::size_t i = 0; i < sizeCasted; ++i )
    {
        if( m_value[i] == toBeFound )
        {
            ++result;
        }
    }

    return result;
}

String::~String()
{
    releaseBuffer();
}

void String::releaseBuffer()
{
    if( m_size == 0 )
    {
        return;
    }

    if( m_dynamicValue )
    {
        delete[] m_dynamicValue;
    }

    m_value = nullptr;
    m_dynamicValue = nullptr;
    m_capacity = SSO_Size;

    deleteTemp();

    m_value = &m_staticValue[0];
    setSize( 0 );
}

void String::deleteTemp()
{
    delete[] m_temp;
    m_temp = nullptr;
}

String CULLib_API CUL::operator+( const char* arg1, const String& arg2 )
{
    String result( arg1 );
    result.append( arg2 );
    return result;
}

bool CULLib_API CUL::operator==( const char* arg1, const String& arg2 )
{
    return arg2 == arg1;
}

bool CULLib_API CUL::operator==( int arg1, const String& arg2 )
{
    return arg2 == arg1;
}

bool CULLib_API CUL::operator==( unsigned int arg1, const String& arg2 )
{
    return arg2 == arg1;
}

bool CULLib_API CUL::operator==( float arg1, const String& arg2 )
{
    return arg2 == arg1;
}

bool CULLib_API CUL::operator==( double arg1, const String& arg2 )
{
    return arg2 == arg1;
}

std::int32_t StringUtil::strLen( const char* inString )
{
    return static_cast<std::int32_t>( std::strlen( inString ) );
}

std::int32_t StringUtil::strLen( const wchar_t* inString )
{
    return static_cast<std::int32_t>( std::wcslen( inString ) );
}