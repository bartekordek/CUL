#pragma once

#include "CUL/ITime.hpp"

NAMESPACE_BEGIN(CUL)

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4820 )
#endif
class TimeConcrete: public ITime
{
public:
    TimeConcrete( void );
    TimeConcrete( const TimeConcrete& tc );
    virtual ~TimeConcrete();

    TimeConcrete& operator=( const TimeConcrete& rhv );

    void setTimeMs( const double ms ) override;
    void setTimeUs( const double us ) override;
    const double getMs()const override;
    const double getS()const override;
    const double getM()const override;
    const double getH()const override;
    const double getUs()const override;

protected:
private:
    double m_us = 0;
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END(CUL)