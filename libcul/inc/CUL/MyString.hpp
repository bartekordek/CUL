#pragma once

#include "CUL/CUL.hpp"
#include "CUL/STL_IMPORTS/STD_string.hpp"
#include "CUL/UselessMacros.hpp"

#if _MSC_VER
#pragma warning( disable: 4244 )
#pragma warning( disable: 4251 )
#endif

NAMESPACE_BEGIN( CUL )
using Length = unsigned int;

class MyStringImpl;
class CULLib_API MyString
{
public:
    MyString();
    MyString( const char* inputString );
    MyString( const unsigned char* inputString );
    MyString( const MyString& inputString );
    MyString( const std::string& inputString );
    MyString( const double val );
    MyString( const float val );
    MyString( const bool val );
    MyString( const int val );
    MyString( const unsigned val );
    virtual ~MyString();

    MyString& operator=( const char* someString );
    MyString& operator=( const unsigned char* someString );
    MyString& operator=( const std::string& someString );
    MyString& operator=( const MyString& someString );
    MyString& operator=( const double val );
    MyString& operator=( const float val );
    MyString& operator=( const bool val );
    MyString& operator=( const int val );
    MyString& operator+( const unsigned val );
    MyString& operator=( const unsigned val );

    MyString operator+( const MyString& rhv );
    MyString& operator+=( const MyString& rhv );

    const bool operator!=( const char* rhv ) const;
    const bool operator!=( const std::string& rhv ) const;
    const bool operator!=( const MyString& rhv ) const;

    const bool operator==( const char* rhv ) const;
    const bool operator==( const std::string& rhv ) const;
    const bool operator==( const MyString& rhv ) const;

    virtual void toLower();
    virtual void toUpper();

    virtual const bool contains( const MyString& inputString )const;
    virtual const bool contains( const char* inputString )const;

    virtual void replace( const MyString& inWhat, const MyString& inFor );

    virtual const std::string& string()const;
    virtual std::string& string();

    virtual const char* cStr()const;
    virtual const Length length() const;
    virtual const Length capacity() const;
    void clear();
    const bool empty()const;

    static void toLowerS( std::string& inOutString );
    static void toUpperS( std::string& inOutString );

protected:
private:
    MyStringImpl* m_impl = nullptr;
};

using CnstMyStr = const MyString;

CnstMyStr CULLib_API operator+( CnstMyStr& lhv, CnstMyStr& rhv );
const bool CULLib_API operator==( const char* lhv, CnstMyStr& rhv );
const bool CULLib_API operator<( CnstMyStr& lhv, CnstMyStr& rhv );

NAMESPACE_END( CUL )