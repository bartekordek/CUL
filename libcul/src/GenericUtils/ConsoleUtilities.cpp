#include "CUL/GenericUtils/ConsoleUtilities.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "ArgumentsPairConcrete.hpp"
#include "CUL/Log/ILogContainer.hpp"

using namespace CUL;
using namespace GUTILS;

ConsoleUtilities::ConsoleUtilities():
    m_args( new ArgumentsPairConcrete() )
{
}

#ifdef _MSC_VER
#pragma warning( push, 0 )
#pragma warning( disable: 5045 )
#endif
void ConsoleUtilities::printInputParameters()
{
    CUL::LOG::LOG_CONTAINER::getLogger()->log( "ConsoleUtilities::printInputParameters()" );
    const auto argc = *m_args->getArgCount();
    const auto argv = m_args->getArgsVal();
    for( int i = 0; i < argc; ++i )
    {
        CUL::LOG::LOG_CONTAINER::getLogger()->logVariable( LOG::Severity::INFO, "Arg[%d] = %s", i, argv[i] );
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

ConsoleUtilities::~ConsoleUtilities()
{
}