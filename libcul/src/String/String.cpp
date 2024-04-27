#include "CUL/String.hpp"

#include "Filesystem/FSUtils.hpp"
#include "CUL/StringUtil.hpp"

#include "CUL/STL_IMPORTS/STD_algorithm.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"
#include "CUL/STL_IMPORTS/STD_sstream.hpp"
#include "CUL/STL_IMPORTS/STD_cmath.hpp"
#include "CUL/STL_IMPORTS/STD_exception.hpp"

using namespace CUL;

String::String() noexcept
{
    setupValue();
}

String::String( const String& arg ) noexcept :
    m_sso( arg.m_sso ),
    m_dyn( arg.m_dyn )
{
    setupValue();
}

String::String( String&& arg ) noexcept :
    m_sso( std::move( arg.m_sso ) ),
    m_dyn( std::move( arg.m_dyn ) )
{
    arg.m_sso.clear();
    arg.m_dyn.clear();

    setupValue();
}

String::String( const bool arg ) noexcept
{
    *this = arg;
}

String::String( const char* arg ) noexcept
{
    *this = arg;
}

String::String( const wchar_t* arg ) noexcept
{
    *this = arg;
}

String::String( unsigned char* arg ) noexcept
{
    *this = arg;
}

String::String( const std::string& arg ) noexcept
{
    *this = arg;
}

String::String( const std::wstring& arg ) noexcept
{
    const std::string result = StringUtil::wcharToChar(arg, 0);
    m_usingSSO = result.size() <= SSO_MaxSize;
    if( m_usingSSO )
    {
        m_sso = result.c_str();
    }
    else
    {
        m_dyn = result.c_str();
    }
    setupValue();
}

String::String( float arg ) noexcept
{
    *this = arg;
}

String::String( double arg ) noexcept
{
    *this = arg;
}

String::String( int arg ) noexcept
{
    *this = arg;
}

String::String( unsigned int arg ) noexcept
{
    *this = arg;
}

String::String( int64_t arg ) noexcept
{
    *this = arg;
}

String::String( uint64_t arg ) noexcept
{
    *this = arg;
}

String& String::operator=( const String& arg )
{
    if( this != &arg )
    {
        m_sso = arg.m_sso;
        m_dyn = arg.m_dyn;
        m_usingSSO = arg.m_usingSSO;
        setupValue();
    }
    return *this;
}

String& String::operator=( String&& arg ) noexcept
{
    if( this != &arg )
    {
        m_sso = std::move( arg.m_sso );
        arg.m_sso.clear();

        m_dyn = std::move( arg.m_dyn );
        arg.m_dyn.clear();

        m_usingSSO = arg.m_usingSSO;
        setupValue();
    }
    return *this;
}

String& String::operator=( const bool arg )
{
    *this = arg ? "true" : "false";
    return *this;
}

String& String::operator=( const char* arg )
{
    const std::int32_t stringLength = StringUtil::getLength( arg );
    m_usingSSO = stringLength < SSO_MaxSize;
    if( m_usingSSO )
    {
        m_sso = arg;
    }
    else
    {
        m_dyn = arg;
    }
    setupValue();
    return *this;
}

String& String::operator=( const wchar_t* arg )
{
    const std::string stringLength = StringUtil::wcharToChar( std::wstring( arg ), 0u );
    m_usingSSO = stringLength.size() < SSO_MaxSize;
    if( m_usingSSO )
    {
        m_sso = stringLength.c_str();
    }
    else
    {
        m_dyn = stringLength.c_str();
    }
    setupValue();
    return *this;
}

#ifdef _MSC_VER
// Yes, I know that is a Spectre mitigation.
// But for now, I let this as TODO, since i don't know
// How to fix this.
// TODO
#pragma warning( push )
#pragma warning( disable: 5045 )
#endif
String& String::operator=( unsigned char* arg )
{
    auto len = strlen( (const char*)arg );
    std::string tmp;
    tmp.resize( len );

    for( unsigned i = 0; i < len; ++i )
    {
        tmp[i] = static_cast<char>( arg[i] );
    }

    setupValue();
    return *this;
}
#ifdef _MSC_VER
#pragma warning( pop )
#endif

String& String::operator=( const std::string& arg )
{
    m_usingSSO = arg.size() < SSO_MaxSize;
    if( m_usingSSO )
    {
        m_sso = arg.c_str();
    }
    else
    {
        m_dyn = arg.c_str();
    }
    setupValue();
    return *this;
}

