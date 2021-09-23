#pragma once

#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_optional.hpp"
#include "CUL/String.hpp"

NAMESPACE_BEGIN( CUL )

class CULLib_API IThreadUtil
{
public:
    IThreadUtil() = default;

    virtual void setCurrentThreadName( const String& name ) = 0;
    virtual std::optional<String> getCurrentThreadName() const = 0;
    virtual std::vector<String> getThreadNames() const = 0;

    virtual ~IThreadUtil() = default;
protected:
private:

    IThreadUtil& operator=( const IThreadUtil& rhv ) = delete;
    IThreadUtil& operator=( IThreadUtil&& rhv ) = delete;
    IThreadUtil( const IThreadUtil& arg ) = delete;
    IThreadUtil( IThreadUtil&& arg ) = delete;
};
NAMESPACE_END( CUL )