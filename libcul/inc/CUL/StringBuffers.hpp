#pragma once

#include "CUL/CUL.hpp"
#include "CUL/STL_IMPORTS/STD_array.hpp"

NAMESPACE_BEGIN( CUL )

constexpr std::size_t SSO_MaxSize = 256;

class IStringBuffer
{
public:
    IStringBuffer();
    IStringBuffer( const IStringBuffer& ) = delete;
    IStringBuffer( IStringBuffer&& ) = delete;
    IStringBuffer* operator=( const IStringBuffer& ) = delete;
    IStringBuffer* operator=( IStringBuffer&& ) = delete;

    virtual std::int32_t size() const = 0;
    virtual void resize( std::int32_t newSize ) = 0;
    virtual bool empty() const = 0;
    virtual char& operator[]( std::int32_t index ) = 0;
    virtual char operator[]( std::int32_t index ) const = 0;
    virtual const char* getChar() const = 0;

    virtual ~IStringBuffer();
protected:
private:
};

class StringBufforStatic final: public IStringBuffer
{
public:
    StringBufforStatic();
    StringBufforStatic( const char* input );
    StringBufforStatic( const wchar_t* input );
    StringBufforStatic( const StringBufforStatic& arg );
    StringBufforStatic( StringBufforStatic&& arg ) noexcept;

    StringBufforStatic& operator=( const StringBufforStatic& arg );
    StringBufforStatic& operator=( StringBufforStatic&& arg ) noexcept;

    StringBufforStatic& operator=( const char* input );
    StringBufforStatic& operator=( const wchar_t* input );

    bool operator==( const StringBufforStatic& rhv ) const;

    const char* getChar() const override;
    char* getChar();

    std::int32_t size() const override;
    void resize( std::int32_t newSize ) override;

    char& operator[]( std::int32_t index ) override;
    char operator[]( std::int32_t index ) const override;

    void Add( const char* input );
    void Add( const wchar_t* input );

    bool empty() const override;
    void clear();

    ~StringBufforStatic();

protected:
private:
    void release();
    std::array<char, SSO_MaxSize> m_char{};
    const char* m_charPtr = &m_char[0];
    std::int32_t m_charSize = 0;
};

class StringBufforDynamic final: public IStringBuffer
{
public:
    StringBufforDynamic();
    StringBufforDynamic( const char* input );
    StringBufforDynamic( const wchar_t* input );
    StringBufforDynamic( const StringBufforDynamic& arg );
    StringBufforDynamic( StringBufforDynamic&& arg ) noexcept;

    StringBufforDynamic& operator=( const StringBufforDynamic& arg );
    StringBufforDynamic& operator=( StringBufforDynamic&& arg ) noexcept;

    StringBufforDynamic& operator=( const char* input );
    StringBufforDynamic& operator=( const wchar_t* input );

    bool operator==( const StringBufforDynamic& rhv ) const;

    char& operator[]( std::int32_t index ) override;
    char operator[]( std::int32_t index ) const override;

    void Add( const char* input );
    void Add( const wchar_t* input );

    const char* getChar() const override;
    char* getChar();
    void clear();

    bool empty() const override;
    std::int32_t size() const override;
    void resize( std::int32_t newSize ) override;

    ~StringBufforDynamic();

protected:
private:
    void release();
    char* m_char = nullptr;
    std::int32_t m_charSize = 0;
};

NAMESPACE_END( CUL )