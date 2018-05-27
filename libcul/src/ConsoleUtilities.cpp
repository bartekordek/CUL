#include "CUL/ConsoleUtilities.hpp"
#include "CUL/SimpleAssert.hpp"
#include "ArgumentsPairConcrete.hpp"

#include <iostream>

using namespace CUL;

ConsoleUtilities::ConsoleUtilities():
    m_args( new ArgumentsPairConcrete() )
{

}

ConsoleUtilities::~ConsoleUtilities()
{

}

void ConsoleUtilities::printInputParameters()
{
    for( int i = 0; i < *m_args->getArgCount(); ++i )
    {
        std::cout << "ARG[" << i << "] = " << m_args->getArgsVal()[i] << "\n";
    }
}

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