#pragma once

#include "CUL/CUL.hpp"
#include "CUL/STL_IMPORTS/STD_string.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"
#include "CUL/STL_IMPORTS/STD_array.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"

#if _MSC_VER
#pragma warning( disable: 4244 )
#pragma warning( disable: 4251 )
#endif

NAMESPACE_BEGIN( CUL )
using Length = std::int64_t;

class StringImpl;
class CULLib_API String final
{
public:
    static constexpr std::size_t SSO_Size = 32;
    static constexpr float CapacityCoeficient = 1.5f;
#ifdef _MSC_VER
    using UnderlyingType = std::wstring;
    using UnderlyingChar = wchar_t;
#else
    using UnderlyingType = std::string;
    using UnderlyingChar = char;
#endif
    static constexpr Length UnderlyingCharSize = sizeof( UnderlyingChar );

    String() noexcept;
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
    String( std::int32_t arg ) noexcept;
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
    String& operator=( std::int32_t arg );
    String& operator=( unsigned arg );
    String& operator=( int64_t arg );
    String& operator=( uint64_t arg );

    String operator+( const String& arg ) const;

    String& operator+=( const String& arg );

    UnderlyingChar operator[]( Length inPos ) const;
    UnderlyingChar& operator[]( Length inPos );

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

    std::int32_t find( const String& arg ) const;
    std::int32_t find( const String& arg, Length startPos ) const;
    String substr( std::int32_t pos = 0, std::int32_t len = -1 ) const;

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
    void reserve( std::int32_t newSize, bool keepValues );
    void erase( Length index );

    void convertToHexData();
    void convertFromHexToString();
    void setBinary( const char* value );
    const std::string getBinary() const;

    const std::vector<String> split( const String& delimiter ) const;

    static Length wideStringToChar( char* out, Length outSize, const wchar_t* in );
    static Length wideStringToChar( char* out, Length outSize, const wchar_t* in, Length inSize );
    static Length charToWideString( Length codePage, wchar_t* out, Length outSize, const char* in );
    static Length charToWideString( Length codePage, wchar_t* out, Length outSize, const char* in, Length inSize );
  
    static void copyString( char* target, const char* source );
    static void copyString( char* target, Length targetSize, const char* source, Length sourceSize );
    static void copyString( wchar_t* target, const wchar_t* source );
    static void copyString( wchar_t* target, Length targetSize, const wchar_t* source, Length sourceSize );

    static std::int32_t cmp( const char* s1, const char* s2 );
    static std::int32_t cmp( const wchar_t* s1, const wchar_t* s2 );

    static std::int32_t strLen( const char* inString );
    static std::int32_t strLen( const wchar_t* inString );

    static void toLower( char* inOut );
    static void toLower( char* inOut, std::int32_t size );

    static void toLower( wchar_t* inOut );
    static void toLower( wchar_t* inOut, std::int32_t size );

    static void toUpper( char* inOut );
    static void toUpper( char* inOut, std::int32_t size );

    static void toUpper( wchar_t* inOut );
    static void toUpper( wchar_t* inOut, std::int32_t size );

    ~String();

protected:
private:
    void createFrom( const String& arg );
    void createFromMove( String& arg );
    void createFrom( bool arg );
    void createFrom( const char* arg );
    void createFrom( const std::string& arg );
    void createFrom( const std::wstring& arg );
    void createFrom( const wchar_t* arg );
    void createFrom( std::int32_t arg );

    void grow( Length targetSize, bool keepValue );
    void releaseBuffer();
    Length calcualteCapacity( Length inSize ) const;
    Length m_capacity{ SSO_Size };
    Length m_size{ 0u };
    std::array<UnderlyingChar, SSO_Size> m_staticValue{};
    UnderlyingChar* m_value = nullptr;
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