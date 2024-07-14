#pragma once

#include "Core/Window.h"
#include "RendererSystem.h"
#include "EventSystem.h"
#include "Events/CC_Event.h"
#include "Events/WindowEvents.h"
#include "Core/CC_Game.h"
#include "Layers/LayerStack.h"

class CC_AppLayer;

constexpr Uint32 FramesPerSecond = 30;

class CC_Engine 
{
public:
	std::unique_ptr<Window> CC_Window;
	std::unique_ptr<RendererSystem> CC_RendererSystem;
	std::unique_ptr<EventSystem> CC_EventSystem;

protected:
	std::shared_ptr<CC_Game> m_Game;
	
private:
	static CC_Engine* s_Instance;
	std::shared_ptr<ImGuiLayer> m_ImGuiLayer;
	LayerStack m_LayerStack;
	
	bool m_IsRunning = true;

public:
	CC_Engine();
	CC_Engine(CC_Game* game);
	virtual ~CC_Engine();

	static CC_Engine& Get() { return *s_Instance;}
	
	void Run();
	
	virtual void Start();

	void OnEvent(CC_Event& event);
	
	void PushLayer(std::shared_ptr<Layer> layer);
	void PushOverlay(std::shared_ptr<Layer> layer);

protected:
	void CreateGame(const std::shared_ptr<CC_Game>& game);
	virtual void Render();
private:
	void Init();
	bool Quit(CC_WindowCloseEvent& event);

	friend int ::main(int argc, char* argv[]);
};
