#pragma once

#include "CUL.hpp"
#include "CUL/MyString.hpp"

namespace CUL
{
    class IName
    {
    public:
        CULLib_API IName();
        CULLib_API IName( CnstMyStr& name );
        CULLib_API IName( const IName& val );
        CULLib_API virtual ~IName();

        CULLib_API IName& operator=( const IName& rhv );

        CULLib_API CnstMyStr& getName()const;
        CULLib_API void setName( CnstMyStr& name );

    protected:
    private:
        MyString m_name;

    };
}