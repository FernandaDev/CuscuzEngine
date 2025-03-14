#include "pch.h"

#include <SDL.h>
#include "Engine.h"

#include "Cuscuz/Core/Window.h"
#include "Cuscuz/Core/Time.h"
#include "Cuscuz/Events/WindowEvents.h"
#include "Cuscuz/GUI/ImGuiLayer.h"
#include "Cuscuz/Layers/Layer.h"
#include "Cuscuz/Render/Renderer.h"
#include "Cuscuz/Utils/Log.h"
#include "Cuscuz/Utils/ResourcesManager.h"
#include "Cuscuz/World/World.h"

namespace Cuscuz
{
	Engine* Engine::s_Instance = nullptr;

	Engine::Engine() : CC_Window{ std::make_unique<Window>(SCREEN_WIDTH, SCREEN_HEIGHT) }
	{
		Init();
	}

	void Engine::Init()
	{
		s_Instance = this;

		Log::Init();
		
		CC_Window->Init("Cuscuz Engine");
		CC_Window->SetEventCallback(BIND_FUNCTION(this, Engine::OnEvent));

		Renderer::Init();
		ResourcesManager::Get().Init();

		m_ImGuiLayer = std::make_shared<ImGuiLayer>(*CC_Window);
		PushOverlay(m_ImGuiLayer);
	}

	Engine::~Engine()
	{
		SDL_Quit();
	}

	void Engine::OnEvent(CuscuzEvent& event)
	{
		EventSingleDispatcher eventDispatcher(event);
		eventDispatcher.Dispatch<CC_WindowCloseEvent>(BIND_FUNCTION(this, Engine::Quit));
		CC_Window->OnEvent(event);
	
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(event);
			if(event.Handled)
				break;
		}
	}

	void Engine::Run()
	{
		while (m_IsRunning)
		{
			Time::Get().Update();

			if(!CC_Window->IsMinimized())
			{
				for (const auto& layer : m_LayerStack)
					layer->OnUpdate(Time::Get().DeltaTime());
			}
		
			m_ImGuiLayer->Begin();
			for (const auto& layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();
		
			CC_Window->Update();
		}
	}

	void Engine::Close()
	{
		LOG_WARN("Quitting the engine...");
		m_IsRunning = false;
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