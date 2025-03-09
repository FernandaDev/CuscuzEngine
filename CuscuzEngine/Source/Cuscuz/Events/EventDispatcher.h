#pragma once

#include <vector>
#include <functional>
#include "CuscuzEvent.h"

namespace Cuscuz
{
    template <typename EventType> //TODO Review this
    class EventDispatcher
    {
        using EventFunc = std::function<void(CuscuzEvent&)>;
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

        void SendEvent(const CuscuzEvent& event)
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

    class EventSingleDispatcher
    {
        template<typename T>
        using EventFunction = std::function<bool(T&)>;
        CuscuzEvent& m_Event;
    
    public:
        EventSingleDispatcher(CuscuzEvent& event)
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
}