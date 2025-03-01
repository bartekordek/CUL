#pragma once

#include "CUL.hpp"
#include "CUL/String.hpp"

NAMESPACE_BEGIN( CUL )

class CULLib_API IName
{
public:
    IName();
    IName( const String& name );
    IName( const IName& val );
    IName( IName&& val ) noexcept;
    
    IName& operator=( const IName& rhv );
    IName& operator=( IName&& rhv ) noexcept;
    const String& getName() const;
    virtual void setName( const String& name );

    virtual ~IName();

protected:
    virtual void onNameChange( const String& newName );

private:
    String m_name;
};

NAMESPACE_END( CUL )