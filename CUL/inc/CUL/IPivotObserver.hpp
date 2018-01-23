#pragma once
#include "CUL/CUL.hpp"
namespace CUL
{
    class CULLib_API IPivotObserver
    {
    public:
        IPivotObserver() = default;
        virtual ~IPivotObserver() = default;

        virtual void pivotHasBeenChanged() = 0;

    protected:
    private:
    };
}