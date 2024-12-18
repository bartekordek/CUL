#pragma once

#include "CUL/String.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( FS )

class CULLib_API PathDialog final
{
public:
    struct Filter
    {
        CUL::String Name;
        CUL::String Spec;
    };


    static PathDialog& getInstance();

    CUL::String pickFolder();
    CUL::String saveDialog( const Filter& inFilter );

    PathDialog( const PathDialog& ) = delete;
    PathDialog( PathDialog&& ) = delete;
    PathDialog& operator=( const PathDialog& ) = delete;
    PathDialog& operator=( PathDialog&& ) = delete;

protected:
private:
    PathDialog();
    ~PathDialog();
};
NAMESPACE_END( FS )
NAMESPACE_END( CUL )