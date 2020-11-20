#pragma once

#include "CUL.hpp"
#include "CUL/String.hpp"

NAMESPACE_BEGIN( CUL )

class IName
{
public:
    CULLib_API IName();
    CULLib_API IName( const String& name );
    CULLib_API IName( const IName& val );
    CULLib_API virtual ~IName();

    CULLib_API IName& operator=( const IName& rhv );

    CULLib_API const String& getName() const;
    CULLib_API void setName( const String& name );

protected:
private:
    String m_name;
};

NAMESPACE_END( CUL )