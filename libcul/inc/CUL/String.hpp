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

class StringImpl;
class CULLib_API String final
{
public:
    explicit String();
    String( const bool arg );
    String( const char* arg );
    String( const std::string& arg );
    String( const double arg );
    String( const int arg );
    String( const unsigned int arg );

    String& operator=( const bool arg );
    String& operator=( const char* arg );
    String& operator=( const std::string& arg );
    String& operator=( const double arg );
    String& operator=( const int arg );
    String& operator=( const unsigned arg );

    String operator+( const String& arg ) const;

    String& operator+=( const String& arg );

    bool operator==( const String& arg ) const;
    bool operator!=( const String& arg ) const;

    bool operator==( const std::string& arg ) const;
    bool operator!=( const std::string& arg ) const;

    bool operator==( const char* arg ) const;
    bool operator!=( const char* arg ) const;

    bool operator!=( const int arg ) const;
    bool operator==( const int arg ) const;
    

    bool operator<( const String& arg ) const;

    void toLower();
    void toUpper();

    bool contains( const String& inputString ) const;
    bool contains( const char* inputString ) const;

    void replace( const String& inWhat, const String& inFor );

    const std::string& string() const;
    std::string& string();

    const char* cStr() const;

    Length length() const;
    Length capacity() const;
    void clear();
    bool empty() const;

    ~String();

protected:
private:
    std::string m_value;
};

String CULLib_API operator+( const char* arg1, const String& arg2 );
bool CULLib_API operator==( const char* arg1, const String& arg2 );
bool CULLib_API operator==( const int arg1, const String& arg2 );

NAMESPACE_END( CUL )