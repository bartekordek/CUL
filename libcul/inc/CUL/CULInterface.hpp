#pragma once

#include "CUL/CUL.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"

NAMESPACE_BEGIN( CUL )

template <typename Type>
using UniquePtr = std::unique_ptr<Type>;

NAMESPACE_BEGIN( LOG )
class ILogger;
NAMESPACE_END( LOG )

class CULLib_API CULInterface
{
public:

    static UniquePtr<CULInterface> createInstance();
    LOG::ILogger* getLogger();

    ~CULInterface();
protected:
private:
    explicit CULInterface();
    explicit CULInterface( const CULInterface& arg ) = delete;
    explicit CULInterface( CULInterface&& arg ) = delete;
    CULInterface& operator=( const CULInterface& arg ) = delete;
    CULInterface& operator=( CULInterface&& arg ) = delete;

    LOG::ILogger* m_logger = nullptr;

};

NAMESPACE_END( CUL )