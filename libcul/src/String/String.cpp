#include "CUL/String/String.hpp"

#include "Filesystem/FSUtils.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/Log/ILogger.hpp"
#include "CUL/String/StringUtil.hpp"

#include "CUL/STL_IMPORTS/STD_algorithm.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"
#include "CUL/STL_IMPORTS/STD_sstream.hpp"
#include "CUL/STL_IMPORTS/STD_cmath.hpp"

#include "CUL/STL_IMPORTS/STD_codecvt.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"
#include "CUL/STL_IMPORTS/STD_cstdarg.hpp"
#include "CUL/STL_IMPORTS/STD_cwchar.hpp"
#include "CUL/STL_IMPORTS/STD_wctype.hpp"

#define CUL_DEBUG_STRING 0

using namespace CUL;

const char* IString::getUtfChar() const
{
    CUL::Assert::simple( false, "Method void removeAll( const wchar_t inWhat ) not implemented" );
    return nullptr;
}

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
    return getUtfChar();
}

String String::operator+( const String& arg ) const
{
    String result( getString() );
    result.append( arg.getString() );
    return result;
}

String& String::operator+=( const String& arg )
{
    append( arg.getString() );
    return *this;
}

String::UnderlyingChar String::operator[]( std::int32_t inPos ) const
{
    return m_value[inPos];
}

String::UnderlyingChar& String::operator[]( std::int32_t inPos )
{
    return m_value[inPos];
}

bool String::operator<( const String& arg ) const
{
    return StringUtil::cmp( m_value, arg.m_value ) < 0;
}

bool String::operator>( const String& arg ) const
{
    return StringUtil::cmp( m_value, arg.m_value ) > 0;
}

String String::substr( std::int32_t pos, std::int32_t len ) const
{
    const std::int32_t targetSize = pos + len;
    if( targetSize > m_size )
    {
        return String{};
    }

    String strResult;
    strResult.grow( len, false );
    StringUtil::copyString( strResult.m_value, strResult.m_capacity, m_value + pos, len );
    strResult.m_value[len] = NullTerminator;
    strResult.setSize( len );
    strResult.removePrecedingZero();
    return strResult;
}

void String::toLower()
{
    StringUtil::toLower( m_value, m_size );
}

String String::toLowerR() const
{
    String result = *this;

    result.toLower();

    return result;
}

void String::toUpper()
{
    StringUtil::toUpper( m_value, m_size );
}

bool String::contains( const char* inputString ) const
{
#if CUL_USE_WCHAR
    const std::int32_t inputLen = StringUtil::strLen( inputString );
    const std::int32_t wcharLen = inputLen * 2;
    wchar_t* temp = new wchar_t[static_cast<std::size_t>( wcharLen )];
    StringUtil::charToWideString( CP_ACP, temp, wcharLen, inputString, inputLen );

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

    const std::int32_t newSize =
        static_cast<std::int32_t>( StringUtil::replaceCalculateRequiredSize( m_value, inWhat.m_value, inFor.m_value, true ) );

    if( newSize > m_capacity )
    {
        grow( newSize, true );
    }

    StringUtil::replace( m_value, static_cast<std::size_t>( newSize + 1 ), inWhat.m_value, inFor.m_value, true );
    m_size = StringUtil::strLen( m_value );
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
    StringUtil::charToWideString( CP_ACP, inConverted, inWhat );

    wchar_t forConverted;
    StringUtil::charToWideString( CP_ACP, forConverted, inFor );

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

    StringUtil::replace( m_value, inWhat, inFor, allOccurences );
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
    StringUtil::charToWideString( 0, what, inWhat );
    StringUtil::removeAll( m_value, what );
#else   // CUL_USE_WCHAR
    UnderlyingChar what = inWhat;
    StringUtil::removeAll( m_value, inWhat );
#endif  // CUL_USE_WCHAR
}

void StringUtil::removeAll( char* inOut, char toRemove )
{
    if( !inOut )
    {
        return;
    }

    char* read = inOut;
    char* write = inOut;

    while( *read )
    {
        if( *read != toRemove )
        {
            *write++ = *read;
        }
        ++read;
    }

    *write = '\0';
}

