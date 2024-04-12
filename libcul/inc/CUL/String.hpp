#pragma once

#include "CUL/CUL.hpp"
#include "CUL/STL_IMPORTS/STD_string.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"

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
#ifdef _MSC_VER
    using UnderlyingType = std::wstring;
    using UnderlyingChar = wchar_t;
#else
    using UnderlyingType = std::string;
    using UnderlyingChar = char;
#endif

    explicit String() noexcept;
    String( const String& arg ) noexcept;
    String( String&& arg ) noexcept;
    String( const bool arg ) noexcept;
    String( const char* arg ) noexcept;
    String( const wchar_t* arg ) noexcept;
    String( unsigned char* arg ) noexcept;
    String( const std::string& arg ) noexcept;
    String( const std::wstring& arg ) noexcept;
    String( float arg ) noexcept;
    String( double arg ) noexcept;
    String( int arg ) noexcept;
    String( unsigned int arg ) noexcept;
    String( int64_t arg ) noexcept;
    String( uint64_t arg ) noexcept;

    String& operator=( const String& arg );
    String& operator=( String&& arg ) noexcept;
    String& operator=( const bool arg );
    String& operator=( const char* arg );
    String& operator=( const wchar_t* arg );
    String& operator=( unsigned char* arg );
    String& operator=( const std::string& arg );
    String& operator=( const std::wstring& arg );
    String& operator=( float arg );
    String& operator=( double arg );
    String& operator=( int arg );
    String& operator=( unsigned arg );
    String& operator=( int64_t arg );
    String& operator=( uint64_t arg );

    String operator+( const String& arg ) const;

    String& operator+=( const String& arg );

    bool operator==( const String& arg ) const;
    bool operator!=( const String& arg ) const;

    bool operator==( const std::string& arg ) const;
    bool operator!=( const std::string& arg ) const;

    bool operator==( const char* arg ) const;
    bool operator!=( const char* arg ) const;

    bool operator!=( int arg ) const;
    bool operator==( int arg ) const;

    bool operator!=( unsigned int arg ) const;
    bool operator==( unsigned int arg ) const;

    bool operator!=( float arg ) const;
    bool operator==( float arg ) const;

    bool operator!=( double arg ) const;
    bool operator==( double arg ) const;

    bool operator<( const String& arg ) const;
    bool operator>( const String& arg ) const;

    bool operator()( const String& v1, const String& v2 ) const;

    size_t find( const String& arg ) const;
    String substr( size_t pos = 0, size_t len = UnderlyingType::npos ) const;

    void toLower();
    String toLowerR()const;
    void toUpper();

    bool contains( const String& inputString ) const;
    bool contains( const char* inputString ) const;

    void replace( const String& inWhat, const String& inFor );
    void replace( const char inWhat, const char inFor );
    void replace( const wchar_t inWhat, const wchar_t inFor );
    void removeAll( const char inWhat );

    bool equals( const char* arg ) const;
    bool equals( const std::string& arg ) const;
    bool equals( const String& arg ) const;

    bool doesEndWith( const UnderlyingType& end ) const;

    std::string string() const;

    std::wstring wstring() const;

    const UnderlyingType& getString() const;

    const char* cStr() const;
    const wchar_t* wCstr() const;
    const UnderlyingChar* getChar() const;

    float toFloat() const;
    double toDouble() const;
    int toInt();
    int64_t toInt64() const;
    uint64_t toUint64() const;
    std::uint64_t toUInt() const;
    bool toBool() const;


    Length length() const;
    size_t size() const;
    Length capacity() const;
    void clear();
    bool empty() const;

    void convertToHexData();
    void convertFromHexToString();
    void setBinary( const char* value );
    const std::string getBinary() const;

    const std::vector<String> split( const String& delimiter ) const;

    ~String();

protected:
private:
    UnderlyingType m_value;
    std::string m_binaryValue;
    std::string m_fallback;
    bool m_isBinary = false;
    mutable std::string m_temp;
};

struct CULLib_API StringHash
{
    std::size_t operator()( const String& s ) const noexcept
    {
        return std::hash<std::string>{}( s.string() );
    }
};


String CULLib_API operator+( const char* arg1, const String& arg2 );

bool CULLib_API operator==( const char* arg1, const String& arg2 );

bool CULLib_API operator==( int arg1, const String& arg2 );

bool CULLib_API operator==( unsigned int arg1, const String& arg2 );

bool CULLib_API operator==( float arg1, const String& arg2 );

bool CULLib_API operator==( double arg1, const String& arg2 );

NAMESPACE_END( CUL )