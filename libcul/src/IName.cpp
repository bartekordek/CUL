#include "CUL/IName.hpp"

using namespace CUL;

CUL::IName::IName()
{
}

CUL::IName::IName( CnstStr& name ):
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
        this->m_name = rhv.m_name;
    }
    return *this;
}

CnstStr & CUL::IName::getName() const
{
    return this->m_name;
}

void CUL::IName::setName( CnstStr& name )
{
    this->m_name = name;
}