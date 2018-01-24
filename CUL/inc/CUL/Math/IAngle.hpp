#pragma once
#include <CUL/CUL.hpp>
namespace CUL
{
    class CULLib_API IAngle
    {
    public:
        IAngle( void );
        virtual ~IAngle( void );

        virtual const double getValue()const = 0;

    protected:
    private:
    };
}