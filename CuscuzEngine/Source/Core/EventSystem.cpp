#include "pch.h"
#include "EventSystem.h"

#include <SDL_events.h>

//#include "Events/EventHandler.h"
#include "Events/WindowEvents.h"
#include "Events/KeyEvents.h"
#include "Events/MouseEvents.h"
#include "Events/SDLEvent.h"

void EventSystem::SetEventCallback(const EventCallbackFn& callback)
{
	m_EventCallbackFn = callback;
}

void EventSystem::Update() const
{
	 SDL_Event event;
	 while (SDL_PollEvent(&event))
	 {
	 	switch (event.type)
	 	{
	 	case SDL_QUIT:
	 		{
				CC_WindowCloseEvent windowCloseEvent;
	 			m_EventCallbackFn(windowCloseEvent);
	 		}
	 		break;	
	 	case SDL_WINDOWEVENT:
	 		{
	 			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
	 			{
	 				CC_WindowResizeEvent windowResizeEvent(event.window.data1, event.window.data2);
	 				m_EventCallbackFn(windowResizeEvent);
	 			}
	 		}
	 		break;
	 	case SDL_KEYUP:
	 		{
	 			CC_KeyUpEvent keyUpEvent(event.key.keysym.scancode);
	 			m_EventCallbackFn(keyUpEvent);
	 		}
	 		break;
	 	case SDL_KEYDOWN:
	 		{
	 			CC_KeyDownEvent keyDownEvent(event.key.keysym.scancode);
	 			m_EventCallbackFn(keyDownEvent);
	 		}
	 		break;
	 	case SDL_MOUSEBUTTONDOWN:
	 		{
	 			CC_MouseButtonDownEvent mouseButtonDownEvent(event.button.button);
	 			m_EventCallbackFn(mouseButtonDownEvent);
	 		}
	 		break;
	 	case SDL_MOUSEBUTTONUP:
	 		{
	 			CC_MouseButtonUpEvent mouseButtonUpEvent(event.button.button);
	 			m_EventCallbackFn(mouseButtonUpEvent);	
	 		}
	 		break;
	 	case SDL_MOUSEMOTION:
	 		{
	 			CC_MouseMovedEvent mouseMovedEvent(event.motion.x, event.motion.y);
	 			m_EventCallbackFn(mouseMovedEvent);
	 		}
	 		break;
	 	case SDL_MOUSEWHEEL:
	 		{
	 			CC_MouseScrolledEvent mouseScrollEvent(event.wheel.preciseX, event.wheel.preciseY);
	 			m_EventCallbackFn(mouseScrollEvent);
	 		}
	 		break;
	 	default:
	 		break;
	 	}
	 
	  	CC_SDLEvent sdlEvent(event);
	  	m_EventCallbackFn(sdlEvent);
	}
}