#pragma once
#include <functional>

#include "Event.h"

template<typename T>
class EventDispatcher
{
    using EventFunc = std::function<void(const Event<T>&)>;
    std::unordered_map<T, std::vector<EventFunc>> m_Listeners;

public:
    void AddListener(T Type, const EventFunc& Func)
    {
        m_Listeners[Type].push_back(Func);
    }

    void SendEvent(const Event<T>& Event)
    {
        if(m_Listeners.find(Event.GetType()) == m_Listeners.end())
            return;

        for (auto&& Listener : m_Listeners.at(Event.GetType()))
        {
            if(!Event.Handled())
                Listener(Event);
        }
    }
};
