#include "CUL/ConsoleUtilities.hpp"
#include "CUL/SimpleAssert.hpp"
#include "ArgumentsPairConcrete.hpp"
#include "CUL/STD_iostream.hpp"

using namespace CUL;

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

    auto argc = *m_args->getArgCount();
    auto argv = m_args->getArgsVal();
    for( int i = 0; i < argc; ++i )
    {
        std::cout << "ARG[" << i << "] = " << argv[i] << "\n";
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
    this->m_args->setArgs( argc, argv );
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