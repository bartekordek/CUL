#pragma once
#include "CUL/ITimer.hpp"
#include "CUL/ITime.hpp"

#include "CUL/STD_memory.hpp"
#include "Chrono.hpp"

namespace CUL
{
#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4820 )
#endif
    class TimerChrono: public ITimer
    {
    public:
        explicit TimerChrono( const bool run = false );
        TimerChrono( const TimerChrono& tc );
        virtual ~TimerChrono();

        TimerChrono& operator=( const TimerChrono& rhv );

        void start() override;
        void stop() override;
        void reset() override;
        const ITime& getElapsed()const override;

    protected:
    private:
        std::chrono::high_resolution_clock clock;
        std::unique_ptr<ITime> time;
        std::chrono::high_resolution_clock::time_point startPoint;
        
    };
#ifdef _MSC_VER
#pragma warning( pop )
#endif
}