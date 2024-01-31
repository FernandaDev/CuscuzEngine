#pragma once

#include "CC_EventDispatcher.h"
#include "KeyEvents.h"
#include "WindowEvents.h"
#include "MouseEvents.h"
#include "GUI/imgui_impl_sdl.h"

class EventHandler
{
    static std::unique_ptr<EventHandler> s_Instance;

    CC_EventDispatcher<CC_WindowEventType> m_WindowEventDispatcher;
    CC_EventDispatcher<CC_KeyEventType> m_KeyEventDispatcher;
    CC_EventDispatcher<CC_MouseEventType> m_MouseEventDispatcher;
    EventDispatcher<SDL_Event> m_SDLEventDispatcher;
    
public:
    static EventHandler* GetInstance();

    CC_EventDispatcher<CC_WindowEventType>& GetWindowDispatcher() { return m_WindowEventDispatcher; }
    CC_EventDispatcher<CC_KeyEventType>& GetKeyDispatcher() { return m_KeyEventDispatcher; }
    CC_EventDispatcher<CC_MouseEventType>& GetMouseDispatcher() { return m_MouseEventDispatcher; }
    EventDispatcher<SDL_Event>& GetSDLEventDispatcher() { return m_SDLEventDispatcher; }
};

#define ADD_WINDOW_EVENT_LISTENER(EventType,  Arg, Func) EventHandler::GetInstance()->GetWindowDispatcher().AddListener(EventType, std::bind(&Func, Arg, std::placeholders::_1))
#define ADD_KEY_EVENT_LISTENER(EventType, Arg,  Func) EventHandler::GetInstance()->GetKeyDispatcher().AddListener(EventType, std::bind(&Func, Arg, std::placeholders::_1))
#define ADD_MOUSE_EVENT_LISTENER(EventType, Arg, Func) EventHandler::GetInstance()->GetMouseDispatcher().AddListener(EventType, std::bind(&Func, Arg, std::placeholders::_1))
#define ADD_SDL_EVENT_LISTENER(Arg, Func) EventHandler::GetInstance()->GetSDLEventDispatcher().AddListener(std::bind(&Func, Arg, std::placeholders::_1))

#define SEND_WINDOW_EVENT(_event) EventHandler::GetInstance()->GetWindowDispatcher().SendEvent(_event)
#define SEND_KEY_EVENT(_event) EventHandler::GetInstance()->GetKeyDispatcher().SendEvent(_event)
#define SEND_MOUSE_EVENT(_event) EventHandler::GetInstance()->GetMouseDispatcher().SendEvent(_event)
#define SEND_SDL_EVENT(_event) EventHandler::GetInstance()->GetSDLEventDispatcher().SendEvent(_event)
