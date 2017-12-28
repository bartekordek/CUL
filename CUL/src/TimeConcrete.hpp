#pragma once
#include "CUL/ITime.hpp"
namespace CUL
{
    class TimeConcrete: public ITime
    {
    public:
        TimeConcrete();
        virtual ~TimeConcrete();

        void setTimeMs( const double time ) override;
        const double getMs()const override;
        const double getS()const override;
        const double getM()const override;
        const double getH()const override;
        const double getUs()const override;

    protected:
    private:
        double m_us = 0;
    };
}