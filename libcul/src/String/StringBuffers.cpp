#include "CUL/StringBuffers.hpp"
#include "CUL/StringUtil.hpp"
#include "CUL/STL_IMPORTS/STD_exception.hpp"

NAMESPACE_BEGIN( CUL )

StringBufforDynamic::StringBufforDynamic() :
    m_char( nullptr ),
    m_charSize(0)
{
}

StringBufforDynamic::StringBufforDynamic( const StringBufforDynamic& arg )
{
    const auto charPair = StringUtil::duplicate( arg.m_char );
    m_char = charPair.first;
    m_charSize = charPair.second;
}

StringBufforDynamic::StringBufforDynamic( StringBufforDynamic&& arg ) noexcept
{
    std::swap( m_char, arg.m_char );
    std::swap( m_charSize, arg.m_charSize );
}

StringBufforDynamic::StringBufforDynamic( const wchar_t* input )
{
    const auto charPair = StringUtil::wcharToChar( input, 0 );
    m_char = charPair.Ptr;
    m_charSize = charPair.Length;
}

StringBufforDynamic::StringBufforDynamic( const char* input )
{
    const auto charPair = StringUtil::duplicate( input, 0 );
    m_char = charPair.first;
    m_charSize = charPair.second;
}

CUL::StringBufforDynamic& StringBufforDynamic::operator=( const wchar_t* input )
{
    StringUtil::wcharToChar( m_char, m_charSize, input, 0,
                               [this](std::size_t newSize)
                               {
                                    delete[] m_char;
                                   m_char = new char[newSize];
                                   return m_char;
                               } );

    return *this;
}

bool StringBufforDynamic::operator==( const StringBufforDynamic& rhv ) const
{
    if( std::strcmp( m_char, rhv.m_char ) == 0 )
    {
        return true;
    }
    return false;
}

CUL::StringBufforDynamic& StringBufforDynamic::operator=( const char* input )
{
    const auto charPair = StringUtil::duplicate( input );
    m_char = charPair.first;
    m_charSize = charPair.second;

    return *this;
}

CUL::StringBufforDynamic& StringBufforDynamic::operator=( StringBufforDynamic&& arg ) noexcept
{
    if( this != &arg )
    {
        std::swap( m_char, arg.m_char );
        std::swap( m_charSize, arg.m_charSize );
    }

    return *this;
}

CUL::StringBufforDynamic& StringBufforDynamic::operator=( const StringBufforDynamic& arg )
{
    if( this != &arg )
    {
        const auto charPair = StringUtil::duplicate( arg.m_char, arg.m_charSize );
        m_char = charPair.first;
        m_charSize = charPair.second;
    }

    return *this;
}

void StringBufforDynamic::Add( const wchar_t* input )
{
    const std::string converted = StringUtil::wcharToChar( std::wstring( input ), 0 );
    Add( converted.c_str() );
}

char& StringBufforDynamic::operator[]( std::int32_t index )
{
    return m_char[index];
}

char StringBufforDynamic::operator[]( std::int32_t index ) const
{
    return m_char[index];
}

void StringBufforDynamic::Add( const char* input )
{
    const std::int32_t inputSize = StringUtil::getLength( input );

    if( m_char == nullptr )
    {
        m_charSize = inputSize;
        m_char = new char[static_cast<std::size_t>( m_charSize )];
        StringUtil::copy( m_char, input );
    }
    else
    {
        const char* oldBuff = m_char;
        m_charSize += inputSize;
        m_char = new char[static_cast<std::size_t>( m_charSize + 1 )];
        std::sprintf( m_char, "%s%s", oldBuff, input );
        delete oldBuff;
    }
}

const char* StringBufforDynamic::getChar() const
{
    return m_char;
}

char* StringBufforDynamic::getChar()
{
    return m_char;
}

void StringBufforDynamic::clear()
{
    release();
}

bool StringBufforDynamic::empty() const
{
    return m_char == nullptr;
}

std::int32_t StringBufforDynamic::size() const
{
    return m_charSize;
}

void StringBufforDynamic::resize( std::int32_t newSize )
{
    m_char = static_cast<char*>( std::realloc( m_char, static_cast<std::size_t>( newSize ) ) );
    m_charSize = newSize;
}

StringBufforDynamic::~StringBufforDynamic()
{
    release();
}

void StringBufforDynamic::release()
{
    delete[] m_char;
    m_char = nullptr;
    m_charSize = 0;
}

