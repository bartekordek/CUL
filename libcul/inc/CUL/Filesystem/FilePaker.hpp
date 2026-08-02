#pragma once

#include "CUL/CUL.hpp"
#include "CUL/GenericUtils/NonCopyable.hpp"

namespace CUL
{
class FilePaker
{
public:
    CULLib_API static FilePaker& getInstance();

    CUL_NONCOPYABLE( FilePaker );

protected:
private:
    FilePaker();
    ~FilePaker();
};
}  // namespace CUL