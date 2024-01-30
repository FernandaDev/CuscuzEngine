#pragma once

#include "EventDispatcher.h"
#include "KeyEvents.h"
#include "WindowEvents.h"
#include "MouseEvents.h"

class EventHandler
{
    static std::unique_ptr<EventHandler> s_Instance;

    EventDispatcher<WindowEventType> m_WindowEventDispatcher;
    EventDispatcher<KeyEventType> m_KeyEventDispatcher;
    EventDispatcher<MouseEventType> m_MouseEventDispatcher;
    
public:
    static EventHandler* GetInstance();

    EventDispatcher<WindowEventType>& GetWindowDispatcher() { return m_WindowEventDispatcher; }
    EventDispatcher<KeyEventType>& GetKeyDispatcher() { return m_KeyEventDispatcher; }
    EventDispatcher<MouseEventType>& GetMouseDispatcher() { return m_MouseEventDispatcher; }
};

#define ADD_WINDOW_EVENT_LISTENER(EventType,  Arg, Func) EventHandler::GetInstance()->GetWindowDispatcher().AddListener(EventType, std::bind(&Func, Arg, std::placeholders::_1))
#define ADD_KEY_EVENT_LISTENER(EventType, Arg,  Func) EventHandler::GetInstance()->GetKeyDispatcher().AddListener(EventType, std::bind(&Func, Arg, std::placeholders::_1))
#define ADD_MOUSE_EVENT_LISTENER(EventType, Arg, Func) EventHandler::GetInstance()->GetMouseDispatcher().AddListener(EventType, std::bind(&Func, Arg, std::placeholders::_1))

#define SEND_WINDOW_EVENT(_event) EventHandler::GetInstance()->GetWindowDispatcher().SendEvent(_event)
#define SEND_KEY_EVENT(_event) EventHandler::GetInstance()->GetKeyDispatcher().SendEvent(_event)
#define SEND_MOUSE_EVENT(_event) EventHandler::GetInstance()->GetMouseDispatcher().SendEvent(_event)