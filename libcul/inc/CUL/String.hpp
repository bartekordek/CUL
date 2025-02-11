#pragma once

#include "CUL/Basic/ThreeState.hpp"
#include "CUL/STL_IMPORTS/STD_string.hpp"
#include "CUL/STL_IMPORTS/STD_array.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"

#if _MSC_VER
#pragma warning( disable: 4244 )
#pragma warning( disable: 4251 )
#endif

NAMESPACE_BEGIN( CUL )
using Length = std::int64_t;

enum class ECharTypes: std::uint8_t
{
    Unkown = 0u,
    Char,
    Wchar
};


class CULLib_API StringUtil
{
public:
    static void valueToHex( std::uint16_t inValue, std::array<std::uint8_t, 2>& outValue );
    static void valueToHex( std::uint8_t inValue, std::uint8_t& outValue );
    static std::uint16_t hexToValue( std::uint16_t inValue );
    static void valueToHex( char in, std::array<char, 2>& outValue );
    static void valueToHex( std::uint8_t in, std::array<uint8_t, 2>& outValue );
    static std::uint8_t hexToValue( const std::array<uint8_t, 2>& in );
    static std::uint8_t hexToValue( std::uint8_t in );
    static std::uint8_t charToValue( std::uint8_t in );

protected:
private:
};

class StringImpl;
class CULLib_API String final
{
public:
    static constexpr std::size_t SSO_Size = 128;
    static constexpr float CapacityCoeficient = 1.5f;
#if CUL_USE_WCHAR
    using UnderlyingType = std::wstring;
    using UnderlyingChar = wchar_t;
#define NullTerminator L'\0'
#define LineEnding L'\n'
#define LineEndingCarriage L'\r\n'
#else
    using UnderlyingType = std::string;
    using UnderlyingChar = char;
#define NullTerminator '\0'
#define LineEnding '\n'
#define LineEndingCarriage '\r\n'
#endif
    static constexpr Length UnderlyingCharSize = sizeof( UnderlyingChar );

    String() noexcept;
    String( const String& arg ) noexcept;
    String( String&& arg ) noexcept;
    explicit String( bool arg ) noexcept;
    String( const char* arg ) noexcept;
    String( const wchar_t* arg ) noexcept;
    String( unsigned char* arg ) noexcept;
    String( const std::string& arg ) noexcept;
    String( const std::wstring& arg ) noexcept;
    String( float arg ) noexcept;
    String( double arg ) noexcept;
    explicit String( std::int32_t arg ) noexcept;
    String( std::uint32_t arg ) noexcept;
    String( std::int64_t arg ) noexcept;
    String( std::uint64_t arg ) noexcept;

    void createFrom( const String& arg );
    void createFromMove( String& arg );
    void createFrom( bool arg );
    void createFrom( const char* arg );
    void createFrom( const std::string& arg );
    void createFrom( const std::wstring& arg );
    void createFrom( const wchar_t* arg );
    void createFrom( std::int32_t arg );
    void createFrom( std::uint32_t arg );
    void createFrom( std::int64_t arg );
    void createFrom( std::uint64_t arg );
    void createFrom( float arg );
    void createFrom( double arg );

    String& operator=( const String& arg );
    String& operator=( String&& arg ) noexcept;
    String& operator=( bool arg );
    String& operator=( const char* arg );
    String& operator=( const wchar_t* arg );
    String& operator=( unsigned char* arg );
    String& operator=( const std::string& arg );
    String& operator=( const std::wstring& arg );
    String& operator=( float arg );
    String& operator=( double arg );
    String& operator=( std::int32_t arg );
    String& operator=( std::uint32_t arg );
    String& operator=( std::int64_t arg );
    String& operator=( std::uint64_t arg );

    const char* operator*() const;

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

    bool operator!=( std::int32_t arg ) const;
    bool operator==( std::int32_t arg ) const;

    bool operator!=( std::uint32_t arg ) const;
    bool operator==( std::uint32_t arg ) const;

    bool operator!=( float arg ) const;
    bool operator==( float arg ) const;

    bool operator!=( double arg ) const;
    bool operator==( double arg ) const;

    bool operator<( const String& arg ) const;
    bool operator>( const String& arg ) const;

    bool operator()( const String& v1, const String& v2 ) const;

    void append( const String& arg );

    void append( const char* inChar );
    void append( const char* inChar, Length inCharLength );
    void append( char inChar );

    void append( const wchar_t* inChar );
    void append( const wchar_t* inChar, Length inCharLength );
    void append( wchar_t inChar );

