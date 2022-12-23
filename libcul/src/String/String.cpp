#include "CUL/String.hpp"

#include "Filesystem/FSUtils.hpp"

#include "CUL/STL_IMPORTS/STD_algorithm.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"

using namespace CUL;

String::String() noexcept
{
}

String::String( const String& arg ) noexcept :
    m_value( arg.m_value )
{
}

String::String( String&& arg ) noexcept :
    m_value( std::move( arg.m_value ) )
{
}

String::String( const bool arg ) noexcept
{
    *this = arg;
}

String::String( const char* arg ) noexcept
{
    *this = arg;
}

String::String( const wchar_t* arg ) noexcept
{
    *this = arg;
}

String::String( unsigned char* arg ) noexcept
{
    *this = arg;
}

String::String( const std::string& arg ) noexcept
{
    *this = arg;
}

String::String( const std::wstring& arg ) noexcept
{
#ifdef _MSC_VER
    m_value = arg;
#else
    m_value = FS::ws2s(arg);
#endif
}

String::String( float arg ) noexcept
{
    *this = arg;
}

String::String( double arg ) noexcept
{
    *this = arg;
}

String::String( int arg ) noexcept
{
    *this = arg;
}

String::String( unsigned int arg ) noexcept
{
    *this = arg;
}

String& String::operator=( const String& arg )
{
    if( this != &arg )
    {
        m_value = arg.m_value;
    }
    return *this;
}

String& String::operator=( String&& arg ) noexcept
{
    if( this != &arg )
    {
        m_value = std::move( arg.m_value );
    }
    return *this;
}

String& String::operator=( const bool arg )
{
    if( true == arg )
    {
        *this = "true";
    }
    else
    {
        *this = "false";
    }
    return *this;
}

String& String::operator=( const char* arg )
{
#ifdef _MSC_VER
    m_value = FS::s2ws( arg );
#else
    m_value = arg;
#endif
    return *this;
}

String& String::operator=( const wchar_t* arg )
{
#ifdef _MSC_VER
    m_value = arg;
#else
    m_value = FS::ws2s( arg );
#endif
    return *this;
}

#ifdef _MSC_VER
// Yes, I know that is a Spectre mitigation.
// But for now, I let this as TODO, since i don't know
// How to fix this.
// TODO
#pragma warning( push )
#pragma warning( disable: 5045 )
#endif
String& String::operator=( unsigned char* arg )
{
    auto len = strlen( (const char*)arg );
    std::string tmp;
    tmp.resize( len );

    for( unsigned i = 0; i < len; ++i )
    {
        tmp[i] = static_cast<char>( arg[i] );
    }

#ifdef _MSC_VER
    m_value = FS::s2ws(tmp);
#else
    m_value = tmp;
#endif

    return *this;
}
#ifdef _MSC_VER
#pragma warning( pop )
#endif

String& String::operator=( const std::string& arg )
{
#ifdef _MSC_VER
    m_value = FS::s2ws( arg );
#else
    m_value = arg;
#endif
    removeAll('\0');
    return *this;
}

String& String::operator=( const std::wstring& arg )
{
#ifdef _MSC_VER
    m_value = arg;
#else
    m_value = FS::ws2s( arg );
#endif
    removeAll( '\0' );
    return *this;
}

String& String::operator=( float arg )
{
#ifdef _MSC_VER
    m_value = std::to_wstring( arg );
#else
    m_value = std::to_string( arg );
#endif

    return *this;
}

String& String::operator=( double arg )
{
#ifdef _MSC_VER
    m_value = std::to_wstring( arg );
#else
    m_value = std::to_string( arg );
#endif
    return *this;
}

String& String::operator=( int arg )
{
#ifdef _MSC_VER
    m_value = std::to_wstring( arg );
#else
    m_value = std::to_string( arg );
#endif
    return *this;
}

