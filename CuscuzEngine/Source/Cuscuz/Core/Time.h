#pragma once
#include <SDL_timer.h>

namespace Cuscuz
{
    class TimeStep
    {
        float m_Time;

    public:
        TimeStep(float time = 0.0f)
            : m_Time(time) {}

        operator float() const { return m_Time; }

        float GetSeconds() const { return m_Time; }
        float GetMilliseconds() const { return m_Time * 1000.0f; }
    
    };

    class Time
    {    
        TimeStep m_DeltaTime;
        Uint64 m_LastFrameTime;

    public:
        static Time& Get()
        {
            static auto* s_Instance = new Time();
            return *s_Instance;
        }
    
        void Update()
        {
            const Uint64 currentFrameTime = SDL_GetTicks64(); 
            m_DeltaTime  = (currentFrameTime - m_LastFrameTime) * 0.001f;
            m_LastFrameTime = currentFrameTime;
        }
    
        TimeStep DeltaTime() const { return m_DeltaTime; }
        int GetFPS() const
        {
            if (m_DeltaTime > 0.0f)
                return static_cast<int>(1.0f / m_DeltaTime);

            return 0;
        }

    private:
        Time() : m_DeltaTime(0), m_LastFrameTime(0) {}
    };
}