String& String::operator=( const std::wstring& arg )
{
    const std::string result = StringUtil::wcharToChar( arg, 0u );
    m_usingSSO = result.size() < SSO_MaxSize;
    if( m_usingSSO )
    {
        m_sso = result.c_str();
    }
    else
    {
        m_dyn = result.c_str();
    }
    setupValue();
    return *this;
}

String& String::operator=( float arg )
{
    const std::string converted = StringUtil::toChar<float>(arg);
    m_usingSSO = converted.size() < SSO_MaxSize;
    if( m_usingSSO )
    {
        m_sso = converted.c_str();
    }
    else
    {
        m_dyn = converted.c_str();
    }
    setupValue();
    return *this;
}

String& String::operator=( double arg )
{
    const std::string converted = StringUtil::toChar<double>( arg );
    m_usingSSO = converted.size() < SSO_MaxSize;
    if( m_usingSSO )
    {
        m_sso = converted.c_str();
    }
    else
    {
        m_dyn = converted.c_str();
    }
    setupValue();
    return *this;
}

String& String::operator=( int arg )
{
    const std::string converted = StringUtil::toChar<int>( arg );
    m_usingSSO = converted.size() < SSO_MaxSize;
    if( m_usingSSO )
    {
        m_sso = converted.c_str();
    }
    else
    {
        m_dyn = converted.c_str();
    }
    setupValue();
    return *this;
}

String& String::operator=( unsigned arg )
{
    const std::string converted = StringUtil::toChar<unsigned>( arg );
    m_usingSSO = converted.size() < SSO_MaxSize;
    if( m_usingSSO )
    {
        m_sso = converted.c_str();
    }
    else
    {
        m_dyn = converted.c_str();
    }
    setupValue();
    return *this;
}

String& String::operator=( int64_t arg )
{
    const std::string converted = StringUtil::toChar<int64_t>( arg );
    m_usingSSO = converted.size() < SSO_MaxSize;
    if( m_usingSSO )
    {
        m_sso = converted.c_str();
    }
    else
    {
        m_dyn = converted.c_str();
    }
    setupValue();
    return *this;
}

String& String::operator=( uint64_t arg )
{
    const std::string converted = StringUtil::toChar<uint64_t>( arg );
    m_usingSSO = converted.size() < SSO_MaxSize;
    if( m_usingSSO )
    {
        m_sso = converted.c_str();
    }
    else
    {
        m_dyn = converted.c_str();
    }
    setupValue();
    return *this;
}

String String::operator+( const String& arg ) const
{
    String result( *this );
    result += arg;

    return result;
}

String& String::operator+=( const String& arg )
{
    const std::int32_t resultSize = size() + arg.size();
    const bool wasUsingSSO = m_usingSSO;

    m_usingSSO = resultSize < SSO_MaxSize;
    if( m_usingSSO )
    {
        m_sso.Add( arg.getChar() );
    }
    else
    {
        if( wasUsingSSO )
        {
            m_dyn = m_sso.getChar();
            m_sso.clear();
        }

        m_dyn.Add( arg.getChar() );
    }
    setupValue();
    return *this;
}

bool String::operator==( const String& arg ) const
{
    if( this == &arg )
    {
        return true;
    }

    if( arg.m_dyn.empty() == false && m_dyn.empty() == false )
    {
        return arg.m_dyn == m_dyn;
    }
    else if( arg.m_dyn.empty() == true && m_dyn.empty() == true )
    {
        return arg.m_sso == m_sso;
    }

    return false;
}

bool String::operator!=( const String& arg ) const
{
    return !operator==( arg );
}

bool String::operator==( const std::string& arg ) const
{
    return this->operator==(arg.c_str());
}

bool String::operator!=( const std::string& arg ) const
{
    return !operator==( arg );
}

bool String::operator==( const char* arg ) const
{
    if( m_usingSSO )
    {
        return m_sso == arg;
    }

    return m_dyn == arg;
}

bool String::operator!=( const char* arg ) const
{
    return !this->operator==( arg );
}

bool String::operator!=( int arg ) const
{
    return !operator==( arg );
}

bool String::operator==( int arg ) const
{
    const std::string converted = StringUtil::toChar<int>(arg);
    return this->operator==( converted );
}

bool String::operator!=( unsigned int arg ) const
{
    return !operator==( arg );
}

