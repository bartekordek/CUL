#pragma once

#include "CUL/String/IString.hpp"

#if defined(_MSC_VER)
    #pragma warning( push )
    #pragma warning( disable : 4251 )
#endif

namespace CUL
{
class String;
class CULLib_API STDStringWrapper: public IString
{
public:
    static STDStringWrapper createFromPrintf( const char* msg,... );

    STDStringWrapper();
    STDStringWrapper( const STDStringWrapper& inArg );
    STDStringWrapper( STDStringWrapper&& inArg ) noexcept;

    STDStringWrapper( const std::string& inArg );
    STDStringWrapper( const char* inArg );
    STDStringWrapper( const char inArg );
    STDStringWrapper( const std::wstring& inArg );
    STDStringWrapper( const wchar_t* inArg );
    STDStringWrapper( const wchar_t inArg );

    STDStringWrapper& operator=( const STDStringWrapper& inArg );
    STDStringWrapper& operator=( STDStringWrapper&& inArg ) noexcept;
    STDStringWrapper& operator=( const char* inArg );
    STDStringWrapper& operator=( const std::string& inArg );
    STDStringWrapper& operator=( const wchar_t* inArg );
    STDStringWrapper& operator=( const std::wstring& inArg );

    STDStringWrapper operator+=( const STDStringWrapper& inArg );
    STDStringWrapper operator+( const STDStringWrapper& inArg ) const;
    STDStringWrapper operator+( const char* inArg ) const;
    STDStringWrapper operator+( const wchar_t* inArg ) const;

    void createFrom( const String& inStr );

    void append( const std::string& inStr ) override;
    void append( const std::wstring& inStr ) override;
    void append( char inChar ) override;
    void append( wchar_t inChar ) override;
    void append( const char* inChar ) override;
    void append( const wchar_t* inChar ) override;
    void append( const STDStringWrapper& inArg );

    const UnderlyingChar* getCharVal() const override;
    std::uint64_t toUint64() const;

    bool operator==( const STDStringWrapper& inArg ) const;
    bool operator<( const STDStringWrapper& inArg ) const;
    bool empty() const;
    bool contains( const STDStringWrapper& inArg ) const;
    std::int32_t size() const override;

    IString::UnderlyingChar operator[]( std::int32_t inPos ) const;
    IString::UnderlyingChar& operator[]( std::int32_t inPos );

    void trim( TrimType type, UnderlyingChar ch = CUL_CHAR( ' ' ) );
    void replace( const char inWhat, const char inFor, bool allOccurences );
    void replace( const wchar_t inWhat, const wchar_t inFor, bool allOccurences );
    void removeFromStart( const wchar_t* inStr );
    void removeFromStart( const char* inStr );

    STDStringWrapper getLower() const;
    STDStringWrapper getUpper() const;

    void toLower();
    void toUpper();

    void erase( std::int32_t offset, std::int32_t len ) override;
    void clear();

    std::string getSTDString() const;
    std::wstring getSTDWstring() const;
    const char* getUtfChar() const;
    const UnderlyingType& getValue() const;

    bool equals( const STDStringWrapper& arg ) const;

    bool equals( const char* arg ) const override;
    bool equals( const std::string& arg ) const override;
    bool equals( const wchar_t* arg ) const override;
    bool equals( const std::wstring& arg ) const override;

    std::int32_t find( const char* inArg ) const override;
    std::int32_t find( const char inArg ) const override;
    std::int32_t find( const wchar_t* inArg ) const override;
    std::int32_t find( const wchar_t inArg ) const override;
    std::int32_t find( const std::wstring& inArg ) const override;
    std::int32_t find( const std::string& inArg ) const override;

    bool contains( const char inArg ) const override;
    bool contains( const char* inArg ) const override;
    bool contains( const std::string& inArg ) const override;

    bool contains( const wchar_t inArg ) const override;
    bool contains( const wchar_t* inArg ) const override;
    bool contains( const std::wstring& inArg ) const override;

    std::vector<STDStringWrapper> split( const STDStringWrapper& delimiter ) const;
    std::vector<STDStringWrapper> split( const char delimiter ) const;
    std::vector<STDStringWrapper> split( const wchar_t delimiter ) const;

    STDStringWrapper substr( std::int32_t off, std::int32_t count ) const;

    void removeAll( const char inWhat ) override;
    void removeAll( const wchar_t inWhat ) override;

    // Compare
    bool startsWith( const char* inArg ) const override;
    bool startsWith( const wchar_t* inArg ) const override;

    // Conversion
    bool isFloat() const override;
    float toFloat() const override;
    void fromFloat( float inValue );
    std::int64_t toInt64() const override;
    std::u8string toU8String() const;

    // Replace
    void replace( const std::string& inWhat, const std::string& inFor );
    void replace( const std::wstring& inWhat, const std::wstring& inFor );

    ~STDStringWrapper();

protected:
private:
    IString::UnderlyingType m_value;
#if CUL_USE_WCHAR
    mutable char* m_utf{ nullptr };
#endif  // #if CUL_USE_WCHAR
};


struct STDStringWrapperHash
{
    size_t operator()( const STDStringWrapper& s ) const noexcept
    {
        return std::hash<std::string_view>{}( s.getUtfChar() );
    }
};


using StringHash = STDStringWrapperHash;
using StringWr = STDStringWrapper;

#if defined( _MSC_VER )
    #pragma warning( pop )
#endif
}  // namespace CUL