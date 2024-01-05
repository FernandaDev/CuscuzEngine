#include <iostream>

#include <SDL.h>
#include "Application.h"

#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720

Application::Application():
	m_Window{ new Window("Game", SCREEN_WIDTH, SCREEN_HEIGHT) },
	m_RendererSystem { new RendererSystem {m_Window}}
{}

Application::~Application()
{
	delete m_RendererSystem;
	delete m_Window;
	SDL_Quit();
}

void Application::Run()
{
	m_RendererSystem->AddTexture("Floor1.png");
	m_RendererSystem->AddTexture("Floor2.png");
	m_RendererSystem->AddTexture("Floor3.png");

	while (m_IsRunning)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				m_IsRunning = false;
		}

		m_RendererSystem->Update();
	}
}
