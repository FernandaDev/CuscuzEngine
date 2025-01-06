#pragma once

#include "Core/EventSystem.h"
#include "Events/CC_Event.h"
#include "Events/WindowEvents.h"
#include "Layers/LayerStack.h"

class PhysicsSystem;
class ResourcesManager;
class ImGuiLayer;
class EngineLayer;
class Window;
class RendererSystem;
class EventSystem;
class World;

class CC_Engine 
{
public:
	std::unique_ptr<Window> CC_Window;
	std::unique_ptr<RendererSystem> CC_RendererSystem;
	std::unique_ptr<PhysicsSystem> CC_PhysicsSystem;
	std::unique_ptr<EventSystem> CC_EventSystem;
	std::unique_ptr<World> CC_World;
	
private:
	static CC_Engine* s_Instance;

	std::shared_ptr<ImGuiLayer> m_ImGuiLayer;
	LayerStack m_LayerStack;
	
	bool m_IsRunning = true;

public:
	CC_Engine();
	virtual ~CC_Engine();

	static CC_Engine& Get() { return *s_Instance;}
	
	void Run();
	
	virtual void Start();

	void OnEvent(CC_Event& event);
	
	void PushLayer(std::shared_ptr<Layer> layer);
	void PushOverlay(std::shared_ptr<Layer> layer);

private:
	void Init();
	bool Quit(CC_WindowCloseEvent& event);

	friend int ::main(int argc, char* argv[]);
};
