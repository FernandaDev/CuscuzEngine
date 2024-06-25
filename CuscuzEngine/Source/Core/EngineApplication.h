#pragma once

#include "Window.h"
#include "RendererSystem.h"
#include "EventSystem.h"
#include "Events/CC_Event.h"
#include "Events/WindowEvents.h"
#include "CC_Game.h"
#include "GUI/ImGuiLayer.h"
#include "Layers/LayerStack.h"

constexpr Uint32 FramesPerSecond = 30;

class EngineApplication 
{
public:
	Window* CC_Window;
	RendererSystem* CC_RendererSystem;
	EventSystem* CC_EventSystem;

protected:
	CC_Game* m_Game;
	
private:
	static EngineApplication* s_Instance;
	//CC_ImGuiLayer m_ImGuiLayer;
	LayerStack m_LayerStack;
	
	bool m_IsRunning = true;

public:
	EngineApplication();
	EngineApplication(CC_Game* Game);
	virtual ~EngineApplication();

	static EngineApplication& Get() { return *s_Instance;}
	
	void Run();
	
	virtual void Start();

	//void OnEvent(Event event);
	
	void PushLayer(Layer* layer);
	void PushOverlay(Layer* layer);

protected:
	virtual void Render();
private:
	void Init();
	void Quit(const CC_Event<CC_WindowEventType>& Event);
	void ProcessInput() const;

	friend int ::main(int argc, char* argv[]);
	friend class ImGuiLayer;
};
