#include "CUL/String.hpp"
#include "CUL/STL_IMPORTS/STD_algorithm.hpp"

using namespace CUL;

String::String()
{
}

String::String( const bool arg )
{
    *this = arg;
}

String::String( const char* arg )
{
    *this = arg;
}

String::String( const std::string& arg )
{
    *this = arg;
}

String::String( const double arg )
{
    *this = arg;
}

String::String( const int arg )
{
    *this = arg;
}

String::String( const unsigned int arg )
{
    *this = arg;
}

String& String::operator=( const bool arg )
{
    if( true == arg )
    {
        m_value = "true";
    }
    else
    {
        m_value = "false";
    }
    return *this;
}

String& String::operator=( const char* arg )
{
    m_value = arg;
    return *this;
}

String& String::operator=( const std::string& arg )
{
    m_value = arg;
    return *this;
}

String& String::operator=( const double arg )
{
    m_value = std::to_string( arg );
    return *this;
}

String& String::operator=( const int arg )
{
    m_value = std::to_string( arg );
    return *this;
}

String& String::operator=( const unsigned arg )
{
    m_value = std::to_string( arg ) + "u";
    return *this;
}

String String::operator+( const String& arg ) const
{
    String result( *this );
    result.m_value = result.m_value + arg.m_value;
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
    return m_value == arg;
}

bool String::operator!=( const std::string& arg ) const
{
    return !operator==( arg );
}

bool String::operator==( const char* arg ) const
{
    return m_value == arg;
}

bool String::operator!=( const char* arg ) const
{
    return !operator==( arg );
}

bool String::operator!=( const int arg ) const
{
    return !operator==( arg );
}

bool String::operator==( const int arg ) const
{
    return m_value == std::to_string( arg );
}

bool String::operator<( const String& arg ) const
{
    return m_value < arg.m_value;
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
    return m_value.find( inputString.string() ) != std::string::npos;
}

bool String::contains( const char* inputString ) const
{
    return m_value.find( inputString ) != std::string::npos;
}

void String::replace( const String& inWhat, const String& inFor )
{
    auto inWhatPosition = m_value.find( inWhat.string() );
    while( std::string::npos != inWhatPosition )
    {
        m_value.replace( inWhatPosition, inWhat.string().length(), inFor.string() );
        inWhatPosition = m_value.find( inWhat.string() );
    }
}

const std::string& String::string() const
{
    return m_value;
}

std::string& String::string()
{
    return m_value;
}

const char* String::cStr() const
{
    return m_value.c_str();
}

Length String::length() const
{
    return Length();
}

Length String::capacity() const
{
    return Length();
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

bool CULLib_API CUL::operator==( const int arg1, const String& arg2 )
{
    return arg2 == arg1;
}