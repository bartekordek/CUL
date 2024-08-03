#include "CUL/String.hpp"

#include "Filesystem/FSUtils.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"

#include "CUL/STL_IMPORTS/STD_algorithm.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"
#include "CUL/STL_IMPORTS/STD_sstream.hpp"
#include "CUL/STL_IMPORTS/STD_cmath.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"
#include "CUL/STL_IMPORTS/STD_wctype.hpp"

using namespace CUL;

String::String() noexcept:
    m_capacity( SSO_Size ),
    m_size(0),
    m_value( &m_staticValue[0] )
{
    m_value = &m_staticValue[0];
#if defined( CUL_WINDOWS )
    m_value[0] = L'\0';
#else // #if defined( CUL_WINDOWS )
    m_value[0] = '\0';
#endif // 
}

String::String( const String& arg ) noexcept
{
    createFrom( arg );
}

String::String( String&& arg ) noexcept
{
    createFromMove( arg );
}

String::String( const bool arg ) noexcept
{
    createFrom( arg );
}

String::String( const char* arg ) noexcept
{
    createFrom( arg );
}

String::String( const wchar_t* arg ) noexcept
{
    createFrom( arg );
}

String::String( unsigned char* arg ) noexcept
{
    throw std::logic_error( "Method not implemented" );
}

String::String( const std::string& arg ) noexcept
{
    createFrom( arg );
}

String::String( const std::wstring& arg ) noexcept
{
    createFrom( arg );
}

String::String( float arg ) noexcept
{
    throw std::logic_error( "Method not implemented" );
}

String::String( double arg ) noexcept
{
    throw std::logic_error( "Method not implemented" );
}

String::String( std::int32_t arg ) noexcept
{
    createFrom( arg );
}

String::String( unsigned int arg ) noexcept
{
    throw std::logic_error( "Method not implemented" );
}

String::String( int64_t arg ) noexcept
{
    throw std::logic_error( "Method not implemented" );
}

String::String( uint64_t arg ) noexcept
{
    throw std::logic_error( "Method not implemented" );
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

String& String::operator=( const bool arg )
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
String& String::operator=( unsigned char* arg )
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
    //createFrom( arg );
    return *this;
}

String& String::operator=( double arg )
{
#if defined( CUL_WINDOWS )
    const std::wstring temp = std::to_wstring( arg );
    operator=( temp );
#else // #if defined( CUL_WINDOWS )
    throw std::logic_error( "Method not implemented" );
#endif // #if defined( CUL_WINDOWS )
    return *this;
}

String& String::operator=( std::int32_t arg )
{
    createFrom( arg );
    return *this;
}

String& String::operator=( unsigned arg )
{
#if defined( CUL_WINDOWS )
    const std::wstring temp = std::to_wstring( arg );
    operator=( temp );
#else // #if defined( CUL_WINDOWS )
    throw std::logic_error( "Method not implemented" );
#endif // #if defined( CUL_WINDOWS )
    return *this;
}

String& String::operator=( int64_t arg )
{
#if defined( CUL_WINDOWS )
    const std::wstring temp = std::to_wstring( arg );
    operator=( temp );
#else // #if defined( CUL_WINDOWS )
    throw std::logic_error( "Method not implemented" );
#endif // #if defined( CUL_WINDOWS )
    return *this;
}

String& String::operator=( uint64_t arg )
{
#if defined( CUL_WINDOWS )
    const std::wstring temp = std::to_wstring( arg );
    operator=( temp );
#else // #if defined( CUL_WINDOWS )
    throw std::logic_error( "Method not implemented" );
#endif // #if defined( CUL_WINDOWS )
    return *this;
}

String String::operator+( const String& arg ) const
{
    String result;
    const std::int32_t wholeSize = m_size + arg.m_size;

    result.reserve( wholeSize, false );

    copyString( result.m_value, wholeSize, m_value, m_size );
    copyString( result.m_value + m_size, wholeSize, arg.m_value, arg.m_size );
    result.m_size = wholeSize;
    return result;
}

