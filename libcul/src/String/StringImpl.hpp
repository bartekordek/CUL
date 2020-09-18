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

    bool operator==( const char* rhv ) const;
    bool operator==( const std::string& rhv ) const;
    bool operator==( const StringImpl& rhv ) const;

    operator const std::string&( ) const;

    char at( const unsigned int index ) const;

    bool operator<( const StringImpl& rhv ) const;

    void toLower();
    void toUpper();
    bool contains( const String & inputString ) const;
    bool contains( const char * inputString ) const;
    void replace( const String& inWhat, const String& inFor );


    const std::string& string() const;
    std::string& string();
    const char* cStr() const;

    Length length() const;
    Length capacity() const;
    void clear();
    bool empty() const;

    ~StringImpl() = default;

protected:
private:
    std::string m_value;
};

NAMESPACE_END( CUL )