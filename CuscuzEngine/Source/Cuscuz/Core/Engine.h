#pragma once

#include "Cuscuz/Core/EventSystem.h"
#include "Cuscuz/Events/CuscuzEvent.h"
#include "Cuscuz/Events/WindowEvents.h"
#include "Cuscuz/Layers/LayerStack.h"

int main(int argc, char** argv);

namespace Cuscuz
{
	class PhysicsSystem;
	class ResourcesManager;
	class ImGuiLayer;
	class EngineLayer;
	class Window;
	class RendererSystem;
	class EventSystem;
	class World;

	class Engine 
	{
	public:
		std::unique_ptr<Window> CC_Window;
	
	private:
		static Engine* s_Instance;

		std::shared_ptr<ImGuiLayer> m_ImGuiLayer;
		LayerStack m_LayerStack;
	
		bool m_IsRunning = true;

	public:
		Engine();
		virtual ~Engine();

		static Engine& Get() { return *s_Instance;}
	
		void Run();
		void Close();
	
		void OnEvent(CuscuzEvent& event);
	
		void PushLayer(std::shared_ptr<Layer> layer);
		void PushOverlay(std::shared_ptr<Layer> layer);

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer.get(); }
	private:
		void Init();
		bool Quit(CC_WindowCloseEvent& event);

		friend int ::main(int argc, char* argv[]);
	};

	Engine* CreateApplication();
}