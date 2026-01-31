#pragma once

#include "CUL/String/IString.hpp"
#include "CUL/Basic/ThreeState.hpp"
#include "CUL/STL_IMPORTS/STD_array.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"

#if _MSC_VER
    #pragma warning( disable : 4244 )
    #pragma warning( disable : 4251 )
#endif

NAMESPACE_BEGIN( CUL )
enum class ECharTypes : std::uint8_t
{
    Unkown = 0u,
    Char,
    Wchar
};

#if CUL_USE_WCHAR
constexpr wchar_t SingleQuote = L'\'';
#else   // #if CUL_USE_WCHAR
constexpr char SingleQuote = '\'';
#endif  // #if CUL_USE_WCHAR

class StringImpl;
class CULLib_API String: public IString
{
public:
    static constexpr std::size_t SSO_Size = 128;
    static constexpr float CapacityCoeficient = 1.5f;

    static constexpr std::int32_t UnderlyingCharSize = sizeof( UnderlyingChar );

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

    UnderlyingChar operator[]( std::int32_t inPos ) const;
    UnderlyingChar& operator[]( std::int32_t inPos );

    bool operator<( const String& arg ) const;
    bool operator>( const String& arg ) const;

    void append( const std::string& inStr ) override;
    void append( const std::wstring& inStr ) override;
    void append( char inChar ) override;
    void append( wchar_t inChar ) override;
    void append( const char* inChar ) override;
    void append( const wchar_t* inChar ) override;

    bool contains( const char inArg ) const override;
    bool contains( const char* inArg ) const override;
    bool contains( const std::string& inArg ) const override;

    bool contains( const wchar_t inArg ) const override;
    bool contains( const wchar_t* inArg ) const override;
    bool contains( const std::wstring& inArg ) const override;

    std::int32_t find( const char* inArg ) const override;
    std::int32_t find( const char inArg ) const override;
    std::int32_t find( const wchar_t* inArg ) const override;
    std::int32_t find( const wchar_t inArg ) const override;
    std::int32_t find( const std::wstring& inArg ) const override;
    std::int32_t find( const std::string& inArg ) const override;

    String substr( std::int32_t pos = 0, std::int32_t len = -1 ) const;

    std::int32_t count( wchar_t inChar ) const;
    std::int32_t count( char inChar ) const;

    void toLower();
    String toLowerR() const;
    void toUpper();

    void replace( const String& inWhat, const String& inFor );
    void replace( const char inWhat, const char inFor, bool allOccurences );
    void replace( const wchar_t inWhat, const wchar_t inFor, bool allOccurences );

    void removeFrist();
    void removeLast();
    void removeAll( char inWhat ) override;
    void removeAll( wchar_t inWhat ) override;
    void erase( std::int32_t offset, std::int32_t len ) override;

    bool equals( const char* arg ) const override;
    bool equals( const std::string& arg ) const override;
    bool equals( const wchar_t* arg ) const override;
    bool equals( const std::wstring& arg ) const override;

    bool doesEndWith( const std::string& end ) const;
    bool doesEndWith( const std::wstring& end ) const;

    std::string string() const;

    std::wstring wstring() const;

    const UnderlyingType getString() const;
    const UnderlyingChar* getCharVal() const override;

    const char* getUtfChar() const override;
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

    std::int32_t length() const;
    std::int32_t size() const override;
    std::int32_t capacity() const;
    void clear();
    bool empty() const;
    void reserve( std::int32_t newSize, bool keepValues );

    void serialize();
    void deserialize();

    std::vector<String> split( const String& delimiter ) const;
    std::vector<String> split( const char delimiter ) const;
    std::vector<String> split( const wchar_t delimiter ) const;

    bool getIsSerialized() const;

    void removeTrailingLineEnd();
    void removeFromStart( const wchar_t* inStr );
    void removeFromStart( const char* inStr );

    bool startsWith( const char* inArg, std::size_t* outInStrLen = nullptr ) const;
    bool startsWith( const wchar_t* inArg, std::size_t* outInStrLen = nullptr ) const;

    static String createFromPrintf( const char* msg... );

    void sanitize();
    void escapeCharacter( const UnderlyingType& characterToEscape );
    void singleQuoteEscape();
    void singleQuoteRestore();

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
    void setSize( std::int32_t newSize );
    void verify();
    void tryFitIntoSSO();
    void removePrecedingZero();

    void grow( std::int32_t targetSize, bool keepValue );
    void releaseBuffer();
    void resetWithMaxValue();
    void verifyTerminator();
    void terminate();
    void fetchTemp() const;
    void deleteTemp();

    std::int32_t calcualteCapacity( std::int32_t inSize ) const;
    UnderlyingChar* m_value{ nullptr };
    std::int32_t m_capacity{ SSO_Size };
    std::int32_t m_size{ 0u };
    std::array<UnderlyingChar, SSO_Size> m_staticValue{};
    UnderlyingChar* m_dynamicValue{ nullptr };
    bool m_isBinary{ false };

#if CUL_USE_WCHAR
    mutable char* m_temp{ nullptr };
#else
    mutable wchar_t* m_temp{ nullptr };
#endif  // #if defined(CUL_WINDOWS)
    bool m_serialized{ false };
};

struct CULLib_API StringHash{ std::size_t operator()( const String & s ) const noexcept { return std::hash<std::string>{}( s.string() );
}
}
;

NAMESPACE_END( CUL )
