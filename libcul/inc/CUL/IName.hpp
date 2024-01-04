#pragma once

#include "CUL.hpp"
#include "CUL/String.hpp"

#include "CUL/STL_IMPORTS/STD_functional.hpp"

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
    void setName( const String& name );

    std::function<void( const String& newName )> AfterNameChangeCallback;

    virtual ~IName();

protected:
private:
    String m_name;
    
};

NAMESPACE_END( CUL )