    std::int32_t find( const String& arg ) const;
    std::int32_t find( const String& arg, Length startPos ) const;

    std::int32_t find( char arg ) const;
    std::int32_t find( char arg, Length startPos ) const;
    std::int32_t find( const char* arg ) const;
    std::int32_t find( const char* arg, Length startPos, Length argSize = -1 ) const;

    std::int32_t find( wchar_t arg ) const;
    std::int32_t find( wchar_t arg, Length startPos ) const;
    std::int32_t find( const wchar_t* arg ) const;
    std::int32_t find( const wchar_t* arg, Length startPos, Length argSize = -1 ) const;

    String substr( Length pos = 0, Length len = -1 ) const;

    void toLower();
    String toLowerR()const;
    void toUpper();

    bool contains( const String& inputString ) const;
    bool contains( const char* inputString ) const;

    void replace( const String& inWhat, const String& inFor );
    void replace( const char inWhat, const char inFor, bool allOccurences );
    void replace( const wchar_t inWhat, const wchar_t inFor, bool allOccurences );
    void removeAll( const char inWhat );

    bool equals( const char* arg ) const;
    bool equals( const std::string& arg ) const;
    bool equals( const String& arg ) const;

    bool doesEndWith( const std::string& end ) const;
    bool doesEndWith( const std::wstring& end ) const;

    std::string string() const;

    std::wstring wstring() const;

    const UnderlyingType getString() const;

    const char* cStr() const;
    const wchar_t* wCstr() const;
    const UnderlyingChar* getChar() const;

    bool isFloat() const;

    float toFloat() const;
    double toDouble() const;
    int toInt();
    int64_t toInt64() const;
    uint64_t toUint64() const;
    std::uint64_t toUInt() const;
    ThreeState toBool() const;

    Length length() const;
    Length size() const;
    Length capacity() const;
    void clear();
    bool empty() const;
    void reserve( std::int32_t newSize, bool keepValues );
    void erase( Length index );

    void serialize();
    void deserialize();

    const std::vector<String> split( const String& delimiter ) const;
    const std::vector<String> split( const char delimiter ) const;
    const std::vector<String> split( const wchar_t delimiter ) const;


    bool getIsSerialized() const;

    static Length wideStringToChar( char* out, Length outSize, const wchar_t* in );
    static Length wideStringToChar( char* out, Length outSize, const wchar_t* in, Length inSize );
    static Length wideStringToChar( char& out, wchar_t in );
    static Length wideStringToChar( std::string& out, const std::wstring& in );

    static Length charToWideString( Length codePage, wchar_t* out, Length outSize, const char* in );
    static Length charToWideString( Length codePage, wchar_t* out, Length outSize, const char* in, Length inSize );
    static Length charToWideString( Length codePage, wchar_t& out, char in );
    static Length charToWideString( std::wstring& out, const std::string& in );

    static void copyString( char* target, const char* source );
    static void copyString( char* target, Length targetSize, const char* source, Length sourceSize );
    static void copyString( wchar_t* target, const wchar_t* source );
    static void copyString( wchar_t* target, Length targetSize, const wchar_t* source, Length sourceSize );

    static std::int32_t cmp( const char* s1, const char* s2 );
    static bool equals( const char* s1, const char* s2, std::size_t length );
    static std::int32_t cmp( const wchar_t* s1, const wchar_t* s2 );
    static bool equals( const wchar_t* s1, const wchar_t* s2, std::size_t length );

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

    void removeTrailingLineEnd();

    ~String();

protected:
private:
    void init();
#if CUL_USE_WCHAR
    void deserializeWchar( std::wstring& out );
#else
    void deserializeWchar( std::string& out );
#endif
    void deserializeChar( std::string& out );
    void setSize( Length newSize );
    void verify();
    void tryFitIntoSSO();

    void grow( Length targetSize, bool keepValue );
    void releaseBuffer();
    void resetWithMaxValue();
    void verifyTerminator();
    void terminate();

    Length calcualteCapacity( Length inSize ) const;
    UnderlyingChar* m_value{nullptr};
    Length m_capacity{ SSO_Size };
    Length m_size{ 0u };
    std::array<UnderlyingChar, SSO_Size> m_staticValue{};
    UnderlyingChar* m_dynamicValue{ nullptr };
    bool m_isBinary{ false };

#if CUL_USE_WCHAR
    mutable char* m_temp{ nullptr };
#else
    mutable wchar_t* m_temp{ nullptr };
#endif // #if defined(CUL_WINDOWS)
    bool m_serialized{ false };
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
