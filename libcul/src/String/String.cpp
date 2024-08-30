#include "CUL/String.hpp"

#include "Filesystem/FSUtils.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/Log/ILogger.hpp"

#include "CUL/STL_IMPORTS/STD_algorithm.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"
#include "CUL/STL_IMPORTS/STD_sstream.hpp"
#include "CUL/STL_IMPORTS/STD_cmath.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"
#include "CUL/STL_IMPORTS/STD_wctype.hpp"
#include "CUL/STL_IMPORTS/STD_codecvt.hpp"

using namespace CUL;

String::String() noexcept:
    m_capacity( SSO_Size ),
    m_size(0)
{
    m_value = &m_staticValue[0];
    m_value[0] = NullTerminator;
    resetWithMaxValue();
}

String::String( const String& arg ) noexcept
{
    resetWithMaxValue();
    createFrom( arg );
}

String::String( String&& arg ) noexcept
{
    resetWithMaxValue();
    createFromMove( arg );
}

String::String( bool arg ) noexcept
{
    resetWithMaxValue();
    createFrom( arg );
}

String::String( const char* arg ) noexcept
{
    resetWithMaxValue();
    createFrom( arg );
}

String::String( const wchar_t* arg ) noexcept
{
    resetWithMaxValue();
    createFrom( arg );
}

String::String( unsigned char* /*arg*/ ) noexcept
{
    resetWithMaxValue();
    CUL::Assert::simple( false, "Method not implemented" );
}

String::String( const std::string& arg ) noexcept
{
    resetWithMaxValue();
    createFrom( arg );
}

String::String( const std::wstring& arg ) noexcept
{
    resetWithMaxValue();
    createFrom( arg );
}

String::String( float arg ) noexcept
{
    resetWithMaxValue();
    createFrom( arg );
}

String::String( double arg ) noexcept
{
    resetWithMaxValue();
    createFrom( arg );
}

String::String( std::int32_t arg ) noexcept
{
    resetWithMaxValue();
    createFrom( arg );
}

String::String( std::uint32_t arg ) noexcept
{
    resetWithMaxValue();
    createFrom( arg );
}

String::String( std::int64_t arg ) noexcept
{
    resetWithMaxValue();
    createFrom( arg );
}

String::String( std::uint64_t arg ) noexcept
{
    resetWithMaxValue();
    createFrom( arg );
}

String& String::operator=( const String& arg )
{
    if( this != &arg )
    {
        createFrom( arg );
    }
    return *this;
}

String& String::operator=( String&& arg ) noexcept
{
    if( this != &arg )
    {
        createFromMove( arg );
    }
    return *this;
}

String& String::operator=( bool arg )
{
    createFrom( arg );
    return *this;
}

String& String::operator=( const char* arg )
{
    createFrom( arg );
    return *this;
}

String& String::operator=( const wchar_t* arg )
{
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
    throw std::logic_error( "Method not implemented" );

    return *this;
}
#ifdef _MSC_VER
#pragma warning( pop )
#endif

String& String::operator=( const std::string& arg )
{
    createFrom( arg );
    return *this;
}

String& String::operator=( const std::wstring& arg )
{
    createFrom( arg );
    return *this;
}

String& String::operator=( float arg )
{
    createFrom( arg );
    return *this;
}

String& String::operator=( double arg )
{
    createFrom( arg );
    return *this;
}

String& String::operator=( std::int32_t arg )
{
    createFrom( arg );
    return *this;
}

String& String::operator=( std::uint32_t arg )
{
    createFrom( arg );
    return *this;
}

String& String::operator=( std::int64_t arg )
{
    createFrom( arg );
    return *this;
}

String& String::operator=( std::uint64_t arg )
{
    createFrom( arg );
    return *this;
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
    return cmp(m_value, arg.m_value) == 0;
}

bool String::operator!=( const String& arg ) const
{
    return !operator==( arg );
}

