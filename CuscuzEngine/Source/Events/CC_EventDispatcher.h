#pragma once

#include "CC_Event.h"

template <typename EventType>
class CC_EventDispatcher
{
    using EventFunc = std::function<void(const CC_Event<EventType>&)>;
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

    void SendEvent(const CC_Event<EventType>& Event)
    {
        if (m_Listeners.find(Event.GetType()) == m_Listeners.end())
            return;

        for (auto&& Listener : m_Listeners.at(Event.GetType()))
        {
            if (!Event.Handled())
                Listener(Event);
        }
    }
};

template <typename T>
class EventDispatcher
{
    using MyEvent = std::function<void(const T&)>;
    std::vector<MyEvent> m_Listeners;

public:
    void AddListener(const MyEvent& Func)
    {
        m_Listeners.push_back(Func);
    }

    void RemoveListener(const MyEvent& Func)
    {
        m_Listeners.erase(std::remove(m_Listeners.begin(), m_Listeners.end(), Func), m_Listeners.end());
    }

    void SendEvent(const T& Event)
    {
        for (const auto& Listener : m_Listeners)
        {
            Listener(Event);
        }
    }
};
