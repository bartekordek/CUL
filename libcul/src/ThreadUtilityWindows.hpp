#pragma once

#include "CUL/IThreadUtility.hpp"

namespace CUL
{
    class ThreadUtilityWindows final :
        public IThreadUtility
    {
    public:
        ThreadUtilityWindows();
        ThreadUtilityWindows( const ThreadUtilityWindows& value ) = delete;
        ~ThreadUtilityWindows();

        ThreadUtilityWindows& operator=( const ThreadUtilityWindows& rhv ) = delete;

        void setCurrentThreadName( CnstStr& name ) override;

    protected:
    private:
    };
}