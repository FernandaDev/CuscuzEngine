#pragma once

#include "Window.h"
#include "RendererSystem.h"
#include "EventSystem.h"
#include "Events/CC_Event.h"
#include "Events/WindowEvents.h"
#include "CC_Game.h"
#include "Layers/LayerStack.h"

class CC_AppLayer;

constexpr Uint32 FramesPerSecond = 30;

class CC_Application 
{
public:
	std::unique_ptr<Window> CC_Window;
	std::unique_ptr<RendererSystem> CC_RendererSystem;
	std::unique_ptr<EventSystem> CC_EventSystem;

protected:
	std::shared_ptr<CC_Game> m_Game;
	
private:
	static CC_Application* s_Instance;
	ImGuiLayer* m_ImGuiLayer;
	LayerStack m_LayerStack;
	
	bool m_IsRunning = true;

public:
	CC_Application();
	CC_Application(CC_Game* game);
	virtual ~CC_Application();

	static CC_Application& Get() { return *s_Instance;}
	
	void Run();
	
	virtual void Start();

	void OnEvent(CC_Event& event);
	
	void PushLayer(Layer* layer);
	void PushOverlay(Layer* layer);

protected:
	void CreateGame(const std::shared_ptr<CC_Game>& game);
	virtual void Render();
private:
	void Init();
	bool Quit(CC_WindowCloseEvent& event);

	friend int ::main(int argc, char* argv[]);
};
