#include "CUL/String/StringWrapper.hpp"

#if !CUL_USE_WCHAR
    #include "CUL/String/StringUtil.hpp"
namespace CUL
{
STDStringWrapper::STDStringWrapper( const char* inArg ): m_value( inArg )
{
}

STDStringWrapper::STDStringWrapper( const char inArg )
{
    m_value.push_back( inArg );
}

STDStringWrapper::STDStringWrapper( const std::string& inArg ): m_value( inArg )
{
}

STDStringWrapper::STDStringWrapper( const std::wstring& inArg )
{
    StringUtil::wideStringToChar( m_value, inArg );
}

STDStringWrapper::STDStringWrapper( const wchar_t* inArg )
{
    const auto buffSize = StringUtil::strLen( inArg ) * 2u;
    m_value.resize( buffSize );
    StringUtil::wideStringToChar( m_value.data(), buffSize, inArg );
}

STDStringWrapper::STDStringWrapper( const wchar_t inArg )
{
    std::wstring inWord;
    inWord.push_back( inArg );
    StringUtil::wideStringToChar( m_value, inWord );
}

void STDStringWrapper::replace( const char inWhat, const char inFor, bool allOccurences )
{
    StringUtil::replace( m_value.data(), inWhat, inFor, allOccurences );
}

void STDStringWrapper::replace( const wchar_t inWhat, const wchar_t inFor, bool allOccurences )
{
    StringUtil::replace( m_value.data(), StringUtil::toChar( inWhat ), StringUtil::toChar( inFor ), allOccurences );
}

STDStringWrapper& STDStringWrapper::operator=( const char* inArg )
{
    m_value = inArg;
    return *this;
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
    m_value = inArg;
    return *this;
}

STDStringWrapper& STDStringWrapper::operator=( const std::wstring& inArg )
{
    StringUtil::wideStringToChar( m_value, inArg );
    return *this;
}

std::string STDStringWrapper::getSTDString() const
{
    return m_value;
}

std::wstring STDStringWrapper::getSTDWstring() const
{
    std::wstring result;
    StringUtil::charToWideString( result, m_value );
    return result;
}

bool STDStringWrapper::equals( const char* inArg ) const
{
    return m_value == inArg;
}

bool STDStringWrapper::equals( const std::string& inArg ) const
{
    return m_value == inArg;
}

bool STDStringWrapper::equals( const wchar_t* inArg ) const
{
    std::string argStr;
    StringUtil::wideStringToChar( argStr, inArg );
    return m_value == argStr;
}

bool STDStringWrapper::equals( const std::wstring& inArg ) const
{
    const std::string word = StringUtil::toSTDstring( inArg );
    return m_value == word;
}

void STDStringWrapper::append( const std::string& inArg )
{
    m_value += inArg;
}

void STDStringWrapper::append( const std::wstring& inArg )
{
    std::string argStr;
    StringUtil::wideStringToChar( argStr, inArg );
    m_value += argStr;
}

void STDStringWrapper::append( char inChar )
{
    m_value += inChar;
}

void STDStringWrapper::append( wchar_t inChar )
{
    m_value.push_back( inChar );
}

void STDStringWrapper::append( const char* inChar )
{
    m_value += inChar;
}

void STDStringWrapper::append( const wchar_t* inChar )
{
    std::string argStr;
    StringUtil::wideStringToChar( argStr, inChar );
    m_value += argStr;
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

std::int32_t STDStringWrapper::find( const char* inArg ) const
{
    return StringUtil::find( m_value, inArg );
}

std::int32_t STDStringWrapper::find( const char inArg ) const
{
    const std::string word( 1u, inArg );
    return StringUtil::find( m_value, word );
}

std::int32_t STDStringWrapper::find( const wchar_t* inArg ) const
{
    return StringUtil::find( m_value.c_str(), inArg );
}

std::int32_t STDStringWrapper::find( const wchar_t inArg ) const
{
    std::wstring word( 1, inArg );
    return StringUtil::find( m_value.c_str(), word.c_str() );
}

std::int32_t STDStringWrapper::find( const std::wstring& inArg ) const
{
    return StringUtil::find( m_value.c_str(), inArg.c_str() );
}

std::int32_t STDStringWrapper::find( const std::string& inArg ) const
{
    return StringUtil::find( m_value, inArg );
}

void STDStringWrapper::removeFromStart( const char* inStr )
{
    StringUtil::removeFromStart( m_value.data(), inStr );
}

void STDStringWrapper::removeFromStart( const wchar_t* inStr )
{
    std::string whatToRemove;
    StringUtil::wideStringToChar( whatToRemove, inStr );
    StringUtil::removeFromStart( m_value.data(), whatToRemove.c_str() );
}

void STDStringWrapper::removeAll( const wchar_t inStr )
{
    const char inChar = StringUtil::toWideChar( inStr );
    removeAll( inChar );
}

void STDStringWrapper::removeAll( const char inStr )
{
    const std::string word( 1u, inStr );

    std::int32_t charPos = StringUtil::find( m_value, word );
    while( !m_value.empty() && ( charPos != -1 ) )
    {
        m_value.erase( (std::size_t)charPos, 1u );
        charPos = StringUtil::find( m_value, word );
    }
}

const char* STDStringWrapper::getUtfChar() const
{
    return m_value.c_str();
}

bool STDStringWrapper::startsWith( const char* inArg ) const
{
    return StringUtil::startsWith( m_value.c_str(), inArg );
}

bool STDStringWrapper::startsWith( const wchar_t* inArg ) const
{
    const std::string stringArg = StringUtil::toSTDstring( std::wstring( inArg ) );
    return StringUtil::startsWith( m_value.c_str(), stringArg.c_str() );
}

void STDStringWrapper::replace( const std::wstring& inWhat, const std::wstring& inFor )
{
    const std::string inWhatS = StringUtil::toSTDstring( inWhat );
    const std::string inForS = StringUtil::toSTDstring( inFor );
    replace( inWhatS, inForS );
}

void STDStringWrapper::replace( const std::string& inWhat, const std::string& inFor )
{
    if( inWhat.empty() )
    {
        return;
    }

    std::size_t pos = 0;

    while( true )
    {
        pos = m_value.find( inWhat, pos );

        if( pos == std::wstring::npos )
        {
            break;
        }

        m_value.replace( pos, inWhat.length(), inFor );
        pos += inFor.length();
    }
}

std::u8string STDStringWrapper::toU8String() const
{
    return std::u8string( reinterpret_cast<const char8_t*>( m_value.data() ),
                          reinterpret_cast<const char8_t*>( m_value.data() + m_value.size() ) );
}

STDStringWrapper::~STDStringWrapper()
{
}
}  // namespace CUL
#endif  // #if !CUL_USE_WCHAR