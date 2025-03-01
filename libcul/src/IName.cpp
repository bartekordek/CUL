#include "CUL/IName.hpp"

using namespace CUL;

IName::IName()
{
}

IName::IName( const String& name ):
    m_name( name )
{
}

IName::IName( const IName& val ):
    m_name( val.m_name )
{
}

IName::IName( IName&& val ) noexcept :
    m_name( val.m_name )
{
}

IName& IName::operator=( IName&& rhv ) noexcept
{
    if( &rhv != this )
    {
        m_name = rhv.m_name;
    }
    return *this;
}

const String& IName::getName() const
{
    return m_name;
}

IName& IName::operator=( const IName& rhv )
{
    if( &rhv != this )
    {
        m_name = rhv.m_name;
    }
    return *this;
}

void IName::setName( const String& name )
{
    m_name = name;
    onNameChange( m_name );
}

void IName::onNameChange( const String& )
{
}

IName::~IName()
{
}




