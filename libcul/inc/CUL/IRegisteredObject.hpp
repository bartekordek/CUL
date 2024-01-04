#pragma once

#include "CUL/CUL.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"

NAMESPACE_BEGIN(CUL)

class CULLib_API IRegisterdObject
{
public:
    IRegisterdObject();
    IRegisterdObject( const IRegisterdObject& ) = delete;
    IRegisterdObject( IRegisterdObject&& ) = delete;
    IRegisterdObject& operator=( const IRegisterdObject& ) = delete;
    IRegisterdObject& operator=( IRegisterdObject&& ) = delete;

    std::uint64_t getId() const;

    virtual ~IRegisterdObject();

protected:
private:
    std::uint64_t m_id = 0u;
};
NAMESPACE_END(CUL)