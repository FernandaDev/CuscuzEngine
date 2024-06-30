#include "pch.h"
#include "SDL.h"

#include "EngineApplication.h"

#include "ResourceManager.h"
#include "Core/Time.h"
#include "Events/EventHandler.h"
#include "Events/WindowEvents.h"
#include "Layers/EngineAppLayer.h"
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

EngineApplication::EngineApplication(CC_Game* game) :
	CC_Window{ new Window("Game", SCREEN_WIDTH, SCREEN_HEIGHT) },
	CC_RendererSystem { new RendererSystem {CC_Window}},
	CC_EventSystem{ new EventSystem() },
	m_Game(game)
{
	Init();
}

void EngineApplication::Init()
{
	s_Instance = this;
	Log::Init();

	ResourceManager::Get().SetRootResourcesPath("../App/Assets/Images/");

	CC_EventSystem->SetEventCallback(BIND_FUNCTION(this, EngineApplication::OnEvent));
}

EngineApplication::~EngineApplication()
{
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
{
	PushLayer(new EngineAppLayer(CC_EventSystem, CC_RendererSystem, m_Game));
	
	m_ImGuiLayer = new ImGuiLayer(*CC_Window, CC_RendererSystem->GetRenderer());
	PushOverlay(m_ImGuiLayer);	
}

void EngineApplication::OnEvent(CC_Event& event)
{
	CC_EventSingleDispatcher eventDispatcher(event);
	eventDispatcher.Dispatch<CC_WindowCloseEvent>(BIND_FUNCTION(this, EngineApplication::Quit));
	CC_Window->OnEvent(event);
	
	for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
	{
		(*--it)->OnEvent(event);
		if(event.Handled())
			break;
	}
}

void EngineApplication::Run()
{
	Start();
	
	while (m_IsRunning)
	{
		Time::Instance().Update();
		
		for (Layer* layer : m_LayerStack)
			layer->OnUpdate();

		m_ImGuiLayer->Begin();
		for (Layer* layer : m_LayerStack)
			layer->OnImGuiRender();
		m_ImGuiLayer->End();
		
		Render();
	}
}

void EngineApplication::Render() 
{
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

void EngineApplication::CreateGame(CC_Game* game)
{
	m_Game = game;
}

bool EngineApplication::Quit(CC_WindowCloseEvent& event)
{
	LOG_WARN("Quitting the engine...");
	m_IsRunning = false;
	return true;
}