bool String::operator==( const std::string& arg ) const
{
#if CUL_USE_WCHAR
    return m_value == FS::s2ws( arg );
#else // #if defined( CUL_USE_WCHAR )
    return cmp( m_value, arg.c_str() ) == 0;
#endif // #if defined( CUL_USE_WCHAR )
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
    const Length argLen = strLen( arg );

    if( argLen == 0 && m_size == 0 )
    {
        return true;
    }

    const Length bufferSize = 2 * argLen;
    UnderlyingChar* buffer = new UnderlyingChar[static_cast<std::size_t>( bufferSize )];
    charToWideString( CP_ACP, buffer, bufferSize, arg, argLen );
    const bool result = cmp( m_value, buffer ) == 0;
    delete[] buffer;
    return result;
#else // #if CUL_USE_WCHAR
    return cmp(m_value, arg) == 0;
#endif // #if CUL_USE_WCHAR
}

bool String::operator!=( std::int32_t arg ) const
{
    return !operator==( arg );
}

bool String::operator==( std::int32_t arg ) const
{
#if CUL_USE_WCHAR
    return operator==( std::to_wstring( arg ) );
#else // #if CUL_USE_WCHAR
    return operator==( std::to_string( arg ) );
#endif // #if CUL_USE_WCHAR
}

bool String::operator!=( std::uint32_t arg ) const
{
    return !operator==( arg );
}

bool String::operator==( std::uint32_t arg ) const
{
#if CUL_USE_WCHAR
    return operator==( std::to_wstring( arg ) );
#else // #if CUL_USE_WCHAR
    return operator==( std::to_string( arg ) );
#endif // #if CUL_USE_WCHAR
}

bool String::operator!=( float arg ) const
{
    return !operator==( arg );
}

bool String::operator==( float arg ) const
{
#if CUL_USE_WCHAR
    return operator==( std::to_wstring( arg ) );
#else // #if CUL_USE_WCHAR
    return operator==( std::to_string( arg ) );
#endif // #if CUL_USE_WCHAR
}

bool String::operator!=( double arg ) const
{
    return !operator==( arg );
}

bool String::operator==( double arg ) const
{
#if CUL_USE_WCHAR
    return operator==( std::to_wstring( arg ) );
#else // #if CUL_USE_WCHAR
    return operator==( std::to_string( arg ) );
#endif // #if CUL_USE_WCHAR
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
    append( inChar, strLen( inChar ) );
}

void String::append( const char* inChar, Length charLength )
{
#if CUL_USE_WCHAR
    const Length maxWcharLength = 2 * charLength;
    UnderlyingChar* out = new UnderlyingChar[static_cast<std::size_t>(maxWcharLength)];
    const Length newLength = charToWideString( CP_ACP, out, maxWcharLength, inChar, charLength );
    append( out, newLength - 1 );
#else // #if CUL_USE_WCHAR
    const Length targetSize = m_size + charLength + 1;
    grow( targetSize, true );
    const std::size_t length = static_cast<std::size_t>(charLength);
    for(std::size_t i = 0; i < length; ++i)
    {
        m_value[m_size + i] = inChar[i];
    }
    m_value[m_size + length] = NullTerminator;

    m_size += charLength;

#endif // #if CUL_USE_WCHAR
    verify();
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
        append( &out[0], static_cast<Length>(result) );
    }
#else // #if CUL_USE_WCHAR
    const Length newSize = m_size + 2;
    grow( newSize, true );

    m_value[static_cast<std::size_t>( m_size )] = inChar;
    m_value[static_cast<std::size_t>( m_size + 1 )] = NullTerminator;
    ++m_size;
#endif // #if CUL_USE_WCHAR
    verify();
}

void String::append( const wchar_t* inWchar )
{
    append( inWchar, strLen( inWchar ) );
}

void String::append( const wchar_t* inChar, Length otherSize )
{
    if( otherSize == 0 )
    {
        return;
    }

#if CUL_USE_WCHAR
    const Length otherSizeWithTerminator = otherSize + 1;
    const Length newSize = m_size + otherSizeWithTerminator;
    grow( newSize, true );

    for( std::size_t i = 0; i < otherSizeWithTerminator; ++i )
    {
        m_value[m_size + i] = inChar[i];
    }
    setSize( newSize - 1 );
#else // #if CUL_USE_WCHAR
    throw std::logic_error( "Method not implemented" );
#endif // #if CUL_USE_WCHAR
    verify();
}

