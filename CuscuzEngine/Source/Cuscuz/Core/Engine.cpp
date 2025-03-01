#include "pch.h"

#include <SDL.h>
#include "Engine.h"

#include "PhysicsSystem.h"
#include "Cuscuz/Core/Window.h"
#include "Cuscuz/Core/RendererSystem.h"
#include "Cuscuz/Core/Time.h"
#include "Cuscuz/Editor/EditorLayer.h"
#include "Cuscuz/Events/WindowEvents.h"
#include "Cuscuz/GUI/ImGuiLayer.h"
#include "Cuscuz/Layers/EngineLayer.h"
#include "Cuscuz/Layers/Layer.h"
#include "Cuscuz/Render/Renderer.h"
#include "Cuscuz/Utils/Log.h"
#include "Cuscuz/Utils/ResourcesManager.h"
#include "Cuscuz/World/World.h"

namespace Cuscuz
{
	Engine* Engine::s_Instance = nullptr;

	Engine::Engine() :
		CC_Window{ std::make_unique<Window>(SCREEN_WIDTH, SCREEN_HEIGHT) },
		CC_RendererSystem{ std::make_unique<RendererSystem>() }, CC_PhysicsSystem{ std::make_unique<PhysicsSystem>() },
		CC_EventSystem{ std::make_unique<EventSystem>() }, CC_World(std::make_unique<World>())
	{
		Init();
	}

	void Engine::Init()
	{
		s_Instance = this;

		Log::Init();
		CC_Window->Init("Cuscuz Engine");
		Renderer::Init();

		CC_EventSystem->SetEventCallback(BIND_FUNCTION(this, Engine::OnEvent));

		ResourcesManager::Get().Init();
	}

	Engine::~Engine()
	{
		SDL_Quit();
	}

	void Engine::Start()
	{
		PushLayer(std::make_shared<EngineLayer>());
		PushOverlay(std::make_shared<EditorLayer>());
	
		m_ImGuiLayer = std::make_shared<ImGuiLayer>(*CC_Window);
		PushOverlay(m_ImGuiLayer);
	}

	void Engine::OnEvent(CC_Event& event)
	{
		CC_EventSingleDispatcher eventDispatcher(event);
		eventDispatcher.Dispatch<CC_WindowCloseEvent>(BIND_FUNCTION(this, Engine::Quit));
		CC_Window->OnEvent(event);
	
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(event);
			if(event.Handled())
				break;
		}
	}

	void Engine::Run()
	{
		Start();
	
		while (m_IsRunning)
		{
			Time::Get().Update();

			CC_EventSystem->OnUpdate();

			if(!CC_Window->IsMinimized())
			{
				for (const auto& layer : m_LayerStack)
					layer->OnUpdate(Time::Get().DeltaTime());
			}
		
			m_ImGuiLayer->Begin();
			for (const auto& layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();
		
			CC_Window->Render();
		}
	}

	void Engine::PushLayer(std::shared_ptr<Layer> layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Engine::PushOverlay(std::shared_ptr<Layer> layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	bool Engine::Quit(CC_WindowCloseEvent& event)
	{
		LOG_WARN("Quitting the engine...");
		m_IsRunning = false;
	
		return true;
	}
}