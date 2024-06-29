#pragma once

#include "CC_Event.h"

template <typename EventType> //TODO Review this
class CC_EventDispatcher
{
    using EventFunc = std::function<void(CC_Event&)>;
    std::unordered_map<EventType, std::vector<EventFunc>> m_Listeners;

public:
    void AddListener(EventType Type, const EventFunc& Func)
    {        
        m_Listeners[Type].emplace_back(Func);
    }

    void RemoveListener(const EventFunc& Func)
    {
        for (auto& listeners : m_Listeners)
        {
            auto it = std::remove_if(listeners.second.begin(), listeners.second.end(),
                [&Func](const EventFunc& listener) {
                    return listener.target_type() == Func.target_type();
                });

            if (it != listeners.second.end()) {
                listeners.second.erase(it, listeners.second.end());
                return;
            }
        }
    }

    void SendEvent(const CC_Event& Event)
    {
        if (m_Listeners.find(Event.GetEventType()) == m_Listeners.end())
            return;

        for (auto&& Listener : m_Listeners.at(Event.GetEventType()))
        {
            if (!Event.Handled())
                Listener(Event);
        }
    }
};

class CC_EventSingleDispatcher
{
    template<typename T>
    using EventFunction = std::function<bool(T&)>;
    CC_Event& m_Event;
    
public:
    CC_EventSingleDispatcher(CC_Event& event)
    : m_Event(event){}
    
    template<typename T>
    bool Dispatch(EventFunction<T> func)
    {
        if(m_Event.GetEventType() == T::GetStaticType())
        {
            m_Event.m_Handled = func(*(T*)&m_Event);
            return true;
        }
        
        return false;
    }
};

inline std::ostream& operator<<(std::ostream& os, const CC_Event& event)
{
    return os << event.ToString();
}