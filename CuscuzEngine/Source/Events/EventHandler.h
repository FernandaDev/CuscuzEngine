#pragma once

#include "CC_EventDispatcher.h"
#include "KeyEvents.h"
#include "WindowEvents.h"
#include "MouseEvents.h"

class EventHandler
{
    static std::unique_ptr<EventHandler> s_Instance;

    CC_EventDispatcher<CC_WindowEventType> m_WindowEventDispatcher;
    CC_EventDispatcher<CC_KeyEventType> m_KeyEventDispatcher;
    CC_EventDispatcher<CC_MouseEventType> m_MouseEventDispatcher;
    
public:
    static EventHandler* GetInstance();

    CC_EventDispatcher<CC_WindowEventType>& GetWindowDispatcher() { return m_WindowEventDispatcher; }
    CC_EventDispatcher<CC_KeyEventType>& GetKeyDispatcher() { return m_KeyEventDispatcher; }
    CC_EventDispatcher<CC_MouseEventType>& GetMouseDispatcher() { return m_MouseEventDispatcher; }
};

#define SUBSCRIBE_WINDOW_EVENT(EventType,  Arg, Func) EventHandler::GetInstance()->GetWindowDispatcher().AddListener(EventType, std::bind(&Func, Arg, std::placeholders::_1))
#define SUBSCRIBE_KEY_EVENT(EventType, Arg,  Func) EventHandler::GetInstance()->GetKeyDispatcher().AddListener(EventType, std::bind(&Func, Arg, std::placeholders::_1))
#define SUBSCRIBE_MOUSE_EVENT(EventType, Arg, Func) EventHandler::GetInstance()->GetMouseDispatcher().AddListener(EventType, std::bind(&Func, Arg, std::placeholders::_1))

#define UNSUBSCRIBE_WINDOW_EVENT(Arg, Func) EventHandler::GetInstance()->GetWindowDispatcher().RemoveListener(std::bind(&Func, Arg, std::placeholders::_1))
#define UNSUBSCRIBE_KEY_EVENT(Arg,  Func) EventHandler::GetInstance()->GetKeyDispatcher().RemoveListener(std::bind(&Func, Arg, std::placeholders::_1))
#define UNSUBSCRIBE_MOUSE_EVENT(Arg, Func) EventHandler::GetInstance()->GetMouseDispatcher().RemoveListener(std::bind(&Func, Arg, std::placeholders::_1))

#define SEND_WINDOW_EVENT(_event) EventHandler::GetInstance()->GetWindowDispatcher().SendEvent(_event)
#define SEND_KEY_EVENT(_event) EventHandler::GetInstance()->GetKeyDispatcher().SendEvent(_event)
#define SEND_MOUSE_EVENT(_event) EventHandler::GetInstance()->GetMouseDispatcher().SendEvent(_event)