#include "CUL/String.hpp"
#include "String/StringImpl.hpp"
#include "CUL/STL_IMPORTS/STD_algorithm.hpp"

using String = CUL::String;
using Length = CUL::Length;
using CsStr = CUL::CsStr;

String::String():
    m_impl( new StringImpl() )
{
}

String::String( const char* inputString ):
    m_impl( new StringImpl( inputString ) )
{
}

String::String( const unsigned char* inputString ):
    m_impl( new StringImpl( inputString ) )
{
}

String::String( const String& inputString ):
    m_impl( new StringImpl( *inputString.m_impl ) )
{
}

String::String( const std::string& inputString ):
    m_impl( new StringImpl( inputString ) )
{
}

String::String( const double val ):
    m_impl( new StringImpl( val ) )
{
}

String::String( const float val ):
    m_impl( new StringImpl( val ) )
{
}

String::String( const bool val ):
    m_impl( new StringImpl( val ) )
{
}

String::String( const int val ):
    m_impl( new StringImpl( val ) )
{
}

String::String( const unsigned val ):
    m_impl( new StringImpl( val ) )
{
}

String::~String()
{
    delete m_impl;
    m_impl = nullptr;
}

String& String::operator=( const char* someString )
{
    *m_impl = someString;
    return *this;
}

String & String::operator=( const unsigned char* someString )
{
    *m_impl = someString;
    return *this;
}

String & String::operator=( const std::string& someString )
{
    *m_impl = someString;
    return *this;
}

String& String::operator=( const String& someString )
{
    *m_impl = *someString.m_impl;
    return *this;
}

String& String::operator=( const double val )
{
    *m_impl = val;
    return *this;
}

String& String::operator=( const float val )
{
    *m_impl = val;
    return *this;
}

String& String::operator=( const bool val )
{
    *m_impl = val;
    return *this;
}

String& String::operator=( const int val )
{
    *m_impl = val;
    return *this;
}

String& String::operator+( const unsigned val )
{
    *m_impl + val;
    return *this;
}

String& String::operator=( const unsigned val )
{
    *m_impl = val;
    return *this;
}

String String::operator+( const String & rhv )
{
    String result = *this;
    *result.m_impl += *rhv.m_impl;
    return result;
}

String& String::operator+=( const String & rhv )
{
    *m_impl += *rhv.m_impl;
    return *this;
}

const bool String::operator!=( const char * rhv ) const
{
    return !operator==( rhv );
}

const bool String::operator!=( const std::string & rhv ) const
{
    return !operator==( rhv );
}

const bool String::operator!=( const String & rhv ) const
{
    return !operator==( rhv );
}

const bool String::operator==( const char * rhv ) const
{
    return *m_impl == rhv;
}

const bool String::operator==( const std::string & rhv ) const
{
    return *m_impl == rhv;
}

const bool String::operator==( const String& rhv ) const
{
    return *m_impl == *rhv.m_impl;
}

String::operator const std::string() const
{
    return *m_impl;
}

String::operator const std::string& () const
{
    return *m_impl;
}

void String::toLower()
{
    m_impl->toLower();
}

void String::toUpper()
{
    m_impl->toUpper();
}

const bool String::contains( const String& inputString ) const
{
    return m_impl->contains( inputString );
}

const bool String::contains( const char* inputString ) const
{
    return m_impl->contains( inputString );
}

void String::replace( const String& inWhat, const String& inFor )
{
    m_impl->replace( inWhat, inFor );
}

const std::string& String::string() const
{
    return m_impl->string();
}

std::string& String::string()
{
    return m_impl->string();
}

const char* String::cStr() const
{
    return m_impl->cStr();
}

const Length String::length() const
{
    return m_impl->length();
}

const Length String::capacity() const
{
    return m_impl->capacity();
}

void String::clear()
{
    m_impl->clear();
}

const bool String::empty() const
{
    return m_impl->empty();
}

void String::toLowerS( std::string& inOutString )
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

void String::toUpperS( std::string& inOutString )
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

CsStr CUL::operator+( CsStr& lhv, CsStr& rhv )
{
    CsStr result( lhv.string() + rhv.string() );
    return result;
}

const bool CUL::operator==( const char* lhv, CsStr& rhv )
{
    return rhv == lhv;
}

const bool CUL::operator<( CsStr& lhv, CsStr& rhv )
{
    return lhv.string() < rhv.string();
}