String& String::operator+=( const String& arg )
{
    const std::int32_t newSize = m_size + arg.m_size;

    if( newSize == 58 )
    {
        auto x = 0;
    }

    if( m_capacity <= newSize )
    {
        grow( newSize, true );
    }

    copyString( m_value + m_size, m_capacity - m_size, arg.m_value, arg.m_size );
    m_size = newSize;

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
    return m_value == arg.m_value;
}

bool String::operator!=( const String& arg ) const
{
    return !operator==( arg );
}

bool String::operator==( const std::string& arg ) const
{
#if defined( CUL_WINDOWS )
    return m_value == FS::s2ws( arg );
#else // #if defined( CUL_WINDOWS )
    return m_value == arg;
#endif // #if defined( CUL_WINDOWS )
}

bool String::operator!=( const std::string& arg ) const
{
    return !operator==( arg );
}

bool String::operator==( const char* arg ) const
{
#if defined( CUL_WINDOWS )
    const Length argLen = strLen( arg );
    const Length bufferSize = 2 * argLen;
    UnderlyingChar* buffer = new UnderlyingChar[bufferSize];
    charToWideString( CP_ACP, buffer, bufferSize, arg, argLen );
    const bool result = cmp( m_value, buffer ) == 0;
    delete[] buffer;
    return result;
#else // #if defined( CUL_WINDOWS )
    return cmp(m_value, arg) == 0;
#endif // #if defined( CUL_WINDOWS )
}

bool String::operator!=( const char* arg ) const
{
#if defined( CUL_WINDOWS )
    return m_value != FS::s2ws( arg );
#else // #if defined( CUL_WINDOWS )
    return m_value != arg;
#endif // #if defined( CUL_WINDOWS )
}

bool String::operator!=( int arg ) const
{
    return !operator==( arg );
}

bool String::operator==( int arg ) const
{
#if defined( CUL_WINDOWS )
    return m_value == std::to_wstring( arg );
#else // #if defined( CUL_WINDOWS )
    return m_value == std::to_string( arg );
#endif // #if defined( CUL_WINDOWS )
}

bool String::operator!=( unsigned int arg ) const
{
    return !operator==( arg );
}

bool String::operator==( unsigned int arg ) const
{
#if defined( CUL_WINDOWS )
    return m_value == std::to_wstring( arg );
#else // #if defined( CUL_WINDOWS )
    return m_value == std::to_string( arg );
#endif // #if defined( CUL_WINDOWS )
}

bool String::operator!=( float arg ) const
{
    return !operator==( arg );
}

bool String::operator==( float arg ) const
{
#if defined( CUL_WINDOWS )
    return m_value == std::to_wstring( arg );
#else // #if defined( CUL_WINDOWS )
    return m_value == std::to_string( arg );
#endif // #if defined( CUL_WINDOWS )
}

bool String::operator!=( double arg ) const
{
    return !operator==( arg );
}

bool String::operator==( double arg ) const
{
#if defined( CUL_WINDOWS )
    return m_value == std::to_wstring( arg );
#else // #if defined( CUL_WINDOWS )
    return m_value == std::to_string( arg );
#endif // #if defined( CUL_WINDOWS )
}

bool String::operator<( const String& arg ) const
{
    return m_value < arg.m_value;
}

bool String::operator>( const String& arg ) const
{
    return m_value > arg.m_value;
}

bool String::operator()( const String& v1, const String& v2 ) const
{
    return v1 == v2;
}

std::int32_t String::find( const String& arg ) const
{
    return find( arg, 0 );
}

std::int32_t String::find( const String& arg, Length startPos ) const
{
    if( startPos + arg.m_size >= m_size )
    {
        return -1;
    }

    for( std::int32_t i = startPos; i < m_size; ++i )
    {
        if( m_value[i] == arg.m_value[0] )
        {
            bool exact{ true };
            std::int32_t ii = i;
            for( std::int32_t j = 1; j < arg.m_size && ii < m_size; ++j )
            {
                if( m_value[ii] != arg.m_value[j] )
                {
                    exact = false;
                    break;
                }
            }

            if( exact )
            {
                return i;
            }
        }
    }
    return -1;
}

