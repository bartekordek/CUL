#include "ArgumentsPairConcrete.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"
#include "CUL/STL_IMPORTS/STD_algorithm.hpp"

using namespace CUL;
using namespace GUTILS;

ArgumentsPairConcrete::ArgumentsPairConcrete()
{
}

void ArgumentsPairConcrete::pushArg( const String& name, const String& value )
{
    NameValue nv;
    nv.name = name;
    nv.value = value;

    m_values.push_back( nv );
}

#ifdef _MSC_VER
// Yes, I know that is a Spectre mitigation.
// But for now, I let this as TODO, since i don't know
// How to fix this.
// TODO
#pragma warning( push )
#pragma warning( disable: 5045 )
#endif

void ArgumentsPairConcrete::setArgs( const int argc, char** argv )
{
    clearArgs();

    bool skip = false;
    for( int i = 0; i < argc; ++i )
    {
        const String argument( argv[i] );
        m_argumentsPtrs.push_back( argument );
        if( false == skip )
        {
            NameValue nameValue;
            nameValue.name = argument;
            if( argument.string()[0] == '-' )
            {
                skip = true;
                if( ( i + 1  ) < argc )
                {
                    const String value(argv[i+1]);
                    nameValue.value = value;
                }
            }
            m_values.push_back( nameValue );
        }
        else
        {
            skip = false;
        }
    }
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif

int* ArgumentsPairConcrete::getArgCount()
{
    return &m_argc;
}

char** CUL::GUTILS::ArgumentsPairConcrete::getArgsVal()
{
    if( 0 == m_argumentsPtrs.size() )
    {
        return nullptr;
    }
    m_valBegining = const_cast<char*>( m_argumentsPtrs.begin()->getUtfChar() );
    m_valBeginingTable = &m_valBegining;
    return m_valBeginingTable;
}

void ArgumentsPairConcrete::createDummyArgs()
{
    clearArgs();
    m_argumentsAreDummy = true;
    // TODO: some strange sheet is going on here.
    auto line1 = new char[20];
#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4996 )
#endif
    strcpy( line1, "Dummy program name." );
    m_argumentsPtrs.emplace_back( line1 );
    auto line2 = new char[23];
    strcpy( line2, "First dummy parameter." );
#ifdef _MSC_VER
#pragma warning( pop )
#endif
    m_argumentsPtrs.emplace_back( line2 );
}

void ArgumentsPairConcrete::clearArgs()
{
    m_argumentsPtrs.clear();
    m_argumentsAreDummy = false;
}

const String& ArgumentsPairConcrete::getFlagValue(
    const String& flagName ) const
{
    auto id = std::find_if( m_values.begin(), m_values.end(),
        [flagName]( const NameValue& val )
    {
        if( val.name.equals( flagName.getString() ) )
        {
            return true;
        }
        return false;
    } );

    if( id == m_values.end() )
    {
        static String nullValue;
        return nullValue;
    }
    else
    {
        return id->value;
    }
}

ArgumentsPairConcrete::~ArgumentsPairConcrete()
{
}