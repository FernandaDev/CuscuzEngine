#include "pch.h"
#include <SDL.h>

#include "CC_Application.h"
#include "ResourceManager.h"
#include "Core/Time.h"
#include "Events/EventHandler.h"
#include "Events/WindowEvents.h"
#include "GUI/ImGuiLayer.h"
#include "Layers/CC_AppLayer.h"
#include "Layers/Layer.h"
#include "Utils/Log.h"

enum
{
	SCREEN_WIDTH = 1280,
	SCREEN_HEIGHT = 720
};

CC_Application* CC_Application::s_Instance = nullptr;

CC_Application::CC_Application() :
	CC_Window{ new Window("Game", SCREEN_WIDTH, SCREEN_HEIGHT) },
	CC_RendererSystem { new RendererSystem {CC_Window.get()}},
	CC_EventSystem{ new EventSystem() }	
{
	Init();
}

CC_Application::CC_Application(CC_Game* game) :
	CC_Window{ new Window("Game", SCREEN_WIDTH, SCREEN_HEIGHT) },
	CC_RendererSystem { new RendererSystem {CC_Window.get()}},
	CC_EventSystem{ new EventSystem() },
	m_Game(game)
{
	Init();
}

void CC_Application::Init()
{
	s_Instance = this;
	Log::Init();

	ResourceManager::Get().SetRootResourcesPath("../App/Assets/Images/");

	CC_EventSystem->SetEventCallback(BIND_FUNCTION(this, CC_Application::OnEvent));
}

CC_Application::~CC_Application()
{
	if(m_Game->IsRunning())
		m_Game->ShutdownGame();

	ResourceManager::Get().UnloadResources();
	
	SDL_Quit();
}

void CC_Application::Start()
{
	PushLayer(new CC_AppLayer(m_Game));
	
	m_ImGuiLayer = new ImGuiLayer(*CC_Window, CC_RendererSystem->GetRenderer());
	PushOverlay(m_ImGuiLayer);	
}

void CC_Application::OnEvent(CC_Event& event)
{
	CC_EventSingleDispatcher eventDispatcher(event);
	eventDispatcher.Dispatch<CC_WindowCloseEvent>(BIND_FUNCTION(this, CC_Application::Quit));
	CC_Window->OnEvent(event);
	
	for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
	{
		(*--it)->OnEvent(event);
		if(event.Handled())
			break;
	}
}

void CC_Application::Run()
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

void CC_Application::Render() 
{
	CC_RendererSystem->Render();
}

void CC_Application::PushLayer(Layer* layer)
{
	m_LayerStack.PushLayer(layer);
}

void CC_Application::PushOverlay(Layer* layer)
{
	m_LayerStack.PushOverlay(layer);
}

void CC_Application::CreateGame(const std::shared_ptr<CC_Game>& game)
{
	m_Game = game;
}

bool CC_Application::Quit(CC_WindowCloseEvent& event)
{
	LOG_WARN("Quitting the engine...");
	m_IsRunning = false;
	return true;
}
