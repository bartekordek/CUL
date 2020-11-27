#include "CUL/GenericUtils/IOnChange.hpp"

using namespace CUL;
using namespace GUTILS;

IOnChange::IOnChange()
{
}

void IOnChange::setOnChange( const std::function<void( void )>& onChange )
{
    m_onChange = onChange;
}

void IOnChange::onChange()
{
    if( m_onChange )
    {
        m_onChange();
    }
}

IOnChange::~IOnChange()
{
}