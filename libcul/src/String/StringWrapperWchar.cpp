#include "CUL/String/StringWrapper.hpp"

#if CUL_USE_WCHAR
    #include "CUL/String/StringUtil.hpp"
namespace CUL
{

STDStringWrapper::STDStringWrapper( const char* inArg )
{
    if( inArg && ( StringUtil::strLen( inArg ) ) > 0 )
    {
        StringUtil::charToWideString( m_value, inArg );
    }
}

STDStringWrapper::STDStringWrapper( const char inArg )
{
    std::string argStr;
    argStr.push_back( inArg );
    StringUtil::charToWideString( m_value, argStr );
}

STDStringWrapper::STDStringWrapper( const std::string& inArg )
{
    StringUtil::charToWideString( m_value, inArg );
}

STDStringWrapper::STDStringWrapper( const wchar_t* inArg ): m_value( inArg )
{
}

STDStringWrapper::STDStringWrapper( const wchar_t inArg )
{
    m_value.push_back( inArg );
}

STDStringWrapper::STDStringWrapper( const std::wstring& inArg ): m_value( inArg )
{
}

STDStringWrapper& STDStringWrapper::operator=( const STDStringWrapper& inArg )
{
    if( this != &inArg )
    {
        m_value = inArg.m_value;
    }
    return *this;
}

STDStringWrapper& STDStringWrapper::operator=( STDStringWrapper&& inArg ) noexcept
{
    if( this != &inArg )
    {
        m_value = std::move( inArg.m_value );
    }
    return *this;
}

STDStringWrapper& STDStringWrapper::operator=( const std::string& inArg )
{
    StringUtil::charToWideString( m_value, inArg );
    return *this;
}

STDStringWrapper& STDStringWrapper::operator=( const char* inArg )
{
    if( inArg && ( StringUtil::strLen( inArg ) > 0 ) )
    {
        StringUtil::charToWideString( m_value, inArg );
    }
    return *this;
}

STDStringWrapper& STDStringWrapper::operator=( const std::wstring& inArg )
{
    m_value = inArg;
    return *this;
}

std::string STDStringWrapper::getSTDString() const
{
    std::string result;
    StringUtil::wideStringToChar( result, m_value );
    return result;
}

std::wstring STDStringWrapper::getSTDWstring() const
{
    return m_value;
}

std::int32_t STDStringWrapper::find( const char* inArg ) const
{
    const std::string argStdStr = inArg;
    std::wstring toFind;
    StringUtil::charToWideString( toFind, argStdStr );
    return StringUtil::find( m_value, toFind );
}

std::int32_t STDStringWrapper::find( const char inArg ) const
{
    std::string argStdStr;
    argStdStr.push_back( inArg );
    std::wstring toFind;
    StringUtil::charToWideString( toFind, argStdStr );
    return StringUtil::find( m_value, toFind );
}

std::int32_t STDStringWrapper::find( const wchar_t* inArg ) const
{
    return StringUtil::find( m_value, inArg );
}

std::int32_t STDStringWrapper::find( const wchar_t inArg ) const
{
    std::wstring word;
    word.push_back( inArg );
    return StringUtil::find( m_value, word );
}

std::int32_t STDStringWrapper::find( const std::wstring& inArg ) const
{
    return StringUtil::find( m_value, inArg );
}

std::int32_t STDStringWrapper::find( const std::string& inArg ) const
{
    std::wstring toFind;
    StringUtil::charToWideString( toFind, inArg );
    return StringUtil::find( m_value, toFind );
}

bool STDStringWrapper::equals( const char* inArg ) const
{
    std::wstring converted;
    const std::string argStr = inArg;

    StringUtil::charToWideString( converted, argStr );
    return converted == m_value;
}

bool STDStringWrapper::equals( const wchar_t* inArg ) const
{
    return m_value == inArg;
}

bool STDStringWrapper::equals( const std::string& inArg ) const
{
    std::wstring converted;
    StringUtil::charToWideString( converted, inArg );
    return converted == m_value;
}

bool STDStringWrapper::equals( const std::wstring& inArg ) const
{
    return m_value == inArg;
}

void STDStringWrapper::append( const std::string& inArg )
{
    std::wstring converted;
    StringUtil::charToWideString( m_value, inArg );
}

void STDStringWrapper::append( const std::wstring& inArg )
{
    m_value += inArg;
}

void STDStringWrapper::append( char inChar )
{
    std::string word;
    word.push_back( inChar );

    std::wstring wordToBeAppended;
    StringUtil::charToWideString( wordToBeAppended, word );
    m_value += wordToBeAppended;
}

void STDStringWrapper::append( wchar_t inChar )
{
    m_value.push_back( inChar );
}

void STDStringWrapper::append( const char* inChar )
{
    std::wstring wordToBeAppended;
    std::string word{ inChar };
    StringUtil::charToWideString( wordToBeAppended, word );
    m_value += wordToBeAppended;
}

void STDStringWrapper::append( const wchar_t* inChar )
{
    m_value += inChar;
}

void STDStringWrapper::replace( const char inWhat, const char inFor, bool allOccurences )
{
    StringUtil::replace( m_value.data(), StringUtil::toWideChar( inWhat ), StringUtil::toWideChar( inFor ), allOccurences );
}

void STDStringWrapper::replace( const wchar_t inWhat, const wchar_t inFor, bool allOccurences )
{
    StringUtil::replace( m_value.data(), inWhat, inFor, allOccurences );
}

void STDStringWrapper::removeFromStart( const char* inStr )
{
    std::wstring inWstr;
    StringUtil::charToWideString( inWstr, inStr );
    StringUtil::removeFromStart( m_value.data(), inWstr.c_str() );
}

void STDStringWrapper::removeFromStart( const wchar_t* inStr )
{
    StringUtil::removeFromStart( m_value.data(), inStr );
}

void STDStringWrapper::removeAll( const char inStr )
{
    const wchar_t toRemove = StringUtil::toWideChar( inStr );
    removeAll( toRemove );
}

void STDStringWrapper::removeAll( const wchar_t inStr )
{
    const std::wstring word( 1u, inStr );

    std::int32_t charPos = StringUtil::find( m_value, word );
    while( !m_value.empty() && ( charPos != -1 ) )
    {
        m_value.erase( (std::size_t)charPos, 1u );
        charPos = StringUtil::find( m_value, word );
    }
}

std::vector<STDStringWrapper> STDStringWrapper::split( const STDStringWrapper& delimiter ) const
{
    std::vector<STDStringWrapper> result;

    if( delimiter.empty() )
    {
        result.push_back( m_value );
        return result;
    }

    std::size_t pos = 0;
    std::size_t next;

    while( ( next = m_value.find( delimiter.m_value, pos ) ) != std::string::npos )
    {
        result.emplace_back( m_value.substr( pos, next - pos ) );
        pos = next + delimiter.size();
    }

    // last token
    result.emplace_back( m_value.substr( pos ) );

    return result;
}

std::vector<STDStringWrapper> STDStringWrapper::split( const char delimiter ) const
{
    auto splitedString = StringUtil::split( m_value, delimiter );
    std::vector<STDStringWrapper> result;
    result.reserve( splitedString.size() );
    for( const auto& str : splitedString )
    {
        result.push_back( str );
    }
    return result;
}

std::vector<STDStringWrapper> STDStringWrapper::split( const wchar_t delimiter ) const
{
    auto splitedString = StringUtil::split( m_value, delimiter );
    std::vector<STDStringWrapper> result;
    result.reserve( splitedString.size() );
    for( const auto& str : splitedString )
    {
        result.push_back( str );
    }
    return result;
}

STDStringWrapper STDStringWrapper::substr( std::int32_t off, std::int32_t count ) const
{
    STDStringWrapper result;

    const std::int32_t stringSize = static_cast<std::int32_t>( m_value.size() );
    if( ( off >= stringSize ) || ( ( off + count ) >= stringSize ) )
    {
        return result;
    }

    result = m_value.substr( (std::size_t)off, static_cast<std::size_t>( count ) );

    return result;
}

const char* STDStringWrapper::getUtfChar() const
{
    const auto size = m_value.size();
    if( !m_utf )
    {
        m_utf = new char[size + 1u];
    }

    StringUtil::wideStringToChar( m_utf, (std::int32_t)size, m_value.c_str(), (std::int32_t)size );

    return m_utf;
}

bool STDStringWrapper::contains( const char inArg ) const
{
    return find( inArg ) != -1;
}

bool STDStringWrapper::contains( const char* inArg ) const
{
    return find( inArg ) != -1;
}

bool STDStringWrapper::contains( const std::string& inArg ) const
{
    return find( inArg ) != -1;
}

bool STDStringWrapper::contains( const wchar_t inArg ) const
{
    return find( inArg ) != -1;
}

bool STDStringWrapper::contains( const wchar_t* inArg ) const
{
    return find( inArg ) != -1;
}

bool STDStringWrapper::contains( const std::wstring& inArg ) const
{
    return find( inArg ) != -1;
}

bool STDStringWrapper::startsWith( const char* inArg ) const
{
    const std::wstring wstringArg = StringUtil::toWideString( inArg );
    return StringUtil::startsWith( m_value.c_str(), wstringArg.c_str() );
}

bool STDStringWrapper::startsWith( const wchar_t* inArg ) const
{
    return StringUtil::startsWith( m_value.c_str(), inArg );
}

STDStringWrapper::~STDStringWrapper()
{
}
}  // namespace CUL
#endif  // #if CUL_USE_WCHAR