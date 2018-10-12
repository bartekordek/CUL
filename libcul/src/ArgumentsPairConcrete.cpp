#include "ArgumentsPairConcrete.hpp"
#include <cstring>

using namespace CUL;

ArgumentsPairConcrete::ArgumentsPairConcrete()
{

}

ArgumentsPairConcrete::~ArgumentsPairConcrete()
{

}

void ArgumentsPairConcrete::setArgs( const int argc, char** argv )
{
    clearArgs();
    for( int i = 0; i < argc; ++i )
    {
        this->m_argumentsPtrs.push_back( argv[i] );
    }
}

int* ArgumentsPairConcrete::getArgCount()
{
    return &this->m_argc;
}

char** CUL::ArgumentsPairConcrete::getArgsVal()
{
    if( 0 == this->m_argumentsPtrs.size() )
    {
        return nullptr;
    }
    return &this->m_argumentsPtrs[0];
}

void ArgumentsPairConcrete::createDummyArgs()
{
    clearArgs();
    this->m_argumentsAreDummy = true;
    auto line1 = new char[ 20 ];
#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4996 )
#endif
    strcpy(line1, "Dummy program name.");
    m_argumentsPtrs.push_back( line1 );
    auto line2 = new char[ 23 ];
    strcpy(line2, "First dummy parameter.");
#ifdef _MSC_VER
#pragma warning( pop )
#endif
    m_argumentsPtrs.push_back( line2 );
}

void ArgumentsPairConcrete::clearArgs()
{
    if( this->m_argumentsAreDummy )
    {
        for( char* arg: this->m_argumentsPtrs )
        {
            delete[] arg;
        }
    }
    this->m_argumentsPtrs.clear();
    this->m_argumentsAreDummy = false;
}
