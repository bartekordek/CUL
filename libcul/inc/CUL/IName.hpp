#pragma once

#include "CUL.hpp"
#include "CUL/STD_string.hpp"

namespace CUL
{
    class IName
    {
    public:
        CULLib_API IName();
        CULLib_API IName( CnstStr& name );
        CULLib_API IName( const IName& val );
        CULLib_API virtual ~IName();

        CULLib_API IName& operator=( const IName& rhv );

        CULLib_API CnstStr& getName()const;
        CULLib_API void setName( CnstStr& name );

    protected:
    private:
        std::string m_name;

    };
}