bool String::operator==( unsigned int arg ) const
{
    const std::string converted = StringUtil::toChar<unsigned int>( arg );
    return this->operator==( converted );
}

bool String::operator!=( float arg ) const
{
    return !operator==( arg );
}

bool String::operator==( float arg ) const
{
    const std::string converted = StringUtil::toChar<float>( arg );
    return this->operator==( converted );
}

bool String::operator!=( double arg ) const
{
    return !operator==( arg );
}

bool String::operator==( double arg ) const
{
    const std::string converted = StringUtil::toChar<double>( arg );
    return this->operator==( converted );
}

bool String::operator<( const String& arg ) const
{
    const char* left = getChar();
    const char* right = arg.getChar();
    const int result = std::strcmp( left, right );
    const std::string leftStr = left;
    const std::string rightStr = right;
    const bool r1 = leftStr < rightStr;
    const bool resultBool = result < 0;
    return resultBool;
}

bool String::operator>( const String& arg ) const
{
    const char* left = getChar();
    const char* right = arg.getChar();
    const int result = std::strcmp( left, right );

    const std::string leftStr = left;
    const std::string rightStr = right;
    const bool r1 = leftStr > rightStr;
    const bool resultBool = result > 0;
    return resultBool;
}

bool String::operator()( const String& v1, const String& v2 ) const
{
    return v1 == v2;
}

std::int32_t strFind( const char* source, std::int32_t sourceLen, const char* phrase, std::int32_t phraseLen )
{
    if( sourceLen < phraseLen )
    {
        return -1;
    }

    if( sourceLen == 0 || phraseLen == 0 )
    {
        return -1;
    }

    for( std::int32_t i = 0; i < sourceLen; ++i )
    {
        if( source[i] == phrase[0] )
        {
            if( phraseLen == 1 )
            {
                return i;
            }

            if( phraseLen > 1 )
            {
                if( i + phraseLen > sourceLen )
                {
                    return -1;
                }

                for( std::int32_t j = 0; j < phraseLen; ++j )
                {
                    const std::int32_t sourceIdx = i + j;
                    if( source[sourceIdx] != phrase[j] )
                    {
                        break;
                    }
                }
                return i;
            }
            return -1;
        }
    }

    return -1;
}

std::int32_t String::find( const String& arg ) const
{
    const std::int32_t currentSize = size();
    const std::int32_t argSize = arg.size();

    if( argSize > currentSize )
    {
        return -1;
    }

    const char* argChar = arg.getChar();
    return strFind( getChar(), currentSize, argChar, argSize );
}

String String::substr( std::int32_t pos, std::int32_t len ) const
{
    String result;
    const std::int32_t currentLength = size();
    if( pos + len > currentLength )
    {
        return result;
    }

    const std::int32_t newLen = len == -1 ? currentLength - pos : len;
    const std::int32_t max = len == -1 ? currentLength : pos + len;
    result.resize( newLen );

    const IStringBuffer& buff = getCurrentBuffer();
    std::int32_t resultIdx = 0;
    for( std::int32_t i = pos; i < max; ++i )
    {
        result.getCurrentBuffer()[resultIdx] = buff[i];
        ++resultIdx;
    }
    return result;
}

void String::toLower()
{
    if( empty() )
    {
        return;
    }

    const std::int32_t currSize = size();
    char* data = getChar();
    for( std::int32_t i = 0; i < currSize; ++i )
    {
        data[i] = (char)tolower(data[i]);
    }
}

String String::toLowerR() const
{
    String result = *this;

    result.toLower();

    return result;
}

void String::toUpper()
{
    if( empty() )
    {
        return;
    }

    const std::int32_t currSize = size();
    char* data = getChar();
    for( std::int32_t i = 0; i < currSize; ++i )
    {
        data[i] = (char)toupper( data[i] );
    }
}

void String::resize( std::int32_t newSize )
{
    if( m_usingSSO )
    {
        if( newSize > SSO_MaxSize )
        {
            m_dyn = m_sso.getChar();
            m_dyn.resize(newSize);
        }
        else
        {
            m_sso.resize( newSize );
        }
    }
    else
    {
        m_dyn.resize( newSize );
    }
    setupValue();
}

bool String::contains( const String& /*inputString*/ ) const
{
    throw std::logic_error( "Not implemented yet." );
    //return m_value.find( inputString.m_value ) != UnderlyingType::npos;
    return false;
}

