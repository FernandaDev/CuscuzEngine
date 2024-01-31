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
        m_Listeners[Type].push_back(Func);
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

    void SendEvent(const T& Event)
    {
        for (const auto& Listener : m_Listeners)
        {
            Listener(Event);
        }
    }
};
