#pragma once
#include <CUL/CUL.hpp>
namespace CUL
{
    class CULLib_API ITime
    {
    public:
        ITime() = default;
        virtual ~ITime() = default;

        virtual void setTimeMs( const double time ) = 0;
        virtual const double getMs()const = 0;
        virtual const double getS()const = 0;
        virtual const double getM()const = 0;
        virtual const double getH()const = 0;
        virtual const double getUs()const = 0;
    };
}