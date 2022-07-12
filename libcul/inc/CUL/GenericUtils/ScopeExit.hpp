#pragma once

#include "CUL/CUL.hpp"

#include "CUL/STL_IMPORTS/STD_functional.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( GUTILS )

class CULLib_API ScopeExit final
{
public:
    ScopeExit( std::function<void( void )> inOnExit ) : m_onExit( inOnExit )
    {
    }

    ~ScopeExit()
    {
        m_onExit();
    }

protected:
private:
    std::function<void( void )> m_onExit;
};

NAMESPACE_END( GUTILS )
NAMESPACE_END( CUL )