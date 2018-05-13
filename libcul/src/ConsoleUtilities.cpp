#include "CUL/ConsoleUtilities.hpp"

#include <iostream>

using namespace CUL;

    ArgumentsPair ConsoleUtilities::s_args = { 0, nullptr };

void ConsoleUtilities::printInputParameters( const ArgumentsPair& args )
{
    for( int i = 0; i < args.argc; ++i )
    {
        std::cout << "ARG[" << i << "] = " << args.argv[i] << "\n";
    }
}

ArgumentsPair& ConsoleUtilities::getDefaultArgs()
{
    if( nullptr == s_args.argv )
    {
        s_args.argc = 2;
        s_args.argv = new char*[ 2 ];

        s_args.argv[ 0 ] = new char[ 6 ];
        s_args.argv[ 0 ] = "12345\0";

        s_args.argv[ 1 ] = new char[ 5 ];
        s_args.argv[ 1 ] = "Test\0";
    }
    return s_args;
}