#pragma once

#include "CUL/CUL.hpp"
#include "CUL/STD_string.hpp"
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
    MyString( void );
    MyString( const char* inputString );
    MyString( const MyString& inputString );
    MyString( const std::string& inputString );
    MyString( const double val );
    MyString( const float val );
    MyString( const bool val );
    MyString( const int val );
    MyString( const unsigned val );
    virtual ~MyString( void );

    MyString& operator=( const char* someString );
    MyString& operator=( const std::string& someString );
    MyString& operator=( const MyString& someString );
    MyString& operator=( const double val );
    MyString& operator=( const float val );
    MyString& operator=( const bool val );
    MyString& operator=( const int val );
    MyString& operator=( const unsigned val );

    const bool operator==( const char* rhv ) const;
    const bool operator==( const std::string& rhv ) const;
    const bool operator==( const MyString& rhv ) const;

    virtual void toLower( void );
    virtual void toUpper( void );

    virtual const bool contains( const MyString& inputString )const;
    virtual const bool contains( const char* inputString )const;

    virtual void replace( const MyString& inWhat, const MyString& inFor );

    virtual CnstStr& string( void )const;
    virtual std::string& string( void );

    virtual const char* cStr( void );
    virtual const Length length( void ) const;
    virtual const Length Capacity( void ) const;
    void clear( void );

    static void toLowerS( std::string& inOutString );
    static void toUpperS( std::string& inOutString );

protected:
private:
    MyStringImpl* m_impl = nullptr;
};

const bool CULLib_API operator==( const char* lhv, const CUL::MyString& rhv );

NAMESPACE_END( CUL )