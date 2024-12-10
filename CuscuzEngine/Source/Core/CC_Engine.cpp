#include "pch.h"
#include <SDL.h>

#include "CC_Engine.h"

#include "PhysicsSystem.h"
#include "Core/Window.h"
#include "Core/RendererSystem.h"
#include "Core/Time.h"
#include "Editor/EditorLayer.h"
#include "Events/WindowEvents.h"
#include "GUI/ImGuiLayer.h"
#include "Layers/EngineLayer.h"
#include "Layers/Layer.h"
#include "Utils/Log.h"
#include "Utils/ResourcesManager.h"
#include "World/World.h"

CC_Engine* CC_Engine::s_Instance = nullptr;

CC_Engine::CC_Engine() :
	CC_Window{ std::make_unique<Window>(SCREEN_WIDTH, SCREEN_HEIGHT) },
	CC_RendererSystem{ std::make_unique<RendererSystem>() }, CC_PhysicsSystem{ std::make_unique<PhysicsSystem>() },
	CC_EventSystem{ std::make_unique<EventSystem>() }, CC_World(std::make_unique<World>())
{
	Init();
}

void CC_Engine::Init()
{
	s_Instance = this;

	Log::Init();
	CC_Window->Init("Cuscuz Engine");
	//CC_RendererSystem->Init();

	CC_EventSystem->SetEventCallback(BIND_FUNCTION(this, CC_Engine::OnEvent));

	ResourcesManager::Get().Init();
}

CC_Engine::~CC_Engine()
{
	SDL_Quit();
}

void CC_Engine::Start()
{
	PushLayer(std::make_shared<EngineLayer>());
	PushOverlay(std::make_shared<EditorLayer>());
	
	m_ImGuiLayer = std::make_shared<ImGuiLayer>(*CC_Window);
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
		
		CC_Window->Render();
	}
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
