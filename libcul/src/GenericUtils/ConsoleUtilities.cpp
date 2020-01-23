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

ConsoleUtilities::~ConsoleUtilities()
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
        CUL::String logInfo = "ARG[" + CUL::String( i ) + "] = " + argv[i];
        CUL::LOG::LOG_CONTAINER::getLogger()->log( logInfo );
    }
}
#ifdef _MSC_VER
#pragma warning( pop )
#endif
IArgumentsPair& ConsoleUtilities::getDefaultArgs()
{
    return *m_args;
}

void ConsoleUtilities::setArgs( const int argc, char** argv )
{
    m_args->setArgs( argc, argv );
}

ConsoleUtilities& ConsoleUtilities::getInstance()
{
    static ConsoleUtilities instance;
    static ConsoleUtilities* oldAddr = nullptr;
    static ConsoleUtilities* addr = &instance;
    if( oldAddr )
    {
        Assert::simple( oldAddr == addr, "DLL PROBLEM! THERE ARE TWO INSTANCES OF SINGLETON!" );
    }
    oldAddr = addr;
    return instance;
}