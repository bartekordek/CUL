#pragma once

#include "CUL.hpp"
#include "CUL/String.hpp"

#include "CUL/STL_IMPORTS/STD_functional.hpp"

NAMESPACE_BEGIN( CUL )

class IName
{
public:
    CULLib_API IName();
    CULLib_API IName( const String& name );
    CULLib_API IName( const IName& val );
    CULLib_API IName( IName&& val ) noexcept;
    CULLib_API virtual ~IName();

    CULLib_API IName& operator=( const IName& rhv );
    CULLib_API IName& operator=( IName&& rhv ) noexcept ;

    CULLib_API const String& getName() const;
    CULLib_API void setName( const String& name );

    std::function<void( const String& newName )> AfterNameChangeCallback;

protected:
private:
    String m_name;
    
};

NAMESPACE_END( CUL )