#include "pch.h"
#include <SDL.h>

#include "CC_Engine.h"
#include "Core/Window.h"
#include "Core/RendererSystem.h"
#include "Core/ResourceManager.h"
#include "Core/Time.h"
#include "Events/EventHandler.h"
#include "Events/WindowEvents.h"
#include "GUI/ImGuiLayer.h"
#include "Layers/CC_MainLayer.h"
#include "Layers/Layer.h"
#include "Utils/Log.h"

CC_Engine* CC_Engine::s_Instance = nullptr;

CC_Engine::CC_Engine() :
	CC_Window{ std::make_unique<Window>("Game", SCREEN_WIDTH, SCREEN_HEIGHT) },
	CC_RendererSystem{ std::make_unique<RendererSystem>(CC_Window.get()) },
	CC_EventSystem{ std::make_unique<EventSystem>() }
{
	Init();
}

void CC_Engine::Init()
{
	s_Instance = this;
	Log::Init();

	ResourceManager::Get().SetRootResourcesPath("../App/Assets/Images/"); // TODO REMOVE THIS

	CC_EventSystem->SetEventCallback(BIND_FUNCTION(this, CC_Engine::OnEvent));
}

CC_Engine::~CC_Engine()
{
	ResourceManager::Get().UnloadResources();
	
	SDL_Quit();
}

void CC_Engine::Start()
{
	PushLayer(std::make_shared<CC_MainLayer>());
	
	m_ImGuiLayer = std::make_shared<ImGuiLayer>(*CC_Window, CC_RendererSystem->GetRenderer());
	PushOverlay(m_ImGuiLayer);	
}

void CC_Engine::OnEvent(CC_Event& event)
{
	CC_EventSingleDispatcher eventDispatcher(event);
	eventDispatcher.Dispatch<CC_WindowCloseEvent>(BIND_FUNCTION(this, CC_Engine::Quit));
	CC_Window->OnEvent(event);
	
	for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
	{
		(*--it)->OnEvent(event);
		if(event.Handled())
			break;
	}
}

void CC_Engine::Run()
{
	Start();
	
	while (m_IsRunning)
	{
		Time::Instance().Update();
		
		for (const auto& layer : m_LayerStack)
			layer->OnUpdate(Time::Instance().DeltaTime());

		m_ImGuiLayer->Begin();
		for (const auto& layer : m_LayerStack)
			layer->OnImGuiRender();
		m_ImGuiLayer->End();
		
		Render();
	}
}

void CC_Engine::Render() 
{
	CC_RendererSystem->Render();
}

void CC_Engine::PushLayer(std::shared_ptr<Layer> layer)
{
	m_LayerStack.PushLayer(layer);
}

void CC_Engine::PushOverlay(std::shared_ptr<Layer> layer)
{
	m_LayerStack.PushOverlay(layer);
}

bool CC_Engine::Quit(CC_WindowCloseEvent& event)
{
	LOG_WARN("Quitting the engine...");
	m_IsRunning = false;
	return true;
}
