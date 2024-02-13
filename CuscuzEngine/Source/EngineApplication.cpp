#include "pch.h"
#include "SDL.h"

#include "EngineApplication.h"

#include "ResourceManager.h"
#include "Core/Time.h"
#include "Events/EventHandler.h"
#include "Events/WindowEvents.h"
#include "Utils/Log.h"

enum
{
	SCREEN_WIDTH = 1280,
	SCREEN_HEIGHT = 720
};

EngineApplication::EngineApplication():
	CC_Window{ new Window("Game", SCREEN_WIDTH, SCREEN_HEIGHT) },
	CC_RendererSystem { new RendererSystem {CC_Window}},
	CC_EventSystem{ new EventSystem() },
	CC_ImGuiLayer{ new ImGuiLayer(*CC_Window, CC_RendererSystem->GetRenderer()) }
{
	SUBSCRIBE_WINDOW_EVENT(CC_WindowEventType::Close, this, EngineApplication::Quit);
	Log::Init();
}

EngineApplication::~EngineApplication()
{
	delete CC_Window;
	delete CC_RendererSystem;
	delete CC_EventSystem;
	delete CC_ImGuiLayer;

	ResourceManager::Instance().UnloadResources();
	
	SDL_Quit();
}

void EngineApplication::Start()
{}

void EngineApplication::Run()
{
	Start();
	
	while (m_IsRunning)
	{
		Time::Instance().Update();

		ProcessInput();
		Update();
		Render();
	}
}

void EngineApplication::ProcessInput() const
{
	CC_EventSystem->Update();
}

void EngineApplication::Update()
{
	CC_RendererSystem->Update();
	CC_ImGuiLayer->Update();
}

void EngineApplication::Render() const 
{
	CC_ImGuiLayer->Render();
	CC_RendererSystem->Render();
}

void EngineApplication::Quit(const CC_Event<CC_WindowEventType>& Event)
{
	m_IsRunning = false;
}