#pragma once

#include "CUL/CUL.hpp"
#include "CUL/STD_memory.hpp"

namespace CUL
{
    class ThreadWrapperImpl;
    class CULLib_API ThreadWrapper
    {
    public:
        ThreadWrapper();
        virtual ~ThreadWrapper();

        void run();
        void waitForCOmpletion();

    protected:
    private:
        std::unique_ptr<ThreadWrapperImpl> m_impl;

    };
}