String& String::operator=( unsigned arg )
{
#ifdef _MSC_VER
    m_value = std::to_wstring( arg );
#else
    m_value = std::to_string( arg );
#endif
    return *this;
}

String String::operator+( const String& arg ) const
{
    String result( *this );
    result.removeAll( '\0' );
    result.m_value = result.m_value + arg.m_value;
    result.removeAll( '\0' );
    return result;
}

String& String::operator+=( const String& arg )
{
    m_value += arg.m_value;
    return *this;
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
#ifdef _MSC_VER
    return m_value == FS::s2ws( arg );
#else
    return m_value == arg;
#endif
}

bool String::operator!=( const std::string& arg ) const
{
    return !operator==( arg );
}

bool String::operator==( const char* arg ) const
{
#ifdef _MSC_VER
    return m_value == FS::s2ws( arg );
#else
    return m_value == arg;
#endif
}

bool String::operator!=( const char* arg ) const
{
#ifdef _MSC_VER
    return m_value != FS::s2ws( arg );
#else
    return m_value != arg;
#endif
}

bool String::operator!=( int arg ) const
{
    return !operator==( arg );
}

bool String::operator==( int arg ) const
{
#ifdef _MSC_VER
    return m_value == std::to_wstring( arg );
#else
    return m_value == std::to_string( arg );
#endif
}

bool String::operator!=( unsigned int arg ) const
{
    return !operator==( arg );
}

bool String::operator==( unsigned int arg ) const
{
#ifdef _MSC_VER
    return m_value == std::to_wstring( arg );
#else
    return m_value == std::to_string( arg );
#endif
}

bool String::operator!=( float arg ) const
{
    return !operator==( arg );
}

bool String::operator==( float arg ) const
{
#ifdef _MSC_VER
    return m_value == std::to_wstring( arg );
#else
    return m_value == std::to_string( arg );
#endif
}

bool String::operator!=( double arg ) const
{
    return !operator==( arg );
}

bool String::operator==( double arg ) const
{
#ifdef _MSC_VER
    return m_value == std::to_wstring( arg );
#else
    return m_value == std::to_string( arg );
#endif
}

bool String::operator<( const String& arg ) const
{
    return m_value < arg.m_value;
}

bool String::operator>( const String& arg ) const
{
    return m_value > arg.m_value;
}

size_t String::find( const String& arg ) const
{
    return m_value.find(arg.m_value);
}

String String::substr( size_t pos, size_t len ) const
{
    auto result = m_value.substr( pos, len );
    String strResult = result;
    return strResult;
}

void String::toLower()
{
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable:4244 )
#endif
    std::transform(
        m_value.begin(),
        m_value.end(),
        m_value.begin(),
        ::tolower );
#if _MSC_VER
#pragma warning( pop )
#endif
}

String String::toLowerR() const
{
    String result = *this;

    result.toLower();

    return result;
}

void String::toUpper()
{
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable:4244 )
#endif
    std::transform(
        m_value.begin(),
        m_value.end(),
        m_value.begin(),
        ::toupper );
#if _MSC_VER
#pragma warning( pop )
#endif
}

bool String::contains( const String& inputString ) const
{
    return m_value.find( inputString.m_value ) != UnderlyingType::npos;
}

bool String::contains( const char* inputString ) const
{
#ifdef _MSC_VER
    return m_value.find( FS::s2ws( inputString ) ) != UnderlyingType::npos;
#else
    return m_value.find( inputString ) != UnderlyingType::npos;
#endif
}