String String::substr( std::int32_t pos, std::int32_t len ) const
{
    const Length targetSize = pos + len;
    if( targetSize > m_size )
    {
        return String{};
    }

    String strResult;
    strResult.grow( len, false );
    copyString( strResult.m_value, strResult.m_capacity, m_value + pos, len );
    strResult.m_size = len;
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
#if defined(CUL_WINDOWS)
    const Length inputLen = strLen( inputString );
    const Length wcharLen = inputLen * 2;
    wchar_t* temp = new wchar_t[wcharLen];
    charToWideString( CP_ACP, temp, wcharLen - 1, inputString, inputLen );

    const bool result = find( temp ) != -1;
    delete temp;
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

        std::int32_t restIndex = index + inWhat.m_size;
        for( std::int32_t i = m_size -1; i > restIndex; --i )
        {
            m_value[i] = inWhat.m_value[i - 1];
        }
    }
    else if(diff < 0 )
    {
        throw std::logic_error("Method not implemented");
    }
    else
    {
        for( std::int32_t i = 0; i < inFor.m_size; ++i )
        {
            m_value[index + i] = inFor.m_value[i];
        }
    }
}

void String::replace( const char inWhat, const char inFor )
{
    throw std::logic_error( "Method not implemented" );
    //if( m_value.empty() )
    //{
    //    return;
    //}

    //auto cInWhat = static_cast<UnderlyingChar>( inWhat );
    //auto cInFor = static_cast<UnderlyingChar>( inFor );

    //size_t inWhatPosition = m_value.find( cInWhat );
    //while( UnderlyingType::npos != inWhatPosition )
    //{
    //    m_value.replace( inWhatPosition, 1, &cInFor );
    //    inWhatPosition = m_value.find( cInWhat );
    //}
}

void String::replace( const wchar_t inWhat, const wchar_t inFor )
{
    throw std::logic_error( "Method not implemented" );
    //    if( m_value.empty() )
//    {
//        return;
//    }
//
//#ifdef _MSC_VER
//    wchar_t cInWhat = inWhat;
//    wchar_t cInFor = inFor;
//#else
//    char cInWhat = inWhat;
//    char cInFor = inFor;
//#endif
//    size_t inWhatPosition = m_value.find( cInWhat );
//    while( UnderlyingType::npos != inWhatPosition )
//    {
//        m_value.replace( inWhatPosition, 1, &cInFor );
//        inWhatPosition = m_value.find( inWhat );
//    }
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
#if defined( CUL_WINDOWS )
    return FS::ws2s( m_value );
#else /// #if defined(CUL_WINDOWS)
    return m_value;
#endif // #if defined(CUL_WINDOWS)
}

std::wstring String::wstring() const
{
#if defined( CUL_WINDOWS )
    return m_value;
#else // #if defined(CUL_WINDOWS)
    return FS::s2ws( m_value );
#endif // #if defined(CUL_WINDOWS)
}

const String::UnderlyingType& String::getString() const
{
    return m_value;
}

const char* String::cStr() const
{
#if defined( CUL_WINDOWS )
    const Length charLength = m_size != 0 ? 2 * m_size : 2;
    char* result = new char[charLength];
    wideStringToChar( result, charLength, m_value, m_size );
    return result;
#else // #if defined( CUL_WINDOWS )
    throw std::logic_error( "Method not implemented" );
#endif // #if defined( CUL_WINDOWS )
}

const wchar_t* String::wCstr() const
{
    throw std::logic_error( "Method not implemented" );
    //#ifdef _MSC_VER
//    return m_value.c_str();
//#else
//    std::wstring resultString = FS::s2ws( m_value );
//    wchar_t* result = new wchar_t[resultString.size()];
//    mbstowcs( result, m_value.c_str(), resultString.size() );
//    return result;
//#endif
    return nullptr;
}

