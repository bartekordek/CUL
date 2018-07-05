#pragma once

#include "CUL.hpp"
#include "CUL/STD_memory.hpp"
#include "CUL/STD_string.hpp"

namespace CUL
{
    class CULLib_API IThreadUtility
    {
    public:
        IThreadUtility() = default;
        IThreadUtility( const IThreadUtility& val ) = delete;
        virtual ~IThreadUtility() = default;

        IThreadUtility& operator=( const IThreadUtility& val ) = delete;

        static std::shared_ptr<IThreadUtility> getConcrete();

        virtual void setCurrentThreadName( CnstStr& name ) = 0;


    protected:
    private:
    };
}