StringBufforStatic::StringBufforStatic()
{
}

StringBufforStatic::StringBufforStatic( const char* source )
{
    char* target = getChar();
    StringUtil::copy( target, source );
    m_charSize = StringUtil::getLength( getChar() );
}

StringBufforStatic::StringBufforStatic( const wchar_t* input )
{
    m_charSize = StringUtil::wcharToChar( m_char.data(), static_cast<std::int32_t>(m_char.size()), input, 0, []( std::int32_t )
                                             {
                                                 throw std::logic_error( "Static buffer! Cannot allocate more memory." );
                                                 return nullptr;
                                             } );
}

StringBufforStatic::StringBufforStatic( const StringBufforStatic& arg )
{
    char* target = getChar();
    const char* source = arg.getChar();
    StringUtil::copy( target, source );
    m_charSize = arg.m_charSize;
}

StringBufforStatic::StringBufforStatic( StringBufforStatic&& arg ) noexcept
{
    StringUtil::copy( getChar(), arg.getChar() );
    m_charSize = arg.m_charSize;
    arg.m_charSize = 0u;
}

CUL::StringBufforStatic& StringBufforStatic::operator=( const StringBufforStatic& arg )
{
    if( this != &arg )
    {
        StringUtil::copy( getChar(), arg.getChar() );
        m_charSize = arg.m_charSize;
    }
    return *this;
}

CUL::StringBufforStatic& StringBufforStatic::operator=( StringBufforStatic&& arg ) noexcept
{
    if( this != &arg )
    {
        StringUtil::copy( getChar(), arg.getChar() );

        m_charSize = arg.m_charSize;
        arg.m_charSize = 0u;
    }
    return *this;
}

CUL::StringBufforStatic& StringBufforStatic::operator=( const char* input )
{
    StringUtil::copy( getChar(), input);
    m_charSize = StringUtil::getLength( input );

    return *this;
}

CUL::StringBufforStatic& StringBufforStatic::operator=( const wchar_t* input )
{
    StringUtil::wcharToChar( m_char.data(), static_cast<std::int32_t>( m_char.size() ), input, 0, []( std::int32_t ) {
        throw std::logic_error( "Static buffer! Cannot allocate more memory." );
        return nullptr;
    } );
    return *this;
}

bool StringBufforStatic::operator==( const StringBufforStatic& rhv ) const
{
    if( std::strcmp(&m_char[0], &rhv.m_char[0]) == 0  )
    {
        return true;
    }
    return false;
}

bool StringBufforStatic::empty() const
{
    return m_charSize == 0u;
}

void StringBufforStatic::clear()
{
    release();
}

const char* StringBufforStatic::getChar() const
{
    return &m_char[0];
}

char* StringBufforStatic::getChar()
{
    return &m_char[0];
}

std::int32_t StringBufforStatic::size() const
{
    return m_charSize;
}

void StringBufforStatic::resize( std::int32_t newSize )
{
    if( newSize > SSO_MaxSize )
    {
        throw std::logic_error( "Static buffer! Cannot allocate more memory." );
    }

    const std::int32_t oldSize = size();
    if( newSize == oldSize )
    {
        return;
    }

    std::int32_t start = std::min( oldSize, newSize );
    std::int32_t stop = std::max( oldSize, newSize );


    for( std::int32_t i = start; i < stop; ++i )
    {
        m_char[i] = '\0';
    }
    m_charSize = newSize;
}

char& StringBufforStatic::operator[]( std::int32_t index )
{
    return m_char[index];
}

char StringBufforStatic::operator[]( std::int32_t index ) const
{
    return m_char[index];
}

void StringBufforStatic::Add( const char* input )
{
    std::string originalCopy = &m_char[0];
    m_charSize = sprintf( &m_char[0], "%s%s", originalCopy.c_str(), input );
}

void StringBufforStatic::Add( const wchar_t* input )
{
}

StringBufforStatic::~StringBufforStatic()
{
    release();
}

void StringBufforStatic::release()
{
    const std::size_t buffLength = m_char.size();
    for( std::size_t i = 0u; i < buffLength; ++i )
    {
        m_char[i] = 0;
    }
    m_charSize = 0u;
}

IStringBuffer::IStringBuffer()
{
}

IStringBuffer::~IStringBuffer()
{
}

NAMESPACE_END( CUL )