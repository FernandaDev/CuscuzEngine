#include "pch.h"
#include "EventSystem.h"

#include "Utils/Log.h"

void EventSystem::Start()
{
	ADD_KEY_EVENT_LISTENER(KeyEventType::Down, this, EventSystem::OnKeyDown);
	ADD_KEY_EVENT_LISTENER(KeyEventType::Up, this, EventSystem::OnKeyUp);
	ADD_MOUSE_EVENT_LISTENER(MouseEventType::ButtonDown, this, EventSystem::OnMouseButtonDown);
	ADD_MOUSE_EVENT_LISTENER(MouseEventType::ButtonUp, this, EventSystem::OnMouseButtonUp);
	//ADD_MOUSE_EVENT_LISTENER(MouseEventType::Moved, this, EventSystem::OnMouseMoved);
}

void EventSystem::Update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			{
				const WindowCloseEvent windowCloseEvent;
				SEND_WINDOW_EVENT(windowCloseEvent);
				return;
			}
		case SDL_WINDOWEVENT:
			{
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					WindowResizeEvent windowResizeEvent(event.window.data1, event.window.data2);
					SEND_WINDOW_EVENT(windowResizeEvent);
				}
			}
			break;
		case SDL_KEYUP:
			{
				KeyUpEvent keyUpEvent(event.key.keysym.sym);
				SEND_KEY_EVENT(keyUpEvent);
			}
			break;
		case SDL_KEYDOWN:
			{
				KeyDownEvent keyDownEvent(event.key.keysym.sym);
				SEND_KEY_EVENT(keyDownEvent);
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			{
				MouseButtonDownEvent mouseButtonDownEvent(event.button.button);
				SEND_MOUSE_EVENT(mouseButtonDownEvent);
			}
			break;
		case SDL_MOUSEBUTTONUP:
			{
				MouseButtonUpEvent mouseButtonUpEvent(event.button.button);
				SEND_MOUSE_EVENT(mouseButtonUpEvent);	
			}
			break;
		case SDL_MOUSEMOTION:
			{
				MouseMovedEvent mouseMovedEvent(event.motion.x, event.motion.y);
				SEND_MOUSE_EVENT(mouseMovedEvent);
			}
			break;
		default:
			break;
		}
	}
}

// do we want this here? we are probably going to create an input system class later on...
bool EventSystem::IsKeyDown(const SDL_Scancode& Input) 
{
	return m_CurrentState[Input];
}

void EventSystem::RefreshKeyState()
{
	m_CurrentState = SDL_GetKeyboardState(NULL);
}

void EventSystem::OnKeyDown(const Event<KeyEventType>& Event)
{
	RefreshKeyState();
	LOG_INFO(Event.ToString()); 
}

void EventSystem::OnKeyUp(const Event<KeyEventType>& Event)
{
	RefreshKeyState();
	LOG_INFO(Event.ToString()); 
}

void EventSystem::OnMouseButtonDown(const Event<MouseEventType>& Event)
{
	LOG_INFO(Event.ToString()); 
}

void EventSystem::OnMouseButtonUp(const Event<MouseEventType>& Event)
{
	LOG_INFO(Event.ToString()); 
}

void EventSystem::OnMouseMoved(const Event<MouseEventType>& Event)
{
	LOG_INFO(Event.ToString()); 
}