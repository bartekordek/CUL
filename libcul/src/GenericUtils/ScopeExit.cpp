#include "CUL/GenericUtils/ScopeExit.hpp"

using namespace CUL;
using namespace GUTILS;

ScopeExit::ScopeExit( std::function<void( void )> inOnExit ) : m_onExit( inOnExit )
{
}

ScopeExit::~ScopeExit()
{
    m_onExit();
}