#pragma once

#include "CUL/CUL.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"
#include "CUL/STL_IMPORTS/STD_string.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"

namespace CUL
{

class CULLib_API IString
{
public:
#if CUL_USE_WCHAR
    using UnderlyingType = std::wstring;
    using UnderlyingChar = wchar_t;
    #define NullTerminator L'\0'
    #define LineEnding L'\n'
    #define LineEndingCarriage L'\r\n'
    #define ZeroChar L'0'
#else  // #if CUL_USE_WCHAR
    using UnderlyingType = std::string;
    using UnderlyingChar = char;
    #define NullTerminator '\0'
    #define LineEnding '\n'
    #define LineEndingCarriage '\r\n'
    #define ZeroChar '0'
#endif  // #if CUL_USE_WCHAR

    IString() = default;
    IString( const IString& inArg ) = default;
    IString( IString&& inArg ) = default;
    IString& operator=( const IString& inArg ) = default;
    IString& operator=( IString&& inArg ) = default;

    virtual void append( const std::string& inStr ) = 0;
    virtual void append( const std::wstring& inStr ) = 0;
    virtual void append( char inChar ) = 0;
    virtual void append( wchar_t inChar ) = 0;
    virtual void append( const char* inChar ) = 0;
    virtual void append( const wchar_t* inChar ) = 0;

    virtual void removeAll( char inWhat ) = 0;
    virtual void removeAll( wchar_t inWhat ) = 0;

    virtual std::int32_t size() const = 0;

    virtual const UnderlyingChar* getCharVal() const = 0;
    virtual bool equals( const char* arg ) const = 0;
    virtual bool equals( const std::string& arg ) const = 0;
    virtual bool equals( const wchar_t* arg ) const = 0;
    virtual bool equals( const std::wstring& arg ) const = 0;

    virtual std::int32_t find( const char* inArg ) const = 0;
    virtual std::int32_t find( const char inArg ) const = 0;
    virtual std::int32_t find( const wchar_t* inArg ) const = 0;
    virtual std::int32_t find( const wchar_t inArg ) const = 0;
    virtual std::int32_t find( const std::wstring& inArg ) const = 0;
    virtual std::int32_t find( const std::string& inArg ) const = 0;

    virtual bool contains( const char inArg ) const = 0;
    virtual bool contains( const char* inArg ) const = 0;
    virtual bool contains( const std::string& inArg ) const = 0;

    virtual bool contains( const wchar_t inArg ) const = 0;
    virtual bool contains( const wchar_t* inArg ) const = 0;
    virtual bool contains( const std::wstring& inArg ) const = 0;

    virtual void erase( std::int32_t offset, std::int32_t len ) = 0;

    virtual const char* getUtfChar() const = 0;

    bool operator==( const char* inArg ) const;

    // Compare
    virtual bool startsWith( const char* inArg ) const;
    virtual bool startsWith( const wchar_t* inArg ) const;

    // Conversion
    virtual bool isFloat() const;
    virtual float toFloat() const;
    virtual std::int64_t toInt64() const;

    virtual ~IString() = default;

protected:
private:
};
}