void String::replace( const String& inWhat, const String& inFor )
{
    if( m_value.empty() )
    {
        return;
    }

    auto& str = m_value;
    const UnderlyingType& from = inWhat.getString();
    const UnderlyingType& to = inFor.getString();
    size_t start_pos = 0;
    while( ( start_pos = str.find( from, start_pos ) ) != std::string::npos )
    {
        str.replace( start_pos, from.length(), to );
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

void String::replace( const char inWhat, const char inFor )
{
    if( m_value.empty() )
    {
        return;
    }

    auto cInWhat = static_cast<UnderlyingChar>( inWhat );
    auto cInFor = static_cast<UnderlyingChar>( inFor );

    size_t inWhatPosition = m_value.find( cInWhat );
    while( UnderlyingType::npos != inWhatPosition )
    {
        m_value.replace( inWhatPosition, 1, &cInFor );
        inWhatPosition = m_value.find( cInWhat );
    }
}

void String::replace( const wchar_t inWhat, const wchar_t inFor )
{
    if( m_value.empty() )
    {
        return;
    }

#ifdef _MSC_VER
    wchar_t cInWhat = inWhat;
    wchar_t cInFor = inFor;
#else
    char cInWhat = inWhat;
    char cInFor = inFor;
#endif
    size_t inWhatPosition = m_value.find( cInWhat );
    while( UnderlyingType::npos != inWhatPosition )
    {
        m_value.replace( inWhatPosition, 1, &cInFor );
        inWhatPosition = m_value.find( inWhat );
    }
}

void String::removeAll( const char inWhat )
{
    UnderlyingChar inWhatChar = ( UnderlyingChar ) inWhat;
    auto inWhatPosition = m_value.find( inWhatChar );
    while( std::string::npos != inWhatPosition )
    {
        m_value.erase(inWhatPosition);
        inWhatPosition = m_value.find( inWhatChar );
    }
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
    size_t it = m_value.find(end);

    if( it == UnderlyingType::npos )
    {
        return false;
    }

    int valueSize = (int)m_value.size();
    int endSize = (int)end.size();
    int diff = valueSize - endSize;

    if( valueSize < endSize )
    {
        return false;
    }

    for( int i = valueSize; i >= 0; --i )
    {
        if( m_value[(size_t)i] != end[(size_t)( i - diff )] )
        {
            return false;
        }
    }

    return true;
}

std::string String::string() const
{
#ifdef _MSC_VER
    return FS::ws2s(m_value);
#else
    return m_value;
#endif
}

std::wstring String::wstring() const
{
#ifdef _MSC_VER
    return m_value;
#else
    return FS::s2ws( m_value );
#endif
}

String::UnderlyingType String::getString() const
{
    return m_value;
}

const char* String::cStr() const
{
#ifdef _MSC_VER
    std::string resultString = FS::ws2s(m_value);
    const size_t size = resultString.size();
    char* result = new char[size+1];
    std::strcpy(result, resultString.c_str());

    return result;
#else
    return m_value.c_str();
#endif
}

const wchar_t* String::wCstr() const
{
#ifdef _MSC_VER
    return m_value.c_str();
#else
    std::wstring resultString = FS::s2ws(m_value);
    wchar_t* result = new wchar_t[resultString.size()];
    mbstowcs(result, m_value.c_str(), resultString.size());
    return result;
#endif
}

const String::UnderlyingChar* String::getChar() const
{
    return m_value.c_str();
}

float String::toFloat() const
{
    return m_value.empty() ? 0.0f: std::stof( m_value, nullptr );
}

double String::toDouble() const
{
    return m_value.empty() ? 0.0 : std::stod( m_value, nullptr );
}

int String::toInt()
{
    removeAll('u');
    return m_value.empty() ? 0 : std::stoi( m_value, nullptr, 0 );
}

unsigned int String::toUInt() const
{
    return m_value.empty() ? 0u : std::stoul( m_value, nullptr, 0 );
}

bool String::toBool() const
{
    if( m_value.empty() )
    {
        return false;
    }

    if( toLowerR() == "true" )
    {
        return true;
    }

    return false;
}

Length String::length() const
{
    return (Length)m_value.size();
}

size_t String::size() const
{
    return m_value.size();
}

Length String::capacity() const
{
    return (Length)m_value.capacity();
}

void String::clear()
{
    m_value.clear();
}

bool String::empty() const
{
    return m_value.empty();
}

String::~String()
{
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