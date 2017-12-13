#pragma once
#include "CUL/ITime.hpp"
namespace CUL
{
    class TimeConcrete: public ITime
    {
    public:
        TimeConcrete( void );
        virtual ~TimeConcrete();

        void setTimeMs( const unsigned int time ) override;
        const unsigned int getMs()const override;
        const unsigned int getS()const override;
        const unsigned int getM()const override;
        const unsigned int getH()const override;

    protected:
    private:
        unsigned int ms = 0;
    };
}