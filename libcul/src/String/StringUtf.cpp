#include "CUL/StrintUTF.hpp"
#include "CUL/StringUtil.hpp"

NAMESPACE_BEGIN( CUL )

StringUTF::StringUTF()
{

}

StringUTF::StringUTF(const char* input)
{
    std::string copied = input;
    m_value.assign( copied.begin(), copied.end() );
}

StringUTF::StringUTF(const wchar_t* input)
{
    std::wstring copied = input;
    m_value.assign( copied.begin(), copied.end() );
}

StringUTF::StringUTF(const float input)
{
    const std::string copied = StringUtil::toChar<float>( input );
    m_value.assign( copied.begin(), copied.end() );
}

StringUTF::StringUTF(const std::uint32_t input)
{
    const std::string copied = StringUtil::toChar<std::uint32_t>( input );
    m_value.assign( copied.begin(), copied.end() );
}

StringUTF::StringUTF(const std::int32_t input)
{
    const std::string copied = StringUtil::toChar<std::int32_t>( input );
    m_value.assign( copied.begin(), copied.end() );
}

StringUTF::StringUTF(const std::uint64_t input)
{
    const std::string copied = StringUtil::toChar<std::uint64_t>( input );
    m_value.assign( copied.begin(), copied.end() );
}

StringUTF::StringUTF(const std::int64_t input)
{
    const std::string copied = StringUtil::toChar<std::int64_t>( input );
    m_value.assign( copied.begin(), copied.end() );
}

StringUTF::StringUTF( const String& input )
{
    const std::string copied = input.getString();
    m_value.assign( copied.begin(), copied.end() );
}

StringUTF& StringUTF::operator=( const char* input )
{
    std::string copied = input;
    m_value.assign( copied.begin(), copied.end() );
    return *this;
}

StringUTF& StringUTF::operator=( const wchar_t* input )
{
    std::wstring copied = input;
    m_value.assign( copied.begin(), copied.end() );
    return *this;
}

StringUTF& StringUTF::operator=( const float input )
{
    const std::string copied = StringUtil::toChar<float>( input );
    m_value.assign( copied.begin(), copied.end() );
    return *this;
}

StringUTF& StringUTF::operator=( const std::uint32_t input )
{
    const std::string copied = StringUtil::toChar<std::uint32_t>( input );
    m_value.assign( copied.begin(), copied.end() );
    return *this;
}

StringUTF& StringUTF::operator=( const std::int32_t input )
{
    const std::string copied = StringUtil::toChar<std::int32_t>( input );
    m_value.assign( copied.begin(), copied.end() );
    return *this;
}

StringUTF& StringUTF::operator=( const std::uint64_t input )
{
    const std::string copied = StringUtil::toChar<std::uint64_t>( input );
    m_value.assign( copied.begin(), copied.end() );
    return *this;
}

StringUTF& StringUTF::operator=(const std::int64_t input)
{
    const std::string copied = StringUtil::toChar<std::int64_t>( input );
    m_value.assign( copied.begin(), copied.end() );
    return *this;
}

StringUTF& StringUTF::operator=( const String& input )
{
    const std::string copied = input.getString();
    m_value.assign( copied.begin(), copied.end() );
    return *this;
}

bool StringUTF::operator==( const StringUTF& rhv ) const
{
    return m_value == rhv.m_value;
}

bool StringUTF::operator!=( const StringUTF& rhv ) const
{
    return m_value != rhv.m_value;
}

StringUTF& StringUTF::operator+=( const StringUTF& rhv )
{
    m_value += rhv.m_value;
    return *this;
}

StringUTF StringUTF::operator+( const StringUTF& rhv )
{
    StringUTF result( *this );
    result += rhv;
    return result;
}

void StringUTF::convertToHexData()
{
}

void StringUTF::convertFromHexToString()
{
}

void StringUTF::toLower()
{
}

void StringUTF::toUpper()
{
}

bool StringUTF::contains( const char* ) const
{
    return false;
}

const char* StringUTF::cStr() const
{
    return nullptr;
}

StringUTF::~StringUTF()
{

}

NAMESPACE_END( CUL )