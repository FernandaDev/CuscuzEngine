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
	// float m_LastFrameTime = 0;

protected:
	Window* CC_Window;
	RendererSystem* CC_RendererSystem;
	EventSystem* CC_EventSystem;
	ImGuiLayer* CC_ImGuiLayer;

	// float m_DeltaTime = 0;
	
public:
	EngineApplication();
	virtual ~EngineApplication();
	
	void Run();
	
	virtual void Start();
	virtual void Update();
	
	void Quit(const CC_Event<CC_WindowEventType>& Event);

private:
	void ProcessInput() const;
	void Render() const;
};
