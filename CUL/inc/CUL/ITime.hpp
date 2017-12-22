#pragma once
#include <CUL/CUL.hpp>
namespace CUL
{
    class CULLib_API ITime
    {
    public:
        ITime() = default;
        virtual ~ITime() = default;

        virtual void setTimeMs( const unsigned int time ) = 0;
        virtual const unsigned int getMs()const = 0;
        virtual const unsigned int getS()const = 0;
        virtual const unsigned int getM()const = 0;
        virtual const unsigned int getH()const = 0;
    };
}