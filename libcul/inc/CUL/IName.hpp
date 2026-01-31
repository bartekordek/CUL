#pragma once

#include "CUL.hpp"
#include "CUL/String/StringWrapper.hpp"

NAMESPACE_BEGIN( CUL )

class CULLib_API IName
{
public:
    IName();
    IName( const StringWr& name );
    IName( const IName& val );
    IName( IName&& val ) noexcept;
    
    IName& operator=( const IName& rhv );
    IName& operator=( IName&& rhv ) noexcept;
    const StringWr& getName() const;
    virtual void setName( const StringWr& name );

    virtual ~IName();

protected:
    virtual void onNameChange( const StringWr& newName );

private:
    StringWr m_name;
};

NAMESPACE_END( CUL )