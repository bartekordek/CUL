#pragma once

#include "CUL/MyString.hpp"

NAMESPACE_BEGIN( CUL )

class MyStringImpl
{
public:
    MyStringImpl( void ) = default;
    MyStringImpl( const char* val );
    MyStringImpl( const unsigned char* val );
    MyStringImpl( const std::string& val );
    MyStringImpl( const MyStringImpl& val );
    MyStringImpl( const double val );
    MyStringImpl( const float val );
    MyStringImpl( const bool val );
    MyStringImpl( const int val );
    MyStringImpl( const unsigned val );
    virtual ~MyStringImpl( void ) = default;

    MyStringImpl& operator=( const char* rhv );
    MyStringImpl& operator=( const unsigned char* rhv );
    MyStringImpl& operator=( const std::string& rhv );
    MyStringImpl& operator=( const MyStringImpl& rhv );
    MyStringImpl& operator=( const double val );
    MyStringImpl& operator=( const float val );
    MyStringImpl& operator=( const bool val );
    MyStringImpl& operator=( const int val );
    MyStringImpl& operator=( const unsigned val );
    MyStringImpl& operator+( const unsigned val );

    MyStringImpl operator+( const MyStringImpl& rhv );
    MyStringImpl& operator+=( const MyStringImpl& rhv );

    const bool operator==( const char* rhv ) const;
    const bool operator==( const std::string& rhv ) const;
    const bool operator==( const MyStringImpl& rhv ) const;

    const bool operator<( const MyStringImpl& rhv )const;

    void toLower( void );
    void toUpper( void );
    const bool contains( const MyString & inputString ) const;
    const bool contains( const char * inputString ) const;
    void replace( const MyString& inWhat, const MyString& inFor );
    const std::string& string( void ) const;
    std::string& string( void );
    const char* cStr( void )const;
    const Length length( void ) const;
    const Length capacity( void ) const;
    void clear( void );
    const bool empty()const;

protected:
private:
    std::string m_value;

};

NAMESPACE_END( CUL )