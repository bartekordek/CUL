#include "CUL/IName.hpp"

using namespace CUL;

CUL::IName::IName()
{
}

CUL::IName::IName( CsStr& name ):
    m_name( name )
{
}

CUL::IName::IName( const IName & val ):
    m_name( val.m_name )
{
}

CUL::IName::~IName()
{
}

IName & CUL::IName::operator=( const IName& rhv )
{
    if( &rhv != this )
    {
        m_name = rhv.m_name;
    }
    return *this;
}

CsStr& CUL::IName::getName() const
{
    return m_name;
}

void CUL::IName::setName( CsStr& name )
{
    m_name = name;
}