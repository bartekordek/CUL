#include "String/MyStringImpl.hpp"

using namespace CUL;

MyStringImpl::MyStringImpl( const char* val ):
    m_value( val )
{
}

MyStringImpl::MyStringImpl( const std::string& val ):
    m_value( val )
{
}

MyStringImpl::MyStringImpl( const MyStringImpl& val ):
    m_value( val.m_value )
{
}

MyStringImpl::MyStringImpl( const double val ):
    m_value( std::to_string( val ) )
{
}

MyStringImpl::MyStringImpl( const float val ):
    m_value( std::to_string( val ) )
{
}

MyStringImpl::MyStringImpl( const bool val ) :
    m_value( std::to_string( val ) )
{
}

MyStringImpl::MyStringImpl( const int val ) :
    m_value( std::to_string( val ) )
{
}

MyStringImpl::MyStringImpl( const unsigned val ) :
    m_value( std::to_string( val ) )
{
}

MyStringImpl& MyStringImpl::operator=( const char* rhv )
{
    this->m_value = rhv;
    return *this;
}

MyStringImpl & MyStringImpl::operator=( const std::string & rhv )
{
    this->m_value = rhv;
    return *this;
}

MyStringImpl& MyStringImpl::operator=( const MyStringImpl& rhv )
{
    if( &rhv != this )
    {
        this->m_value = rhv.m_value;
    }
    return *this;
}

MyStringImpl& MyStringImpl::operator=( const double val )
{
    this->m_value = std::to_string( val );
    return *this;
}

MyStringImpl& MyStringImpl::operator=( const float val )
{
    this->m_value = std::to_string( val );
    return *this;
}

MyStringImpl& MyStringImpl::operator=( const bool val )
{
    this->m_value = std::to_string( val );
    return *this;
}

MyStringImpl& MyStringImpl::operator=( const int val )
{
    this->m_value = std::to_string( val );
    return *this;
}

MyStringImpl& MyStringImpl::operator=( const unsigned val )
{
    this->m_value = std::to_string( val );
    return *this;
}

MyStringImpl MyStringImpl::operator+( const MyStringImpl& rhv )
{
    MyStringImpl result = *this;
    result += rhv;
    return result;
}

MyStringImpl& MyStringImpl::operator+=( const MyStringImpl& rhv )
{
    this->m_value += rhv.m_value;
    return *this;
}

const bool MyStringImpl::operator==( const char * rhv ) const
{
    return this->m_value == rhv;
}

const bool MyStringImpl::operator==( const std::string & rhv ) const
{
    return this->m_value == rhv;
}

const bool MyStringImpl::operator==( const MyStringImpl & rhv ) const
{
    return this->m_value == rhv.m_value;
}

void MyStringImpl::toLower( void )
{
    MyString::toLowerS( this->m_value );
}

void MyStringImpl::toUpper( void )
{
    MyString::toUpperS( this->m_value );
}

const bool MyStringImpl::contains( const MyString& inputString ) const
{
    return this->m_value.find( inputString.string() ) != std::string::npos;
}

const bool MyStringImpl::contains( const char* inputString ) const
{
    return this->m_value.find( inputString ) != std::string::npos;
}

void MyStringImpl::replace( const MyString& inWhat, const MyString& inFor )
{
    auto inWhatPosition = this->m_value.find( inWhat.string() );
    if( std::string::npos != inWhatPosition )
    {
        this->m_value.replace( inWhatPosition, inWhat.string().length(), inFor.string() );
    }
}

CnstStr& MyStringImpl::string() const
{
    return this->m_value;
}

std::string& MyStringImpl::string()
{
    return this->m_value;
}

const char* MyStringImpl::cStr()const
{
    return this->m_value.c_str();
}

const Length MyStringImpl::length() const
{
    return static_cast< Length >( this->m_value.length() );
}

const Length MyStringImpl::capacity( void ) const
{
    return static_cast< Length >( this->m_value.capacity() );
}

void MyStringImpl::clear( void )
{
    this->m_value.clear();
}