void StringUtil::removeAll( char* inOut, wchar_t toRemove )
{
    char toRemoveUtfchar;
    StringUtil::wideStringToChar( toRemoveUtfchar, toRemove );
    removeAll( inOut, toRemoveUtfchar );
}

void StringUtil::removeAll( wchar_t* inOut, char toRemove )
{
    std::string inOutAsStr;
    wideStringToChar( inOutAsStr, inOut );
    removeAll( inOutAsStr.data(), toRemove );

    std::wstring output;
    // output.resize( inOutAsStr.size() * 2 );
    charToWideString( output, inOutAsStr );
    StringUtil::copyString( inOut, output.c_str() );
}

void String::removeAll( const wchar_t inWhat )
{
    StringUtil::removeAll( m_value, inWhat );
}

bool String::doesEndWith( const std::string& end ) const
{
    if( m_size == 0 )
    {
        return false;
    }

    const auto endLen_t = end.size();
    const auto endLen = static_cast<std::int32_t>( endLen_t );

    if( m_size < endLen )
    {
        return false;
    }

    const std::size_t endPos = static_cast<std::size_t>( m_size - endLen );

#if CUL_USE_WCHAR
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converterX;
    const std::wstring stringCpy = converterX.from_bytes( end );
    return StringUtil::equals( &m_value[endPos], stringCpy.c_str() );
#else   // #if CUL_USE_WCHAR
    return StringUtil::equals( &m_value[endPos], end.c_str() );
#endif  // #if CUL_USE_WCHAR
}

bool String::doesEndWith( const std::wstring& end ) const
{
    if( m_size == 0 )
    {
        return false;
    }

    const auto endLen_t = end.size();
    const auto endLen = static_cast<std::int32_t>( endLen_t );

    if( m_size < endLen )
    {
        return false;
    }

    const std::size_t endPos = m_size - endLen_t;
#if CUL_USE_WCHAR
    return StringUtil::equals( &m_value[endPos], end.c_str(), endLen_t );
#else   // #if CUL_USE_WCHAR
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converterX;
    const std::string stringCpy = converterX.to_bytes( end );

    return StringUtil::equals( &m_value[endPos], stringCpy.c_str() );
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

const IString::UnderlyingChar* String::getCharVal() const
{
    return m_value;
}

const char* String::getUtfChar() const
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
    const std::int32_t charLength = m_size != 0 ? 2 * m_size : 2;
    m_temp = new char[static_cast<std::size_t>( charLength )];
    StringUtil::wideStringToChar( m_temp, charLength, m_value, m_size );
#else   // #if CUL_USE_WCHAR
    const std::size_t wcharBufferSize = 2u * m_size;
    m_temp = new wchar_t[wcharBufferSize];
    StringUtil::charToWideString( 0, m_temp, wcharBufferSize, m_value, m_size );
#endif  // #if CUL_USE_WCHAR
}

const String::UnderlyingChar* String::getChar() const
{
    return m_value;
}

bool String::isFloat() const
{
    std::istringstream iss( getUtfChar() );
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
    return std::stoll( m_value, nullptr, 10 );
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
    if( lowerCaseValue.equals( L"true" ) )
    {
        return ThreeState::True;
    }

    if( StringUtil::cmp( m_value, L"false" ) )
    {
        return ThreeState::False;
    }
#else   // #if CUL_USE_WCHAR
    if( lowerCaseValue.equals( "true" ) )
    {
        return ThreeState::True;
    }

    if( StringUtil::cmp( m_value, "false" ) )
    {
        return ThreeState::False;
    }
#endif  // #if CUL_USE_WCHAR

    return ThreeState::Undetermined;
}

std::int32_t String::length() const
{
    return m_size;
}

std::int32_t String::size() const
{
    return m_size;
}

std::int32_t String::capacity() const
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

