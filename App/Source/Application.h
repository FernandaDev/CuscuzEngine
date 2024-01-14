#pragma once

#include "Window.h"
#include "RendererSystem.h"
#include "EventSystem.h"
#include "Events/Event.h"
#include "Events/WindowEvents.h"

constexpr Uint32 FramesPerSecond = 30;

class Application 
{
	Window* m_Window;
	RendererSystem* m_RendererSystem;
	EventSystem* m_EventSystem;

	bool m_IsRunning = true;

	int m_frameCount = 0;

	Uint32 m_lastDeltaTime = 0;
	Uint32 m_frameStart = 0;
	Uint32 m_frameEnd = 0;
	Uint32 m_targetFrameDuration = 1000 / FramesPerSecond;

public:
	Application();
	~Application();
	
	void Run();
	void Start();

	void FrameStart();
	void FrameEnd();
	
	void Quit(const Event<WindowEventType>& Event);
};
