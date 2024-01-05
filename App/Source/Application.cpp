#include <iostream>

#include <SDL.h>
#include "Application.h"

#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720

Application::Application():
	m_Window{ new Window("Game", SCREEN_WIDTH, SCREEN_HEIGHT) }
{
	m_Renderer = SDL_CreateRenderer(m_Window->GetWindow(), -1, 0);

	if (!m_Renderer)
	{
		std::cout << "Could not create a renderer." << std::endl;
		return;
	}
}

Application::~Application()
{
	SDL_DestroyRenderer(m_Renderer);

	delete m_Window;

	SDL_Quit();
}

void Application::Run()
{
	while (m_IsRunning)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				m_IsRunning = false;
		}
	}
}
