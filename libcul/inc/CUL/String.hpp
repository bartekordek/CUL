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
    String();
    String( const char* inputString );
    String( const unsigned char* inputString );
    String( const String& inputString );
    String( const std::string& inputString );
    String( const double val );
    String( const float val );
    String( const bool val );
    String( const int val );
    String( const unsigned val );
    ~String();

    String& operator=( const char* someString );
    String& operator=( const unsigned char* someString );
    String& operator=( const std::string& someString );
    String& operator=( const String& someString );
    String& operator=( const double val );
    String& operator=( const float val );
    String& operator=( const bool val );
    String& operator=( const int val );
    String& operator+( const unsigned val );
    String& operator=( const unsigned val );

    String operator+( const String& rhv );
    String& operator+=( const String& rhv );

    const bool operator!=( const char* rhv ) const;
    const bool operator!=( const std::string& rhv ) const;
    const bool operator!=( const String& rhv ) const;

    const bool operator==( const char* rhv ) const;
    const bool operator==( const std::string& rhv ) const;
    const bool operator==( const String& rhv ) const;

    operator const std::string() const;
    operator const std::string&() const;

    void toLower();
    void toUpper();

    const bool contains( const String& inputString ) const;
    const bool contains( const char* inputString ) const;

    void replace( const String& inWhat, const String& inFor );

    const std::string& string() const;
    std::string& string();

    const char* cStr() const;
    const Length length() const;
    const Length capacity() const;
    void clear();
    const bool empty() const;

    static void toLowerS( std::string& inOutString );
    static void toUpperS( std::string& inOutString );

protected:
private:
    StringImpl* m_impl = nullptr;
};

using CsStr = const String;

CsStr CULLib_API operator+( CsStr& lhv, CsStr& rhv );
const bool CULLib_API operator==( const char* lhv, CsStr& rhv );
const bool CULLib_API operator<( CsStr& lhv, CsStr& rhv );

NAMESPACE_END( CUL )