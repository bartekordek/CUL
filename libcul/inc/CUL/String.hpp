#pragma once

#include "CUL/StringBuffers.hpp"
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

    std::int32_t find( const String& arg ) const;
    String substr( std::int32_t pos = 0, std::int32_t len = -1 ) const;

    void toLower();
    String toLowerR()const;
    void toUpper();

    void resize( std::int32_t newSize );

    bool contains( const String& inputString ) const;
    bool contains( const char* inputString ) const;

    bool replaceAll( const String& inWhat, const String& inFor );
    bool replace( const String& inWhat, const String& inFor );
    void replace( const char inWhat, const char inFor );
    void replace( const wchar_t inWhat, const wchar_t inFor );
    void removeAll( const char inWhat );

    bool doesEndWith( const char* end ) const;

    std::wstring wstring() const;

    std::string getString() const;

    const char* getChar() const;
    char* getChar();
    const char* cStr() const;
    char operator[]( std::size_t index ) const;

    float toFloat() const;
    double toDouble() const;
    int toInt();
    int64_t toInt64() const;
    uint64_t toUint64() const;
    std::uint64_t toUInt() const;
    bool toBool() const;

    std::int32_t size() const;
    void clear();
    bool empty() const;

    void setBinary( const char* value );
    const std::string getBinary() const;

    const std::vector<String> split( const String& delimiter ) const;
    constexpr static std::int32_t npos = -1;

    ~String();

protected:
private:
    void setupValue();
    IStringBuffer& getCurrentBuffer();
    const IStringBuffer& getCurrentBuffer() const;
    bool m_usingSSO = true;
    StringBufforStatic m_sso;
    StringBufforDynamic m_dyn;
    const char* m_value = nullptr;
};

struct CULLib_API StringHash
{
    std::size_t operator()( const String& s ) const noexcept
    {
        return std::hash<std::string>{}( s.getString() );
    }
};


String CULLib_API operator+( const char* arg1, const String& arg2 );

bool CULLib_API operator==( const char* arg1, const String& arg2 );

bool CULLib_API operator==( int arg1, const String& arg2 );

bool CULLib_API operator==( unsigned int arg1, const String& arg2 );

bool CULLib_API operator==( float arg1, const String& arg2 );

bool CULLib_API operator==( double arg1, const String& arg2 );

NAMESPACE_END( CUL )