constexpr char hexmap[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

#ifdef _MSC_VER
    // avoid warning about unreachable statement at the end of filesize()
    #pragma warning( push )
    #pragma warning( disable : 4365 )
#endif
void StringUtil::valueToHex( std::uint16_t inValue, std::array<std::uint8_t, 2>& outValue )
{
    outValue[0u] = hexmap[( inValue & 0xF0 ) >> 8];
    outValue[1u] = hexmap[( inValue & 0x0F ) >> 0];
}

void StringUtil::valueToHex( std::uint8_t inValue, std::uint8_t& outValue )
{
    outValue = hexmap[( inValue & 0x0F ) >> 0];
}
#ifdef _MSC_VER
    #pragma warning( pop )
#endif
std::uint8_t StringUtil::charToValue( std::uint8_t inValue )
{
    return inValue - 48u;
}

bool StringUtil::isNumber( const char* inNumber )
{
    return isNumber( inNumber, (std::size_t)StringUtil::strLen( inNumber ) );
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
    return isNumber( inNumber, (std::size_t)StringUtil::strLen( inNumber ) );
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
    const std::uint16_t MSB = static_cast<std::uint16_t>( inValue & 0xF0 >> 4 );
    const std::uint16_t LSB = static_cast<std::uint16_t>( inValue & 0x0F >> 0 );
    return 16u * MSB + LSB;
}

std::uint8_t hexToChar( std::uint8_t in )
{
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

    const std::uint8_t upper = static_cast<std::uint8_t>( (std::uint8_t)( in & 0xF0 ) );
    const std::uint8_t lower = static_cast<std::uint8_t>( (std::uint8_t)( in & 0x0F ) );
    const std::uint8_t MSB_i = static_cast<std::uint8_t>( lower );
    const std::uint8_t LSB_i = static_cast<std::uint8_t>( upper >> 4 );

    outValue[1] = hexToChar( MSB_i );
    outValue[0] = hexToChar( LSB_i );
}

void StringUtil::valueToHex( char in, std::array<char, 2>& outValue )
{
    const std::uint8_t upper = static_cast<std::uint8_t>( ( in & 0xF0 ) );
    const std::uint8_t lower = static_cast<std::uint8_t>( ( in & 0x0F ) );
    const std::uint8_t MSB_i = lower;
    const std::uint8_t LSB_i = static_cast<std::uint8_t>( upper >> 4 );

    outValue[1] = (char)hexToChar( MSB_i );
    outValue[0] = (char)hexToChar( LSB_i );
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
        StringUtil::valueToHex( current, twoBytes );
        result.push_back( twoBytes[0] );
        result.push_back( twoBytes[1] );
    }

    releaseBuffer();
    const std::size_t newBufferSize = result.size();
    grow( static_cast<std::int32_t>( newBufferSize + 1u ), false );

    for( std::size_t i = 0u; i < newBufferSize; ++i )
    {
        m_value[i] = result[i];
    }
    m_value[newBufferSize] = NullTerminator;

    m_size = (std::int32_t)newBufferSize;
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
    StringUtil::wideStringToChar( temp, m_value + 1u );
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

    std::int32_t zeroCount{ 0u };
    for( std::int32_t i = target.size() - 1; i >= 0; --i )
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
    StringUtil::wideStringToChar( temp, m_value + 1u );
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

    std::int32_t zeroCount{ 0u };
    for( std::int32_t i = target.size() - 1; i >= 0; --i )
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

    if( m_size + 1 > static_cast<std::int32_t>( SSO_Size ) )
    {
        return;
    }

    if( m_dynamicValue == nullptr )
    {
        return;
    }

    StringUtil::copyString( &m_staticValue[0], SSO_Size, m_dynamicValue, m_size );
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

std::vector<String> String::split( const String& delimiter ) const
{
    std::vector<String> result;
    const auto sentence = StringUtil::split( m_value, delimiter.getString() );
    for( const auto& word : sentence )
    {
        result.push_back( word );
    }
    return result;
}

std::vector<String> String::split( const char delimiter ) const
{
    auto splitedString = StringUtil::split( m_value, delimiter );
    std::vector<String> result;
    result.resize( splitedString.size() );
    for( const auto& str : splitedString )
    {
        result.push_back( str );
    }
    return result;
}

std::vector<String> String::split( const wchar_t delimiter ) const
{
    auto splitedString = StringUtil::split( m_value, delimiter );
    std::vector<String> result;
    result.resize( splitedString.size() );
    for( const auto& str : splitedString )
    {
        result.push_back( str );
    }
    return result;
}

bool String::getIsSerialized() const
{
    return m_serialized;
}

void String::setSize( std::int32_t newSize )
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
        const std::int32_t copySize = m_size + 1;  // +1 for nullterminator.
        if( arg.m_dynamicValue )
        {
            m_dynamicValue = new UnderlyingChar[static_cast<std::size_t>( m_capacity )];
            m_value = m_dynamicValue;
        }
        else
        {
            m_value = &m_staticValue[0];
        }
        StringUtil::copyString( m_value, copySize, arg.m_value, copySize );
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
            StringUtil::copyString( m_value, m_size, arg.m_value, m_size );
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
    StringUtil::copyString( m_value, m_capacity, arg ? L"true" : L"false", m_size );
#else   // #if CUL_USE_WCHAR
    std::strcpy( m_value, arg ? "true" : "false" );
#endif  // #if CUL_USE_WCHAR
    deleteTemp();
}