bool String::contains( const char* /*inputString*/ ) const
{
    throw std::logic_error( "Not implemented yet." );
    //#ifdef _MSC_VER
//    return m_value.find( FS::s2ws( inputString ) ) != UnderlyingType::npos;
//#else
//    return m_value.find( inputString ) != UnderlyingType::npos;
//#endif
    return false;
}

bool String::replaceAll( const String& inWhat, const String& inFor )
{
    while( replace( inWhat, inFor ) )
    {
    }
    return true;
}

bool String::replace( const String& inWhat, const String& inFor )
{
    std::int32_t idx = find( inWhat );

    if( idx == -1 )
    {
        return false;
    }

    const char* inForCstr = inFor.getChar();
    const std::int32_t whatCstrSize = inWhat.size();
    const std::int32_t currSize = size();
    const std::int32_t inForSize = inFor.size();

    const std::int32_t sizeDiff = inForSize - whatCstrSize;
    const std::int32_t newSize = currSize + sizeDiff;

    if( sizeDiff > 0 )
    {
        if( m_usingSSO )
        {
            if( currSize + sizeDiff > SSO_MaxSize )
            {
                m_dyn = m_sso.getChar();
                m_sso.clear();
            }
        }
    }

    char* charValue = getChar();
    if( sizeDiff > 0 )
    {
        std::int32_t replaceStart = idx + 1;
        for( std::int32_t i = newSize - 1; i >= replaceStart; --i )
        {
            charValue[i] = charValue[i-1];
        }

        const std::int32_t lastOne = idx + inForSize;
        std::int32_t j = 0;
        for( std::int32_t i = idx; i < lastOne; ++i, ++j )
        {
            charValue[i] = inForCstr[j];
        }
    }
    else if( sizeDiff == 0 )
    {
        std::int32_t replaceStart = idx;
        std::int32_t forIdx = 0;
        for( std::int32_t i = replaceStart; (i < newSize) && (forIdx < inForSize); ++i )
        {
            charValue[i] = inForCstr[forIdx];
            ++forIdx;
        }
    }
    else if( sizeDiff < 0 )
    {
        throw std::logic_error( "Not implemented yet." );
    }

    setupValue();
    return true;
}

void String::replace( const char /*inWhat*/, const char /*inFor*/ )
{
    throw std::logic_error( "Not implemented yet." );
    //if( m_value.empty() )
    //{
    //    return;
    //}

    //auto cInWhat = static_cast<UnderlyingChar>( inWhat );
    //auto cInFor = static_cast<UnderlyingChar>( inFor );

    //size_t inWhatPosition = m_value.find( cInWhat );
    //while( UnderlyingType::npos != inWhatPosition )
    //{
    //    m_value.replace( inWhatPosition, 1, &cInFor );
    //    inWhatPosition = m_value.find( cInWhat );
    //}
}

void String::replace( const wchar_t inWhat, const wchar_t inFor )
{
    throw std::logic_error( "Not implemented yet." );
    //    if( m_value.empty() )
//    {
//        return;
//    }
//
//#ifdef _MSC_VER
//    wchar_t cInWhat = inWhat;
//    wchar_t cInFor = inFor;
//#else
//    char cInWhat = inWhat;
//    char cInFor = inFor;
//#endif
//    size_t inWhatPosition = m_value.find( cInWhat );
//    while( UnderlyingType::npos != inWhatPosition )
//    {
//        m_value.replace( inWhatPosition, 1, &cInFor );
//        inWhatPosition = m_value.find( inWhat );
//    }
}

void String::removeAll( const char inWhat )
{
    throw std::logic_error( "Not implemented yet." );
    //UnderlyingChar inWhatChar = ( UnderlyingChar ) inWhat;
    //auto inWhatPosition = m_value.find( inWhatChar );
    //while( std::string::npos != inWhatPosition )
    //{
    //    m_value.erase(inWhatPosition);
    //    inWhatPosition = m_value.find( inWhatChar );
    //}
}


bool String::doesEndWith( const char* end ) const
{
    throw std::logic_error( "Not implemented yet." );
    const std::size_t endingLength = StringUtil::getLength( end );
    return false;
}

std::wstring String::wstring() const
{
    const char* value = getChar();
    return StringUtil::charToWchar(std::string(value), 0);
}

std::string String::getString() const
{
    const std::string result = getChar();
    return result;
}

