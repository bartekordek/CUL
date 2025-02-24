#include "CUL/GenericUtils/ConsoleUtilities.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/Log/ILogger.hpp"
#include "ArgumentsPairConcrete.hpp"

using namespace CUL;
using namespace GUTILS;

ConsoleUtilities::ConsoleUtilities() : m_args( new ArgumentsPairConcrete() )
{
}

#ifdef _MSC_VER
#pragma warning( push, 0 )
#pragma warning( disable : 5045 )
#endif
void ConsoleUtilities::printInputParameters()
{
    LOG::ILogger::getInstance().log( "ConsoleUtilities::printInputParameters()" );
    const auto argc = *m_args->getArgCount();
    const auto argv = m_args->getArgsVal();
    for( int i = 0; i < argc; ++i )
    {
        LOG::ILogger::getInstance().logVariable( LOG::Severity::Info, "Arg[%d] = %s", i, argv[i] );
    }
}
#ifdef _MSC_VER
#pragma warning( pop )
#endif
IArgumentsList& ConsoleUtilities::getArgs()
{
    return *m_args;
}

CULLib_API const String& ConsoleUtilities::getFlagValue( const String& flagName ) const
{
    return m_args->getFlagValue( flagName );
}

void ConsoleUtilities::setArgs( const int argc, char** argv )
{
    m_args->setArgs( argc, argv );
}

void ConsoleUtilities::setArgs( const char* args )
{
    String argsStr{ args };
    const std::vector<String> strVec = argsStr.split( " " );
    const std::size_t strVecSize = strVec.size();

    for( std::size_t i = 0u; i < strVecSize; ++i )
    {
        String name;
        String value;
        const String& current = strVec[i];
        if( current[0] == '-' )
        {
            name = current;
        }
        else
        {
        }

        if( i + 1 < strVecSize )
        {
            const String nextValue = strVec[i + 1];
            if( nextValue[0] == '-' )
            {
                value = name;
            }
            else
            {
                value = nextValue;
                ++i;
            }
        }
        m_args->pushArg( name, value );
    }
}

ConsoleUtilities::~ConsoleUtilities()
{
}