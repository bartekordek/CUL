#pragma once

#include "CUL.hpp"
#include "CUL/String.hpp"

namespace CUL
{
    class IName
    {
    public:
        CULLib_API IName();
        CULLib_API IName( CsStr& name );
        CULLib_API IName( const IName& val );
        CULLib_API virtual ~IName();

        CULLib_API IName& operator=( const IName& rhv );

        CULLib_API CsStr& getName()const;
        CULLib_API void setName( CsStr& name );

    protected:
    private:
        String m_name;

    };
}