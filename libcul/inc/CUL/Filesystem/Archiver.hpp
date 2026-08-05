#pragma once

#include "CUL/CUL.hpp"
#include "CUL/GenericUtils/NonCopyable.hpp"

namespace CUL
{
class Archiver
{
public:
    CULLib_API static Archiver& getInstance();

    CUL_NONCOPYABLE( Archiver );

protected:
private:
    Archiver();
    ~Archiver();
};
}  // namespace CUL