void String::createFrom( const char* arg )
{
    const std::int32_t newLength = StringUtil::strLen( arg );
    grow( newLength, false );

#if CUL_USE_WCHAR
    if( newLength == 0 )
    {
        m_value[0] = NullTerminator;
        setSize( 0 );
    }
    else
    {
        StringUtil::charToWideString( CP_ACP, m_value, m_capacity, arg );
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
        StringUtil::copyString( m_value, m_capacity, arg, newLength );
        setSize( newLength );
    }
#endif  // #if CUL_USE_WCHAR
    deleteTemp();
    removePrecedingZero();
}

void String::createFrom( const std::string& arg )
{
#if CUL_USE_WCHAR
    const std::int32_t argLen = static_cast<std::int32_t>( arg.size() );
    const std::int32_t newLength = static_cast<std::int32_t>( static_cast<float>( argLen ) * 1.2f );
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
        StringUtil::charToWideString( CP_ACP, m_value, m_capacity, arg.c_str(), argLen );
    }
#else   // #if CUL_USE_WCHAR
    const std::int32_t argLen = static_cast<std::int32_t>( arg.size() );
    if( argLen == 0 )
    {
        m_value[0] = NullTerminator;
    }
    else
    {
        grow( argLen + 1, false );
        StringUtil::copyString( m_value, m_capacity, arg.c_str(), arg.size() );
    }
#endif  // #if CUL_USE_WCHAR
    setSize( argLen );
    deleteTemp();
}

