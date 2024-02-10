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

	//int m_frameCount = 0;

	Uint32 m_frameStart = 0;
	Uint32 m_frameEnd = 0;
	Uint32 m_targetFrameDuration = 1000 / FramesPerSecond;

protected:
	Window* CC_Window;
	RendererSystem* CC_RendererSystem;
	EventSystem* CC_EventSystem;
	ImGuiLayer* CC_ImGuiLayer;

	Uint32 m_lastDeltaTime = 0;
	
public:
	EngineApplication();
	virtual ~EngineApplication();
	
	void Run();
	
	virtual void Start();
	virtual void Update();

	void FrameStart();
	void FrameEnd();
	
	void Quit(const CC_Event<CC_WindowEventType>& Event);

private:
	void ProcessInput() const;
	void Render() const;
};
