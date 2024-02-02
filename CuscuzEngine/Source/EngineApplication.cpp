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
	m_EventSystem{ new EventSystem() },
	m_ImGuiLayer{ new ImGuiLayer(*m_Window, m_RendererSystem->GetRenderer()) }
{
	SUBSCRIBE_WINDOW_EVENT(CC_WindowEventType::Close, this, EngineApplication::Quit);
	Log::Init();
}

EngineApplication::~EngineApplication()
{
	delete m_Window;
	delete m_RendererSystem;
	delete m_EventSystem;
	delete m_ImGuiLayer;
	
	SDL_Quit();
}

void EngineApplication::Start()
{	
	m_lastDeltaTime = m_targetFrameDuration;
}

void EngineApplication::Run()
{
	Start();
	
	while (m_IsRunning)
	{
		FrameStart();
		
		Update();
		Render();

		FrameEnd();
	}
}

void EngineApplication::Update()
{
	m_EventSystem->Update();
	m_RendererSystem->Update();
	m_ImGuiLayer->Update();
}


void EngineApplication::Render()
{
	m_ImGuiLayer->Render();
	m_RendererSystem->Render();
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

void EngineApplication::Quit(const CC_Event<CC_WindowEventType>& Event)
{
	m_IsRunning = false;
}

