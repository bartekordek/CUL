#pragma once

#include "CUL/ITime.hpp"

NAMESPACE_BEGIN( CUL )

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4820 )
#endif
class TimeConcrete: public ITime
{
public:
    TimeConcrete();
    TimeConcrete( const TimeConcrete& tc );
    virtual ~TimeConcrete();

    TimeConcrete& operator=( const TimeConcrete& rhv );

    void setTimeMs( const double ms ) override;
    void setTimeUs( const double us ) override;
    double getMs() const override;
    double getS() const override;
    double getM() const override;
    double getH() const override;
    double getUs() const override;

protected:
private:
    double m_us = 0;
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( CUL )