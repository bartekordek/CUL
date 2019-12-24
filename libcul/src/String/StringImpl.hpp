#pragma once

#include "CUL/String.hpp"

NAMESPACE_BEGIN( CUL )

class StringImpl final
{
public:
    StringImpl() = default;
    StringImpl( const char* val );
    StringImpl( const unsigned char* val );
    StringImpl( const std::string& val );
    StringImpl( const StringImpl& val );
    StringImpl( const double val );
    StringImpl( const float val );
    StringImpl( const bool val );
    StringImpl( const int val );
    StringImpl( const unsigned val );
    ~StringImpl() = default;

    StringImpl& operator=( const char* rhv );
    StringImpl& operator=( const unsigned char* rhv );
    StringImpl& operator=( const std::string& rhv );
    StringImpl& operator=( const StringImpl& rhv );
    StringImpl& operator=( const double val );
    StringImpl& operator=( const float val );
    StringImpl& operator=( const bool val );
    StringImpl& operator=( const int val );
    StringImpl& operator=( const unsigned val );
    StringImpl& operator+( const unsigned val );

    StringImpl operator+( const StringImpl& rhv );
    StringImpl& operator+=( const StringImpl& rhv );

    const bool operator==( const char* rhv ) const;
    const bool operator==( const std::string& rhv ) const;
    const bool operator==( const StringImpl& rhv ) const;

    operator const std::string() const;
    operator const std::string&() const;

    const bool operator<( const StringImpl& rhv ) const;

    void toLower( void );
    void toUpper( void );
    const bool contains( const String & inputString ) const;
    const bool contains( const char * inputString ) const;
    void replace( const String& inWhat, const String& inFor );
    const std::string& string( void ) const;
    std::string& string( void );
    const char* cStr( void ) const;
    const Length length( void ) const;
    const Length capacity( void ) const;
    void clear( void );
    const bool empty() const;

protected:
private:
    std::string m_value;

};

NAMESPACE_END( CUL )