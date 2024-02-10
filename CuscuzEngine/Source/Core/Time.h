#pragma once
#include <SDL_timer.h>

class Time
{    
    float m_LastFrameTime;
    float m_DeltaTime;
    float m_TimeScale;

    bool m_LimitFrameRate;
    float m_TargetFrameRate;
    float m_MaxDeltaTime;

public:
    static Time& Instance()
    {
        static auto* s_Instance = new Time();
        return *s_Instance;
    }
    
    void Update()
    {
        if(m_LimitFrameRate)
        {
            while(!SDL_TICKS_PASSED(static_cast<float>(SDL_GetTicks()), m_LastFrameTime + m_TargetFrameRate * 0.001f))
                ;
        }
        
        const auto time = static_cast<float>(SDL_GetTicks()) * 0.001f;
        m_DeltaTime =  time - m_LastFrameTime;
        if(m_DeltaTime > m_MaxDeltaTime)
            m_DeltaTime = m_MaxDeltaTime;
        
        m_LastFrameTime = time;
    }
    
    float DeltaTime() { return m_DeltaTime; }
    float TimeScale() { return m_TimeScale; }
    void SetTimeScale(float NewTimeScale) { m_TimeScale = NewTimeScale; }
    void LimitTimeFrame(bool Limit) { m_LimitFrameRate = Limit; }

private:
    Time() : m_LastFrameTime(0), m_DeltaTime(0), m_TimeScale(1.f),
    m_LimitFrameRate(true), m_TargetFrameRate(60.f), m_MaxDeltaTime(0.05f)
    {}
    ~Time() = default;
    Time(Time const&){}
    Time operator=(Time const&) { return *this; }
};
