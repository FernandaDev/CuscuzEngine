#pragma once

#include "Window.h"
#include "RendererSystem.h"
#include "EventSystem.h"
#include "Events/CC_Event.h"
#include "Events/WindowEvents.h"
#include "GUI/ImGuiLayer.h"

constexpr Uint32 FramesPerSecond = 30;

class EngineApplication 
{
	bool m_IsRunning = true;

public:
	EngineApplication();
	virtual ~EngineApplication();
	
	void Run();
	
	virtual void Start();
	virtual void Update();
	
	void Quit(const CC_Event<CC_WindowEventType>& Event);

	Window* CC_Window;
	RendererSystem* CC_RendererSystem;
	EventSystem* CC_EventSystem;
	ImGuiLayer* CC_ImGuiLayer;

private:
	void ProcessInput() const;
	void Render() const;
};
