#include "CUL/MyString.hpp"
#include "String/MyStringImpl.hpp"
#include "CUL/STD_algorithm.hpp"

using namespace CUL;

MyString::MyString():
    m_impl( new MyStringImpl() )
{
}

MyString::MyString( const char* inputString ) :
    m_impl( new MyStringImpl( inputString ) )
{
}

MyString::MyString( const MyString& inputString ):
    m_impl( new MyStringImpl( *inputString.m_impl ) )
{
}

MyString::MyString( const std::string& inputString ):
    m_impl( new MyStringImpl( inputString ) )
{
}

MyString::MyString( const double val ):
    m_impl( new MyStringImpl( val ) )
{
}

MyString::MyString( const float val ):
    m_impl( new MyStringImpl( val ) )
{
}

MyString::MyString( const bool val ):
    m_impl( new MyStringImpl( val ) )
{
}

MyString::MyString( const int val ):
    m_impl( new MyStringImpl( val ) )
{
}

MyString::MyString( const unsigned val ):
    m_impl( new MyStringImpl( val ) )
{
}

MyString::~MyString()
{
    delete this->m_impl;
    this->m_impl = nullptr;
}

MyString& MyString::operator=( const char* someString )
{
    *this->m_impl = someString;
    return *this;
}

MyString & MyString::operator=( const std::string & someString )
{
    *this->m_impl = someString;
    return *this;
}

MyString& MyString::operator=( const MyString& someString )
{
    *this->m_impl = *someString.m_impl;
    return *this;
}

MyString& MyString::operator=( const double val )
{
    *this->m_impl = val;
    return *this;
}

MyString& MyString::operator=( const float val )
{
    *this->m_impl = val;
    return *this;
}

MyString& MyString::operator=( const bool val )
{
    *this->m_impl = val;
    return *this;
}

MyString& MyString::operator=( const int val )
{
    *this->m_impl = val;
    return *this;
}

MyString& MyString::operator=( const unsigned val )
{
    *this->m_impl = val;
    return *this;
}

const bool MyString::operator==( const char * rhv ) const
{
    return *this->m_impl == rhv;
}

const bool MyString::operator==( const std::string & rhv ) const
{
    return *this->m_impl == rhv;
}

const bool MyString::operator==( const MyString& rhv ) const
{
    return *this->m_impl == *rhv.m_impl;
}

void MyString::toLower( void )
{
    this->m_impl->toLower();
}

void MyString::toUpper( void )
{
    this->m_impl->toUpper();
}

const bool MyString::contains( const MyString& inputString ) const
{
    return this->m_impl->contains( inputString );
}

const bool MyString::contains( const char* inputString ) const
{
    return this->m_impl->contains( inputString );
}

void MyString::replace( const MyString& inWhat, const MyString& inFor )
{
    this->m_impl->replace( inWhat, inFor );
}

CnstStr& MyString::string() const
{
    return this->m_impl->string();
}

std::string& MyString::string()
{
    return this->m_impl->string();
}

const char* MyString::cStr()
{
    return this->m_impl->cStr();
}

const Length MyString::length( void ) const
{
    return this->m_impl->length();
}

const Length MyString::Capacity( void ) const
{
    return this->m_impl->capacity();
}

void MyString::clear( void )
{
    this->m_impl->clear();
}

void MyString::toLowerS( std::string& inOutString )
{
#if _MSC_VER
    __pragma(warning( push )) \
    __pragma(warning( disable:4244 ))
#endif
    std::transform(
        inOutString.begin(),
        inOutString.end(),
        inOutString.begin(),
            ::tolower );
#if _MSC_VER
    __pragma(warning( pop ))
#endif
}

void MyString::toUpperS( std::string& inOutString )
{
#if _MSC_VER
    __pragma(warning( push )) \
    __pragma(warning( disable:4244 ))
#endif
    std::transform(
        inOutString.begin(),
        inOutString.end(),
        inOutString.begin(),
        ::toupper );
#if _MSC_VER
    __pragma(warning( pop ))
#endif
}

const bool CUL::operator==( const char* lhv, const CUL::MyString& rhv )
{
    return rhv == lhv;
}