const char* String::cStr() const
{
    return getChar();
}

char String::operator[]( std::size_t index ) const
{
    if( index >= size() )
    {
        throw std::logic_error( "Out of bounds." );
        return ' ';
    }

    return getChar()[index];
}

char* String::getChar()
{
    if( m_usingSSO )
    {
        return m_sso.getChar();
    }

    return m_dyn.getChar();
}

const char* String::getChar() const
{
    if( m_usingSSO )
    {
        return m_sso.getChar();
    }

    return m_dyn.getChar();
}

float String::toFloat() const
{
    return StringUtil::toFloat( getChar() );
}

double String::toDouble() const
{
    return StringUtil::toDouble( getChar() );
}

int String::toInt()
{
    return StringUtil::toInt32( getChar() );
}

int64_t String::toInt64() const
{
    return StringUtil::toInt64( getChar() );
}

uint64_t String::toUint64() const
{
    return StringUtil::toUint64( getChar() );
}

std::uint64_t String::toUInt() const
{
    return StringUtil::toUint32( getChar() );
}

bool String::toBool() const
{
    const char* value = getChar();
    return std::strcmp( value, "true" );
}

std::int32_t String::size() const
{
    if( m_usingSSO )
    {
        return m_sso.size();
    }

    return m_dyn.size();
}

void String::clear()
{
    if( m_usingSSO )
    {
        m_sso.clear();
    }
    else
    {
        m_dyn.clear();
    }
}

bool String::empty() const
{
    if( m_usingSSO )
    {
        return m_sso.empty();
    }
    return m_dyn.empty();
}

constexpr char hexmap[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };


std::string data2StringHex( unsigned char* data, size_t len )
{
    std::string s( len * 2u, ' ' );
    for( size_t i = 0; i < len; ++i )
    {
        s[2u * i] = hexmap[( data[i] & 0xF0 ) >> 4];
        s[2u * i + 1] = hexmap[data[i] & 0x0F];
    }
    return s;
}

uint16_t hexCharToInt(char valu)
{
    uint16_t result = valu - 48u;
    if( result >= 10u )
    {
        result = result - 39u;
    }
    return result;
}

uint16_t stringHex2Data( char val[4] )
{
    uint16_t result = 0u;

    for(int i = 0; i < 4; ++i)
    {
        const auto currentValue = val[3 - i];
        const auto intVal = hexCharToInt( currentValue );
        const auto powValue = std::pow( 16, i );
        result += powValue * intVal;
    }

    return result;
}

void String::setBinary( const char* value )
{
    throw std::logic_error( "Not implemented yet." );
}

const std::string String::getBinary() const
{
    throw std::logic_error( "Not implemented yet." );
    return false;
}

const std::vector<String> String::split( const String& delimiter ) const
{
    std::vector<String> result;

    throw std::logic_error( "Not implemented yet." );

    //size_t pos = 0u;
    //UnderlyingType token;
    //UnderlyingType vcopy = m_value; 
    //while( ( pos = vcopy.find( delimiter.m_value ) ) != UnderlyingType::npos )
    //{
    //    token = vcopy.substr( 0, pos );
    //    result.push_back( token );
    //    vcopy.erase( 0, pos + delimiter.length() );
    //}

    return result;
}


void String::setupValue()
{
    m_value = getCurrentBuffer().getChar();
}

IStringBuffer& String::getCurrentBuffer()
{
    if( m_usingSSO )
    {
        return m_sso;
    }

    return m_dyn;
}

const IStringBuffer& String::getCurrentBuffer() const
{
    if( m_usingSSO )
    {
        return m_sso;
    }

    return m_dyn;
}

String CULLib_API CUL::operator+( const char* arg1, const String& arg2 )
{
    String left( arg1 );
    String result = left + arg2;

    return result;
}

bool CULLib_API CUL::operator==( const char* arg1, const String& arg2 )
{
    return arg2 == arg1;
}

bool CULLib_API CUL::operator==( int arg1, const String& arg2 )
{
    return arg2 == arg1;
}

bool CULLib_API CUL::operator==( unsigned int arg1, const String& arg2 )
{
    return arg2 == arg1;
}

bool CULLib_API CUL::operator==( float arg1, const String& arg2 )
{
    return arg2 == arg1;
}

bool CULLib_API CUL::operator==( double arg1, const String& arg2 )
{
    return arg2 == arg1;
}


String::~String()
{
}