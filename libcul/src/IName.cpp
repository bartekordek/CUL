#include "CUL/IName.hpp"

using namespace CUL;

CUL::IName::IName()
{
}

CUL::IName::IName( const String& name ):
    m_name( name )
{
}

CUL::IName::IName( const IName& val ) : m_name( val.m_name )
{
}

CUL::IName::IName( IName&& val ) noexcept : m_name( val.m_name )
{
}

CUL::IName::~IName()
{
}

IName& CUL::IName::operator=( const IName& rhv )
{
    if( &rhv != this )
    {
        m_name = rhv.m_name;
    }
    return *this;
}

IName& CUL::IName::operator=( IName&& rhv ) noexcept
{
    if( &rhv != this )
    {
        m_name = rhv.m_name;
    }
    return *this;
}

const String& CUL::IName::getName() const
{
    return m_name;
}

void CUL::IName::setName( const String& name )
{
    m_name = name;
    if( AfterNameChangeCallback )
    {
        AfterNameChangeCallback( name );
    }
}