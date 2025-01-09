#pragma once

#include "CUL/CUL.hpp"

#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_functional.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( GUTILS )

class SimpleDelegate final
{
public:
    CULLib_API SimpleDelegate() noexcept;

    CULLib_API void addDelegate( std::function<void( void )> delegate );
    CULLib_API void execute();

    CULLib_API ~SimpleDelegate();

protected:
private:
    std::vector<std::function<void(void)>> m_delegates;

private:
    SimpleDelegate(const SimpleDelegate& arg);
    SimpleDelegate(SimpleDelegate&& arg);
    SimpleDelegate& operator=(const SimpleDelegate& arg) = delete;
    SimpleDelegate& operator=(SimpleDelegate&& arg) = delete;
};

NAMESPACE_END( GUTILS )
NAMESPACE_END( CUL )