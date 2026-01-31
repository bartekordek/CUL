#pragma once

#include "CUL/String/IString.hpp"

namespace CUL
{
class String;
class STDStringWrapper: public IString
{
public:
    CULLib_API static STDStringWrapper createFromPrintf( const char* msg... );

    CULLib_API STDStringWrapper();
    CULLib_API STDStringWrapper( const STDStringWrapper& inArg );
    CULLib_API STDStringWrapper( STDStringWrapper&& inArg ) noexcept;

    CULLib_API STDStringWrapper( const std::string& inArg );
    CULLib_API STDStringWrapper( const char* inArg );
    CULLib_API STDStringWrapper( const char inArg );
    CULLib_API STDStringWrapper( const std::wstring& inArg );
    CULLib_API STDStringWrapper( const wchar_t* inArg );
    CULLib_API STDStringWrapper( const wchar_t inArg );

    CULLib_API STDStringWrapper& operator=( const STDStringWrapper& inArg );
    CULLib_API STDStringWrapper& operator=( STDStringWrapper&& inArg ) noexcept;
    CULLib_API STDStringWrapper& operator=( const char* inArg );
    CULLib_API STDStringWrapper& operator=( const std::string& inArg );
    CULLib_API STDStringWrapper& operator=( const wchar_t* inArg );
    CULLib_API STDStringWrapper& operator=( const std::wstring& inArg );

    CULLib_API STDStringWrapper operator+=( const STDStringWrapper& inArg );
    CULLib_API STDStringWrapper operator+( const STDStringWrapper& inArg ) const;
    CULLib_API STDStringWrapper operator+( const char* inArg ) const;
    CULLib_API STDStringWrapper operator+( const wchar_t* inArg ) const;

    CULLib_API void createFrom( const String& inStr );

    CULLib_API void append( const std::string& inStr ) override;
    CULLib_API void append( const std::wstring& inStr ) override;
    CULLib_API void append( char inChar ) override;
    CULLib_API void append( wchar_t inChar ) override;
    CULLib_API void append( const char* inChar ) override;
    CULLib_API void append( const wchar_t* inChar ) override;

    CULLib_API const UnderlyingChar* getCharVal() const override;
    CULLib_API std::uint64_t toUint64() const;

    CULLib_API bool operator==( const STDStringWrapper& inArg ) const;
    CULLib_API bool operator<( const STDStringWrapper& inArg ) const;
    CULLib_API bool empty() const;
    CULLib_API bool contains( const STDStringWrapper& inArg ) const;
    CULLib_API std::int32_t size() const override;

    CULLib_API IString::UnderlyingChar operator[]( std::int32_t inPos ) const;
    CULLib_API IString::UnderlyingChar& operator[]( std::int32_t inPos );

    CULLib_API void replace( const char inWhat, const char inFor, bool allOccurences );
    CULLib_API void replace( const wchar_t inWhat, const wchar_t inFor, bool allOccurences );
    CULLib_API void removeFromStart( const wchar_t* inStr );
    CULLib_API void removeFromStart( const char* inStr );

    CULLib_API STDStringWrapper getLower() const;
    CULLib_API STDStringWrapper getUpper() const;

    CULLib_API void toLower();
    CULLib_API void toUpper();

    CULLib_API void erase( std::int32_t offset, std::int32_t len ) override;
    CULLib_API void clear();

    CULLib_API std::string getSTDString() const;
    CULLib_API std::wstring getSTDWstring() const;
    CULLib_API const char* getUtfChar() const;
    CULLib_API const UnderlyingType& getValue() const;

    CULLib_API bool equals( const STDStringWrapper& arg ) const;

    CULLib_API bool equals( const char* arg ) const override;
    CULLib_API bool equals( const std::string& arg ) const override;
    CULLib_API bool equals( const wchar_t* arg ) const override;
    CULLib_API bool equals( const std::wstring& arg ) const override;

    CULLib_API std::int32_t find( const char* inArg ) const override;
    CULLib_API std::int32_t find( const char inArg ) const override;
    CULLib_API std::int32_t find( const wchar_t* inArg ) const override;
    CULLib_API std::int32_t find( const wchar_t inArg ) const override;
    CULLib_API std::int32_t find( const std::wstring& inArg ) const override;
    CULLib_API std::int32_t find( const std::string& inArg ) const override;

    CULLib_API bool contains( const char inArg ) const override;
    CULLib_API bool contains( const char* inArg ) const override;
    CULLib_API bool contains( const std::string& inArg ) const override;

    CULLib_API bool contains( const wchar_t inArg ) const override;
    CULLib_API bool contains( const wchar_t* inArg ) const override;
    CULLib_API bool contains( const std::wstring& inArg ) const override;

    CULLib_API std::vector<STDStringWrapper> split( const STDStringWrapper& delimiter ) const;
    CULLib_API std::vector<STDStringWrapper> split( const char delimiter ) const;
    CULLib_API std::vector<STDStringWrapper> split( const wchar_t delimiter ) const;

    CULLib_API STDStringWrapper substr( std::int32_t off, std::int32_t count ) const;

    CULLib_API void removeAll( const char inWhat ) override;
    CULLib_API void removeAll( const wchar_t inWhat ) override;

    // Compare
    bool startsWith( const char* inArg ) const override;
    bool startsWith( const wchar_t* inArg ) const override;

    // Conversion
    CULLib_API bool isFloat() const override;
    CULLib_API float toFloat() const override;
    CULLib_API void fromFloat( float inValue );
    CULLib_API std::int64_t toInt64() const override;

    // Replace
    void replace( const std::string& inWhat, const std::string& inFor );
    void replace( const std::wstring& inWhat, const std::wstring& inFor );

    CULLib_API ~STDStringWrapper();

protected:
private:
    IString::UnderlyingType m_value;
#if CUL_USE_WCHAR
    mutable char* m_utf{ nullptr };
#endif  // #if CUL_USE_WCHAR
};

using StringWr = STDStringWrapper;
}  // namespace CUL