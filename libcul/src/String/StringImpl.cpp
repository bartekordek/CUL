#include "String/StringImpl.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"
#include "CUL/STL_IMPORTS/STD_stddef.hpp"
#include "CUL/STL_IMPORTS/STD_iostream.hpp"

using namespace CUL;

size_t signedCharLength( const unsigned char* val )
{
    size_t iterator = 0;
    while( val[iterator++] != '\0' )
    {

    }
    return iterator;
}

std::string unsignedChar2String( const unsigned char* val )
{
    auto length = signedCharLength( val );
    std::string result;
    char* charTable = new char[ length + 1 ];
    for( size_t i = 0; i < length; ++i )
    {
        charTable[i] = static_cast<char>( val[i] );
    }
    result = charTable;
    return result;
}

StringImpl::StringImpl( const char* val ):
    m_value( val )
{
}

StringImpl::StringImpl( const unsigned char* val ):
    m_value( unsignedChar2String( val ) )
{
}

StringImpl::StringImpl( const std::string& val ):
    m_value( val )
{
}

StringImpl::StringImpl( const StringImpl& val ):
    m_value( val.m_value )
{
}

StringImpl::StringImpl( const double val ):
    m_value( std::to_string( val ) )
{
}

StringImpl::StringImpl( const float val ):
    m_value( std::to_string( val ) )
{
}

StringImpl::StringImpl( const bool val ) :
    m_value( std::to_string( val ) )
{
}

StringImpl::StringImpl( const int val ) :
    m_value( std::to_string( val ) )
{
}

StringImpl::StringImpl( const unsigned val ) :
    m_value( std::to_string( val ) )
{
}

StringImpl& StringImpl::operator=( const char* rhv )
{
    m_value = rhv;
    return *this;
}

StringImpl& StringImpl::operator=( const unsigned char * rhv )
{
    m_value = unsignedChar2String( rhv );
    return *this;
}

StringImpl & StringImpl::operator=( const std::string & rhv )
{
    m_value = rhv;
    return *this;
}

StringImpl& StringImpl::operator=( const StringImpl& rhv )
{
    if( &rhv != this )
    {
        m_value = rhv.m_value;
    }
    return *this;
}

StringImpl& StringImpl::operator=( const double val )
{
    m_value = std::to_string( val );
    return *this;
}

StringImpl& StringImpl::operator=( const float val )
{
    m_value = std::to_string( val );
    return *this;
}

StringImpl& StringImpl::operator=( const bool val )
{
    m_value = std::to_string( val );
    return *this;
}

StringImpl& StringImpl::operator=( const int val )
{
    m_value = std::to_string( val );
    return *this;
}

StringImpl& StringImpl::operator+( const unsigned val )
{
    m_value += std::to_string( val );
    return *this;
}

StringImpl& StringImpl::operator=( const unsigned val )
{
    m_value = std::to_string( val );
    return *this;
}

StringImpl StringImpl::operator+( const StringImpl& rhv )
{
    StringImpl result = *this;
    result += rhv;
    return result;
}

StringImpl& StringImpl::operator+=( const StringImpl& rhv )
{
    m_value += rhv.m_value;
    return *this;
}

const bool StringImpl::operator==( const char * rhv ) const
{
    return m_value == rhv;
}

const bool StringImpl::operator==( const std::string & rhv ) const
{
    return m_value == rhv;
}

const bool StringImpl::operator==( const StringImpl & rhv ) const
{
    return m_value == rhv.m_value;
}

StringImpl::operator const std::string&() const
{
    return m_value;
}

const char StringImpl::at( const unsigned int index ) const
{
    return m_value.at( index );
}

const bool StringImpl::operator<( const StringImpl & rhv ) const
{
    return m_value < rhv.m_value;
}

void StringImpl::toLower()
{
    String::toLowerS( m_value );
}

void StringImpl::toUpper()
{
    String::toUpperS( m_value );
}

const bool StringImpl::contains( const String& inputString ) const
{
    return m_value.find( inputString.string() ) != std::string::npos;
}

const bool StringImpl::contains( const char* inputString ) const
{
    return m_value.find( inputString ) != std::string::npos;
}

void StringImpl::replace( const String& inWhat, const String& inFor )
{
    auto inWhatPosition = m_value.find( inWhat.string() );
    while( std::string::npos != inWhatPosition )
    {
        m_value.replace( inWhatPosition, inWhat.string().length(), inFor.string() );
        inWhatPosition = m_value.find( inWhat.string() );
    }
}

const std::string& StringImpl::string() const
{
    return m_value;
}

std::string& StringImpl::string()
{
    return m_value;
}

const char* StringImpl::cStr() const
{
    return m_value.c_str();
}

const Length StringImpl::length() const
{
    return static_cast< Length >( m_value.length() );
}

const Length StringImpl::capacity() const
{
    return static_cast< Length >( m_value.capacity() );
}

void StringImpl::clear()
{
    m_value.clear();
}

const bool StringImpl::empty() const
{
    return m_value.empty();
}