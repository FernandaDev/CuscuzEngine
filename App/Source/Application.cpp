#include "pch.h"
#include "SDL.h"

#include "Application.h"
#include "Events/EventHandler.h"
#include "Events/WindowEvents.h"
#include "Utils/Log.h"

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
	Log::Init();
}

Application::~Application()
{
	delete m_RendererSystem;
	delete m_Window;
	SDL_Quit();
}

void Application::Start()
{	
	m_RendererSystem->CreateSprite("Floor1.png", 250, 400);
	m_RendererSystem->CreateSprite("Floor2.png", 620, 250, 2, 2);
	//m_RendererSystem->CreateSprite("Floor3.png", 500, 500, 3, 3);

	m_EventSystem->Start();

	m_lastDeltaTime = m_targetFrameDuration;
}

void Application::Run()
{
	Start();
	
	while (m_IsRunning)
	{
		FrameStart();
		
		m_EventSystem->Update();
		m_RendererSystem->Update();

		FrameEnd();
	}
}

void Application::FrameStart()
{
	m_frameStart = SDL_GetTicks();
}

void Application::FrameEnd()
{
	m_frameEnd = SDL_GetTicks();
		
	m_frameCount++;
	m_lastDeltaTime = m_frameEnd - m_frameStart;

	if(m_lastDeltaTime < m_targetFrameDuration)
		SDL_Delay(m_targetFrameDuration - m_lastDeltaTime);
}

void Application::Quit(const Event<WindowEventType>& Event)
{
	m_IsRunning = false;
}
