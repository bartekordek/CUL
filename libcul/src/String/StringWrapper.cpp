#include "CUL/String/StringWrapper.hpp"
#include "CUL/String/StringUtil.hpp"
#include "CUL/String/String.hpp"
#include "CUL/STL_IMPORTS/STD_cstdarg.hpp"

namespace CUL
{
STDStringWrapper STDStringWrapper::createFromPrintf( const char* msg... )
{
    va_list args;
    va_start( args, msg );
    constexpr std::size_t bufferSize{ 1024u };
    char buffer[bufferSize];
    vsnprintf( buffer, bufferSize, msg, args );
    va_end( args );

    STDStringWrapper result( buffer );

    return result;
}

STDStringWrapper::STDStringWrapper()
{
}

// Conversion
bool STDStringWrapper::isFloat() const
{
    return StringUtil::isFloat( m_value );
}

float STDStringWrapper::toFloat() const
{
    const std::optional<float> result = StringUtil::toFloat( m_value );

    if( result )
    {
        return *result;
    }
    return 0.f;
}

std::int64_t STDStringWrapper::toInt64() const
{
    const std::optional<std::int64_t> result = StringUtil::strToUint64( m_value );

    if( result )
    {
        return *result;
    }
    return 0;
}

void STDStringWrapper::fromFloat( float inValue )
{
    StringUtil::fromFloat( m_value, inValue );
}

void STDStringWrapper::createFrom( const String& inStr )
{
    m_value = inStr.getString();
}

STDStringWrapper::STDStringWrapper( const STDStringWrapper& inArg ): m_value( inArg.m_value )
{
}

STDStringWrapper::STDStringWrapper( STDStringWrapper&& inArg ) noexcept: m_value( std::move( inArg.m_value ) )
{
}

STDStringWrapper STDStringWrapper::operator+( const STDStringWrapper& inArg ) const
{
    STDStringWrapper result( *this );
    result.m_value += inArg.m_value;
    return result;
}

STDStringWrapper STDStringWrapper::operator+( const char* inArg ) const
{
    STDStringWrapper result( *this );
    result += inArg;

    return result;
}

STDStringWrapper STDStringWrapper::operator+( const wchar_t* inArg ) const
{
    STDStringWrapper result( *this );
    result += inArg;

    return result;
}

STDStringWrapper STDStringWrapper::operator+=( const STDStringWrapper& inArg )
{
    this->m_value += inArg.m_value;
    return *this;
}

bool STDStringWrapper::equals( const STDStringWrapper& inArg ) const
{
    return m_value == inArg.m_value;
}

bool STDStringWrapper::contains( const STDStringWrapper& inArg ) const
{
    return StringUtil::find( m_value.c_str(), inArg.m_value.c_str() ) != -1;
}

std::int32_t STDStringWrapper::size() const
{
    return static_cast<std::int32_t>( m_value.size() );
}

String::UnderlyingChar STDStringWrapper::operator[]( std::int32_t inPos ) const
{
    return m_value[static_cast<std::size_t>( inPos )];
}

String::UnderlyingChar& STDStringWrapper::operator[]( std::int32_t inPos )
{
    return m_value[static_cast<std::size_t>( inPos )];
}

void STDStringWrapper::erase( std::int32_t offset, std::int32_t len )
{
    m_value.erase( (std::size_t)offset, (std::size_t)len );
}

void STDStringWrapper::clear()
{
    m_value.clear();
}

STDStringWrapper STDStringWrapper::getLower() const
{
    STDStringWrapper result( *this );
    result.toLower();
    return result;
}

STDStringWrapper STDStringWrapper::getUpper() const
{
    STDStringWrapper result( *this );
    result.toUpper();
    return result;
}

void STDStringWrapper::toLower()
{
    StringUtil::toLower( m_value.data() );
}

void STDStringWrapper::toUpper()
{
    StringUtil::toUpper( m_value.data() );
}

bool STDStringWrapper::empty() const
{
    return m_value.empty();
}

const IString::UnderlyingChar* STDStringWrapper::getCharVal() const
{
    return m_value.c_str();
}

const IString::UnderlyingType& STDStringWrapper::getValue() const
{
    return m_value;
}

std::uint64_t STDStringWrapper::toUint64() const
{
    return StringUtil::strToUint64( m_value );
}

bool STDStringWrapper::operator==( const STDStringWrapper& inArg ) const
{
    return m_value == inArg.m_value;
}

bool STDStringWrapper::operator<( const STDStringWrapper& inArg ) const
{
    return m_value < inArg.m_value;
}
}  // namespace CUL