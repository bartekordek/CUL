#pragma once

#include "CUL/IThreadUtility.hpp"

namespace CUL
{
    class ThreadUtilityDummy final :
        public IThreadUtility
    {
    public:
        ThreadUtilityDummy();
        ThreadUtilityDummy( const ThreadUtilityDummy& value ) = delete;
        ~ThreadUtilityDummy();

        ThreadUtilityDummy& operator=( const ThreadUtilityDummy& rhv ) = delete;

        void setCurrentThreadName( CnstStr& name ) override;
    protected:
    private:
    };
}