const String::UnderlyingChar* String::getChar() const
{
#if defined( CUL_WINDOWS )
    return m_value;
#else // #if defined( CUL_WINDOWS )
    throw std::logic_error( "Method not implemented" );
#endif // #if defined( CUL_WINDOWS )
    return nullptr;
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
    throw std::logic_error( "Method not implemented" );
    //    if( m_value.empty() )
//    {
//        return 0;
//    }
//
//    auto copy = m_value;
//    if( m_value[0] == 'u' )
//    {
//        copy = m_value.substr( 1, m_value.size() );
//    }
//#if defined( _MSC_VER )
//    std::string resultString = FS::ws2s( copy );
//    std::istringstream iss( resultString );
//#else
//    std::istringstream iss( copy );
//#endif
//    int64_t value;
//    iss >> value;
//    return value;
    return 0;
}

uint64_t String::toUint64() const
{
    throw std::logic_error( "Method not implemented" );
    //    if( m_value.empty() )
//    {
//        return 0u;
//    }
//    auto copy = m_value;
//    if( m_value[0] == 'u' )
//    {
//        copy = m_value.substr( 1, m_value.size() );
//    }
//#if defined( _MSC_VER )
//    std::string resultString = FS::ws2s( copy );
//    std::istringstream iss( resultString );
//#else
//    std::istringstream iss( copy );
//#endif
//    uint64_t value;
//    iss >> value;
//    return value;
    return 0u;
}

std::uint64_t String::toUInt() const
{
    throw std::logic_error( "Method not implemented" );
    //return m_value.empty() ? 0u : std::stoull( m_value, nullptr, 0 );
    return 0u;
}

bool String::toBool() const
{
    throw std::logic_error( "Method not implemented" );
    //if( m_value.empty() )
    //{
    //    return false;
    //}

    //if( toLowerR() == "true" )
    //{
    //    return true;
    //}

    return false;
}

Length String::length() const
{
    return m_size;
}

size_t String::size() const
{
    return m_size;
}

Length String::capacity() const
{
    return m_capacity;
}

void String::clear()
{
    m_size = 0;
}

bool String::empty() const
{
    return m_size == 0;
}

void String::reserve( std::int32_t newSize, bool keepValues )
{
    if( m_capacity < newSize )
    {
        grow( newSize, keepValues );
    }
}

void String::erase( Length index )
{
    for( Length i = index + 1; i < m_size; ++i )
    {
        m_value[i - 1] = m_value[i];
    }
    --m_size;
}

