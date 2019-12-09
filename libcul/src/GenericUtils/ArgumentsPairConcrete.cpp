#include "ArgumentsPairConcrete.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"

using namespace CUL;
using namespace GUTILS;

ArgumentsPairConcrete::ArgumentsPairConcrete()
{

}

ArgumentsPairConcrete::~ArgumentsPairConcrete()
{

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

    for( int i = 0; i < argc; ++i )
    {
        m_argumentsPtrs.push_back( argv[i] );
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
    m_valBegining = const_cast<char*>( m_argumentsPtrs.begin()->cStr() );
    m_valBeginingTable = &m_valBegining;
    return m_valBeginingTable;
}

void ArgumentsPairConcrete::createDummyArgs()
{
    clearArgs();
    m_argumentsAreDummy = true;
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
    m_argumentsPtrs.clear();
    m_argumentsAreDummy = false;
}