#include "pch.h"
#include "SDL.h"

#include "EngineApplication.h"
#include "Events/EventHandler.h"
#include "Events/WindowEvents.h"
#include "Utils/Log.h"

enum
{
	SCREEN_WIDTH = 1280,
	SCREEN_HEIGHT = 720
};

EngineApplication::EngineApplication():
	m_Window{ new Window("Game", SCREEN_WIDTH, SCREEN_HEIGHT) },
	m_RendererSystem { new RendererSystem {m_Window}},
	m_EventSystem{ new EventSystem() }
{
	ADD_WINDOW_EVENT_LISTENER(WindowEventType::Close, this, EngineApplication::Quit);
	Log::Init();
}

EngineApplication::~EngineApplication()
{
	delete m_RendererSystem;
	delete m_Window;
	SDL_Quit();
}

void EngineApplication::Start()
{	
	m_EventSystem->Start();

	m_lastDeltaTime = m_targetFrameDuration;
}

void EngineApplication::Run()
{
	Start();
	
	while (m_IsRunning)
	{
		FrameStart();
		
		Update();

		FrameEnd();
	}
}

void EngineApplication::Update()
{
	m_EventSystem->Update();
	m_RendererSystem->Update();
}

void EngineApplication::FrameStart()
{
	m_frameStart = SDL_GetTicks();
}

void EngineApplication::FrameEnd()
{
	m_frameEnd = SDL_GetTicks();
		
	m_frameCount++;
	m_lastDeltaTime = m_frameEnd - m_frameStart;

	if(m_lastDeltaTime < m_targetFrameDuration)
		SDL_Delay(m_targetFrameDuration - m_lastDeltaTime);
}

void EngineApplication::Quit(const Event<WindowEventType>& Event)
{
	m_IsRunning = false;
}
