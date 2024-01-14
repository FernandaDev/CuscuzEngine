#include <iostream>
#include "Window.h"

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
}

Window::~Window()
{
	if(m_Window)
		SDL_DestroyWindow(m_Window);
}
