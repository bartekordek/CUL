#pragma once

#include "CUL/CUL.hpp"

#include "CUL/STL_IMPORTS/STD_functional.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( GUTILS )

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4251 )
#endif
class CULLib_API IOnChange
{
public:
    IOnChange();

    void setOnChange( const std::function<void( void )>& onChange );
    void onChange();

    virtual ~IOnChange();
protected:
    std::function<void( void )> m_onChange;

private:

    IOnChange( const IOnChange& arg ) = delete;
    IOnChange( IOnChange&& arg ) = delete;
    IOnChange& operator=( const IOnChange& arg ) = delete;
    IOnChange& operator=( IOnChange&& arg ) = delete;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( GUTILS )
NAMESPACE_END( CUL )