void String::createFrom( const std::wstring& arg )
{
#if CUL_USE_WCHAR
    const std::int32_t argLen = static_cast<std::int32_t>( arg.size() );
    grow( argLen, false );
    StringUtil::copyString( m_value, m_capacity, arg.c_str(), argLen );
    setSize( argLen );
#else
    std::string out;
    StringUtil::wideStringToChar( out, arg );

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
    const std::int32_t newLength = StringUtil::strLen( arg );
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
    StringUtil::copyString( m_value, m_capacity, arg, newLength );
#else

    StringUtil::wideStringToChar( m_value, m_capacity, arg, newLength );
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

void String::grow( std::int32_t targetSize, bool keepValue )
{
    if( targetSize + 1 < m_capacity )
    {
        return;
    }

    const std::int32_t oldCapacity = m_capacity;
    m_capacity = calcualteCapacity( targetSize );

    UnderlyingChar* newArray = new UnderlyingChar[static_cast<std::size_t>( m_capacity )];

    if( keepValue && m_size > 0 )
    {
        StringUtil::copyString( newArray, m_capacity, m_value, m_size + 1 );
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

std::int32_t String::calcualteCapacity( std::int32_t inSize ) const
{
    if( inSize < m_capacity - 1 )
    {
        return m_capacity;
    }

    return static_cast<std::int32_t>( static_cast<float>( ( inSize + 1 ) ) * CapacityCoeficient );
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

    const std::int32_t sizeCast = static_cast<std::int32_t>( m_size );
    for( std::int32_t i = sizeCast - 1; i >= 0; )
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
        const auto sizeCast2 = static_cast<std::int32_t>( m_size );
        for( std::int32_t j = sizeCast2 - 1; j > i; --j )
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

    const std::int32_t sizeCast = static_cast<std::int32_t>( m_size );
    for( std::int32_t i = sizeCast - 1; i >= 0; )
    {
        const std::size_t iCast = static_cast<std::size_t>( i );
        if( m_value[iCast] != SingleQuote )
        {
            --i;
            continue;
        }

        if( i < 1 )
        {
            --i;
            continue;
        }

        std::int32_t consecutiveQuotesCount{ 0 };
        std::int32_t sizeCast2 = static_cast<std::int32_t>( m_size );
        for( std::int32_t j = i; j >= 0; --j )
        {
            const std::size_t jCast = static_cast<std::size_t>( j );
            if( m_value[jCast] == SingleQuote )
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
        sizeCast2 = static_cast<std::int32_t>( m_size );
        for( std::int32_t j = sizeCast2 - 1; j > i; --j )
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

    for( std::int32_t i = 0; i < m_size; )
    {
        const std::size_t iCast = static_cast<std::size_t>( i );

        if( m_value[iCast] != SingleQuote )
        {
            ++i;
            continue;
        }

        std::int32_t consecutiveQuotesCount{ 0 };
        for( std::int32_t j = i; j < m_size; ++j )
        {
            const std::size_t jCast = static_cast<std::size_t>( j );
            if( m_value[jCast] == SingleQuote )
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

        const std::int32_t reduceSize = consecutiveQuotesCount > 1 ? consecutiveQuotesCount / 2 : 0;
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

std::int32_t String::count( wchar_t inChar ) const
{
    if( m_size == 0u )
    {
        return 0;
    }

    std::int32_t result{ 0 };

#if CUL_USE_WCHAR
    wchar_t toBeFound = inChar;
#else
    char toBeFound = static_cast<char>( inChar );
    // wideStringToChar( toBeFound, inChar );
    Assert::check( false, "NOT IMPLEMENTED!" );
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
    if( m_size < 2 )
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

        for( std::int32_t i = 0u; i < m_size; ++i )
        {
            m_value[i] = m_value[i + 1u];
        }
        --m_size;
    }
}

std::int32_t String::count( char inChar ) const
{
    if( m_size == 0u )
    {
        return 0;
    }

    std::int32_t result{ 0 };
#if CUL_USE_WCHAR
    wchar_t toBeFound;
    StringUtil::charToWideString( CP_ACP, toBeFound, inChar );
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

std::int32_t StringUtil::strLen( const char* inString )
{
    return static_cast<std::int32_t>( std::strlen( inString ) );
}

std::int32_t StringUtil::strLen( const wchar_t* inString )
{
    return static_cast<std::int32_t>( std::wcslen( inString ) );
}

std::uint64_t StringUtil::strToUint64( const std::wstring& inString )
{
    std::string out;
    StringUtil::wideStringToChar( out, inString );
    return strToUint64( out );
}

std::uint64_t StringUtil::strToUint64( const std::string& inString )
{
    std::uint64_t result;
    std::istringstream iss( inString );
    iss >> result;
    return result;
}

std::size_t StringUtil::replaceCalculateRequiredSize( const char* source, const char* inWhat, const char* inFor, bool allOccurences )
{
    if( !source || !inWhat || !inFor )
    {
        return 0;
    }

    const std::size_t sourceLen = std::strlen( source );
    const std::size_t lenWhat = std::strlen( inWhat );
    const std::size_t lenFor = std::strlen( inFor );

    if( lenWhat == 0 )
    {
        return sourceLen + 1;
    }

    std::size_t count = 0;
    const char* pos = source;

    while( ( pos = std::strstr( pos, inWhat ) ) != nullptr )
    {
        ++count;
        pos += lenWhat;

        if( !allOccurences )
            break;
    }

    // +1 for null terminator
    return sourceLen + count * ( lenFor - lenWhat ) + 1;
}

std::size_t StringUtil::replaceCalculateRequiredSize( const wchar_t* source, const wchar_t* inWhat, const wchar_t* inFor,
                                                      bool allOccurences )
{
    if( !source || !inWhat || !inFor )
    {
        return 0;
    }

    const std::size_t sourceLen = strLen( source );
    const std::size_t lenWhat = strLen( inWhat );
    const std::size_t lenFor = strLen( inFor );

    if( lenWhat == 0 )
    {
        return sourceLen + 1;
    }

    std::size_t count = 0;
    const wchar_t* pos = source;

    while( ( pos = std::wcsstr( pos, inWhat ) ) != nullptr )
    {
        ++count;
        pos += lenWhat;

        if( !allOccurences )
            break;
    }

    // +1 for null terminator
    return sourceLen + count * ( lenFor - lenWhat ) + 1;
}

bool StringUtil::replace( char* inSource, const char inWhat, const char inFor, bool allOccurences )
{
    const std::size_t sourceSize = strLen( inSource );

    for( std::size_t i = 0; i < sourceSize; ++i )
    {
        if( inSource[i] == inWhat )
        {
            inSource[i] = inFor;
            if( allOccurences == false )
            {
                return true;
            }
        }
    }
    return false;
}

bool StringUtil::replace( wchar_t* inSource, const wchar_t inWhat, const wchar_t inFor, bool allOccurences )
{
    const std::size_t sourceSize = strLen( inSource );

    for( std::size_t i = 0; i < sourceSize; ++i )
    {
        if( inSource[i] == inWhat )
        {
            inSource[i] = inFor;
            if( allOccurences == false )
            {
                return true;
            }
        }
    }
    return false;
}

bool StringUtil::replace( char* inSource, std::size_t inSourceSize, const char* inWhat, const char* inFor, bool allOccurences )
{
    if( !inSource || !inWhat || !inFor )
    {
        return false;
    }

    const std::size_t lenWhat = std::strlen( inWhat );
    const std::size_t lenFor = std::strlen( inFor );

    if( lenWhat == 0 )
    {
        return false;
    }

    char* pos = inSource;

    while( ( pos = std::strstr( pos, inWhat ) ) != nullptr )
    {
        const std::size_t currentLen = std::strlen( inSource );

        // Calculate new length after replacement
        const std::size_t newLen = currentLen - lenWhat + lenFor;

        // Check buffer overflow
        if( newLen + 1 > inSourceSize )
        {
            return false;
        }

        // Move the tail if lengths differ
        if( lenFor != lenWhat )
        {
            std::memmove( pos + lenFor, pos + lenWhat, currentLen - ( pos - inSource ) - lenWhat + 1 );
        }

        // Copy replacement text
        std::memcpy( pos, inFor, lenFor );

        if( !allOccurences )
            break;

        pos += lenFor;  // continue after replaced text
    }

    return true;
}

bool StringUtil::replace( wchar_t* inSource, std::size_t inSourceSize, const wchar_t* inWhat, const wchar_t* inFor, bool allOccurences )
{
    if( !inSource || !inWhat || !inFor )
    {
        return false;
    }

    const std::size_t lenWhat = strLen( inWhat );
    const std::size_t lenFor = strLen( inFor );

    if( lenWhat == 0 )
    {
        return false;
    }

    wchar_t* pos = inSource;

    while( ( pos = std::wcsstr( pos, inWhat ) ) != nullptr )
    {
        const std::size_t currentLen = strLen( inSource );

        // Calculate new length after replacement
        const std::size_t newLen = currentLen - lenWhat + lenFor;

        // Check buffer overflow
        if( newLen + 1 > inSourceSize )
        {
            return false;
        }

        // Move the tail if lengths differ
        if( lenFor != lenWhat )
        {
            std::wmemmove( pos + lenFor, pos + lenWhat, currentLen - ( pos - inSource ) - lenWhat + 1 );
        }

        // Copy replacement text
        std::wmemcpy( pos, inFor, lenFor );

        if( !allOccurences )
        {
            break;
        }

        pos += lenFor;  // continue after replaced text
    }

    return true;
}

void String::erase( std::int32_t offset, std::int32_t len )
{
    if( offset + len > m_size )
    {
        return;
    }

    const std::int32_t stop = offset + len;
    for( std::int32_t i = offset; i < m_size; ++i )
    {
        if( ( i >= offset ) && ( i < stop ) )
        {
            m_value[i] = m_value[i + offset];
        }
        else
        {
            m_value[i] = NullTerminator;
        }
    }
}
