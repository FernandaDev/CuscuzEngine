#include <iostream>
#include "Window.h"

Window::Window(const char* Name, int Width, int Height):
	m_Width{Width}, m_Height{Height}
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not be initialized: " << SDL_GetError() << std::endl;
		return;
	}

	m_Window = SDL_CreateWindow(Name, SDL_WINDOWPOS_UNDEFINED, 
									  SDL_WINDOWPOS_UNDEFINED,
									  m_Width, m_Height, 
									  SDL_WINDOW_SHOWN);

	if (!m_Window)
		std::cout << "Could not create a window." << std::endl;
}

Window::~Window()
{
	if(m_Window)
		SDL_DestroyWindow(m_Window);
}