constexpr char hexmap[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

std::string data2StringHex( unsigned char* data, size_t len )
{
    throw std::logic_error( "Method not implemented" );
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
    throw std::logic_error( "Method not implemented" );
    uint16_t result = valu - 48u;
    if( result >= 10u )
    {
        result = result - 39u;
    }
    return result;
}

uint16_t stringHex2Data( char val[4] )
{
    throw std::logic_error( "Method not implemented" );
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
    throw std::logic_error( "Method not implemented" );
    //#if defined( CUL_WINDOWS )
//    const size_t dataSize = m_value.size();
//    if( dataSize > 0 )
//    {
//        const size_t sizeOfWchar = sizeof( wchar_t );
//        const size_t wholeDataSize = dataSize * sizeOfWchar;
//
//        const auto hexValue = data2StringHex( (unsigned char*)m_value.data(), wholeDataSize );
//
//        m_binaryValue = hexValue;
//        m_isBinary = true;
//    }
//#else   // #if defined(CUL_WINDOWS)
//#endif  // #if defined(CUL_WINDOWS)
}

void String::setBinary( const char* value )
{
    throw std::logic_error( "Method not implemented" );
    //m_binaryValue = value;
    //m_isBinary = true;
}

const std::string String::getBinary() const
{
    throw std::logic_error( "Method not implemented" );
    //return m_binaryValue;
    return std::string{};
}

void String::convertFromHexToString()
{
    throw std::logic_error( "Method not implemented" );
    //#if defined( CUL_WINDOWS )
//    const size_t dataSize = m_binaryValue.size();
//    if( dataSize > 0 )
//    {
//        constexpr size_t dataWidth = 4;
//
//        std::wstring result;
//        for( size_t i = 0; i < dataSize; i += dataWidth )
//        {
//            std::string currentHex( m_binaryValue, i, dataWidth );
//            char charStr[4];
//            charStr[2] = currentHex[0];
//            charStr[3] = currentHex[1];
//            charStr[0] = currentHex[2];
//            charStr[1] = currentHex[3];
//            wchar_t val = stringHex2Data( charStr );
//            result.push_back( val );
//        }
//        m_value = result;
//        m_isBinary = false;
//    }
//#else   // #if defined(CUL_WINDOWS)
//#endif  // #if defined(CUL_WINDOWS)
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
#if defined( CUL_WINDOWS )
    UINT codePage = CP_ACP;
    DWORD dwFlags = WC_COMPOSITECHECK;
    const int sizeNeeded = WideCharToMultiByte( codePage, dwFlags, in, inSize, NULL, 0, NULL, NULL );
    if( sizeNeeded + 1 < outSize )
    {
        WideCharToMultiByte( codePage, dwFlags, in, inSize, out, sizeNeeded, NULL, NULL );
        result = sizeNeeded;
        out[inSize] = L'\0';
        return true;
    }
#else   // #if defined( CUL_WINDOWS )
    throw std::logic_error( "Method not implemented" );
#endif  // #if defined( CUL_WINDOWS )
    return false;
}

Length String::charToWideString( Length codePage, wchar_t* out, Length outSize, const char* in )
{
    return charToWideString( codePage, out, outSize, in, std::strlen( in ) );
}

Length String::charToWideString( Length codePage, wchar_t* out, Length outSize, const char* in, Length inSize )
{
    Length result = 0u;
#if defined( CUL_WINDOWS )
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
        return result;
    }

#else   // #if defined( CUL_WINDOWS )
    throw std::logic_error( "Method not implemented" );
#endif  // #if defined( CUL_WINDOWS )
    return result;
}

void String::copyString( char* target, const char* source )
{
    copyString( target, strLen( target ), source, strLen( source ) );
}

void String::copyString( char* target, Length targetSize, const char* source, Length sourceSize )
{
    CUL::Assert::simple( targetSize >= sourceSize, "TARGET TOO SMALL!" );
    std::strncpy(target, source, sourceSize);
}

void String::copyString( wchar_t* target, const wchar_t* source )
{
    copyString( target, strLen( target ), source, strLen( source ) );
}

