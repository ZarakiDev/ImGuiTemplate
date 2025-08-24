#pragma once

#include <chrono>
#include <functional>
#include <utility>

class ExecutionTimer
{
public:
    ExecutionTimer() : LastTime(GetCurrentTime()) {}

    float GetCurrentTime()
    {
        using namespace std::chrono;
        return duration_cast<duration<float>>(steady_clock::now().time_since_epoch()).count();
    }

    template <typename F, typename... Args>
    void UpdateWithInterval(float Interval, F&& Function, Args&&... args)
    {
        float CurrentTime = GetCurrentTime();
        if (CurrentTime - LastTime >= Interval)
        {
            std::invoke(std::forward<F>(Function), std::forward<Args>(args)...);
            LastTime = CurrentTime;
        }
    }

private:
    float LastTime;
};

