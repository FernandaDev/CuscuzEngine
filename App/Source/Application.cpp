#include <iostream>
#include <SDL.h>

#include "Application.h"
#include "Events/EventHandler.h"
#include "Events/WindowEvents.h"

enum
{
	SCREEN_WIDTH = 1280,
	SCREEN_HEIGHT = 720
};

Application::Application():
	m_Window{ new Window("Game", SCREEN_WIDTH, SCREEN_HEIGHT) },
	m_RendererSystem { new RendererSystem {m_Window}},
	m_EventSystem{ new EventSystem() }
{
	ADD_WINDOW_EVENT_LISTENER(WindowEventType::Close, this, Application::Quit);
}

Application::~Application()
{
	delete m_RendererSystem;
	delete m_Window;
	SDL_Quit();
}

void Application::Run() const
{
	m_RendererSystem->AddTexture("Floor1.png");
	m_RendererSystem->AddTexture("Floor2.png");
	m_RendererSystem->AddTexture("Floor3.png");

	m_EventSystem->Start();
	
	while (m_IsRunning)
	{
		m_EventSystem->Update();
		m_RendererSystem->Update();
	}
}

void Application::Quit(const Event<WindowEventType>& Event)
{
	m_IsRunning = false;
}
