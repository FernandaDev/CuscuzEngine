#include "pch.h"
#include "EventSystem.h"

#include <SDL_events.h>

#include "Events/EventHandler.h"
#include "Events/WindowEvents.h"

void EventSystem::Update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			{
				const CC_WindowCloseEvent windowCloseEvent;
				SEND_WINDOW_EVENT(windowCloseEvent);
				return;
			}
		case SDL_WINDOWEVENT:
			{
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					CC_WindowResizeEvent windowResizeEvent(event.window.data1, event.window.data2);
					SEND_WINDOW_EVENT(windowResizeEvent);
				}
			}
			break;
		case SDL_KEYUP:
			{
				CC_KeyUpEvent keyUpEvent(event.key.keysym.scancode);
				SEND_KEY_EVENT(keyUpEvent);
			}
			break;
		case SDL_KEYDOWN:
			{
				CC_KeyDownEvent keyDownEvent(event.key.keysym.scancode);
				SEND_KEY_EVENT(keyDownEvent);
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			{
				CC_MouseButtonDownEvent mouseButtonDownEvent(event.button.button);
				SEND_MOUSE_EVENT(mouseButtonDownEvent);
			}
			break;
		case SDL_MOUSEBUTTONUP:
			{
				CC_MouseButtonUpEvent mouseButtonUpEvent(event.button.button);
				SEND_MOUSE_EVENT(mouseButtonUpEvent);	
			}
			break;
		case SDL_MOUSEMOTION:
			{
				CC_MouseMovedEvent mouseMovedEvent(event.motion.x, event.motion.y);
				SEND_MOUSE_EVENT(mouseMovedEvent);
			}
			break;
		case SDL_MOUSEWHEEL:
			{
				CC_MouseScrollEvent mouseScrollEvent(event.wheel.preciseX, event.wheel.preciseY);
				SEND_MOUSE_EVENT(mouseScrollEvent);
				break;
			}
		default:
			break;
		}

		m_SDLEventDelegate.Broadcast(event);
	}
}
