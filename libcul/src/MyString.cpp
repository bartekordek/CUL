#include "CUL/MyString.hpp"
#include "String/MyStringImpl.hpp"
#include "CUL/STL_IMPORTS/STD_algorithm.hpp"

using MyString = CUL::MyString;
using Length = CUL::Length;
using CnstMyStr = CUL::CnstMyStr;

MyString::MyString():
    m_impl( new MyStringImpl() )
{
}

MyString::MyString( const char* inputString ):
    m_impl( new MyStringImpl( inputString ) )
{
}

MyString::MyString( const unsigned char* inputString ):
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
    *m_impl = someString;
    return *this;
}

MyString & MyString::operator=( const unsigned char* someString )
{
    *m_impl = someString;
    return *this;
}

MyString & MyString::operator=( const std::string& someString )
{
    *m_impl = someString;
    return *this;
}

MyString& MyString::operator=( const MyString& someString )
{
    *m_impl = *someString.m_impl;
    return *this;
}

MyString& MyString::operator=( const double val )
{
    *m_impl = val;
    return *this;
}

MyString& MyString::operator=( const float val )
{
    *m_impl = val;
    return *this;
}

MyString& MyString::operator=( const bool val )
{
    *m_impl = val;
    return *this;
}

MyString& MyString::operator=( const int val )
{
    *m_impl = val;
    return *this;
}

MyString& MyString::operator+( const unsigned val )
{
    *m_impl + val;
    return *this;
}

MyString& MyString::operator=( const unsigned val )
{
    *m_impl = val;
    return *this;
}

MyString MyString::operator+( const MyString & rhv )
{
    MyString result = *this;
    *result.m_impl += *rhv.m_impl;
    return result;
}

MyString& MyString::operator+=( const MyString & rhv )
{
    *m_impl += *rhv.m_impl;
    return *this;
}

const bool MyString::operator!=( const char * rhv ) const
{
    return !this->operator==( rhv );
}

const bool MyString::operator!=( const std::string & rhv ) const
{
    return !operator==( rhv );
}

const bool MyString::operator!=( const MyString & rhv ) const
{
    return !operator==( rhv );
}

const bool MyString::operator==( const char * rhv ) const
{
    return *m_impl == rhv;
}

const bool MyString::operator==( const std::string & rhv ) const
{
    return *m_impl == rhv;
}

const bool MyString::operator==( const MyString& rhv ) const
{
    return *m_impl == *rhv.m_impl;
}

void MyString::toLower()
{
    m_impl->toLower();
}

void MyString::toUpper()
{
    m_impl->toUpper();
}

const bool MyString::contains( const MyString& inputString ) const
{
    return m_impl->contains( inputString );
}

const bool MyString::contains( const char* inputString ) const
{
    return m_impl->contains( inputString );
}

void MyString::replace( const MyString& inWhat, const MyString& inFor )
{
    m_impl->replace( inWhat, inFor );
}

const std::string& MyString::string() const
{
    return m_impl->string();
}

std::string& MyString::string()
{
    return m_impl->string();
}

const char* MyString::cStr()const
{
    return m_impl->cStr();
}

const Length MyString::length() const
{
    return m_impl->length();
}

const Length MyString::capacity() const
{
    return m_impl->capacity();
}

void MyString::clear()
{
    m_impl->clear();
}

const bool MyString::empty() const
{
    return m_impl->empty();
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

CnstMyStr CUL::operator+( CnstMyStr& lhv, CnstMyStr& rhv )
{
    CnstMyStr result( lhv.string() + rhv.string() );
    return result;
}

const bool CUL::operator==( const char* lhv, CnstMyStr& rhv )
{
    return rhv == lhv;
}

const bool CUL::operator<( CnstMyStr& lhv, CnstMyStr& rhv )
{
    return lhv.string() < rhv.string();
}