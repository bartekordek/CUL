#pragma once
#include "CUL/ITimer.hpp"
#include "CUL/ITime.hpp"
#include <chrono>
#include <memory>
namespace CUL
{
    class TimerChrono: public ITimer
    {
    public:
        explicit TimerChrono( const bool run = false );
        virtual ~TimerChrono();

        void start() override;
        void stop() override;
        void reset() override;
        const ITime& getElapsed()const override;

    protected:
    private:
        std::chrono::high_resolution_clock clock;
        std::chrono::high_resolution_clock::time_point startPoint;
        std::unique_ptr<ITime> time;
    };
}