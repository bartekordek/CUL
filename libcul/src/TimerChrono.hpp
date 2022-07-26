#pragma once

#include "CUL/ITimer.hpp"
#include "CUL/ITime.hpp"

#include "CUL/STL_IMPORTS/STD_memory.hpp"
#include "STD_chrono.hpp"
#include "CUL/GenericUtils/DumbPtr.hpp"

NAMESPACE_BEGIN( CUL )

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4820 )
#endif

class TimerChrono final:
    public ITimer
{
public:
    TimerChrono();

    void start() override;
    void stop() override;
    void reset() override;
    const ITime& getElapsed() const override;

    ~TimerChrono();

protected:
private:


    std::chrono::high_resolution_clock clock;
    std::unique_ptr<ITime> time;
    std::chrono::high_resolution_clock::time_point startPoint;

private: // Deleted
    TimerChrono( const TimerChrono& tc ) = delete;
    TimerChrono& operator=( const TimerChrono& rhv ) = delete;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( CUL )