void String::append( wchar_t inChar )
{
#if CUL_USE_WCHAR
    grow( m_size + 2, true );

    m_value[m_size] = inChar;
    m_value[m_size + 1] = NullTerminator;
    ++m_size;
#else  // #if CUL_USE_WCHAR
    throw std::logic_error( "Method not implemented" );
#endif // #if CUL_USE_WCHAR
    verify();
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

    const Length currentSize = static_cast<Length>( m_size );
    for( size_t i = startPos; i < currentSize; ++i )
    {
        if( m_value[i] == argConverted )
        {
            return static_cast<Length>( i );
        }
    }
#else // #if defined(CUL_WINDOWS)
    const std::size_t currentSize = static_cast<std::size_t>( m_size );
    for( std::size_t i = startPos; i < currentSize; ++i )
    {
        if( m_value[i] == arg )
        {
            return static_cast<Length>( i );
        }
    }
#endif // #if defined(CUL_WINDOWS)

    return -1;
}

std::int32_t String::find( const char* arg ) const
{
    return find( arg, 0 );
}

std::int32_t String::find( const char* arg, Length startPos, Length inArgSize ) const
{
#if CUL_USE_WCHAR
    CUL::Assert::check( false, "Not implemented yet." );
#else // #if defined(CUL_WINDOWS)
    if( arg == nullptr )
    {
        return -1;
    }

    const Length argSize = inArgSize != -1 ? inArgSize : strLen( arg );

    if( startPos + argSize >= m_size )
    {
        return -1;
    }

    for( std::int32_t i = startPos; i < m_size; ++i )
    {
        if( m_value[i] == arg[0] )
        {
            bool exact{ true };
            std::int32_t ii = i;
            ++ii;
            for( std::int32_t j = 1; j < argSize && ii < m_size; ++j )
            {
                if( m_value[ii] != arg[j] )
                {
                    exact = false;
                    break;
                }
                ++ii;
            }

            if( exact )
            {
                return i;
            }
        }
    }
#endif // #if defined(CUL_WINDOWS)
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
    const Length currentSize = static_cast<Length>( m_size );
    for( size_t i = startPos; i < currentSize; ++i )
    {
        if( m_value[i] == arg )
        {
            return static_cast<Length>( i );
        }
    }
#else // #if defined(CUL_WINDOWS)
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
#endif // #if defined(CUL_WINDOWS)

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

    const Length argSize = inArgSize != -1 ? inArgSize : strLen( arg );

    if( startPos + argSize >= m_size )
    {
        return -1;
    }

    for( std::int32_t i = startPos; i < m_size; ++i )
    {
        if( m_value[i] == arg[0] )
        {
            bool exact{ true };
            std::int32_t ii = i;
            ++ii;
            for( std::int32_t j = 1; j < argSize && ii < m_size; ++j )
            {
                if( m_value[ii] != arg[j] )
                {
                    exact = false;
                    break;
                }
                ++ii;
            }

            if( exact )
            {
                return i;
            }
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
    const Length inputLen = strLen( inputString );
    const Length wcharLen = inputLen * 2;
    wchar_t* temp = new wchar_t[static_cast<std::size_t>( wcharLen )];
    charToWideString( CP_ACP, temp, wcharLen, inputString, inputLen );

    const bool result = find( temp ) != -1;
    delete[] temp;
    return result;
#else // #if defined(CUL_WINDOWS)
    return find( inputString ) != -1;
#endif // #if defined(CUL_WINDOWS)
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
    }
    else if(diff < 0 )
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

#else // #if defined(CUL_WINDOWS)
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
#endif // #if defined(CUL_WINDOWS)
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

#else // #if defined(CUL_WINDOWS)
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
#endif // #if defined(CUL_WINDOWS)
}

void String::removeAll( const char inWhat )
{
    throw std::logic_error( "Method not implemented" );
    //UnderlyingChar inWhatChar = (UnderlyingChar)inWhat;
    //auto inWhatPosition = m_value.find( inWhatChar );
    //while( std::string::npos != inWhatPosition )
    //{
    //    m_value.erase( inWhatPosition );
    //    inWhatPosition = m_value.find( inWhatChar );
    //}
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

bool String::doesEndWith( const UnderlyingType& end ) const
{
    throw std::logic_error( "Method not implemented" );
    //size_t it = m_value.find( end );

    //if( it == UnderlyingType::npos )
    //{
    //    return false;
    //}

    //int valueSize = (int)m_value.size();
    //int endSize = (int)end.size();
    //int diff = valueSize - endSize;

    //if( valueSize < endSize )
    //{
    //    return false;
    //}

    //for( int i = valueSize; i >= 0; --i )
    //{
    //    if( m_value[(size_t)i] != end[(size_t)( i - diff )] )
    //    {
    //        return false;
    //    }
    //}

    return true;
}

std::string String::string() const
{
#if CUL_USE_WCHAR
    return FS::ws2s( m_value );
#else /// #if defined(CUL_WINDOWS)
    return m_value;
#endif // #if defined(CUL_WINDOWS)
}

std::wstring String::wstring() const
{
#if CUL_USE_WCHAR
    return m_value;
#else // #if defined(CUL_WINDOWS)
    return FS::s2ws( m_value );
#endif // #if defined(CUL_WINDOWS)
}

const String::UnderlyingType String::getString() const
{
    return String::UnderlyingType( m_value );
}

const char* String::cStr() const
{
#if CUL_USE_WCHAR
    // TODO: check when it should be released, possible leak.
    const Length charLength = m_size != 0 ? 2 * m_size : 2;
    delete[] m_temp;
    m_temp = new char[charLength];
    wideStringToChar( m_temp, charLength, m_value, m_size );
    return m_temp;
#else // #if CUL_USE_WCHAR
    return m_value;
#endif // #if CUL_USE_WCHAR
}

const wchar_t* String::wCstr() const
{
#if CUL_USE_WCHAR
    return m_value;
#else // #if CUL_USE_WCHAR
    delete[] m_temp;
    const std::size_t wcharBufferSize = 2u * m_size;
    m_temp = new wchar_t[wcharBufferSize];
    charToWideString(0, m_temp, wcharBufferSize, m_value, m_size);
    return m_temp;
#endif // #if CUL_USE_WCHAR
    return nullptr;
}

const String::UnderlyingChar* String::getChar() const
{
    return m_value;
}

float String::toFloat() const
{
    throw std::logic_error( "Method not implemented" );
    //return m_value.empty() ? 0.0f : std::stof( m_value, nullptr );
    return 0.f;
}

double String::toDouble() const
{
    throw std::logic_error( "Method not implemented" );
    //return m_value.empty() ? 0.0 : std::stod( m_value, nullptr );
    return 0.0;
}

int String::toInt()
{
    throw std::logic_error( "Method not implemented" );
    //removeAll( 'u' );
    //if( m_value.empty() )
    //{
    //    return 0;
    //}

    //return std::stoi( m_value );
    return 0;
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

bool String::toBool() const
{
#if CUL_USE_WCHAR
    return cmp( m_value, L"true" ) == 0;
#else // #if CUL_USE_WCHAR
    return cmp( m_value, "true" ) == 0;
#endif // #if CUL_USE_WCHAR
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
    setSize( 0 );
    m_value[0] = NullTerminator;
    m_value[1] = NullTerminator;
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

std::string data2StringHex( unsigned char* data, size_t len )
{
    std::string s( len * 2u, ' ' );
    for( size_t i = 0; i < len; ++i )
    {
        s[2u * i] = hexmap[( data[i] & 0xF0 ) >> 4];
        s[2u * i + 1] = hexmap[data[i] & 0x0F];
    }
    return s;
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

void String::convertToHexData()
{
#if CUL_USE_WCHAR
    if( m_size > 0 )
    {
        const size_t sizeOfWchar = sizeof( wchar_t );
        const size_t wholeDataSize = m_size * sizeOfWchar;

        const std::string hexValue = data2StringHex( (unsigned char*)m_value, wholeDataSize );
        releaseBuffer();
        createFrom( hexValue );
        m_isBinary = true;
    }
#else // #if defined(CUL_WINDOWS)
#endif // #if defined(CUL_WINDOWS)
}

void String::setBinary( const char* value )
{
    releaseBuffer();
    createFrom( value );
    m_isBinary = true;
}

void String::convertFromHexToString()
{
#if CUL_USE_WCHAR
    if( m_size == 0 )
    {
        return;
    }

    constexpr size_t dataWidth = 4;

    std::wstring result;
    const char* binaryValue = cStr();
    for( size_t i = 0; i < m_size; i += dataWidth )
    {
        std::string currentHex( binaryValue, i, dataWidth );
        char charStr[4];
        charStr[2] = currentHex[0];
        charStr[3] = currentHex[1];
        charStr[0] = currentHex[2];
        charStr[1] = currentHex[3];
        wchar_t val = stringHex2Data( charStr );
        result.push_back( val );
    }
    releaseBuffer();
    createFrom( result );
    m_isBinary = false;
#else // #if defined(CUL_WINDOWS)
#endif // #if defined(CUL_WINDOWS)
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

Length String::wideStringToChar( char* out, Length outSize, const wchar_t* in )
{
    return wideStringToChar( out, outSize, in, std::wcslen( in ) );
}

Length String::wideStringToChar( char* out, Length outSize, const wchar_t* in, Length inSize )
{
    std::size_t result = 0u;
#if CUL_USE_WCHAR
    UINT codePage = CP_ACP;
    DWORD dwFlags = WC_COMPOSITECHECK;
    const int sizeNeeded = WideCharToMultiByte( codePage, dwFlags, in, inSize, NULL, 0, NULL, NULL );
    if( sizeNeeded < outSize )
    {
        WideCharToMultiByte( codePage, dwFlags, in, inSize, out, sizeNeeded, NULL, NULL );
        result = sizeNeeded;
        out[sizeNeeded] = NullTerminator;
        return true;
    }
    CUL::Assert::check( false, "TOO SMALL BUFFER." );
#else // #if CUL_USE_WCHAR
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;
    const std::string stringCpy = converterX.to_bytes(in);
    copyString( out, stringCpy.c_str() );

    return true;
#endif // #if CUL_USE_WCHAR
    return false;
}

Length String::wideStringToChar( char& inOut, wchar_t inChar)
{
#if CUL_USE_WCHAR
    UINT codePage = CP_ACP;
    DWORD dwFlags = WC_COMPOSITECHECK;
    const int sizeNeeded = WideCharToMultiByte( codePage, dwFlags, &inChar, 1, NULL, 0, NULL, NULL );

    char result[4];
    const auto convertedLength = WideCharToMultiByte( codePage, dwFlags, &inChar, 1, &result[0], sizeNeeded, NULL, NULL );

    return 1;

#else // #if CUL_USE_WCHAR
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;
    const std::string stringCpy = converterX.to_bytes(inChar);
    inOut = stringCpy[0];

    return true;
#endif // #if CUL_USE_WCHAR
}

Length String::charToWideString( Length codePage, wchar_t* out, Length outSize, const char* in )
{
    return charToWideString( codePage, out, outSize, in, std::strlen( in ) );
}

Length String::charToWideString( Length codePage, wchar_t* out, Length outSize, const char* in, Length inSize )
{
    CUL::Assert::simple(outSize >= inSize, "NOT ENOUGH PLACE FOR STRING");

    Length result = 0u;
#if CUL_USE_WCHAR
    int cbMultiByte = -1;

    /*
    Flags indicating the conversion type. The application can specify a combination of the following values, with MB_PRECOMPOSED being the
    default. MB_PRECOMPOSED and MB_COMPOSITE are mutually exclusive. MB_USEGLYPHCHARS and MB_ERR_INVALID_CHARS can be set regardless of the
    state of the other flags.
    */
    DWORD dwFlags = 0;
    int wcharsNum = MultiByteToWideChar( codePage, dwFlags, in, cbMultiByte, NULL, 0 );

    if( wcharsNum < outSize )
    {
        MultiByteToWideChar( codePage, dwFlags, in, cbMultiByte, out, wcharsNum );
        result = wcharsNum;
    }
    return result;
#else // #if CUL_USE_WCHAR
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;
    const std::wstring wstringCopy = converterX.from_bytes(in);
    copyString(out, outSize, wstringCopy.c_str(), wstringCopy.size());

    return wstringCopy.size();
#endif // #if CUL_USE_WCHAR
}

Length String::charToWideString( Length codePage, wchar_t& out, char in )
{
#if CUL_USE_WCHAR
    int cbMultiByte = -1;
    /*
    Flags indicating the conversion type. The application can specify a combination of the following values, with MB_PRECOMPOSED being the
    default. MB_PRECOMPOSED and MB_COMPOSITE are mutually exclusive. MB_USEGLYPHCHARS and MB_ERR_INVALID_CHARS can be set regardless of the
    state of the other flags.
    */
    DWORD dwFlags = 0;
    int wcharsNum = MultiByteToWideChar( codePage, dwFlags, &in, cbMultiByte, NULL, 0 );

    wchar_t result[4];
    const auto convertedLength = MultiByteToWideChar( codePage, dwFlags, &in, cbMultiByte, &result[0], wcharsNum );
    return 1;

#else // #if CUL_USE_WCHAR
    throw std::logic_error( "Method not implemented" );
    return -1;
#endif // #if CUL_USE_WCHAR
}

void String::copyString( char* target, const char* source )
{
    copyString( target, strLen( target ), source, strLen( source ) );
}

void String::copyString(char* target, Length targetSize, const char* source, Length sourceSize)
{
    CUL::Assert::simple(targetSize >= sourceSize, "TARGET TOO SMALL!");
    std::strncpy(target, source, static_cast<std::size_t>(sourceSize + 1));
}

void String::copyString( wchar_t* target, const wchar_t* source )
{
    copyString( target, strLen( target ), source, strLen( source ) );
}

void String::copyString( wchar_t* target, Length targetSize, const wchar_t* source, Length sourceSizeS )
{
    CUL::Assert::simple( targetSize >= sourceSizeS, "TARGET TOO SMALL!" );
    const std::size_t sourceSize = static_cast<std::size_t>( sourceSizeS );
    for( std::size_t i = 0; i <= sourceSize; ++i )
    {
        const UnderlyingChar sourceChar = source[i];
        target[i] = sourceChar;
    }
}

std::int32_t String::cmp( const char* s1, const char* s2 )
{
    return std::strcmp( s1, s2 );
}

std::int32_t String::cmp( const wchar_t* s1, const wchar_t* s2 )
{
    return std::wcscmp( s1, s2 );
}

std::int32_t String::strLen( const char* inString )
{
    return static_cast<Length>( std::strlen( inString ) );
}

std::int32_t String::strLen( const wchar_t* inString )
{
    return std::wcslen( inString );
}

void String::toLower( char* inOut )
{
    toLower( inOut, strLen( inOut ) );
}

void String::toLower( char* inOut, std::int32_t size )
{
    for( std::int32_t i = 0; i < size; ++i )
    {
        inOut[i] = std::tolower( inOut[i] );
    }
}

void String::toLower( wchar_t* inOut )
{
    toLower( inOut, strLen( inOut ) );
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
    toUpper( inOut, strLen( inOut ) );
}

void String::toUpper( char* inOut, std::int32_t size )
{
    for( std::int32_t i = 0; i < size; ++i )
    {
        inOut[i] = static_cast<char>(std::toupper( inOut[i] ));
    }
}

void String::toUpper( wchar_t* inOut )
{
    toUpper( inOut, strLen( inOut ) );
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
}

void String::verify()
{
    const std::size_t currentSize = static_cast<std::size_t>( m_size );
    for( std::size_t i = 0; i < currentSize; ++i )
    {
        CUL::Assert::check( m_value[i] != NullTerminator, "FOUND NULL TERMINATOR IN BETWEEN RANGE!" );
    }
}

void String::createFrom(const String& arg)
{
    if(arg.m_size == 0)
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
        if(arg.m_dynamicValue)
        {
            m_dynamicValue = new UnderlyingChar[static_cast<std::size_t>(m_capacity)];
            m_value = m_dynamicValue;
        }
        else
        {
            m_value = &m_staticValue[0];
        }
        copyString(m_value, copySize, arg.m_value, copySize);
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
        if( m_size > 0 )
        {
            delete m_dynamicValue;
            m_dynamicValue = nullptr;
            m_value = &m_staticValue[0];
            copyString( m_value, m_size, arg.m_value, m_size );
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
#else // #if CUL_USE_WCHAR
    std::strcpy( m_value, arg ? "true" : "false" );
#endif // #if CUL_USE_WCHAR
}

void String::createFrom( const char* arg )
{
    const Length newLength = strLen( arg );
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
        setSize( strLen( m_value ) );
    }
#else // #if CUL_USE_WCHAR
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
#endif // #if CUL_USE_WCHAR
}

void String::createFrom( const std::string& arg )
{
    const Length argLen = static_cast<Length>(arg.size());
    const Length newLength = static_cast<Length>(argLen * 1.2f);
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

    if( newLength == 0 )
    {
        m_value[0] = NullTerminator;
    }
    else
    {
        const Length newSize = charToWideString( CP_ACP, m_value, m_capacity, arg.c_str(), argLen );
        if( newSize != newLength )
        {
            LOG::ILogger::getInstance().logVariable( LOG::Severity::WARN, "Difference between" );
        }
    }
#else // #if CUL_USE_WCHAR
    if( argLen == 0 )
    {
        m_value[0] = NullTerminator;
    }
    else
    {
        copyString( m_value, m_capacity, arg.c_str(), static_cast<Length>( arg.size() ) );
    }
#endif // #if CUL_USE_WCHAR
    setSize( argLen );
}

void String::createFrom( const std::wstring& arg )
{
    const Length argLen = static_cast<Length>( arg.size() );
    grow( argLen, false );
#if CUL_USE_WCHAR
    copyString( m_value, m_capacity, arg.c_str(), argLen );
#else
    wideStringToChar(m_value, m_capacity, arg.c_str(), argLen);
#endif
    setSize( argLen );
}

void String::createFrom( const wchar_t* arg )
{
    const Length newLength = strLen( arg );
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

    wideStringToChar(m_value, m_capacity, arg, newLength );
#endif
    setSize( newLength );
}

void String::createFrom( std::int32_t arg )
{
#if CUL_USE_WCHAR
    const std::wstring temp = std::to_wstring( arg );
#else // #if CUL_USE_WCHAR
    const std::string temp = std::to_string( arg );
#endif // #if CUL_USE_WCHAR
    createFrom( temp );
}

void String::createFrom( std::uint32_t arg )
{
#if CUL_USE_WCHAR
    const std::wstring temp = std::to_wstring( arg );
#else // #if CUL_USE_WCHAR
    const std::string temp = std::to_string( arg );
#endif // #if CUL_USE_WCHAR
    createFrom( temp );
}

void String::createFrom( std::int64_t arg )
{
#if CUL_USE_WCHAR
    const std::wstring temp = std::to_wstring( arg );
#else // #if CUL_USE_WCHAR
    const std::string temp = std::to_string( arg );
#endif // #if CUL_USE_WCHAR
    createFrom( temp );
}

void String::createFrom( std::uint64_t arg )
{
#if CUL_USE_WCHAR
    const std::wstring temp = std::to_wstring( arg );
#else // #if CUL_USE_WCHAR
    const std::string temp = std::to_string( arg );
#endif // #if CUL_USE_WCHAR
    createFrom( temp );
}

void String::createFrom( float arg )
{
#if CUL_USE_WCHAR
    const std::wstring temp = std::to_wstring( arg );
#else // #if CUL_USE_WCHAR
    const std::string temp = std::to_string( arg );
#endif // #if CUL_USE_WCHAR
    createFrom( temp );
}

void String::createFrom( double arg )
{
#if CUL_USE_WCHAR
    const std::wstring temp = std::to_wstring( arg );
#else // #if CUL_USE_WCHAR
    const std::string temp = std::to_string( arg );
#endif // #if CUL_USE_WCHAR
    createFrom( temp );
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
        delete m_value;
    }

    m_value = newArray;
    m_dynamicValue = newArray;

    if( keepValue && m_size == 0 )
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
    const std::size_t capacity = static_cast<std::size_t>(m_capacity);
    for(std::size_t i = 0; i < capacity; ++i)
    {
        m_staticValue[i] = L'D';
    }
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
    setSize( 0 );
    m_value = nullptr;
    m_dynamicValue = nullptr;
    m_capacity = SSO_Size;

    if( m_temp )
    {
        delete[] m_temp;
        m_temp = nullptr;
    }

    m_value = &m_staticValue[0];
}

String CULLib_API CUL::operator+( const char* arg1, const String& arg2 )
{
    String left( arg1 );
    String result = left + arg2;

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