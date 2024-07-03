#pragma once

#include "CC_Event.h"

template <typename EventType> //TODO Review this
class CC_EventDispatcher
{
    using EventFunc = std::function<void(CC_Event&)>;
    std::unordered_map<EventType, std::vector<EventFunc>> m_Listeners;

public:
    void AddListener(EventType type, const EventFunc& func)
    {        
        m_Listeners[type].emplace_back(func);
    }

    void RemoveListener(const EventFunc& func)
    {
        for (auto& listeners : m_Listeners)
        {
            auto it = std::remove_if(listeners.second.begin(), listeners.second.end(),
                [&func](const EventFunc& listener) {
                    return listener.target_type() == func.target_type();
                });

            if (it != listeners.second.end()) {
                listeners.second.erase(it, listeners.second.end());
                return;
            }
        }
    }

    void SendEvent(const CC_Event& event)
    {
        if (m_Listeners.find(event.GetEventType()) == m_Listeners.end())
            return;

        for (auto&& Listener : m_Listeners.at(event.GetEventType()))
        {
            if (!event.Handled())
                Listener(event);
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