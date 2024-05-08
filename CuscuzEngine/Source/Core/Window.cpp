#include "pch.h"
#include "Window.h"

#include "Events/EventHandler.h"
#include "Utils/Log.h"

Window::Window(const char* Name, int Width, int Height):
	m_Width{Width}, m_Height{Height}
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG_ERROR("SDL could not be initialized: %s", SDL_GetError());
		return;
	}

	m_Window = SDL_CreateWindow(Name, SDL_WINDOWPOS_UNDEFINED, 
									  SDL_WINDOWPOS_UNDEFINED,
									  m_Width, m_Height, 
									  SDL_WINDOW_SHOWN);

	if (!m_Window)
		LOG_ERROR("Could not create a window.");

	SUBSCRIBE_WINDOW_EVENT(CC_WindowEventType::Resize, this , Window::OnWindowResized);
}

Window::~Window()
{
	UNSUBSCRIBE_WINDOW_EVENT(this, Window::OnWindowResized);
	
	if(m_Window)
		SDL_DestroyWindow(m_Window);
}

void Window::OnWindowResized(const CC_Event<CC_WindowEventType>& Event)
{
	const auto resizeEvent = Event.ToType<CC_WindowResizeEvent>();

	m_Height = resizeEvent.GetHeight();
	m_Width = resizeEvent.GetWidth();
}