void String::copyString( wchar_t* target, Length targetSize, const wchar_t* source, Length sourceSize )
{
    CUL::Assert::simple( targetSize >= sourceSize, "TARGET TOO SMALL!" );
    std::memcpy( target, source, sourceSize * UnderlyingCharSize );
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
    return std::strlen( inString );
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

void String::createFrom( const String& arg )
{
    if( m_capacity >= arg.m_capacity )
    {
        m_value = &m_staticValue[0];
        m_size = arg.m_size;
        if( m_size > 0 )
        {
            copyString( m_value, m_size, arg.m_value, m_size );
        }
    }
    else
    {
        m_value = new UnderlyingChar[static_cast<std::size_t>( arg.m_capacity )];
        m_size = arg.m_size;
        m_capacity = arg.m_capacity;
    }

    if( m_size == 0 )
    {
        m_value[0] = '\0';
    }
    else
    {
        copyString( m_value, m_size, arg.m_value, m_size );
    }
}

void String::createFromMove( String& arg )
{
    if( arg.m_capacity == SSO_Size )
    {
        m_value = &m_staticValue[0];
        copyString( m_value, m_capacity, arg.m_value, arg.m_size );

        m_size = arg.m_size;

        arg.m_size = 0u;
        arg.m_capacity = 0;
    }
    else
    {
        std::swap( m_value, arg.m_value );
        std::swap( m_capacity, arg.m_capacity );
        std::swap( m_size, arg.m_size );
    }
}

void String::createFrom( bool arg )
{
    m_value = &m_staticValue[0];
    m_size = arg ? 4 : 5;
#if defined( CUL_WINDOWS )
    copyString( m_value, m_capacity, arg ? L"true" : L"false", m_size );
#else   // #if defined( CUL_WINDOWS )
    std::strcpy( m_value, arg ? "true" : "false" );
#endif  // #if defined( CUL_WINDOWS )
}

void String::createFrom( const char* arg )
{
    const Length newLength = strLen( arg );
    if( newLength >= m_capacity )
    {
        m_capacity = calcualteCapacity( newLength );
        m_value = new UnderlyingChar[static_cast<std::size_t>( m_capacity )];
    }
    else
    {
        m_value = &m_staticValue[0];
    }

#if defined( CUL_WINDOWS )
    if( newLength == 0 )
    {
        m_value[0] = L'\0';
        m_size = 0;
    }
    else
    {
        charToWideString( CP_ACP, m_value, m_capacity, arg );
        m_size = strLen( m_value );
    }
#else   // #if defined( CUL_WINDOWS )
    if( newLength == 0 )
    {
        m_value[0] = L'\0';
        m_size = 0;
    }
    else
    {
        copyString( m_value, arg );
        m_size = newLength;
    }
#endif  // #if defined( CUL_WINDOWS )
}

void String::createFrom( const std::string& arg )
{
    const Length newLength = arg.size() * 2;
    if( newLength >= m_capacity )
    {
        m_capacity = calcualteCapacity( newLength );
        m_value = new UnderlyingChar[static_cast<std::size_t>( m_capacity )];
    }
    else
    {
        m_value = &m_staticValue[0];
    }
#if defined( CUL_WINDOWS )

    if( newLength == 0 )
    {
        m_value[0] = L'\0';
    }
    else
    {
        m_size = charToWideString( CP_ACP, m_value, m_capacity, arg.c_str(), arg.size() );
    }
#else   // #if defined( CUL_WINDOWS )
    if( argLen == 0 )
    {
        m_value[0] = L'\0';
    }
    else
    {
        copyString( m_value, arg );
        m_size = newLength;
    }
#endif  // #if defined( CUL_WINDOWS )
}

void String::createFrom( const std::wstring& arg )
{
    const Length newLength = static_cast<Length>( arg.size() );
    if( newLength >= m_capacity )
    {
        m_capacity = calcualteCapacity( newLength );
        m_value = new UnderlyingChar[static_cast<std::size_t>( m_capacity )];
    }
    else
    {
        m_value = &m_staticValue[0];
    }

    copyString( m_value, m_capacity, arg.c_str(), newLength );
    m_size = newLength;
}

void String::createFrom( const wchar_t* arg )
{
    const Length newLength = strLen( arg );
    if( newLength >= m_capacity )
    {
        m_capacity = calcualteCapacity( newLength );
        m_value = new UnderlyingChar[static_cast<std::size_t>( m_capacity )];
    }
    else
    {
        m_value = &m_staticValue[0];
    }

    copyString( m_value, m_capacity, arg, newLength );
    m_size = newLength;
}

void String::createFrom( std::int32_t arg )
{
#if defined( CUL_WINDOWS )
    const std::wstring temp = std::to_wstring( arg );
    operator=( temp );
#else   // #if defined( CUL_WINDOWS )
    throw std::logic_error( "Method not implemented" );
#endif  // #if defined( CUL_WINDOWS )
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
    m_size = targetSize;
}

Length String::calcualteCapacity( Length inSize ) const
{
    if( inSize < m_capacity - 1 )
    {
        return m_capacity;
    }

    return static_cast<Length>( static_cast<float>( ( inSize + 1 ) ) * CapacityCoeficient );
}

String::~String()
{
    releaseBuffer();
}

void String::releaseBuffer()
{
    if( m_value && m_capacity > SSO_Size )
    {
        delete[] m_value;
    }
    m_capacity = 0;
    m_size = 0;
    m_value = nullptr;
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