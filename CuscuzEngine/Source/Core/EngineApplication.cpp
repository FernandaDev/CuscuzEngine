#include "pch.h"
#include "SDL.h"

#include "EngineApplication.h"

#include "ResourceManager.h"
#include "Core/Time.h"
#include "Events/EventHandler.h"
#include "Events/WindowEvents.h"
#include "Layers/GameLayer.h"
#include "Layers/Layer.h"
#include "Utils/Log.h"

enum
{
	SCREEN_WIDTH = 1280,
	SCREEN_HEIGHT = 720
};

EngineApplication* EngineApplication::s_Instance = nullptr;

EngineApplication::EngineApplication() :
	CC_Window{ new Window("Game", SCREEN_WIDTH, SCREEN_HEIGHT) },
	CC_RendererSystem { new RendererSystem {CC_Window}},
	CC_EventSystem{ new EventSystem() }	
{
	Init();	
}

EngineApplication::EngineApplication(CC_Game* Game) :
	CC_Window{ new Window("Game", SCREEN_WIDTH, SCREEN_HEIGHT) },
	CC_RendererSystem { new RendererSystem {CC_Window}},
	CC_EventSystem{ new EventSystem() },
	m_Game(Game)
{
	Init();
}

void EngineApplication::Init()
{
	SUBSCRIBE_WINDOW_EVENT(CC_WindowEventType::Close, this, EngineApplication::Quit);
	s_Instance = this;
	Log::Init();

	ResourceManager::Get().SetRootResourcesPath("../App/Assets/Images/");

	PushLayer(new ImGuiLayer(*CC_Window, CC_RendererSystem->GetRenderer()));
	PushLayer(new GameLayer(m_Game));
}

EngineApplication::~EngineApplication()
{
	UNSUBSCRIBE_WINDOW_EVENT(this, EngineApplication::Quit);

	if(m_Game->IsRunning())
		m_Game->ShutdownGame();

	delete m_Game;
	
	delete CC_Window;
	delete CC_RendererSystem;
	delete CC_EventSystem;

	ResourceManager::Get().UnloadResources();
	
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
		
		for (Layer* layer : m_LayerStack)
			layer->OnUpdate();

		Render();
	}
}

void EngineApplication::ProcessInput() const // should we have an input layer?
{
	CC_EventSystem->Update();
}

void EngineApplication::Render() 
{
	CC_RendererSystem->Update();
	CC_RendererSystem->Render();
}

void EngineApplication::PushLayer(Layer* layer)
{
	m_LayerStack.PushLayer(layer);
}

void EngineApplication::PushOverlay(Layer* layer)
{
	m_LayerStack.PushOverlay(layer);
}

void EngineApplication::Quit(const CC_Event<CC_WindowEventType>& Event)
{
	m_IsRunning = false;
}

// void EngineApplication::OnEvent()
// {
// 	for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
// 	{
// 		(*--it)->OnEvent(event);
// 		if(e.Handled)
// 			break;
// 	}
// }
